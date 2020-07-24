#pragma once




class Task
{
public:
	Task(void* data=nullptr) :m_pdata(data) {};
	~Task() {};
	virtual void Run()=0;	
protected:
	void *m_pdata;
};



class TestTask :public Task
{
public:
	TestTask(void* data = nullptr) :Task(data) {};
	~TestTask() {};
	void Run();
};

