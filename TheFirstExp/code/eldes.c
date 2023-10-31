#include <stdio.h>
#include <string.h>
#include "baseFunc.h"
#include <stdlib.h>

//main函数
void main(int argc,char** argv)
{
    char m_buff[255];
    char k_buff[255];
    char c_buff[255];
    if(argc==11&&strcmp(argv[1],"-p")==0&&strcmp(argv[3],"-k")==0&&strcmp(argv[5],"-v")==0&&strcmp(argv[7],"-m")==0&&strcmp(argv[9],"-c")==0){
        load(m_buff,argv[2]);
        printf("m:%s\n",m_buff);
        load(k_buff,argv[4]);
        printf("k:%s\n",k_buff);
        char v_buff[255];
        load(v_buff,argv[6]);
        printf("v:%s\n",v_buff);
        if(strcmp(argv[8],"CBC")==0){
            char *c = CBC_en(m_buff,k_buff,v_buff);
            write(c,argv[10],0);
        } else if(strcmp(argv[8],"CFB")==0){
            char *c = CFB_en(m_buff,k_buff,v_buff);
            write(c,argv[10],0);
        } else if(strcmp(argv[8],"OFB")==0){
            char *c = OFB_en(m_buff,k_buff,v_buff);
            write(c,argv[10],0);
        }
    } else if(argc==9&&strcmp(argv[1],"-p")==0&&strcmp(argv[3],"-k")==0&&strcmp(argv[5],"-m")==0&&strcmp(argv[7],"-c")==0){
        load(m_buff,argv[2]);
        printf("m:%s\n",m_buff);
        load(k_buff,argv[4]);
        printf("k:%s\n",k_buff);
        if(strcmp(argv[6],"ECB")==0){
            char *c = ECB_en(m_buff,k_buff);
            write(c,argv[8],0);
        } else {
            printf("Invalid instruction!");
        }
    } else {
        printf("Invalid instruction!");
    }
}
