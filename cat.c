/*1. 实现 '-b' 选项：输出文件，对空行不编号
2. 实现‘-n’选项：输出文件，对所有行编号
3. 默认情况下：输出文件，不编号*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int bflag, nflag, num;//标记是b还是b  和 行号
void cat_file(const char *);
int main(int argc, char *argv[]) {
    char c;
    while((c = getopt(argc, argv, "bn")) != -1) {//判断命令行参数 是 -b 还是 -n
        switch(c) {
            case 'b':
                bflag = 1;
                break;
            case 'n':
                nflag = 1;
                break;
            default :
                fprintf(stdout, "Use : %s [-b|-n] file!\n", argv[0]);
                exit(1);
        }
    }
    for(int i = optind; i < argc; i++) {
        cat_file(argv[i]);
    }
    return 0;
}
void cat_file(const char *file) {
    FILE *fp;
    if((fp = fopen(file, "r")) == NULL) {
        //打印错误信息
        perror(file);
        exit(1);
    }
    char buff[1024] = {0};
    while(fgets(buff, sizeof(buff), fp)) {
        //都不成立 直接打印
        if(!nflag && !bflag) {
            printf("%s", buff);
            continue;
        }
        if(buff[0] != '\n'){ 
            num++;
            printf("%d\t%s", num, buff);
        }else {
            //nflag成立 打印行号 不成立 不打印行号
            if(nflag && !bflag) {
                num++;
                printf("%d\t\n", num);
            }else {
                printf("\n");
            }
        }
    }
    fclose(fp);
    return ;
}
