/*************************************************************************
	> File Name: acf.c
	> Author: huangben
	> Mail: huangben@baidu.com 
	> Created Time: 2013年07月29日 星期一 16时58分12秒
 ************************************************************************/
#include "acf.h"
#include <libconfig.h>

global_data_t g_data;//全局变量

int creat_server()
{
	int listenfd,connfd;
	struct sockaddr_in servaddr,cliaddr;
	char *ip = g_data.srt.ip;
	int port = g_data.srt.port;
	//char *ip = "127.0.0.1";
	char buf[1024] = {0} ;
	socklen_t len = 0;

	listenfd = Socket(AF_INET,SOCK_STREAM,0);
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	Inet_pton(AF_INET, ip, &servaddr.sin_addr);
	
	//0表示通配
	servaddr.sin_port = htons(port);

	//地址复用端口复用
	unsigned value = 1;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &value, sizeof(value));
	
	Bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	//getsockname(listenfd,(struct sockaddr *)&servaddr,&len);
	//printf("server: %s,port:%d\n",inet_ntoa(servaddr.sin_addr),ntohs(servaddr.sin_port));
	Listen(listenfd,BACKLOG);
	signal(SIGCHLD,sig_child);
	for(;;)
	{
		printf("now pid:%d\n",getpid());	
		fflush(stdout);
		len = sizeof(cliaddr);
		//别忘了给len赋值，这个坑让我查了一个多小时
		connfd = Accept(listenfd,(struct sockaddr *)&cliaddr,&len);
		pid_t childpid;
		if((childpid = fork()) == 0)
		{
			Close(listenfd);	
			char ipbuf[INET_ADDRSTRLEN];
			Inet_ntop(AF_INET, (void *)&cliaddr.sin_addr, ipbuf,sizeof(ipbuf));
			printf("connection from %s,port:%d,len:%d,pid:%d\n",ipbuf,ntohs(cliaddr.sin_port),len,getpid());
			int n;
			while((n = Recv(connfd,buf,sizeof(buf),0)) > 0 )
			{
				buf[n] = 0;
				printf("recv:%s,strlen:%d,sizeof:%d\n",buf,strlen(buf),sizeof(buf));
				Send(connfd,buf,strlen(buf),0);
			}
			Close(connfd);
			exit(0);
		}
		Close(connfd);
	}
}

void sig_child(int signo)
{
	pid_t pid;
	int stat;
	while((pid = waitpid(-1, &stat, WNOHANG)) > 0 );
	return ;
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{	
		printf("args wrong!\n");
		exit(1);
	}
	char *conf_path = argv[1];
    
    config_t cfg;
    config_init(&cfg);
    if (!config_read_file(&cfg, conf_path))
    {
        return -1;
    }
   
    const char* ip;
    if (!config_lookup_string(&cfg, "server.ip", &ip)) 
    {
        printf("fuck");
        return -1;
    }
    snprintf(g_data.srt.ip, TINY_STR_LEN, "%s", ip);
    if (!config_lookup_int(&cfg, "server.port", &g_data.srt.port))
    {
        printf("fuck");
        return -1;
    }
    printf("%s, %d\n", g_data.srt.ip, g_data.srt.port);
    config_destroy(&cfg);
	creat_server();
	return 0;
}


