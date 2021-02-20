#include <unistd.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "mylock.h"
int main(void)
{
	int fd;fd = open("hello",O_RDWR | O_CREAT, 0644);if(fd < 0)
	{	
		printf("Open file error\n");
		exit(1);  
	}
	lock_set(fd, F_RDLCK);	/* 给文件上读取锁*/
	getchar();
	lock_set(fd, F_UNLCK);	/* 给文件解锁*/
	getchar();
	close(fd);
	exit(0);    
	return 0;
}