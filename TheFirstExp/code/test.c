#include <stdio.h>
#include "baseFunc.h"
#include <stdlib.h>
#include <string.h>

char mikey[18] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
char *k = "57696C6C69616D53";//密钥
char *v = "5072656E74696365";//初始向量
void main(){    
    //生成随机数据
    int size = 100*1024;
    char *m = (char*)malloc(size+1);
    memset(m,'\0',size+1);
    int num = 0;
    for (int i=0; i<size; i++) {
        num = rand()%16;
        m[i] = mikey[num];
    }
    //加解密20次
    for(int i=0; i<20; i++){

        char *c1 = ECB_en(m,k);
        char *m1 = ECB_de(c1,k);

        // char *c2 = CBC_en(m,k,v);
        // char *m2 = CBC_de(c2,k,v);
        
        // char *c3 = CFB_en(m,k,v);
        // char *m3 = CFB_de(c3,k,v);

        // char *c4 = OFB_en(m,k,v);
        // char *m4 = OFB_de(c4,k,v);
    }
}