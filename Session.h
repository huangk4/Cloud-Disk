#pragma once
#include"Task.h"
class Session :public Task
{
private:
	int m_connfd;
	int m_n;//��������С
	struct sockaddr_in m_servaddr;
public:
	Session(int connfd, int n = 65535) :m_connfd(connfd), m_n(n) {}
	void Run();
	void Commute();//ͨ��
	void SaveFile();//�����ļ�
};
