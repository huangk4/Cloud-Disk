#pragma once
#include"pch.h"
#include"Task.h"

using namespace std;

void TestTask::Run()
{
	cout <<this_thread::get_id()<< "£º123\n";
	Sleep(rand()%2000+500);
}