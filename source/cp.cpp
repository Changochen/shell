#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/stat.h>
#define BUFFSIZE 4096
int main(int argc,char **argv)
{
    int n;
    char buf[BUFFSIZE];
    FILE * source,*dest;
    if((source=fopen(argv[1],"rb"))==NULL)
    {
        printf("cannot open file %s\n",argv[1]);
        exit(-1);
    }
    dest=fopen(argv[2],"wb");
    while((n=fread(buf,1,BUFFSIZE,source))>0)
    {
        if(fwrite(buf,1,n,dest)!=n)
        {
            printf("copy error!\n");
            exit(-1);
        }
    }
    if(n<0){
        printf("read error!\n");
        exit(-1);
    }
    fclose(dest);
    fclose(source);
    struct stat sstat,dstat;
    if(lstat(argv[2],&dstat)<0||lstat(argv[1],&sstat)<0)
    {
        printf("Using default file access permission!\n");
    }
    else{
        dstat.st_mode=sstat.st_mode;
        printf("%d\n",sstat.st_mode&S_IXUSR);
        printf("%d\n",dstat.st_mode&S_IXUSR);

    }
    exit(0);
}
