#pragma once
#include<iostream>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h> 
using namespace std;

class Ma_String
{
public:
	//构造时加入字符串
	Ma_String(const char* sz = nullptr);
	//构造时加入同类型
	Ma_String(const Ma_String& str);
	//析构时释放内存
	~Ma_String();
	//返回字符串
	char* GetBuffer();
	//返回字符串长度
	size_t GetLen();
	//判断是否为空
	bool IsEmpty()const; 
	//清空
	void Clear(); 
	//字符串赋值
	void SetBuffer(const char* sz);
public:
	//拼接字符串
	Ma_String& Append(const char* sz);
	Ma_String& Append(const Ma_String& str);
	Ma_String& Append(int n, int nRadix = 10);
	Ma_String& Append(float f);
	Ma_String& Append(double dbl);
	Ma_String& Append(char ch);
public:
	//查找
	size_t Find(const char* sz, size_t nBegin = 0); //从nBegin开始
	size_t Find(const Ma_String& str, size_t nBegin = 0);

public:
	//转大小写
	Ma_String& ToUpper();//转大写
	Ma_String& ToLower();//转小写
public:
	//转数值
	size_t ToInt(int nRadix = 10);
	float ToFloat();
	double ToDouble();
public:
	//格式化
	Ma_String& Formate(const char* szFmt, ...);
public:
	//运算符重载
	char& operator[](int n);
	Ma_String operator=(const char* sz);
	Ma_String operator=(const Ma_String& str);
	Ma_String operator+=(const char* sz);
	bool operator==(const char* sz);
	bool operator!=(const char* sz);
private:




private:
	char* m_sz = nullptr; //存储字符串的缓冲区
	size_t m_nLen = 0; //字符串长度



};

