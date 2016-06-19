 ///
 /// @file    Singleton2.h
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-19 00:44:32
 ///

//单例模式（自动释放内存）（平台相关）
//用到两个函数：pthread_once(),atexit()

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;

class Singleton
{
public:
	static Singleton* getInstance();
	static void init();
	static void destroy();
private:
	Singleton();
	~Singleton();
private:
	static Singleton* _pInstance;
	static pthread_once_t _once;
};

#endif
 
