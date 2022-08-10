#include "Ma_String.h"

//构造时加入字符串
Ma_String::Ma_String(const char* sz)
{
	if (sz == nullptr)
	{
		Clear();
	}
	else
	{
		SetBuffer(sz);
	}
}
//构造时加入自己
Ma_String::Ma_String(const Ma_String& str)
{
	if (str.m_sz != nullptr)
	{
		SetBuffer(str.m_sz);
	}
}
//析构时释放内存
Ma_String::~Ma_String()
{
	Clear();
}
//返回字符串
char* Ma_String::GetBuffer()
{
	return m_sz;
}
//返回字符串长度
size_t Ma_String::GetLen()
{
	return m_nLen;
}
//判断是否为空
bool Ma_String::IsEmpty() const
{
	return m_sz == nullptr;
}
//清空
void Ma_String::Clear()
{
	if (m_sz == nullptr)
	{
		return;
	}
	delete[]m_sz;
	m_sz = nullptr;
	m_nLen = 0;
}
//字符串赋值
void Ma_String::SetBuffer(const char* sz)
{
	Clear();
	m_nLen = strlen(sz);
	m_sz = new char[m_nLen + 1];
	if (m_sz == nullptr)
	{
		m_nLen = 0;
		return;
	}
	strcpy_s(m_sz, m_nLen + 1, sz);
}


//字符串拼接
Ma_String& Ma_String::Append(const char* sz)
{
	//是否为空
	if (sz == nullptr)
	{
		return *this;
	}
	//申请新的内存
	size_t nNewLen = m_nLen + strlen(sz);
	char* szNew = new char[nNewLen + 1]();
	if (szNew == nullptr)
	{
		return *this;
	}
	//拷贝自己
	if (m_sz != nullptr)
	{
		memcpy(szNew, m_sz, m_nLen);
	}
	//拷贝目标
	memcpy(szNew + m_nLen, sz, strlen(sz));
	//清空自己
	Clear();
	//重置指针和长度
	m_sz = szNew;
	m_nLen = nNewLen;
	return *this;
}
//字符串拼接同类
Ma_String& Ma_String::Append(const Ma_String& str)
{
	return Append(str.m_sz);
}
//字符串拼接int值,含进制
Ma_String& Ma_String::Append(int n, int nRadix)
{
	char szBuff[33] = {};
	_itoa_s(n, szBuff, sizeof(szBuff), nRadix);
	return Append(szBuff);
}
//字符串拼接float
Ma_String& Ma_String::Append(float f)
{
	char szBuff[32] = {};
	sprintf_s(szBuff, sizeof(szBuff), "%f", f);
	return Append(szBuff);
}
//字符串拼接double
Ma_String& Ma_String::Append(double dbl)
{
	char szBuff[64] = {};
	sprintf_s(szBuff, sizeof(szBuff), "%lf", dbl);
	return Append(szBuff);
}
//字符串拼接char
Ma_String& Ma_String::Append(char ch)
{
	char szBuff[2] = { };
	szBuff[0] = ch;
	return Append(szBuff);
}

//字符串正向查找
size_t Ma_String::Find(const char* sz, size_t nBegin)
{
	char* pszTemp = strstr(m_sz + nBegin, sz);
	if (pszTemp == NULL)
	{
		return -1;
	}
	return m_nLen - strlen(pszTemp);
}
//同类正向查找
size_t Ma_String::Find(const Ma_String& str, size_t nBegin)
{
	char* pszTemp = strstr(m_sz + nBegin, str.m_sz);
	if (pszTemp == NULL)
	{
		return -1;
	}
	return m_nLen - strlen(pszTemp);
}



//运算符重载[]
char& Ma_String::operator[](int n)
{
	if ((n < 0) || (n > m_nLen + 1))
	{
		return m_sz[0];
	}
	return m_sz[n];
}
//运算符重载=
Ma_String Ma_String::operator=(const char* sz)
{
	SetBuffer(sz);
	return *this;
}
Ma_String Ma_String::operator=(const Ma_String& str)
{
	SetBuffer(str.m_sz);
	return *this;
}
//运算符重载+=
Ma_String Ma_String::operator+=(const char* sz)
{
	Append(sz);
	return *this;
}
//运算符重载==
bool Ma_String::operator==(const char* sz)
{
	if (strcmp(m_sz, sz) == 0)
	{
		return true;
	}
	return false;
}
//运算符重载!=
bool Ma_String::operator!=(const char* sz)
{
	if (strcmp(m_sz, sz) == 0)
	{
		return false;
	}
	return true;
}

//转大写
Ma_String& Ma_String::ToUpper()
{
	if (m_nLen == 0)
	{
		return *this;
	}
	Ma_String temp(m_sz);
	Clear();
	for (size_t i = 0; i < temp.m_nLen; i++)
	{
		if (temp.m_sz[i] >= 'a' && temp.m_sz[i] <= 'z')
		{
			temp.m_sz[i] -= 32;
		}
	}
	SetBuffer(temp.m_sz);
	return *this;
}
//转小写
Ma_String& Ma_String::ToLower()
{
	if (m_nLen == 0)
	{
		return *this;
	}
	Ma_String temp(m_sz);
	Clear();
	for (size_t i = 0; i < temp.m_nLen; i++)
	{
		if (temp.m_sz[i] >= 'A' && temp.m_sz[i] <= 'Z')
		{
			temp.m_sz[i] += 32;
		}
	}
	SetBuffer(temp.m_sz);
	return *this;
}
//转int
size_t Ma_String::ToInt(int nRadix)
{
	char* p = nullptr;
	return strtol(m_sz, &p, nRadix);
}
//转float
float Ma_String::ToFloat()
{
	return (float)atof(m_sz);
}
//转double
double Ma_String::ToDouble()
{
	return atof(m_sz);
}

//格式化
Ma_String& Ma_String::Formate(const char* szFmt, ...)
{
	Clear();
	char szBuffer[100] = { 0 };
	va_list valist;
	va_start(valist, szFmt);
	vsprintf_s(szBuffer, szFmt, valist);
	va_end(valist);
	m_nLen = strlen(szBuffer);
	m_sz = new char[m_nLen + 1]();
	memcpy(m_sz, szBuffer, m_nLen);
	return *this;
}

