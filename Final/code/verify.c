#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lib/fileRW.h"
#include "lib/encrypt.h"


int main(int argc, char** argv) {
    if(argc>6) {
        printf("Invalid input!");
        return 0;
    }
    for(int i=1; i<argc; i++){
        if(!strcmp(argv[i],"-ver")){
            if( argv[i+1] == NULL || argv[i+2] == NULL || argv[i+3] == NULL || argv[i+4] == NULL) {
                printf("Invalid input!");
                return 0;
            }
            // char *sig = fileLoad(argv[i+1]);    //获取签名
            char *hM = sha256_hash(argv[i+2]);      //获取明文 -sha256的散列值
            char *hm = RSA_de(argv[i+1],argv[i+3],argv[i+4]); //签名解密得到散列值
            printf("HM_B:%s\nHM_A:%s\n",hM,hm);
            if(strcmp(hM,hm) == 0) {
                printf("Validation successful!\n");
                return 0;
            } else {
                printf("Validation failed!\n");
            }
            i+=4;
        }
    }
}