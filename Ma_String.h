#pragma once
#include<iostream>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h> 
using namespace std;

class Ma_String
{
public:
	//����ʱ�����ַ���
	Ma_String(const char* sz = nullptr);
	//����ʱ����ͬ����
	Ma_String(const Ma_String& str);
	//����ʱ�ͷ��ڴ�
	~Ma_String();
	//�����ַ���
	char* GetBuffer();
	//�����ַ�������
	size_t GetLen();
	//�ж��Ƿ�Ϊ��
	bool IsEmpty()const; 
	//���
	void Clear(); 
	//�ַ�����ֵ
	void SetBuffer(const char* sz);
public:
	//ƴ���ַ���
	Ma_String& Append(const char* sz);
	Ma_String& Append(const Ma_String& str);
	Ma_String& Append(int n, int nRadix = 10);
	Ma_String& Append(float f);
	Ma_String& Append(double dbl);
	Ma_String& Append(char ch);
public:
	//����
	size_t Find(const char* sz, size_t nBegin = 0); //��nBegin��ʼ
	size_t Find(const Ma_String& str, size_t nBegin = 0);

public:
	//ת��Сд
	Ma_String& ToUpper();//ת��д
	Ma_String& ToLower();//תСд
public:
	//ת��ֵ
	size_t ToInt(int nRadix = 10);
	float ToFloat();
	double ToDouble();
public:
	//��ʽ��
	Ma_String& Formate(const char* szFmt, ...);
public:
	//���������
	char& operator[](int n);
	Ma_String operator=(const char* sz);
	Ma_String operator=(const Ma_String& str);
	Ma_String operator+=(const char* sz);
	bool operator==(const char* sz);
	bool operator!=(const char* sz);
private:




private:
	char* m_sz = nullptr; //�洢�ַ����Ļ�����
	size_t m_nLen = 0; //�ַ�������



};

