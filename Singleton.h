 ///
 /// @file    singleton.h
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-18 23:26:21
 ///

//单例模式（完整版）类种类实现自动释放内存


#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
 
class Singleton
{
private:
	class AutoRelease  //子类AutoRelease,自动释放内存
	{
	public:
		AutoRelease()
		{
			cout << "AutoRelease()" << endl;
		}
		~AutoRelease()
		{
			cout << "~AutoRelease()" << endl;
			if(_pInstance != NULL)  //自动释放父类申请的内存
				delete _pInstance;
		}
	};

public:
	static Singleton* getInstance();
private:
	Singleton();  //constructor
	~Singleton();  //destructor
private:
	static Singleton* _pInstance;
	static AutoRelease _autoRelease;
	
};

#endif
