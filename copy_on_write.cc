 ///
 /// @file    cow_string.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-06-17 16:05:23
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

class String
{
private:
	class CharProxy
	{//23种设计模式之代理模式
	public:
		CharProxy(String & str, int idx);
		
		char & operator=(char ch);

		operator char()
		{	//类型转换函数,由CharProxy转向char
			return _str._pstr[_idx];
		}

		//friend ostream & operator<<(ostream & os, const CharProxy &rhs);
	private:
		String & _str;
		int _idx;
	};
	//friend ostream & operator<<(ostream & os, const CharProxy & rhs);
public:
	String();
	String(const char * pstr);
	String(const String & rhs);
	String & operator=(const String & rhs);
	~String();

	int useCount()
	{	return _pstr[length() + 1];	}

	int length()
	{	return strlen(_pstr);	}


	CharProxy operator[](int idx);//返回CharProxy对象
	char & operator[](int idx) const;
private:
	void initRefcount()
	{	_pstr[length() + 1] = 1; }

	void increaseRefcount()
	{	++_pstr[length() + 1];	}

	void decreaseRefcount()
	{	--_pstr[length() + 1];	}
private:
	char * _pstr;
};

String::String()
: _pstr(new char[2])
{
	cout << "String()" << endl;
	initRefcount();
}

String::String(const char * pstr)
{
	int len = strlen(pstr);
	_pstr = new char[len + 2];
	strcpy(_pstr, pstr);
	initRefcount();//将引用计数设置为1
	cout << "String(const char *)" << endl;
}

String::String(const String & rhs)
: _pstr(rhs._pstr)
{
	increaseRefcount();
	cout << "String(const String & rhs)" << endl;
}

String & String::operator=(const String & rhs)
{
	if(this != &rhs)
	{
		decreaseRefcount();//将原来的引用计数减1
		if(useCount() == 0)
		{	
			delete [] _pstr;
		}
		_pstr = rhs._pstr;//进行浅拷贝
		increaseRefcount();
	}
	return * this;
}

String::~String()
{
	decreaseRefcount();
	if(useCount() == 0)
	{
		delete [] _pstr;
		cout << "~String()" << endl;
	}
}

//operator[]() 不能区分读操作还是写操作
char & String::operator[](int idx) const
{
	cout << "operator[](int) const" << endl;
	return _pstr[idx];
}

String::CharProxy String::operator[](int idx) 
{
	return CharProxy(*this, idx);
}
		
String::CharProxy::CharProxy(String & str, int idx)
: _str(str)
, _idx(idx)
{
}
	
char & String::CharProxy::operator=(char ch)
{
	if(_idx >=0 && _idx < _str.length())
	{
		if(_str.useCount() == 1)//1.当对象没有共享内存时
		{
			_str._pstr[_idx] = ch;//进行修改
			return _str._pstr[_idx];
		}
		_str.decreaseRefcount();//2.当对象共享内存时
		char * ptmp = new char[_str.length() + 2];
		strcpy(ptmp, _str._pstr);//进行复制
		_str._pstr = ptmp;
		_str.initRefcount();
		_str._pstr[_idx] = ch;//进行修改
		return _str._pstr[_idx];
	}
	else
	{
		static char nullchar = '\0';
		cout << "下标越界" << endl;
		return nullchar;
	}
}

#if 0
ostream & operator<<(ostream & os, const String::CharProxy & rhs)
{
	os << rhs._str._pstr[rhs._idx];
	return os;
}
#endif
	
int main(void)
{
	String s1 = "hello,world";
	String s2 = s1;
	String s3 = s2;

	cout << "s1' useCnt = " << s1.useCount() << endl;
	cout << "s2' useCnt = " << s2.useCount() << endl;
	cout << "s3' useCnt = " << s3.useCount() << endl;
	cout << endl;


	String s4 = "shenzhen";
	cout << "s4' useCnt = " << s4.useCount() << endl;
	cout << endl;
	s4 = s2;
	cout << "s1' useCnt = " << s1.useCount() << endl;
	cout << "s2' useCnt = " << s2.useCount() << endl;
	cout << "s3' useCnt = " << s3.useCount() << endl;
	cout << "s4' useCnt = " << s4.useCount() << endl;
	cout << endl;

	//写操作时会发生写时复制
	s4[0] = 'X';
	cout << "s1' useCnt = " << s1.useCount() << endl;
	cout << "s2' useCnt = " << s2.useCount() << endl;
	cout << "s3' useCnt = " << s3.useCount() << endl;
	cout << "s4' useCnt = " << s4.useCount() << endl;
	cout << endl;

	//读操作时也会发生复制
	cout << s3[0] << endl;
	cout << "s1' useCnt = " << s1.useCount() << endl;
	cout << "s2' useCnt = " << s2.useCount() << endl;
	cout << "s3' useCnt = " << s3.useCount() << endl;
	cout << endl;

	return 0;

}
