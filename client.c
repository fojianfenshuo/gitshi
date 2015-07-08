#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>

#define MYPORT  43210
#define BUFFER_SIZE 1024

int main()
{

    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    char a = 'a';
    int flag;

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);
    servaddr.sin_addr.s_addr = inet_addr("10.210.106.48");
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }
    while (1)
    {
    	sleep(1);
    	printf("I want send [%c]\n", a);
        flag = send(sock_cli, &a, 1, 0);
        printf("send:[%d]||data:[%c]\n", flag, a);
        if(a == 'l')
        {
        	sleep(5);
        }
        a++;
    }

    close(sock_cli);
    return 0;
}