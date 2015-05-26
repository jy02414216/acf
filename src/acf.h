/*************************************************************************
	> File Name: server.h
	> Author: huangben
	> Mail: huangben@baidu.com 
	> Created Time: 2013年08月04日 星期日 22时01分19秒
 ************************************************************************/
#ifndef _ACF_SRC_ACF_H
#define _ACF_SRC_ACF_H

#include "acf_define.h"
#include "acf_type.h"
#include "wrapsock.h"
#include <libconfig.h>

//进程退出的回调函数
void sig_child(int signo);
//从配置文件读取配置
void load_conf(char *conf_path);
//创建server
int creat_server();

#endif
