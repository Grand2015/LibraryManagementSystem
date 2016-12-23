#include"Book.h"
#include<string>
#include<fstream>
#include<iostream>
#include<iomanip>

using namespace std;

CBook::CBook(char* cName, char* cIsbn,char* cPrice,char* cAuthor)
{
	strncpy(m_cName,cName,NUM1);
	strncpy(m_cIsbn,cIsbn,NUM1);
	strncpy(m_cPrice,cPrice,NUM2);
	strncpy(m_cAuthor,cAuthor,NUM2);
}

char* CBook::GetName()
{
	return m_cName;
}

void CBook::SetName(char* cName)
{
	
	strncpy(m_cName,cName,NUM1);
}

char* CBook::GetIsbn()
{
	return m_nIsbn;
}

void CBook::SetIsbn(char* cIsbn)
{
	strncpy(m_cIsbn,cIsbn,NUM1);
}

char* CBook::GetPrice()
{
	return m_cPrice;
}

void CBook::SetPrice(char* cPrice)
{
	strncpy(m_cPrice,cPrice,NUM2);
}

char* CBook::GetAuthor()
{
	return m_cAuthor;
}

void CBook::SetAuthor(char* cAuthor)
{
	strncpy(m_cAuthor,cAuthor,NUM2);
}

//WirteData function 
void CBook::WirteData()
{
	ofstream ofile;
	ofile.open("book.dat",ios::binary|ios::app);
	try
	{
		ofile.write(m_cName,NUM1);
		ofile.write(m_cIsbn,NUM1);
		ofile.write(m_cPrice,NUM2);	
		ofile.write(m_cAuthor,NUM2);
	}
	catch(...)
	{
		throw"file error occurred";
		ofile.close();
	}
	ofile.close();
}

void main()
{
	return 0;
}
