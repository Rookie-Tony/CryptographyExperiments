#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/encrypt.h"
#include "lib/fileRW.h"

int main(int argc, char **argv){
    for(int i=1; i<argc; i++){
        if(!strcmp(argv[i],"-des")) {
            i++;
            if(!strcmp(argv[i],"-en")) { //加密
                //加密，后面的三个参数分别为1.明文文件，2.密钥文件，3.密文文件
                if( argv[i+1] == NULL || argv[i+2] == NULL || argv[i+3] == NULL ) { //判断后面的三个文件是否为空
                    printf("Invalid input!");
                    return 0;
                }
                DES_en(argv[i+1],argv[i+2],argv[i+3]);
                i+=3;
                return 0;
            } else if(!strcmp(argv[i],"-de")){
                //解密，后面的三个参数分别为1.密文文件，2.密钥文件，3.明文文件
                if( argv[i+1] == NULL || argv[i+2] == NULL || argv[i+3] == NULL ){
                    printf("Invalid input!");
                    return 0;
                }
                DES_de(argv[i+1],argv[i+2],argv[i+3]);
                i+=3;
                return 0;
            } else {
                printf("Invalid input!");
                return 0;
            }
        } else if(!strcmp(argv[i],"-rsa")) {
            i++;
            if(!strcmp(argv[i],"-en")) { //加密
                //加密，后面的三个参数分别为1.明文文件，2.密钥文件，3.密文文件
                if( argv[i+1] == NULL || argv[i+2] == NULL || argv[i+3] == NULL || argv[i+4] == NULL) { //判断后面的三个文件是否为空
                    printf("Invalid input!");
                    return 0;
                }
                // printf("%s,%s,%s,%s",argv[i+1],argv[i+2],argv[i+3],argv[i+4]);
                char *c = RSA_en(argv[i+1],argv[i+2],argv[i+3]);
                fileWrite(c,argv[i+4]);
                i+=4;
                return 0;
            } else if(!strcmp(argv[i],"-de")) {
                //解密
                if( argv[i+1] == NULL || argv[i+2] == NULL || argv[i+3] == NULL || argv[i+4] == NULL) { //判断后面的三个文件是否为空
                    printf("Invalid input!");
                    return 0;
                }
                char *m = RSA_de(argv[i+1],argv[i+2],argv[i+3]);
                // printf("%s",m);
                fileWrite(m,argv[i+4]);
                i+=4;
                return 0;
            } else {
                printf("Invalid input!");
                return 0;
            }
        } else if(!strcmp(argv[i],"-sha256")) {
            if(argv[i+1]==NULL || argv[i+2] == NULL) {
                printf("Invailid input!");
                return 0;
            }
            char *h = sha256_hash(argv[i+1]);
            fileWrite(h,argv[i+2]);
            i+=2;
            return 0;
        }
    }
}