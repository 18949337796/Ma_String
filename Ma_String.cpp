#include "Ma_String.h"

//����ʱ�����ַ���
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
//����ʱ�����Լ�
Ma_String::Ma_String(const Ma_String& str)
{
	if (str.m_sz != nullptr)
	{
		SetBuffer(str.m_sz);
	}
}
//����ʱ�ͷ��ڴ�
Ma_String::~Ma_String()
{
	Clear();
}
//�����ַ���
char* Ma_String::GetBuffer()
{
	return m_sz;
}
//�����ַ�������
size_t Ma_String::GetLen()
{
	return m_nLen;
}
//�ж��Ƿ�Ϊ��
bool Ma_String::IsEmpty() const
{
	return m_sz == nullptr;
}
//���
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
//�ַ�����ֵ
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


//�ַ���ƴ��
Ma_String& Ma_String::Append(const char* sz)
{
	//�Ƿ�Ϊ��
	if (sz == nullptr)
	{
		return *this;
	}
	//�����µ��ڴ�
	size_t nNewLen = m_nLen + strlen(sz);
	char* szNew = new char[nNewLen + 1]();
	if (szNew == nullptr)
	{
		return *this;
	}
	//�����Լ�
	if (m_sz != nullptr)
	{
		memcpy(szNew, m_sz, m_nLen);
	}
	//����Ŀ��
	memcpy(szNew + m_nLen, sz, strlen(sz));
	//����Լ�
	Clear();
	//����ָ��ͳ���
	m_sz = szNew;
	m_nLen = nNewLen;
	return *this;
}
//�ַ���ƴ��ͬ��
Ma_String& Ma_String::Append(const Ma_String& str)
{
	return Append(str.m_sz);
}
//�ַ���ƴ��intֵ,������
Ma_String& Ma_String::Append(int n, int nRadix)
{
	char szBuff[33] = {};
	_itoa_s(n, szBuff, sizeof(szBuff), nRadix);
	return Append(szBuff);
}
//�ַ���ƴ��float
Ma_String& Ma_String::Append(float f)
{
	char szBuff[32] = {};
	sprintf_s(szBuff, sizeof(szBuff), "%f", f);
	return Append(szBuff);
}
//�ַ���ƴ��double
Ma_String& Ma_String::Append(double dbl)
{
	char szBuff[64] = {};
	sprintf_s(szBuff, sizeof(szBuff), "%lf", dbl);
	return Append(szBuff);
}
//�ַ���ƴ��char
Ma_String& Ma_String::Append(char ch)
{
	char szBuff[2] = { };
	szBuff[0] = ch;
	return Append(szBuff);
}

//�ַ����������
size_t Ma_String::Find(const char* sz, size_t nBegin)
{
	char* pszTemp = strstr(m_sz + nBegin, sz);
	if (pszTemp == NULL)
	{
		return -1;
	}
	return m_nLen - strlen(pszTemp);
}
//ͬ���������
size_t Ma_String::Find(const Ma_String& str, size_t nBegin)
{
	char* pszTemp = strstr(m_sz + nBegin, str.m_sz);
	if (pszTemp == NULL)
	{
		return -1;
	}
	return m_nLen - strlen(pszTemp);
}



//���������[]
char& Ma_String::operator[](int n)
{
	if ((n < 0) || (n > m_nLen + 1))
	{
		return m_sz[0];
	}
	return m_sz[n];
}
//���������=
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
//���������+=
Ma_String Ma_String::operator+=(const char* sz)
{
	Append(sz);
	return *this;
}
//���������==
bool Ma_String::operator==(const char* sz)
{
	if (strcmp(m_sz, sz) == 0)
	{
		return true;
	}
	return false;
}
//���������!=
bool Ma_String::operator!=(const char* sz)
{
	if (strcmp(m_sz, sz) == 0)
	{
		return false;
	}
	return true;
}

//ת��д
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
//תСд
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
//תint
size_t Ma_String::ToInt(int nRadix)
{
	char* p = nullptr;
	return strtol(m_sz, &p, nRadix);
}
//תfloat
float Ma_String::ToFloat()
{
	return (float)atof(m_sz);
}
//תdouble
double Ma_String::ToDouble()
{
	return atof(m_sz);
}

//��ʽ��
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

