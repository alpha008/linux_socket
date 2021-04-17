#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    // 文件描述符
    int fd;
    int ret;
    //判断是否创建管道文件
    if ((ret = access("./myfifo", F_OK)) == -1)
    {
        //创建管道
        ret =  mkfifo("./myfifo", 0777);
        if (ret < 0)
        {
            perror("mkfifo error");
            return -1;
        }
    }

    //打开文件
    fd = open("./myfifo", O_RDWR);
    if (fd < 0)
    {
        perror("open error");
        return -1;
    }
    //=====================写数据到管道中============================
    while (1)
    {
        sleep(1);
        write(fd, "alpha, spider", strlen("alpha, spider"));
    }
    close(fd);
	return 0;
}