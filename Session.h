#pragma once
#include"Task.h"
class Session :public Task
{
private:
	int m_connfd;
	int m_n;//缓冲区大小
	struct sockaddr_in m_servaddr;
public:
	Session(int connfd, int n = 65535) :m_connfd(connfd), m_n(n) {}
	void Run();
	void Commute();//通信
	void SaveFile();//传输文件
};
