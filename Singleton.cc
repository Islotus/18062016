 ///
 /// @file    Singleton.cc
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-18 23:36:16
 ///

#include "Singleton.h"
#include <stdio.h>

//Singleton* Singleton::_pInstance = NULL;  //非线程安全
Singleton* Singleton::_pInstance = getInstance();  //线程安全
Singleton::AutoRelease Singleton::_autoRelease;  //创建自动释放内存子类AutoRelease对象

Singleton* Singleton::getInstance()
{
	if(_pInstance == NULL)
		_pInstance = new Singleton;  //在类里面进行调用
	return _pInstance;
}

Singleton::Singleton()
{
	cout << "Singleton()" << endl;
}

Singleton::~Singleton()
{
	cout << "~Singleton()" << endl;
}

int main()
{
	Singleton* p1 = Singleton::getInstance();
	Singleton* p2 = Singleton::getInstance();

	printf("p1 = %p\n", p1);
	printf("p2 = %p\n", p2);

	cout << sizeof(Singleton) << endl;

	return 0;

}

