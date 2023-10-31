#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define least 1000000001    //生成大素数至少大于该值
#define n_1w 10000          //数字1w，定义为宏
#define MAX_SIZE 1024       //数组最大为1024位


char* Hex2Dec(char *str);
char* Dec2Hex(char *str);
char* Dec2Str(long long x);
int Hex2Bin(int bin[MAX_SIZE],char *s);
int maxer(char *str1, char *str2);
char *add(char *str1, char *str2);
char *sub(char *str1,char *str2);
char *mul(char *str1, char *str2);
char *divi(char *str1,char *str2);
char *myPow(char *str,int index);
char *mol(char *str1, char *str2);
char *EncryptOrDecrypt(char *n,char *mOrc,char *eOrd);
long long *bigPrime();
void key_generate();
void write(char *buff,char *filename);


int main(int argc, char **argv){
    if(argc==1) {
        key_generate();
        return 0;
    } else if(argc<7){
        printf("Invalid Instruction!\n");
        return 1;
    } else if(argc>9) {
        printf("Too many arguments!");
    }
    char buff[256];
    char n[256];
    char e[256];
    char d[256];
    char *c;
    for(int i=1; i<argc; i++) {
        if(!strcmp(argv[i],"-p")){
            FILE *fp;
            fp = fopen(argv[++i],"r");
            fscanf(fp,"%s",buff);
            printf("m:%s\n",buff);
            fclose(fp);
        } else if(!strcmp(argv[i],"-n")){
            FILE *fp;
            fp = fopen(argv[++i],"r");
            fscanf(fp,"%s",n);
            printf("n:%s\n",n);
            fclose(fp);
        } else if(!strcmp(argv[i],"-e")){
            FILE *fp;
            fp = fopen(argv[++i],"r");
            fscanf(fp,"%s",e);
            printf("e:%s\n",e);
            char *n_d = Hex2Dec(n);
            char *buff_d = Hex2Dec(buff);
            char *temp = EncryptOrDecrypt(n_d,buff_d,e);
            c = Dec2Hex(temp);
            printf("cipher:%s",c);
            fclose(fp);
        } else if(!strcmp(argv[i],"-d")){
            FILE *fp;
            fp = fopen(argv[++i],"r");
            fscanf(fp,"%s",d);
            printf("d:%s\n",d);
            char *n_d = Hex2Dec(n);
            char *buff_d = Hex2Dec(buff);
            char *temp = EncryptOrDecrypt(n_d,buff_d,d);
            c = Dec2Hex(temp);
            printf("sign:%s",c);
            fclose(fp);
        } else if(!strcmp(argv[i],"-c")){
            FILE *fp;
            fp = fopen(argv[++i],"w+");
            fprintf(fp,"%s",c);
            fclose(fp);
        } else {
            printf("Invalid Instruction!\n");
            break;
        }
    }
    return 0;
}

/**
 * @brief 将十六进制转换为二进制数组，反序
 * 
 * @param bin 二进制数组
 * @param s 十六进制字符串
 * @return int 返回二进制数组长度
 */
int Hex2Bin(int bin[MAX_SIZE],char *s){
    int num = 0,count = 0;
    for(int i=strlen(s)-1; i>=0; i--) {
        if(s[i]<='9'&&s[i]>='0') num = s[i] - '0';
        else num = s[i] -'A' + 10;
        bin[count++] = (num)&1;
        bin[count++] = (num>>1)&1;
        bin[count++] = (num>>2)&1;
        bin[count++] = (num>>3)&1;
    }
    return count;
}

/**
 * @brief maxer函数 判断str1 是否 大于str2
 * 
 * @param str1 数1
 * @param str2 数2
 * @return int 结果为0，相等；结果为负数，str1<str2；结果为正数，str1>str2
 */
int maxer(char *str1, char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 > len2)
        return 1;
    else if (len1 < len2)
        return -1;
    else
    {
        int n = strcmp(str1, str2);
        if (n > 0)
            return 1;
        else if (n == 0)
            return 0;
        else
            return -1;
    }
}
 
/**
 * @brief 加法
 * 
 * @param str1 加数1 
 * @param str2 加数2
 * @return char* 结果
 */
char *add(char *str1, char *str2)
{
    if(str1[0] != '-' && str2[0] != '-'){ //两正数相加
        //  确定较大，较小的字符串，并获取它们的长度
        int n = maxer(str1, str2);
        char *max_str = n >= 0 ? str1 : str2;
        char *min_str = n >= 0 ? str2 : str1;
        int len_max = strlen(max_str);
        int len_min = strlen(min_str);
 
        //  创建 较大字符串 长度大1 的空间 存储结果
        char *str = malloc(MAX_SIZE + 1);
        // str[len_max + 1] = '\0';
        memset(str,'\0',MAX_SIZE+1);
 
        //  进行加法运算
        int plus = 0;        // plus 为 进位
        int i = len_max - 1; // 标记 较大字符串 最低位字符的位置
        int j = len_min - 1; // 标记 较小字符串 最低位字符的位置
        for (; i >= 0; i--)
        {
            if (j >= 0)
            {
                str[i + 1] = max_str[i] + min_str[j] - '0' + plus; // 字符相加
                j--;                                               // 位置左移 1
                plus = str[i + 1] > '9' ? 1 : 0;                   // 判断是否进位
                if (plus == 1)
                    str[i + 1] -= 10; // 进位 则减 10
            }
            else // 较小字符串的字符 全部加完
            {
                str[i + 1] = max_str[i] + plus;
                plus = str[i + 1] > '9' ? 1 : 0;
                if (plus == 1)
                    str[i + 1] -= 10;
            }   
        }
 
        //  根据 最高位 是否 进位，确定 返回指针
        if (plus == 0)
            return str + 1; // 返回 str 右移1位的位置
        else
        {
            str[0] = '1'; // str首位 赋 '1'
            return str;   // 返回 str
        }

    } else if(str1[0] == '-' && str2[0] == '-') {   //两负数相加，相当于两个数的正数部分相加再取负
        char *tmp = add(str1+1,str2+1);
        char *res = (char*)malloc(strlen(tmp)+2);
        memset(res,'\0',strlen(tmp)+2);
        res[0] = '-';
        for(int i=1,j=0; j<strlen(tmp); i++,j++){
            res[i] = tmp[j];
        }
        return res;
    } else if(str1[0] != '-' && str2[0] == '-') {   //一正一负相加，相当于第一个数减去第二个数的正数部分
        return sub(str1,str2+1);
    } else {
        return sub(str2,str1+1);                    //一负一正相加，相当于第二个数减去第一个数的正数部分
    }
}

/**
 * @brief 减法
 * 
 * @param str1 被减数 
 * @param str2 减数
 * @return char* 结果
 */
char *sub(char *str1,char *str2) {
    if(str1[0]!='-'&&str2[0]!='-') {    //两正数相减
        //  确定结果 正负 或 0
        int is_neg = maxer(str1, str2);
        if (is_neg == 0)
            return "0"; // 若为 0, 直接返回 "0" 结束
        char *max_str = is_neg > 0 ? str1 : str2;
        char *min_str = is_neg > 0 ? str2 : str1;
        int len_max = strlen(max_str);
        int len_min = strlen(min_str);

        char *str = malloc(MAX_SIZE + 1);
        // str[len_max + 1] = '\0';
        memset(str,'\0',MAX_SIZE+1);

        //  进行减法运算
        int plus = 0; // plus 为退位
        int i = len_max - 1;
        int j = len_min - 1;
        for (; i >= 0; i--)
        {
            if (j >= 0)
            {
                str[i + 1] = max_str[i] - min_str[j] + '0' + plus; // 字符相减
                j--;
                plus = str[i + 1] < '0' ? -1 : 0; // 是否 退位
                if (plus == -1)
                    str[i + 1] += 10; // 退位 则加 10
            }
            else
            {
                str[i + 1] = max_str[i] + plus;
                plus = str[i + 1] < '0' ? -1 : 0;
                if (plus == -1)
                    str[i + 1] += 10;
            }
        }

        //  确定最后一个 前位0 的位置，默认 str首位 为'0'
        int n_zero = 0;
        for (int i = 1; i <= len_max; i++)
        {
            if (str[i] != '0')
                break;
            n_zero++;
        }

        //  根据 正负 和 最后一个前位0的位置 确定 返回指针
        if (is_neg < 0)
        {
            str[n_zero] = '-';   // 将最后一个前置0的 赋为 '-'
            return str + n_zero; // 返回'-'的位置
        }
        else
            return str + n_zero + 1; // 返回最后一个前置0 右移1位的位置
    } else if(str1[0]=='-'&&str2[0]=='-') {     //两负数相减，相当于第二个数的正数部分减去第一个数的正数部分
        return sub(str2+1,str1+1);
    } else if(str1[0]!='-'&&str2[0]=='-'){      //一正一负相减，相当于第一个数加上第二个数的正数部分
        return add(str1,str2+1);
    } else {                                    //一负一正相减，相当于两个负数相加
        char *_str2 = sub("0",str2);
        return add(str1,_str2);
    }
}

/**
 * @brief 乘法
 * 
 * @param str1 乘数1 
 * @param str2 乘数2
 * @return char* 结果
 */
char *mul(char *str1, char *str2)
{
    if(str1[0]!='-'&&str2[0]!='-'){     //两正数相乘
        // 判断 str1 和 str2 中是否为 0,若有, 返回 "0" 结束
        if (*str1 == '0' || *str2 == '0')
            return "0";
    
        // 提高效率
        int n = maxer(str1, str2);
        char *max_str = n > 0 ? str1 : str2;
        char *min_str = n > 0 ? str2 : str1;
        int len_min = strlen(min_str);
    
        // 进行乘法运算
        char *str_sum = "0";
        // str2每个字符 乘 str1
        for (int i = 0; i < len_min; i++)
        {
            char *str = "0";
            int m = (int)(min_str[i] - '0'); // 把字符转成整型
            if (m == 0)
                continue;
            else
            {
                for (int j = 0; j < m; j++)
                    str = add(str, max_str);
            }
            // 根据字符位数 往str后面 添 '0'
            int len = strlen(str);
            for (int j = 0; j < len_min - i - 1; j++)
            {
                str[len + j] = '0';
            }
            str[len + len_min - i - 1] = '\0';
            //printf("%s\n", str);
            // 将每次得到的结果相加
            str_sum = add(str_sum, str);
            //printf("%s\n", str_sum);
        }
        return str_sum;
    } else if(str1[0]=='-'&&str2[0]=='-') { //两负数相乘，相当于两数正数部分相乘
        return mul(str1+1,str2+1);
    } else if(str1[0]!='-'&&str2[0]=='-') { //一正一负相乘,相当于两数正数部分相乘再取负
        char *tmp = mul(str1,str2+1);
        return sub("0",tmp);
    } else {
        char *tmp = mul(str1+1,str2);
        return sub("0",tmp);
    }
}

/**
 * @brief 除法
 * 
 * @param str1 被除数 
 * @param str2 除数
 * @return char* 结果
 */
char *divi(char *str1, char *str2)
{
    if(str1[0]!='-'&&str2[0]!='-'){
        // 解决一些特殊情况
        if (*str2 == '0')
            return " 0 不能作为除数！";
        if (maxer(str1, str2) == -1)
            return "0";
    
        // 初始化 余数(被除数) 除数 和 结果
        char *str_mol = add(str1, "0");  // 得到 str1 副本
        char *str_divi = add(str2, "0"); // 得到 str2 副本
        char *str_sum = "0";
    
        // 进行除法运算
        // 将 str_mol 和 str_divi 右对齐
        int n = strlen(str1) - strlen(str2);
        char *str_n = "1";
        for (int i = 0; i < n; i++)
            str_n = mul(str_n, "10");    // 得到str_divi 扩大的倍数
        str_divi = mul(str_divi, str_n); // 实现右对齐
    
        for (int i = 0; i <= n; i++)
        {
            while (maxer(str_mol, str_divi) >= 0)
            {
                str_mol = sub(str_mol, str_divi);
                str_sum = add(str_sum, str_n); // 将每次结果加起来
                //puts(str_mol);
                //puts(str_sum);
            }
            if (i < n)
            {
                *(str_n + strlen(str_n) - 1) = '\0';       // 去除尾位置的 '0'
                *(str_divi + strlen(str_divi) - 1) = '\0'; // 去除尾位置的 '0'
            }
        }
        return str_sum;
    } else if(str1[0]=='-'&&str2[0]=='-'){
        return divi(str1+1,str2+1);
    } else if(str1[0]!='-'&&str2[0]=='-'){
        char *tmp = divi(str1,str2+1);
        if(!strcmp(tmp,"0")) return tmp;
        else return sub("0",tmp);
    } else {
        char *tmp = divi(str1+1,str2);
        if(!strcmp(tmp,"0")) return tmp;
        else return sub("0",tmp);
    }
}
 
/**
 * @brief 取模
 * 
 * @param str1 被模数 
 * @param str2 模数
 * @return char* 结果
 */
char *mol(char *str1, char *str2)
{
    if (*str2 == '0')
        return " 0 不能作为除数！";
    if (maxer(str1, str2) == -1)
        return str1;
    char *str_mol = add(str1, "0");
    char *str_divi = add(str2, "0");
    char *str_sum = "0";
    int n = strlen(str1) - strlen(str2);
    char *str_n = "1";
    for (int i = 0; i < n; i++)
        str_n = mul(str_n, "10");
    str_divi = mul(str_divi, str_n);
    for (int i = 0; i <= n; i++)
    {
        while (maxer(str_mol, str_divi) >= 0)
        {
            str_mol = sub(str_mol, str_divi);
            str_sum = add(str_sum, str_n);
        }
        if (i < n)
        {
            *(str_n + strlen(str_n) - 1) = '\0';
            *(str_divi + strlen(str_divi) - 1) = '\0';
        }
    }
    return str_mol;
}

/**
 * @brief 乘方
 * 
 * @param str 底数
 * @param index 指数
 * @return char* 结果
 */
char *myPow(char *str,int index){
    if(index == 0) return "1";
    char *res = str;
    for(int i=1; i<index; i++){
        res = mul(res,str);
    }
    return res;
}


/**
 * @brief 将16进制字符串转换为10进制字符串
 * 
 * @param str 待转换的十六进制字符串
 * @return char* 转换后的十进制字符串
 */
char* Hex2Dec(char *str){
    char *res = "0";
    char *temp = str;
    char ch[3];
    int index = 0;
    for(int i=strlen(str)-1; i>=0; i--){
        if(str[i]>='A'&&str[i]<='F'){
            int num = str[i] - 'A' + 10;
            if(num == 10) strcpy(ch,"10");
            else if(num == 11) strcpy(ch,"11");
            else if(num == 12) strcpy(ch,"12");
            else if(num == 13) strcpy(ch,"13");
            else if(num == 14) strcpy(ch,"14");
            else strcpy(ch,"15");
        } else {
            memset(ch,'\0',3);
            ch[0] = str[i];
        }
        temp = myPow("16",index++);
        temp = mul(ch,temp);
        res = add(res,temp);
    }
    return res;
}

/**
 * @brief 将十进制字符串转换为十六进制字符串
 * 
 * @param str 待转换的十进制字符串
 * @return char* 转换后的十六进制字符串
 */
char* Dec2Hex(char *str){
    char res[257];
    memset(res,'\0',257);
    char *tmp = str;
    int count = 0;
    while(strcmp(tmp,"0")){
        char *a = mol(tmp,"16");
        if(!strcmp(a,"10")) res[count++] = 'A';
        else if(!strcmp(a,"11")) res[count++] = 'B';
        else if(!strcmp(a,"12")) res[count++] = 'C';
        else if(!strcmp(a,"13")) res[count++] = 'D';
        else if(!strcmp(a,"14")) res[count++] = 'E';
        else if(!strcmp(a,"15")) res[count++] = 'F';
        else {
            res[count++] = a[0];
        }
        tmp = divi(tmp,"16");
    }
    char *reverse = (char*)malloc(count+1);
    memset(reverse,'\0',count+1);
    for(int i=0; i<count; i++){
        reverse[i] = res[count-i-1];
    }
    return reverse;
}

/**
 * @brief RSA算法
 * 
 * @param n n = p*q
 * @param mOrc 明文或密文 
 * @param eOrd e或者d
 * @return char* 返回加密结果或者解密结果
 */
char *EncryptOrDecrypt(char *n,char *mOrc,char *eOrd){
    int bin[MAX_SIZE];  //将e或d转为二进制数组
    int k = Hex2Bin(bin,eOrd);
    char *tmp1 = mOrc;
    char *z = "1";
    for(int i=k-1; i>=0; i--) {
        z = mul(z,z);   
        z = mol(z,n);
        if(bin[i]==1){
            z = mul(z,mOrc);
            z = mol(z,n);
        }
    }
    return z;
}

/**
 * @brief 计算在指定范围内的大素数，并且存储在数组中
 * 
 * @param rangeFrom 范围区间最小值
 * @param rangeTo   范围区间最大值
 * @return long long* 保存大素数的数组
 */
long long *bigPrime(){
    long long *res = (long long*)malloc(sizeof(long long)*1000);
    srand(time(0));
    int x = rand()%100;
    int y = rand()%100+100;
    long long rangeFrom = least+x*n_1w;
    long long rangeTo = least+y*n_1w;
    if(rangeFrom%2==0) rangeFrom++; //确保最开始的数是个奇数
    int j=2,count = 0;
    for(long long i = rangeFrom; i<=rangeTo; i += 8 ){
        for(j=2; j*j<=i; j++){
            if(i%j == 0) break;
        }
        if(j*j>i){
            res[count++] = i;
        }
        if(count==1000) break;
    }
    return res;
}

/**
 * @brief 将整形十进制转换为十进制字符串
 * 
 * @param x 整数x
 * @return char* 字符串x
 */
char* Dec2Str(long long x){
    char *res = (char*)malloc(24);
    char str[24];
    memset(res,'\0',24);
    int tmp = 0,count = 0;
    do{
        tmp = x%10;
        char ch = tmp + '0';
        str[count++] = ch;
        x = x/10;
    } while(x>0);
    for(int i=0; i<count; i++) res[i] = str[count-1-i];
    return res;
}


/**
 * @brief 生成密钥，并且将相关内容写入到文件中，默认写入进p.txt,q.txt,n.txt,e.txt,n.txt
 * 
 */
void key_generate(){
    long long *num = bigPrime();    //得到一个有1000个随机大素数的数组
    srand(time(0));                 //重置随机数种子
    //获取两个随机数
    int x = rand()%500;                      
    int y = rand()%500+500;
    //以上述两个随机数为下标在大素数数组中选出p,q,并且将它们转化为十进制字符串
    char *str1 = Dec2Str(num[x]);   
    char *str2 = Dec2Str(num[y]);
    //p,q相乘得到n
    char *str3 = mul(str1,str2);
    char *p = Dec2Hex(str1);
    char *q = Dec2Hex(str2);
    printf("p:%s\n",str1);
    printf("q:%s\n",str2);
    char *n = Dec2Hex(str3);
    printf("n:%s\n",n);
    //计算(p-1)*(q-1)
    char *str1_1 = sub(str1,"1");   //p-1
    char *str2_1 = sub(str2,"1");   //q-1
    char *Fn = mul(str1_1,str2_1);  //Fn = (p-1)*(q-1)
    printf("(p-1)*(q-1)%s\n",Fn);   
    
    char *e = "10001";              //e:选用常用的65537，H(e)=10001

    //计算d = e^(-1) mod Fn
    char *e_d = Hex2Dec(e);     
    printf("e:%s\n",e_d);
    char *d;
    char *a = Fn;
    char *b = e_d;
    char *q1,*r;
    char *u = "0", *v = "1",*t;
    while(strcmp(b,"0")){
        q1 = divi(a,b);
        char *tmp = mul(b,q1);
        r = sub(a,tmp);
        a = b;
        b = r;
        t = v;
        char *tmp1 = mul(q1,v);
        v = sub(u,tmp1);
        u = t;
    }
    //最后如果 u<0 , d = u + Fn, 否则 d = u
    if(u[0]=='-') d = add(u,Fn);
    else d = u;
    printf("d:%s\n",d);
    d = Dec2Hex(d);
    write(n,"n.txt");
    write(p,"p.txt");
    write(q,"q.txt");
    write(e,"e.txt");
    write(d,"d.txt");
}

/**
 * @brief 往指定文件写入
 * 
 * @param buff 要写入的内容
 * @param filename 文件名，若没有，则创建
 */
void write(char *buff,char *filename){
    FILE *fp = fopen(filename,"w+");
    fprintf(fp,"%s",buff);
    fclose(fp);
}
