#pragma once
#include"Task.h"
class Session :public Task
{
private:
	int m_connfd;
	int m_n;//��������С
	struct sockaddr_in m_servaddr;
	void Savehash();	
	bool Checkhash(std::string hash);
	bool Checkrecover(std::string hash);
	void Commute();//ͨ��,��¼����¼
	void SaveFile(size_t pos=0);//�����ļ�������
	void SendFile(size_t pos=0);//�����ļ�
public:
	Session(int connfd, int n = 65535) :m_connfd(connfd), m_n(n) {}
	void Run();
};
