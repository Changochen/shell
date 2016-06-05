#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc,char** argv)
{
    int output[5]={0,0,0,0,0};//line,word,byte,character,max line
    unsigned int res[5]={0,0,0,0,0};
    int i=1;
    for(;i!=argc;i++)//handle the argument
    {
        int siz=strlen(argv[i]);
        if(argv[i][0]=='-'&&siz>=2)
        {
            if(siz==2)
            {
                switch(argv[i][1])
                {
                    case 'c':
                        output[2]=1;
                        break;
                    case 'm':
                        output[3]=1;
                        break;
                    case 'l':
                        output[0]=1;
                        break;
                    case 'L':
                        output[4]=1;
                        break;
                    case 'w':
                        output[1]=1;
                        break;
                }
            }
            else if(strcmp(argv[i],"--bytes")==0)
                output[2]=1;
            else if(strcmp(argv[i],"--chars")==0)
                output[3]=1;
            else if(strcmp(argv[i],"--lines")==0)
                output[0]=1;
            else if(strcmp(argv[i],"--words")==0)
                output[1]=1;
            else if(strcmp(argv[i],"--max-line-length")==0)
                output[4]=1;
        }
        else break;
    }
    if(i==1){
        output[0]=1;
        output[1]=1;
        output[2]=1;
    }
    int flag=(argc-i)>1;//whether more than one file needs to be count
    for(;i!=argc;i++)
    {
        unsigned int t_res[5]={0,0,0,0,0};
        FILE *file;
        if(argv[i][0]=='-')file=stdin;
        else
            if((file=fopen(argv[i],"r"))==NULL)
            {
                printf("cannot open file %s\n",argv[i]);
                exit(-1);
            }
        int c;
        int word_flag=0;
        int tempsen=0;
        while((c=fgetc(file))!=EOF)
        {
            t_res[2]++;
            if(c>=33&&c<127)word_flag=1;
            if(c<128)t_res[3]++;
            if(c!='\n')tempsen++;
            else if(c=='\n')
            {
                if(t_res[4]<tempsen)t_res[4]=tempsen;
                tempsen=0;
                if(word_flag==1)t_res[1]++;
                word_flag=0;
                t_res[0]++;
            }
            else{
                if(word_flag==1)t_res[1]++;
                word_flag=0;
            }
        }
        if(tempsen>t_res[4]){
            t_res[4]=tempsen;
        }
        if(word_flag==1)t_res[1]++;
        for(int i=0;i!=5;i++)
        {
            res[i]+=t_res[i];
            if(output[i]==1)printf("%d\t",t_res[i]);
        }
        if(argv[i][0]=='-')printf("Stdin\n");
        else printf("%s\n",argv[i]);
    }
    if(flag==1){
        for(int i=0;i!=5;i++)
        {
           if(output[i]==1)printf("%d\t",res[i]);
        }
        printf("Total\n");
    }
}
