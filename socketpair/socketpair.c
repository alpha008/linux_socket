#include <sys/types.h>
#include <sys/socket.h>
 
#include <stdlib.h>
#include <stdio.h>
 
int main()
{
    pid_t  pid;
    int    fds[2];
    int    valRead, valWrite;

    if (0 > socketpair(AF_UNIX, SOCK_STREAM, 0, fds))
    {
        printf("creat failed\n");
        return 0;
    }
 
    pid = fork();
 
    if (0 == pid)
    {
        pid = getpid();
        printf("[%d]-child process start \n", pid);
        close(fds[0]);
        
        //read write on fds[1]
        write(fds[1], &valWrite, sizeof(valWrite)); 
        read(fds[1], &valRead, sizeof(valRead));
        printf("child read %d\n", valRead);
    }
    else if (0 < pid)
    {
        valWrite = 4;
        pid = getpid();
        printf("[%d]-parent process start \n", pid);
        close(fds[1]);
 
        //read write on fds[0]
        read(fds[0], &valRead, sizeof(valRead));
        write(fds[0], &valWrite, sizeof(valWrite)); 
        printf("parent write %d \n", valWrite);
    }
    else
    {
        printf("%s", "fork failed");
    }
 
    return 0;
}