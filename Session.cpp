

#include"pch.h"
#include"Session.h"


using std::ios;

void showinfo(int connfd, char recvline[], std::string& t)//用于显示交互信息
{
	std::cout << "接收到来自 id:" << connfd << " 的信息" << recvline << std::endl;
	std::cout << "请输入回复给 id:" << connfd << " 的信息\n";
	std::cin >> t;

}

void Session::Run()
{
	SaveFile();

}

void Session::Commute()
{
	std::unique_ptr<char[]> recvline(new char[m_n]);
	std::unique_ptr<char[]> sendline(new char[m_n]);
	while (true)
	{
		memset(recvline.get(), 0, m_n);
		memset(sendline.get(), 0, m_n);
		int recvlen = recv(m_connfd, recvline.get(), m_n, 0);
		if (recvlen < 0)
		{
			std::cout << "接受客户端信息错误\n";
			break;
		}
		std::string t;
		showinfo(m_connfd, recvline.get(), t);
		int sendlen = t.length();
		strcpy_s(sendline.get(), m_n, t.c_str());
		int send_len = send(m_connfd, sendline.get(), sendlen, 0);
		if (send_len < 0)
		{
			std::cout << "发送信息错误\n";
			break;
		}
	}
}

void Session::SaveFile()
{
	std::ofstream saveF(g_savepath, ios::app|ios::binary);
	if (saveF.fail())
	{
		std::cout<<"打开文件错误\n";
		std::cout<<GetLastError();
	}
	std::unique_ptr<char> recvline(new char[m_n]);
	while (true)
	{
		memset(recvline.get(), 0, m_n);
		int recvlen = recv(m_connfd, recvline.get(), m_n, 0);
		if (recvlen < 0)
		{
			std::cout << "接受客户端信息错误\n";
			break;
		}
		if(recvlen==0)
			break;
		saveF.write(recvline.get(),recvlen);
	}
	saveF.close();
}