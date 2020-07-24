#pragma once
#include"ThreadPool.h"
#include"Task.h"
#include"MyNetwork.h"
#include"pch.h"
#include"CheckOS.h"
#include"Session.h"

#ifdef I_OS_WIN32

void InitWSA()
{
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		std::cout << "初始化套接字库失败！" << std::endl;
	}
	else {
		std::cout << "初始化套接字库成功！" << std::endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		std::cout << "套接字库版本号不符！" << std::endl;
		WSACleanup();
	}
	else {
		std::cout << "套接字库版本正确！" << std::endl;
	}
	//填充服务端地址信息
}

#endif // 

int Socket(int family, int type, int protocol)
{
	int code;
	if ((code = socket(family, type, protocol)) < 0)
	{
		print_err("socket error", code);
	}
	return code;
}

void Bind(int listenfd,SA *servaddr, socklen_t size)
{
	int code;
	if ((code=bind(listenfd, servaddr, size) )!= 0)//注意与标准库bind做区分
	{
		print_err("bind error",code);
	}
}

void Listen(int listenfd,int max)
{
	int code;
	if ((code=listen(listenfd, max)) != 0)
	{
		print_err("listen error",code);
	}
}

int Accept(SOCKET listenfd,SA *servaddr, socklen_t* len)
{
	int code;
	if ((code=accept(listenfd,servaddr,len)) < 0)
	{
		print_err("accept error", code);
	}
	return code;
}






MyNetwork::MyNetwork(int listen) :m_stop(false), m_listenNum(listen)
{
#ifdef I_OS_WIN32
	InitWSA();
#endif

	//初始化TCP套接字
	m_listenfd = Socket(AF_INET, SOCK_STREAM, 0);
	//设置网际套接字地址
	memset(&m_servaddr, 0, sizeof(m_servaddr));
	m_servaddr.sin_family = AF_INET;
	m_servaddr.sin_port = htons(1333);
	m_servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	Bind(m_listenfd, (SA*)&m_servaddr, sizeof(m_servaddr));
	//将套接字转化为监听套接字
}

MyNetwork::~MyNetwork()
{
#ifdef I_OS_WIN32
	WSACleanup();
#endif
}


void MyNetwork::Run()
{
	const int testthead = 2;
	//创建线程池
	ThreadPool threadpool(testthead, m_listenNum);
	threadpool.Init();

	Listen(m_listenfd,m_listenNum);
	while (!m_stop)
	{
		//获取通信套接字，从线程池取线程去运行
		int connfd=Accept(m_listenfd,(SA *)NULL,NULL);
		auto session=std::make_shared<Session>(connfd);
		threadpool.AddTask(session);
	}
#ifdef I_OS_WIN32
	closesocket(m_listenfd);
#endif

#ifdef I_OS_LINUX
	close(m_listenfd);
#endif
}




