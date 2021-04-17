#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <fcntl.h>  
  
int main()  
{  
    if((access("test.c",F_OK))!=-1)  
    {  
        printf("文件 test.c 存在.\n ");  
    }  
    else  
    {  
        printf("test.c 不存在!\n ");  
    }  
  
    if(access("test.c",R_OK)!=-1)  
    {  
        printf("test.c 有可读权限\n ");  
    }  
    else  
    {  
        printf("test.c 不可读. \n");  
    }  
  
    if(access("test.c",W_OK)!=-1)  
    {  
        printf("test.c 有可写权限\n ");  
    }  
    else  
    {  
        printf("test.c 不可写.\n ");  
    }  
    if(access("test.c",X_OK)!=-1)  
    {  
        printf("test.c 有可执行权限\n ");  
    }  
    else  
    {  
        printf("test.c 不可执行.\n ");  
    }  
  
    return 0;  
}  