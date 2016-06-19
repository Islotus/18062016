 ///
 /// @file    Singleton2.cc
 /// @author  Islotus(2791201278@qq.com)
 /// @date    2016-06-19 00:49:13
 ///
#include "Singleton2.h"

Singleton* Singleton::_pInstance = NULL;  //此时线程安全
pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

Singleton* Singleton::getInstance()
{
	pthread_once(&_once, &Singleton::init);  //注册一次，整个函数执行期间值执行一次
	return _pInstance;
}

void Singleton::init()
{
	::atexit(&Singleton::destroy);  //函数注册几次，在程序退出时执行几次注册的函数
	if(_pInstance == NULL)
		_pInstance = new Singleton;
}

void Singleton::destroy()
{
	if(_pInstance != NULL)
		delete _pInstance;
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

	return 0;
}
 
