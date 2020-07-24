#pragma once

#include"pch.h"
#include"Task.h"

/**
线程池类
**/
class ThreadPool
{
private:
	std::queue<std::shared_ptr<Task>> m_taskQueue; //任务队列
	std::list<std::shared_ptr<std::thread>> m_threadList;	//线程列表
	static bool m_shutdown;   //停止获取任务标志
	size_t m_ThreadNum;   //线程池中已经启动的线程数
	std::mutex m_mutex;	//互斥锁
	size_t m_maxTaskNum;	//最大任务数
	std::condition_variable m_notEmpty;	//条件变量

protected:


public:
	//构造函数，参数为线程数，最大任务队列数
	ThreadPool(size_t threadNum = std::thread::hardware_concurrency(),size_t maxTask=100) :m_ThreadNum(threadNum), m_maxTaskNum(maxTask) {};
	~ThreadPool();
	bool AddTask(std::shared_ptr<Task> ptask);  //添加任务
	void StopAll();  //停止全部线程池中的线程
	void Init();   //创建线程池中的线程
	void Run();		//线程自动获取任务并执行
};