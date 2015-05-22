/*************************************************************************
	> File Name: server.h
	> Author: huangben
	> Mail: huangben@baidu.com 
	> Created Time: 2013��08��04�� ������ 22ʱ01��19��
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

//�������ļ���ȡ����
void load_conf(char *conf_path);
//����server
int creat_client();

#endif
