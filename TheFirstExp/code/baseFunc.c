#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "baseFunc.h"

//用于生成子密钥时保存左右两边的信息
struct node{
    int c[80];
    int d[80];
    int cd[80];
};
//用于加密时保存左右的字符串
struct node_1{
    int l[80];
    int r[80];
};

//初始置换IP
int pc_ip[80] = {0,
    58,50,42,34,26,18,10,2,
    60,52,44,36,28,20,12,4,
    62,54,46,38,30,22,14,6,
    64,56,48,40,32,24,16,8,
    57,49,41,33,25,17,9,1,
    59,51,43,35,27,19,11,3,
    61,53,45,37,29,21,13,5,
    63,55,47,39,31,23,15,7
};

//初始逆置换IP-1
int pc_ip_1[80] = {0,
    40,8,48,16,56,24,64,32,
    39,7,47,15,55,23,63,31,
    38,6,46,14,54,22,62,30,
    37,5,45,13,53,21,61,29,
    36,4,44,12,52,20,60,28,
    35,3,43,11,51,19,59,27,
    34,2,42,10,50,18,58,26,
    33,1,41,9,49,17,57,25
};

//E-扩展运算
int pc_e[80] = {0,
    32,1,2,3,4,5,
    4,5,6,7,8,9,
    8,9,10,11,12,13,
    12,13,14,15,16,17,
    16,17,18,19,20,21,
    20,21,22,23,24,25,
    24,25,26,27,28,29,
    28,29,30,31,32,1
};

//置换函数P
int pc_p[80] = {0,
    16,7,20,21,29,12,28,17,
    1,15,23,26,5,18,31,10,
    2,8,24,14,32,27,3,9,
    19,13,30,6,22,11,4,25
};

//置换选择PC-1
int pc_1[60] = {0,
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

//置换选择PC-2
int pc_2[60] = {0,
    14,17,11,24,1,5,3,28,
    15,6,21,10,23,19,12,4,
    26,8,16,7,27,20,13,2,
    41,52,31,37,47,55,30,40,
    51,45,33,48,44,49,39,56,
    34,53,46,42,50,36,29,32
};

//S盒
int s_box[8][4][16] = {
    14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
    0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
    4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
    15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,

    15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
    3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
    0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
    13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,

    10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
    13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
    13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
    1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,

    7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
    13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
    10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
    3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,

    2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
    14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
    4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
    11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,

    12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
    10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
    9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
    4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,

    4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
    13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
    1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
    6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,

    13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
    1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
    7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
    2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
};

/**
 * @brief 从指定文件中读信息
 * 
 * @param buff 取得信息暂存于这个缓冲器
 * @param name 文件名
 */
void load(char *buff,char *name){
    FILE *fp = fopen(name,"r");
    fscanf(fp,"%s",buff);
    fclose(fp);
}

/**
 * @brief 向指定文件中写信息
 * 
 * @param buff 要写入的内容
 * @param name 文件名
 */
void write(char *buff,char *name,int choice){
    FILE *fp = NULL;
    if(choice == 0) {
        fp = fopen(name,"w+");
        fprintf(fp,buff);
    } else {
        fp = fopen(name,"a+");
        char buff_1[20];
        memset(buff_1,'\0',20);
        for(int i=0; i<16; i++) buff_1[i] = buff[i];
        buff_1[16] = '\n';
        fprintf(fp,buff_1);
    }
    fclose(fp);
}

/**
 * @brief 将十六进制字符串转换为二进制数组
 * 
 * @param s 待转换的十六进制字符串
 * @return int* 返回的二进制数组首地址
 */
void Hex2Bin(int res[80],char *s){
    int num=0,count=0;
    for(int i=0; i<strlen(s); i++){
        if(s[i]<='9'&&s[i]>='0') num = s[i] - '0';
        else num = s[i] -'A' + 10;
        res[++count] = (num>>3)&1;
        res[++count] = (num>>2)&1;
        res[++count] = (num>>1)&1;
        res[++count] = num&1;
    }
}

/**
 * @brief 将二进制密文字符串转换为十六进制
 * 
 * @param c_16 用来保存十六进制的密文
 * @param c_2 待转换的二进制密文字符串
 * @param len 二进制字符串的长度
 */
void Bin2Hex(char *c_16,int *c_2,int len){
    int tem_num;
    for(int i=1; i<=len; i+=4){
        tem_num = c_2[i]*8 + c_2[i+1]*4 + c_2[i+2]*2 + c_2[i+3]*1;
        if(tem_num>=10){
            c_16[i/4] = tem_num - 10 + 'A';
        } else {
            c_16[i/4] = tem_num + '0';
        }
    }
}

/**
 * @brief f函数
 * 
 * @param r 明文块，执行函数后被加密为密文
 * @param kn 密钥
 */
void f(int r[80],int kn[80]){
    int x = 0;
    int e[80] = {0};
    int h=0,l=0,idx=0;
    //E盒拓展得到E(Ri)
    for(int i=1; i<=48; i++){
        e[i] = r[pc_e[i]];
    }
    //异或运算得到k^(E(Ri))
    for(int i=1; i<=48; i++){
        r[i] = e[i]^kn[i];
    }
    //S盒压缩将48位分为8组，每组6位，得到S(k^E(Ri))
    for(int i=1; i<=48; i+=6){
        h = r[i]*2 + r[i+5]*1;
        l = r[i+1]*8 + r[i+2]*4 + r[i+3]*2 + r[i+4]*1;
        e[++idx] = (s_box[x][h][l]>>3)&1;
        e[++idx] = (s_box[x][h][l]>>2)&1;
        e[++idx] = (s_box[x][h][l]>>1)&1;
        e[++idx] = (s_box[x][h][l])&1;
        x++;
    }
    //P盒置换
    for(int i = 1; i<=32; i++){
        r[i] = e[pc_p[i]];
    }
}

/**
 * @brief 生成十六轮子密钥
 * 
 * @param k_16 生成的密钥保存在该二维数组中
 * @param k 初始密钥
 */
void key_generate(int (*k_16)[80],char *k){
    int bin_k[80] = {0};
    int bin_kup[80] = {0};
    struct node c_and_d[20];
    for(int i=0;i<20;i++){
        memset(c_and_d[i].c,0,80);
        memset(c_and_d[i].d,0,80);
        memset(c_and_d[i].cd,0,80);
    }
    Hex2Bin(bin_k,k);
    //将密钥用pc_1置换
    for(int i=1; i<=56; i++){
        bin_kup[i] = bin_k[pc_1[i]];
    }
    //左右分组得到C0，D0
    for(int i=1; i<=28; i++){
        c_and_d[0].c[i]=bin_kup[i];
        c_and_d[0].d[i]=bin_kup[i+28];
    }
    //16轮生成每轮子密钥
    for(int i=1; i<=16; i++){
        //如果为第1、2、9、16轮，Ci、Di循环左移1位
        if(i==1||i==2||i==9||i==16){
            for(int j=1;j<=27;j++){
                c_and_d[i].c[j] = c_and_d[i-1].c[j+1];
                c_and_d[i].d[j] = c_and_d[i-1].d[j+1];
            }
            c_and_d[i].c[28] = c_and_d[i-1].c[1];
            c_and_d[i].d[28] = c_and_d[i-1].d[1];
        } else {
            //如果为其他轮次，Ci、Di循环左移2位
            for(int j=1;j<=26;j++){
                c_and_d[i].c[j] = c_and_d[i-1].c[j+2];
                c_and_d[i].d[j] = c_and_d[i-1].d[j+2];
            }
            c_and_d[i].c[27] = c_and_d[i-1].c[1];
            c_and_d[i].c[28] = c_and_d[i-1].c[2];
            c_and_d[i].d[27] = c_and_d[i-1].d[1];
            c_and_d[i].d[28] = c_and_d[i-1].d[2];
        }
        //合并每一轮的C、D
        for(int j=1;j<=28;j++){
            c_and_d[i].cd[j] = c_and_d[i].c[j];
            c_and_d[i].cd[j+28] = c_and_d[i].d[j];
        }
    }
    //PC_2置换后获得16轮子密钥
    for(int i=1;i<=16;i++)
        for(int j=1;j<=48;j++)
            k_16[i][j] = c_and_d[i].cd[pc_2[j]];
}

/**
 * @brief 对明文块进行加密，加密64bit
 * 
 * @param m     要加密的明文块
 * @param kn    密钥
 * @param c     所得的密文块
 */
void encrypt(char *m,int (*kn)[80],char *c){
    int ip[80] = {0};
    int res[80] = {0};
    //将明文转化为二进制
    Hex2Bin(res,m);
    //进行初始变换ip,对于
    for(int i=1; i<=64; i++){
        ip[i] = res[pc_ip[i]];
    }
    //初始化得到 l[0]  r[0]
    struct node_1 l_r[20];
    for(int i=0; i<20; i++) 
        for(int j=0; j<80; j++) {
            l_r[i].l[j] = 0;
            l_r[i].r[j] = 0;
        }
    for(int i=1; i<=32; i++){
        l_r[0].l[i] = ip[i];
        l_r[0].r[i] = ip[i+32];
    }
    //进行十六轮运算
    for(int i=1; i<=16; i++){
        for(int j=1; j<=32; j++){
            //Li = Ri-1得到Li
            l_r[i].l[j]=l_r[i-1].r[j];
        }
        //f函数包含E盒扩展、异或、S盒压缩、P盒置换
        f(l_r[i-1].r,kn[i]);
        //左右合在一起，两者进行最终按位异或得到Ri
        for(int j=1; j<=32; j++){
            l_r[i].r[j]=l_r[i-1].l[j]^l_r[i-1].r[j];
        }
    }
    //将最后得到的L,R合并在一起并交换位置
    int LR[80] = {0};
    for(int i=1; i<=32; i++){
        LR[i] = l_r[16].r[i];
        LR[i+32] = l_r[16].l[i];
    }
    //得到最终变换
    int ans[80] = {0};
    //进行ip逆置换
    for(int i=1; i<=64; i++)
        ans[i] = LR[pc_ip_1[i]];

    //将二进制密文转换为十六进制
    Bin2Hex(c,ans,64);
}

/**
 * @brief 对密文块进行解密，解密64bit
 * 
 * @param c 待解密的密文块
 * @param k 密钥
 * @param m 所得的明文块
 */
void decrypt(char *c,int (*kn)[80],char *m){
    int ip[80] = {0};
    int res[80] = {0};
    //将密文转化为二进制
    Hex2Bin(res,c);
    //初始变换ip
    for(int i=1; i<=64; i++){
        ip[i] = res[pc_ip[i]];
    }
    //初始化得到l[0],r[0]
    struct node_1 l_r[20];
    for(int i=0; i<20; i++) 
        for(int j=0; j<80; j++) {
            l_r[i].l[j] = 0;
            l_r[i].r[j] = 0;
        }
    for(int i=1; i<=32; i++){
        l_r[0].l[i] = ip[i];
        l_r[0].r[i] = ip[i+32];
    }
    //计算L1->l16,R1->R16
    for(int i=1; i<=16; i++){
        for(int j=1; j<=32; j++)
            l_r[i].l[j]=l_r[i-1].r[j];
        f(l_r[i-1].r,kn[16-i+1]);
        for(int j=1; j<=32; j++)
            l_r[i].r[j]=l_r[i-1].l[j]^l_r[i-1].r[j];
    }
    //将最后得到的L,R合并在一起并交换位置
    int LR[80] = {0};
    for(int i=1; i<=32; i++){
        LR[i] = l_r[16].r[i];
        LR[i+32] = l_r[16].l[i];
    }
    //得到最终变换
    int ans[80] = {0};
    //进行ip逆置换
    for(int i=1; i<=64; i++)
        ans[i] = LR[pc_ip_1[i]];
    //将二进制密文转换为十六进制
    Bin2Hex(m,ans,64);
}


char *zeroPadding(char *m,int *len_m){
    char *m_std;
    int len = strlen(m);
    if(len%16==0) {
        *len_m = strlen(m);
        m_std = m;
    } else {
        int toAdd = 16-len%16;
        *len_m = len+toAdd;
        int len_m_std = sizeof(char)*(*len_m+1);
        m_std = (char*)malloc(len_m_std);
        memset(m_std,'\0',len_m_std);
        memset(m_std,'0',len_m_std-1);    
        for(int i=0; i<len; i++) {
            m_std[i] = m[i];
        }
    }
    return m_std;
}

/**
 * @brief 两字符串进行异或运算，结果保存进第一个字符串中
 * 
 * @param m1 字符串1
 * @param m2 字符串2
 * @param len 二进制长度
 */
void XOR(char *m1,char *m2,int len){
    int m1_2[80]={0};
    int m2_2[80]={0};
    int tmp[80]={0};
    Hex2Bin(m1_2,m1);
    Hex2Bin(m2_2,m2);
    for(int i=1; i<=len; i++){
        tmp[i] = m1_2[i]^m2_2[i];
    }
    Bin2Hex(m1,tmp,len);
};

/**
 * @brief ECB模式加密
 * 
 * @param m 明文
 * @param k 密钥
 * @return char* 返回密文字符串的首地址 
 */
char *ECB_en(char *m,char *k){
    char tmp[16];      //用于暂存明文分组
    int count = 0;
    int len = 0;
    int k_2[20][80] = {0};
    key_generate(k_2,k);
    char *m_std = zeroPadding(m,&len);   //检查待加密字符串大小是否是16的倍数，检查结果为m_std
    char *c = (char*)malloc(sizeof(char)*(len+1)); //用于暂存密文
    memset(c,'\0',len+1);
    //len是待加密的明文的长度
    for(int i = 0; i<len; i++){
        tmp[i%16] = m_std[i];
        //每16个十六进制字符为一组
        if(i%16==15) {
            char c_b[20];
            memset(c_b,'0',20);
            encrypt(tmp,k_2,c_b);       //对该明文分组加密
            for(int j=0; j<16; j++){    
                c[count++] = c_b[j];    //保存密文
            }       
        }
    }
    printf("c:%s\n",c);
    return c;
}

char *CBC_en(char *m,char *k,char *v){
    int len = 0,count=0;            
    char *m_std = zeroPadding(m,&len);
    //生成子密钥
    int k_2[20][80] = {0};
    key_generate(k_2,k);
    //定义一个存储器来储存密文
    char *c = (char*)malloc(sizeof(char)*(len+1));
    memset(c,'\0',len+1);
    //加密
    char tmp1[17];
    char tmp2[17];
    memset(tmp1,'\0',17);
    memset(tmp2,'\0',17);
    for(int i=0; i<16; i++) tmp2[i] = v[i];
    for(int i=0; i<len; i++){
        //存储明文，16个为一组
        tmp1[i%16] = m_std[i];
        if(i%16==15) {
            //tmp2为上一个密文块,第一次执行时，tmp2是v向量
            //明文块与上一个密文块进行异或
            XOR(tmp1,tmp2,64);
            //加密，tmp2被覆盖为加密后的密文
            encrypt(tmp1,k_2,tmp2);
            for(int j=0; j<16; j++){
                c[count++] = tmp2[j];
            }
        }
    }
    printf("c:%s\n",c);
    return c;
}

char *CFB_en(char *m,char *k,char *v){
    int len = 0,count=0;            
    char *m_std = zeroPadding(m,&len);
    //生成子密钥
    int k_2[20][80] = {0};
    key_generate(k_2,k);
    //定义一个存储器来储存密文
    char *c = (char*)malloc(sizeof(char)*(len+1));
    memset(c,'\0',len+1);
    //加密
    char tmp1[2];
    char tmp2[17];
    char tmp2_c[17];
    memset(tmp1,'\0',2);
    memset(tmp2,'\0',17);
    memset(tmp2_c,'\0',17);
    
    for(int i=0; i<16; i++) tmp2[i] = v[i];
    
    for(int i=0; i<len; i++){
        //存储明文，2个为一组,即8个bit
        tmp1[i%2] = m_std[i];
        if(i%2==1) {
            //tmp2为上一个密文块,第一次执行时，tmp2是v向量
            //对上一个密文块进行加密，第一次执行时，即加密v向量
            encrypt(tmp2,k_2,tmp2_c);
            char tmp2_c_8[2];
            //取分组加密后的前两个十六进制字符，即最左边的8个bit
            for(int j=0;j<2;j++) tmp2_c_8[j] = tmp2_c[j];
            //异或运算
            XOR(tmp1,tmp2_c_8,8);
            for(int j=0; j<2; j++){
                c[count++] = tmp1[j];
            }
            //寄存器向左移位，移动两个十六进制字符，即8bit
            for(int j=0; j<14;j++){
                tmp2[j] = tmp2[j+2];
            }
            tmp2[14] = tmp1[0];
            tmp2[15] = tmp1[1];
        }
    }
    printf("c:%s\n",c);
    return c;
}

char *OFB_en(char *m,char *k,char *v){
    int len = 0,count=0;            
    char *m_std = zeroPadding(m,&len);
    //生成子密钥
    int k_2[20][80] = {0};
    key_generate(k_2,k);
    //定义一个存储器来储存密文
    char *c = (char*)malloc(sizeof(char)*(len+1));
    memset(c,'\0',len+1);
    //加密
    char tmp1[2];
    char tmp2[17];
    char tmp2_c[17];
    memset(tmp1,'\0',2);
    memset(tmp2,'\0',17);
    memset(tmp2_c,'\0',17);
    
    for(int i=0; i<16; i++) tmp2[i] = v[i];
    
    for(int i=0; i<len; i++){
        //存储明文，2个为一组,即8个bit
        tmp1[i%2] = m_std[i];
        if(i%2==1) {
            //tmp2为上一个密文块,第一次执行时，tmp2是v向量
            //对上一个密文块进行加密，第一次执行时，即加密v向量
            encrypt(tmp2,k_2,tmp2_c);
            char tmp2_c_8[2];
            //取分组加密后的前两个十六进制字符，即最左边的8个bit
            for(int j=0;j<2;j++) tmp2_c_8[j] = tmp2_c[j];
            //异或运算
            XOR(tmp1,tmp2_c_8,8);
            for(int j=0; j<2; j++){
                c[count++] = tmp1[j];
            }
            //寄存器向左移位，移动两个十六进制字符，即8bit
            for(int j=0; j<14;j++){
                tmp2[j] = tmp2[j+2];
            }
            tmp2[14] = tmp2_c[0];
            tmp2[15] = tmp2_c[1];
        }
    }
    printf("c:%s\n",c);
    return c;
}

char *ECB_de(char *c,char *k){
    int count = 0;
    //生成子密钥
    int k_2[20][80] = {0};
    key_generate(k_2,k);
    char tmp[17];
    memset(tmp,'\0',17);
    char *m = (char*)malloc(sizeof(char)*(strlen(c)+1));
    memset(m,'\0',strlen(c)+1);
    for(int i=0; i<strlen(c); i++) {
        tmp[i%16] = c[i];
        if(i%16==15) {
            char m_block[17];
            memset(m_block,'\0',17);
            decrypt(tmp,k_2,m_block);
            for(int j=0; j<16; j++) m[count++] = m_block[j];
        }
    }
    return m;
}

char *CBC_de(char *c,char *k,char *v){
    int count = 0;
    //生成子密钥
    int k_2[20][80] = {0};
    key_generate(k_2,k);
    char tmp1[17];
    char tmp2[17];
    char tmp3[17];
    char m_block[17];//暂存异或明文块
    memset(tmp1,'\0',17);
    memset(tmp2,'\0',17);
    memset(tmp3,'\0',17);
    memset(m_block,'\0',17);
    char *m = (char*)malloc(sizeof(char)*(strlen(c)+1)); //存储明文
    memset(m,'\0',strlen(c)+1);

    for(int i=0; i<16; i++) tmp3[i] = v[i];

    for(int i=0; i<strlen(c); i++) {
        tmp1[i%16] = c[i];
        if(i%16 == 15) {
            decrypt(tmp1,k_2,tmp2);
            XOR(tmp2,tmp3,64);
            for(int j=0; j<16; j++) {
                m[count++] = tmp2[j];  
                tmp3[j] = tmp1[j];
            }
        }
    }
    return m;
}

char *CFB_de(char *c,char *k,char *v){
    int count=0;            
    //生成子密钥
    int k_2[20][80] = {0};
    key_generate(k_2,k);
    //定义一个存储器来储存明文
    char *m = (char*)malloc(sizeof(char)*(strlen(c)+1));
    memset(m,'\0',strlen(c)+1);

    char tmp1[2];
    char tmp2[17];
    char tmp3[17];
    memset(tmp1,'\0',2);
    memset(tmp2,'\0',17);
    memset(tmp3,'\0',17);
    
    for(int i=0; i<16; i++) tmp3[i] = v[i];
    
    for(int i=0; i<strlen(c); i++){
        //存储密文，2个为一组,即8个bit
        tmp1[i%2] = c[i];
        if(i%2==1) {
            encrypt(tmp3,k_2,tmp2);
            char t_8[2];
            t_8[0] = tmp2[0];
            t_8[1] = tmp2[1];
            XOR(t_8,tmp1,8);
            for(int j=0; j<2; j++) m[count++] = t_8[j];
            //移位
            for(int j=0; j<14; j++){
                tmp3[j] = tmp3[j+2];
            }
            tmp3[14] = tmp1[0];
            tmp3[15] = tmp1[1];
        }
    }
    return m;
}

char *OFB_de(char *c,char *k,char *v){
    int count=0;
    //生成子密钥
    int k_2[20][80] = {0};
    key_generate(k_2,k);
    //定义一个存储器来储存明文
    char *m = (char*)malloc(sizeof(char)*(strlen(c)+1));
    memset(m,'\0',strlen(c)+1);
    
    char tmp1[2];
    char tmp2[17];
    char tmp3[17];
    memset(tmp1,'\0',2);
    memset(tmp2,'\0',17);
    memset(tmp3,'\0',17);

    for(int i=0; i<16; i++) tmp3[i] = v[i];

    for(int i=0; i<strlen(c); i++){
        //存储密文，2个为一组,即8个bit
        tmp1[i%2] = c[i];
        if(i%2==1) {
            encrypt(tmp3,k_2,tmp2);
            char t_8[2];
            t_8[0] = tmp2[0];
            t_8[1] = tmp2[1];
            XOR(t_8,tmp1,8);
            for(int j=0; j<2; j++) m[count++] = t_8[j];
            //移位
            for(int j=0; j<14; j++){
                tmp3[j] = tmp3[j+2];
            }
            tmp3[14] = tmp2[0];
            tmp3[15] = tmp2[1];
        }
    }
    return m;
}
