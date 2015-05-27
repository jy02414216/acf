/*************************************************************************
	> File Name: wrapsock.c
	> Author: huangben
	> Mail: huangben@baidu.com 
	> Created Time: 2013年08月01日 星期四 22时12分10秒
 ************************************************************************/

#include "wrapsock.h"

void err_sys(char* msg)
{
	fprintf(stderr,"error:%d ",errno);
	perror(msg);
	exit(1);
}

int Socket(int family, int type, int protocol)
{
	int fd = socket(family,type, protocol);
	if(fd < 0)
	{
		err_sys("socket create error!");
	}
	return fd;

}

void Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen)
{
	if((connect(sockfd, servaddr, addrlen)) < 0)
	{
		err_sys("connect error!");
	}
}

void Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen)
{
	if(bind(sockfd, myaddr, addrlen) < 0)
	{
		err_sys("bind error!");
	}
}


void Listen(int sockfd, int backlog)
{
	if(listen(sockfd, backlog) < 0)
	{
		err_sys("listen error!");
	}
}

int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen)
{
	int fd = accept(sockfd, cliaddr, addrlen);
	if(fd < 0)
	{
		err_sys("accept error!");
	}
	return fd;
}

ssize_t Send(int sockfd, const void *buff, size_t nbytes, int flags)
{
	ssize_t n = send(sockfd, buff, nbytes, flags);
	
	if(n != (ssize_t)nbytes)
	{
		err_sys("send error!");
	}
	return n;
}

ssize_t Recv(int sockfd, void *buff, size_t nbytes, int flags)
{
	ssize_t n = recv(sockfd, buff, nbytes, flags);
	
	if(n < 0)
	{
		err_sys("send error!");
	}
	return n;
}

//addrptr是一个指向in_addr的结构指针
const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len)
{
	const char  *ptr;
	if (strptr == NULL)     /* check for old code */
		err_sys("NULL 3rd argument to inet_ntop");
	if ( (ptr = inet_ntop(family, addrptr, strptr, len)) == NULL)
		err_sys("inet_ntop error");     /* sets errno */
	return(ptr);
}

//addrptr是一个指向in_addr的结构指针
void Inet_pton(int family, const char *strptr, void *addrptr)
{
	int n;  
    if ( (n = inet_pton(family, strptr, addrptr)) < 0)
        err_sys("inet_pton error!");  /* errno set */
    //不是有效表单试
	else if (n == 0)
        err_sys("inet_pton error!"); /* errno not set */
    /* nothing to return */
}

void Close(int fd)
{
	if(close(fd) < 0)
	{
        err_sys("close error!");  
	}
}
