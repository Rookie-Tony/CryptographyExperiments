#ifndef __ENCRYPT__H__
#define __ENCRYPT__H__

char *str_2Hex(char *str);
char *hex_2Str(char *hex);
void DES_en(char *m,char *key,char *c);
void DES_de(char *c,char* key,char *m);
char *RSA_en(char *m,char *n,char *e);
char *RSA_de(char *c,char *n,char *d);
char *sha256_hash(char *m);
char *my_strcat(char *str1, char *str2);


#endif