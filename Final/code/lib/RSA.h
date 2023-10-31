#ifndef __RSA__H__
#define __RSA__H__

#define least 1000000001    //生成大素数至少大于该值
#define n_1w 10000          //数字1w，定义为宏
#define MAX_SIZE 1024       //数组最大为1024位


char* Hex2Dec(char *str);
char* Dec2Hex(char *str);
char* Dec2Str(long long x);
int RSA_Hex2Bin(int bin[MAX_SIZE],char *s);
int maxer(char *str1, char *str2);
char *add(char *str1, char *str2);
char *sub(char *str1,char *str2);
char *mul(char *str1, char *str2);
char *divi(char *str1,char *str2);
char *myPow(char *str,int index);
char *mol(char *str1, char *str2);
char *EncryptOrDecrypt(char *n,char *mOrc,char *eOrd);
long long *bigPrime();
void RSA_key_generate(char *n__,char *pub,char *pri);
void RSA_write(char *buff,char *filename);

#endif