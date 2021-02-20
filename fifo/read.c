#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    //文件描述符
    int fd;
    int ret;
    char buf[1024];
    //检测是否有管道文件
    if ((ret = access("./myfifo", F_OK)) == -1)
    {
        ret = mkfifo("./myfifo", 0777);
        if (ret < 0)
        {
            perror("mkfifo error");
            return -1;
        }
    }

    //打开管道文件
    fd = open("./myfifo", O_RDWR);
    if (fd < 0)
    {
        perror("open error");
        return -1;
    }
    //==============读取管道中数据=========================
    while (1)
    {
        //=================   设置read函数非阻塞  ==================
/*      int flags = fcntl(fd, F_GETFL);
        flags |= O_NONBLOCK;
        fcntl(fd, F_SETFL, flags);*/
        sleep(1);
        memset(buf, 0x00, sizeof(buf));
        ret = read(fd, buf, sizeof(buf));
        printf("读取数据：%d, buf = %s\n", ret, buf);
    }
    //关闭文件
    close(fd);

    return 0;
}