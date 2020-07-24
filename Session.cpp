

#include"pch.h"
#include"Session.h"


using std::ios;

void showinfo(int connfd, char recvline[], std::string& t)//������ʾ������Ϣ
{
	std::cout << "���յ����� id:" << connfd << " ����Ϣ" << recvline << std::endl;
	std::cout << "������ظ��� id:" << connfd << " ����Ϣ\n";
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
			std::cout << "���ܿͻ�����Ϣ����\n";
			break;
		}
		std::string t;
		showinfo(m_connfd, recvline.get(), t);
		int sendlen = t.length();
		strcpy_s(sendline.get(), m_n, t.c_str());
		int send_len = send(m_connfd, sendline.get(), sendlen, 0);
		if (send_len < 0)
		{
			std::cout << "������Ϣ����\n";
			break;
		}
	}
}

void Session::SaveFile()
{
	std::ofstream saveF(g_savepath, ios::app|ios::binary);
	if (saveF.fail())
	{
		std::cout<<"���ļ�����\n";
		std::cout<<GetLastError();
	}
	std::unique_ptr<char> recvline(new char[m_n]);
	while (true)
	{
		memset(recvline.get(), 0, m_n);
		int recvlen = recv(m_connfd, recvline.get(), m_n, 0);
		if (recvlen < 0)
		{
			std::cout << "���ܿͻ�����Ϣ����\n";
			break;
		}
		if(recvlen==0)
			break;
		saveF.write(recvline.get(),recvlen);
	}
	saveF.close();
}