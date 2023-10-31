#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib/RSA.h"

char lower2upper(char low);

int main(int argc, char **argv){
    if(argc<=2||argc>5) {
        printf("Invalid input!\n");
        return 0;
    }
    for(int i=1; i<argc; i++){
        if(!strcmp(argv[i],"-des")) {       //生成DES加解密密钥
            if(argv[++i] == NULL) {
                printf("Invalid input!\n");
                return 0;
            }
            char *hex = malloc(17);         //用于存储16个16进制数，即64bit密钥
            memset(hex,'\0',17);
            srand((unsigned)time(NULL));
            for(int j=0; j<16; j++){
                int dec = rand()%16;                //生成一个0~15的随机十进制数
                char temp[2]; temp[2] = '\0';   
                itoa(dec,temp,16);                  //将随机数转换成十六进制
                temp[0] = lower2upper(temp[0]);     //转换大小写
                hex[j] = temp[0];                   //存入缓存中
            }
            FILE *fp = fopen(argv[i],"w+");
            fprintf(fp,hex);
            free(hex);
            fclose(fp);
            return 0;
        } else if(!strcmp(argv[i],"-rsa")) { //生成RSA密钥,分为公钥和私钥
            // printf("%s,%s,%s",argv[i+1],argv[i+2],argv[i+3]);
            if( argv[i+1] == NULL || argv[i+2] == NULL || argv[i+3] == NULL) {
                printf("Invalid input!\n"); 
                return 0;
            }
            RSA_key_generate(argv[i+1],argv[i+2],argv[i+3]);
            i+=3;
            return 0;
        }
    }
}

char lower2upper(char low){
    if(low>='a'&&low<='f') return low-32;
    else return low;
}