#pragma once
#include"Task.h"
class Session :public Task
{
private:
	int m_connfd;
	int m_n;//缓冲区大小
	struct sockaddr_in m_servaddr;
	void Savehash();	
	bool Checkhash(std::string hash);
	bool Checkrecover(std::string hash);
	void Commute();//通信,登录并记录
	void SaveFile(size_t pos=0);//接受文件并保存
	void SendFile(size_t pos=0);//发送文件
public:
	Session(int connfd, int n = 65535) :m_connfd(connfd), m_n(n) {}
	void Run();
};
