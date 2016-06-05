#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<unistd.h>

#define LINE 2048
int main(int argc,char** argv)
{
    FILE* f1=fopen(argv[1],"r");
    FILE* f2=fopen(argv[2],"r");
    if(f1==NULL||f2==NULL)
    {
        printf("cannot open file!\n");
        exit(-1);
    }
    char buf1[LINE],buf2[LINE];
    int n1,n2;
    int bytecount=0;
    int lineno=0;
    while((fgets(buf1,LINE,f1)!=NULL)&&(fgets(buf2,LINE,f2)!=NULL)){
        lineno++;
        if(strcmp(buf1,buf2)==0)
        {
            bytecount+=strlen(buf1);
            continue;
        }
        else break;
    }
    n1=strlen(buf1);
    n2=strlen(buf2);
    if(strcmp(buf1,buf2)==0){printf("The contents of %s and %s are the same.\n",argv[1],argv[2]);
    exit(0);}
    if(n1>n2)n1=n2;
    for(int i=0;i!=n1;i++)
    {
        if(buf1[i]==buf2[i])bytecount++;
        else break;
    }
    bytecount++;
    if(n1==0)lineno++;
    printf("%s %s,differ:byte %d,line %d\n",argv[1],argv[2],bytecount,lineno);
    exit(0);

}
