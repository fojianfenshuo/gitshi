#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <setjmp.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
int g_iSockServerFd;
int g_iSockAppConn;
#define MYPORT 43210
void SocketServerInit()
{
	g_iSockServerFd = socket(AF_INET,SOCK_STREAM, 0);
	
	struct sockaddr_in server_sockaddr;
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(MYPORT);
	server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	printf("serverfd:[%d]\n", g_iSockServerFd);
	bind_while:
	if(bind(g_iSockServerFd,(struct sockaddr *)&server_sockaddr,sizeof(server_sockaddr))==-1)
	{
		perror("bind");
		sleep(1);
		goto bind_while;
		return;
	}

	if(listen(g_iSockServerFd,10) == -1)
	{
		perror("listen");
		return;
	}	
	return;
}
void socketAccept()
{
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);
	char a = 'a';
	int flag;
	g_iSockAppConn = accept(g_iSockServerFd, (struct sockaddr*)&client_addr, &length);
	while(1)
	{
		sleep(1);
		flag = recv(g_iSockAppConn, &a, 1, 0);
		printf("recv:[%d]||data:[%c]\n", flag, a);
		if(a == 'l')
		{
			close(g_iSockAppConn);
			exit(0);
		}
	}
	return;
}
int main()
{
	SocketServerInit();
	socketAccept();
	return 0;
}