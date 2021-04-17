
#include <stdio.h>
#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "mylock.h"
int main(void)
{  
	int fd;/* 首先打开文件*/
	fd = open("hello",O_RDWR | O_CREAT, 0644);if(fd < 0)
	{   	
		printf("Open file error\n");	
		exit(1);   
  	}    
 	lock_set(fd, F_WRLCK);  	/* 给文件上写入锁*/  
	getchar();             /*程序暂停，按回车键继续*/    
 	lock_set(fd, F_UNLCK);	/* 给文件解锁*/   
	getchar();   
	close(fd);   
	exit(0);    
	return 0;
}