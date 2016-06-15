#include<stdio.h>
#include<stdlib.h>
#include<stddef.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
#include<sys/wait.h>


#define MAXLINE 4096
static void sig_int(int);

int main()
{
    printf("welcome to can-do-nothin shell!\n");
    char buf[MAXLINE];
    pid_t pid;
    int status;

    if(signal(SIGINT,sig_int)==SIG_ERR)
        printf("signal error!\n");

    printf("$ ");

    while(fgets(buf,MAXLINE,stdin)!=NULL)
    {
        if(strlen(buf)==1&&*buf=='\n')
        {
            printf("$ ");
            continue;
        }
        if(buf[strlen(buf)-1]=='\n')
            buf[strlen(buf)-1]=0;
        int d1=0,d2=0;
        int len=strlen(buf);
        while(buf[d2]==' ')d2++;
        for(;d2!=len;d2++)
        {
            if(buf[d2]!=' ')
            {
                buf[d1++]=buf[d2];
                continue;
            }
            else{
                while(buf[d2]==' ')d2++;
                d2--;
                buf[d1++]=buf[d2];
            }
        }
        buf[d1]=0;
        if(strcmp(buf,"exit")==0)exit(0);
        if((pid=fork())<0)
        {
            printf("fork error!\n");
            continue;
        }
        else if(pid==0)
        {
            char sys_call[MAXLINE];
            char temp[MAXLINE];
            const char* dir="./bin/";//the directory which holds the executable files
            strcpy(temp,dir);
            strcat(temp,buf);
            strcpy(buf,temp);
            char* program[MAXLINE];
            int count=0;
            int siz=strlen(buf);
            int i=0;
            for(;i!=MAXLINE;i++)//parse command
            {
                program[i]=new char[MAXLINE];
                int k=0;
                for(;count!=siz;count++)
                {
                    if(buf[count]!=' ')program[i][k++]=buf[count];
                    else{
                        count++;
                        break;
                    }
                }
                program[i][k]=0;
                if(count==siz)break;
            }
            strcpy(sys_call,program[0]+strlen(dir));
            program[i+1]=(char*)0;
            if(execvp(program[0],program)==-1)//if not included in local command then invoke system command.
            {
                program[0]=sys_call;
                if(execvp(program[0],program)==-1)
                printf("Error: unknown command %s\n",program[0]+2);
            }
            exit(127);
        }
        if((pid=waitpid(pid,&status,0))<0)
        {
            printf("waitpid error!\n");
        }

        printf("$ ");
    }
    exit(0);
}


void sig_int(int signo)
{
    printf("\n$ ");
}
