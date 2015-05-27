/*************************************************************************
	> File Name: client.c
	> Author: huangben
	> Mail: huangben@baidu.com 
	> Created Time: 2013年07月30日 星期二 14时04分02秒
 ************************************************************************/

#include "acf.h"
#include <vector>
#include <iostream>
#define DATA_MAX_LEN 1000

typedef struct _g_data_t
{
    char conf_path[GEN_STR_LEN];//配置文件地址
    server_t server; //服务器配置
    int thread_num;
    int per_thread_loop_num;
    std::vector<int> thread_v;
}g_data_t;

g_data_t g_data;

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
	Inet_pton(AF_INET,g_data.server.ip,&servddr.sin_addr);
	servddr.sin_port = htons(g_data.server.port);
	
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

int init_config() 
{
    config_t cfg;
    config_init(&cfg);
    if (!config_read_file(&cfg, g_data.conf_path))
    {
        return -1;
    }
   
    const char* ip;
    if (!config_lookup_string(&cfg, "server.ip", &ip)) 
    {
        fprintf(stderr, "get server ip fail");
        return -1;
    }
    snprintf(g_data.server.ip, TINY_STR_LEN, "%s", ip);
    if (!config_lookup_int(&cfg, "server.port", &g_data.server.port))
    {
        fprintf(stderr, "get server port fail");
        return -1;
    }
    if (!config_lookup_int(&cfg, "server.port", &g_data.server.port))
    {
        fprintf(stderr, "get server port fail");
        return -1;
    }
    if (!config_lookup_int(&cfg, "thread_num", &g_data.thread_num))
    {
        fprintf(stderr, "get server port fail");
        g_data.thread_num = 0;
    }
    fprintf(stdout, "threadnum:%d\n", g_data.thread_num);

    if (!config_lookup_int(&cfg, "per_thread_loop_num", &g_data.per_thread_loop_num))
    {
        fprintf(stderr, "per_thread_loop_num error");
        g_data.per_thread_loop_num = 0;
    }
    fprintf(stdout, "per_thread_loop_num:%d\n", g_data.per_thread_loop_num);

    config_destroy(&cfg);
    printf("server:%s, %d\n", g_data.server.ip, g_data.server.port);
    return 0;
}

void *thread_send_query(void *arg)
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
	Inet_pton(AF_INET,g_data.server.ip,&servddr.sin_addr);
	servddr.sin_port = htons(g_data.server.port);
	
	Connect(fd,(struct sockaddr *)&servddr,sizeof(servddr));
	
    for (int i = 0; i < g_data.per_thread_loop_num; ++i)
    {   
        snprintf(buf, sizeof(buf), "%s", "hello, huangben!");
	    Send(fd,buf,strlen(buf),0);
		int n =Recv(fd,buf,sizeof(buf),0);
		buf[n] = 0;
		printf("from server:%s\n",buf);
    }
	
	Close(fd);
    return NULL;
}

int init_pthread()
{
    pthread_t pid = 0;
    int ret = 0;

    for (int i = 0; i < g_data.thread_num; ++i)
    {
        ret = pthread_create(&pid, NULL, thread_send_query, NULL);
        if (ret < 0) 
        {
            fprintf(stderr, "prhtread_create error!\n");
            return -1;
        } 
        else 
        {
            g_data.thread_v.push_back(pid);       
        }
    }
    return 0;
}

int init()
{
    if (init_config() != 0) 
    {
        fprintf(stderr, "init config failed");
        return -1;
    }
    if (init_pthread() != 0) 
    {
        fprintf(stderr, "init pthread failed");
        return -1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (argc != 2)
	{	
		fprintf(stderr, "args wrong!\n");
        return -1;
	}
	char *conf_path = argv[1];
    snprintf(g_data.conf_path, sizeof(g_data.conf_path), "%s", conf_path);
    if (init() != 0) 
    {
        return -1;
    }
	//creat_client();
    std::cout<<g_data.thread_v.size()<<std::endl;
    for (size_t i = 0; i < g_data.thread_v.size(); ++i)
    {
        int pid = g_data.thread_v[i];
        pthread_join(pid, NULL);
    }

	return 0;
}



