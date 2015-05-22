/*************************************************************************
 > File Name: acf_type.h
  > Author: huangben
  > Mail: huangben@baidu.com 
  > Created Time: 2015年05月14日 星期四 20时46分36秒
 ************************************************************************/

#include "acf_define.h"

#ifndef _ACF_SRC_ACF_TYPE_H
#define _ACF_SRC_ACF_TYPE_H

typedef struct _server_t 
{
    int port;
    char ip[TINY_STR_LEN];
}server_t;

//全局变量
typedef struct _global_data_t
{
    server_t srt;
}global_data_t;

#endif

