#include <stdlib.h>
#include <string.h>
#include "encrypt.h"
#include "fileRW.h"
#include "DES.h"
#include "RSA.h"
#include "sha256.h"

/**
 * @brief 将字符串转换为16进制序列
 * 
 * @param str 字符串
 * @return char* 十六进制序列
 */
char *str_2Hex(char *str){
    int strLen = strlen(str); //获取字符串长度
    char *ret = malloc(strLen*2+1);
    memset(ret,0,strLen*2+1);
    int count = 0;
    for(int i=0; i<strlen(str); i++){
        char ch = str[i];
        char temp[3];
        memset(temp,'\0',3);
        itoa(ch,temp,16);
        for(int j=0; j<strlen(temp); j++){
            if(temp[j]>='a'&&temp[j]<='f') {
                ret[count++] = temp[j] - 32;
            } else {
                ret[count++] = temp[j];
            } 
        }
    }
    return ret;
}

/**
 * @brief 将十六进制序列转换为字符串
 * 
 * @param hex 
 * @return char* 
 */
char *hex_2Str(char *hex) {
    char *ret = malloc(strlen(hex)/2+1);
    memset(ret,'\0',strlen(hex)/2+1);
    int count = 0;
    for(int i=0; i<strlen(hex); ){
        char temp[3];
        temp[2] = '\0';
        temp[0] = hex[i++];
        temp[1] = hex[i++];
        long num = strtol(temp,NULL,16);
        ret[count++] = (char)num;
    }
    return ret;
}

/**
 * @brief DES加密，ECB模式
 * 
 * @param m 明文文件名
 * @param key 密钥文件名
 * @param c 密文文件名
 */
void DES_en(char *m,char *key,char *c){
    char *m_buff = fileLoad(m);
    char *hex_m_buff = str_2Hex(m_buff); //将明文字符串转换为十六进制序列
    char *key_buff = fileLoad(key);
    char *res = ECB_en(hex_m_buff,key_buff);
    fileWrite(res,c);
    free(m_buff);
    free(key_buff);
}

/**
 * @brief DES解密，ECB模式
 * 
 * @param c 密文文件名
 * @param key 密钥文件名
 * @param m 明文文件名
 */
void DES_de(char *c,char* key,char *m){
    char *c_buff = fileLoad(c);
    char *key_buff = fileLoad(key);
    char *res = ECB_de(c_buff,key_buff);
    char *str_res = hex_2Str(res);
    printf("%s",str_res);
    fileWrite(str_res,m);
    free(c_buff);
    free(key_buff);
    free(res);
    free(str_res);
}

/**
 * @brief rsa加密，对明文十进制序列每16位为一块进行加密，若位数不够则以小于八位的十六进制段加密。
 * 
 * @param m 明文文件名
 * @param n 公钥n
 * @param e 公钥e
 * @param c 密文文件名
 */
char *RSA_en(char *m,char *n,char *e) {
    char *m_buff = fileLoad(m);
    char *hex_m = str_2Hex(m_buff);
    char *hex_n = fileLoad(n);
    char *hex_e = fileLoad(e);
    char *dec_n = Hex2Dec(hex_n);

    char *res = "";
    char *temp = malloc(9);
    memset(temp,'\0',9);
    int count = 0;
    for(int i=0; i<strlen(hex_m); i++) {
        temp[count++] = hex_m[i];    
        if(count==8||i==(strlen(hex_m)-1)) {
            char *dec_temp = Hex2Dec(temp);
            char *c_block = EncryptOrDecrypt(dec_n,dec_temp,hex_e);
            char *hex_c_block = Dec2Hex(c_block);
            res = my_strcat(res,hex_c_block);
            res = my_strcat(res,"#");
            count = 0;
            memset(temp,'\0',9);
        }
    }
    return res;
}

/**
 * @brief RSA解密
 * 
 * @param c 密文
 * @param n 公钥n
 * @param d 私钥d
 * @return char* 明文
 */
char* RSA_de(char *c,char *n,char *d){
    char *hex_c = fileLoad(c);
    char *hex_n = fileLoad(n);
    char *hex_d = fileLoad(d);
    char *dec_n = Hex2Dec(hex_n);

    char *res = "";
    char *temp = malloc(20);
    memset(temp,'\0',20);
    int count = 0;
    for(int i=0; i<strlen(hex_c); i++) {
        temp[count++] = hex_c[i];
        if(hex_c[i+1]=='#'){
            i++;
            char *dec_c = Hex2Dec(temp);
            char *m_block = EncryptOrDecrypt(dec_n,dec_c,hex_d);
            char *hex_m_block = Dec2Hex(m_block);
            res = my_strcat(res,hex_m_block);
            count = 0;
            memset(temp,'\0',20);
        }
    }
    char *str_res = hex_2Str(res);
    return str_res;
}

/**
 * @brief sha256哈希
 * 
 * @param m 明文
 * @param h 散列值
 */
char *sha256_hash(char *m){
    unsigned char *m_buff = fileLoad(m);
    // printf("%s\n",m_buff);
    unsigned char buff[32];
    char *hash = malloc(65);
    memset(hash,'\0',65);
    memset(buff,0,32);
    sha256(m_buff,strlen(m_buff),buff);
    int count = 0;
    for(int i=0; i<32; i++){
        char *temp = malloc(3);
        memset(temp,'\0',3);
        itoa(buff[i],temp,16);
        if(strlen(temp)==1){
            hash[count++] = '0';
            hash[count++] = temp[0];
        } else {
            hash[count++] = temp[0];
            hash[count++] = temp[1];
        }
    }
    return hash;
}

/**
 * @brief 拼接两个字符串
 * 
 * @param str1 字符串1
 * @param str2 字符串2
 * @return char* 拼接后的字符串
 */
char *my_strcat(char *str1, char *str2) {
    if(strlen(str1)==0) return str2;
    if(strlen(str2)==0) return str1;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char *res = malloc(len1+len2+1);
    int i;
    for( i=0; i<len1; i++) res[i] = str1[i];
    for( ; i<(len1+len2); i++) res[i] = str2[i-len1];
    res[i] = '\0';
    return res;
}