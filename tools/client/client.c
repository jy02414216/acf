/*************************************************************************
	> File Name: client.c
	> Author: huangben
	> Mail: huangben@baidu.com 
	> Created Time: 2013��07��30�� ���ڶ� 14ʱ04��02��
 ************************************************************************/

#include "hb.h"
#define DATA_MAX_LEN 1000

void creat_client()
{	
	int fd;
	struct sockaddr_in cliddr,servddr;
	char *ip = "127.0.0.1";
	char *servip = "10.40.55.41";
	char buf[1000] = {0};
	
	cliddr.sin_family = AF_INET;
	Inet_pton(AF_INET,ip,&cliddr.sin_addr);
	//����˿�
	cliddr.sin_port = htons(0);
	
	fd = Socket(AF_INET,SOCK_STREAM,0);
	//Bind(fd,(struct sockaddr *)&cliddr,sizeof(cliddr));

	servddr.sin_family = AF_INET;
	Inet_pton(AF_INET,servip,&servddr.sin_addr);
	servddr.sin_port = htons(31161);
	
	Connect(fd,(struct sockaddr *)&servddr,sizeof(servddr));
	
	while(fgets(buf,DATA_MAX_LEN,stdin) !=  NULL)
	{
		buf[strlen(buf) -1] = 0;//�����س�
		Send(fd,buf,strlen(buf),0);
		int n =Recv(fd,buf,sizeof(buf),0);
		buf[n] = 0;
		printf("from server:%s\n",buf);
	}
	
	Close(fd);
	
}


int main()
{
	creat_client();
	exit(0);
	return 0;
}


