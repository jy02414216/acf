/*************************************************************************
	> File Name: server.h
	> Author: huangben
	> Mail: huangben@baidu.com 
	> Created Time: 2013年08月04日 星期日 22时01分19秒
 ************************************************************************/
#ifndef _CLIENT_H
#define _CLIENT_H

#include "hb.h"

#define CONF_MAX_LEN 20
#define DATA_MAX_LEN 1000

typedef struct _server_conf
{
	char *ip;
	int port;
}server_conf;

//从配置文件读取配置
void load_conf(char *conf_path);
//创建server
int creat_client();

#endif
