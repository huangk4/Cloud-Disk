

#include"pch.h"
#include"Session.h"
#include"MD5.h"


using std::ios;
using std::ofstream;
using std::ifstream;
using std::ios_base;
using std::filebuf;




void showinfo(int connfd, char recvline[])//������ʾ������Ϣ
{
	std::cout << "���յ����� id:" << connfd << " ����Ϣ" << recvline << std::endl;
	std::cout << "������ظ��� id:" << connfd << " ����Ϣ\n";

}

void Session::Run()
{
	Commute();
	SaveFile();
}

//g,s,d,t,r,c
//get,send,delete,transform,recover��cancle
//Ӧ��ֻ���տͻ��˴����Ļ�ȡ�����͡�ɾ����������ȡ����Ϣ
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

		std::string recvstr=recvline.get();
		if (recvlen == 33)
		{
			std::string hash=recvstr.substr(1,32);
			if (recvstr[0] == 'g')
			{
				//����hashȷ���ļ��Ƿ����
				if (Checkhash(hash))
				{
					SendFile();
				}
			}
		}
		
		//����ļ������ڻ�����Ϣ�������͸��ͻ���������Ϣ
		if (true)
		{
			std::string t;
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
}


//g,s,d,t,r,c
//get,send,delete,transform,recover��cancle
//Ӧ��ֻ���տͻ��˴������ļ���Ϣ
void Session::SaveFile(size_t pos)
{
	string path=g_savepath+"test.png";
	ofstream saveF(path, ios::app|ios::binary);
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


//g,s,d,t,r,c
//get,send,delete,transform,recover��cancle
//Ӧ��ֻ�����ļ���Ϣ
void Session::SendFile(size_t pos)
{
	int send_len = 0;
	std::string senddata;
	std::string path = "E:\\files\\�����ļ�\\picture\\favor\\3ye.png";
	std::ifstream mf(path, ios::binary | ios::in);
	if (mf.fail())
	{
		std::cout << "�ļ��򿪴���\n";
		std::cout << GetLastError();
	}
	filebuf* pbuf = mf.rdbuf();
	int size = pbuf->pubseekoff(0, ios_base::end, ios_base::in);
	pbuf->pubseekpos(0, ios_base::in);
	char* buf = new char[size];
	pbuf->sgetn(buf, size);
	mf.close();

	send_len = send(m_connfd, buf, size, 0);
	send(m_connfd,buf, 0, 0);
	if (send_len < 0) {
		std::cout << "����ʧ�ܣ�\n" ;
	}
	//������Ϲر�����
	closesocket(m_connfd);
}

void Session::Savehash()
{
	std::string path2 = "E:\\files\\�����ļ�\\test\\shash.txt";
	MD5 md5;
	std::string hash = md5.toString();
	ofstream hashf(path2, ios::out);
	hashf << hash;
	hashf.close();
}


bool Session::Checkhash(std::string hash)
{
	std::string path2 = "E:\\files\\�����ļ�\\test\\shash.txt";
	MD5 md5;
	std::string fhash = md5.toString();
	ifstream hashf(path2, ios::in);
	std::string check;
	hashf>>check;
	hashf.close();
	if (check == hash)
		return true;
	return false;
}