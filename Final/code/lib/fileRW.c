#include "fileRW.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * @brief 从文件中读取
 * 
 * @param filename 文件名
 * @return char* 缓存块
 */
char *fileLoad(char *filename){
    FILE *fp = fopen(filename,"rb");
    fseek(fp,0,SEEK_END);
    long length = ftell(fp); //获得文件字节数
    fp = fopen(filename,"rb");
    
    char *buff = (char *)malloc(length+1);
    memset(buff,'\0',length+1);
    
    int count = 0;
    char ch;
    while( (ch=fgetc(fp)) != EOF ) {
        buff[count++] = ch;
    }

    fclose(fp);
    return buff;
}

/**
 * @brief 将缓存区的数据写入指定文件
 * 
 * @param buff 缓冲区
 * @param filename 指定文件名
 */
void fileWrite(char *buff,char *filename){
    FILE *fp = fopen(filename,"wb");
    for(int i=0; i<strlen(buff); i++){
        fputc(buff[i],fp);
    }
    fclose(fp);
}