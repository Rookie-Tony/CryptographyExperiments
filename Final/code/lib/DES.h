#ifndef _DES_H_
#define _DES_H_

void load(char *buff,char *name);   //读取文件中的内容    
void write(char *buff,char *name,int choice);  //往文件中写入内容
void Hex2Bin(int *res,char *s);     //将十六进制字符串转化为二进制整形数组
void Bin2Hex(char *c_16,int *c_2,int len); //将二进制整形数组转化为十六进制字符串
void f(int *r,int *kn);             //f函数
void key_generate(int (*k_16)[80],char *k); //生成子密钥
void encrypt(char *m,int (*kn)[80],char *c);  //基础des加密
void decrypt(char *c,int (*kn)[80],char *m);  //基础des解密
char *zeroPadding(char *m,int *len_m);  //给长度不够的字符串填充零
void XOR(char *m1,char *m2,int len); //两个字符串进行异或
char *ECB_en(char *m,char *k);   //ECB模式加密
char *CBC_en(char *m,char *k,char *v);   //ECB模式加密
char *CFB_en(char *m,char *k,char *v);   //CFB模式加密
char *OFB_en(char *m,char *k,char *v);   //OFB模式加密
char *ECB_de(char *c,char *k);    //ECB模式解密
char *CBC_de(char *c,char *k,char *v); //CBC模式解密
char *CFB_de(char *c,char *k,char *v);  //CFB模式解密
char *OFB_de(char *c,char *k,char *v);  //OFB模式解密

#endif
