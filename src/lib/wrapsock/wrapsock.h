/*************************************************************************
	> File Name: hb.h
	> Author: huangben
	> Mail: huangben@baidu.com 
	> Created Time: 2013年07月31日 星期三 21时32分59秒
 ************************************************************************/
#ifndef _wrapsock_h
#define _wrapsock_h

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<sys/wait.h>

#define BACKLOG 128

/*############error相关函数#######################*/
//输出错误信息并退出
void err_sys(char* msg);

/*#################socket 相关函数############*/

//socket的包裹函数
int Socket(int family, int type, int protocol);
void Connect(int sockfd, const struct sockaddr *servaddr, socklen_t addrlen);
void Bind(int sockfd, const struct sockaddr *myaddr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *cliaddr, socklen_t *addrlen);
ssize_t Send(int sockfd, const void *buff, size_t nbytes, int flags);
ssize_t Recv(int sockfd, void *buff, size_t nbytes, int flags);
const char *Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
void Inet_pton(int family, const char *strptr, void *addrptr);
void Close(int fd);
#endif

