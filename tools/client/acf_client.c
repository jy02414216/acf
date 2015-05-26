/*************************************************************************
	> File Name: client.c
	> Author: huangben
	> Mail: huangben@baidu.com 
	> Created Time: 2013年07月30日 星期二 14时04分02秒
 ************************************************************************/

#include "acf.h"
#include <libconfig.h>
#define DATA_MAX_LEN 1000

server_t server;

void creat_client()
{	
	int fd;
	struct sockaddr_in cliddr,servddr;
	char *ip = "127.0.0.1";
	char buf[1000] = {0};
	
	cliddr.sin_family = AF_INET;
	Inet_pton(AF_INET,ip,&cliddr.sin_addr);
	//随机端口
	cliddr.sin_port = htons(0);
	
	fd = Socket(AF_INET,SOCK_STREAM,0);
	//Bind(fd,(struct sockaddr *)&cliddr,sizeof(cliddr));

	servddr.sin_family = AF_INET;
	Inet_pton(AF_INET,server.ip,&servddr.sin_addr);
	servddr.sin_port = htons(server.port);
	
	Connect(fd,(struct sockaddr *)&servddr,sizeof(servddr));
	
	while(fgets(buf,DATA_MAX_LEN,stdin) !=  NULL)
	{
		buf[strlen(buf) -1] = 0;//不带回车
		Send(fd,buf,strlen(buf),0);
		int n =Recv(fd,buf,sizeof(buf),0);
		buf[n] = 0;
		printf("from server:%s\n",buf);
	}
	
	Close(fd);
	
}

int init() 
{

}

int main(int argc, char **argv)
{
    if (argc != 2)
	{	
		fprintf(stderr, "args wrong!\n");
        return -1;
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
        fprintf(stderr, "get server ip fail");
        return -1;
    }
    snprintf(server.ip, TINY_STR_LEN, "%s", ip);
    if (!config_lookup_int(&cfg, "server.port", &server.port))
    {
        fprintf(stderr, "get server port fail");
        return -1;
    }
    config_destroy(&cfg);
    printf("server:%s, %d\n", server.ip, server.port);
	creat_client();
	exit(0);
	return 0;
}


