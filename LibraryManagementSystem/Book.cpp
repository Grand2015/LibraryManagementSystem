/***********************************************************/
//
//
//
/**********************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include "Book.h"
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <cstdio>
//win32下面包含conio.h，lnuix系统下面包含curses.h
#include <conio.h>
//#include <curses.h>

#define CMD_COLS 80
#define CMD_LINES 25
//#define NUM1 128
//#define NUM2 50

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
	return m_cIsbn;
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
void CBook::WriteData()
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

//GetBookFromFile Function
void CBook::GetBookFromFile(int iCount)
{
	char cName[NUM1];
	char cIsbn[NUM1];
	char cPrice[NUM2];
	char cAuthor[NUM2];
	ifstream ifile;
	ifile.open("Book.dat",ios::binary);
	try
	{
		ifile.seekg(iCount*(NUM1+NUM1+NUM2+NUM2),ios::beg);
		ifile.read(cName,NUM1);
		if(ifile.tellg()>0)
			strncpy(m_cName,cName,NUM1);
		ifile.read(cIsbn,NUM1);
		if(ifile.tellg()>0)
			strncpy(m_cIsbn,cIsbn,NUM1);
		ifile.read(cPrice,NUM2);
		if(ifile.tellg()>0)
			strncpy(m_cPrice,cPrice,NUM2);
		ifile.read(cAuthor,NUM2);
		if(ifile.tellg()>0)
			strncpy(m_cAuthor,cAuthor,NUM2);
	}
	catch(...)
	{
		throw "file error occured";
		ifile.close();
	}
	ifile.close();
}
//DeleteData function
void CBook::DeleteData(int iCount)
{
	long respos;
	int iDataCount=0;
	fstream file,tmpfile;
	ofstream ofile;
	char cTempBUf[NUM1+NUM1+NUM2+NUM2];
	file.open("book.dat",ios::binary|ios::in|ios::out);
	tmpfile.open("temp.dat",ios::binary|ios::in|ios::out|ios::trunc);
	file.seekg(0,ios::end);
	respos=(long)file.tellg();
	iDataCount=respos/(NUM1+NUM1+NUM2+NUM2);
	if(iCount<0 && iCount>iDataCount)
	{
		throw "Input number error";
	}
	else
	{
		file.seekg((iCount)*(NUM1+NUM1+NUM2+NUM2),ios::beg);
		for(int j=0;j<(iDataCount-iCount);j++)
		{
			memset(cTempBUf,0,NUM1+NUM1+NUM2+NUM2);
			file.read(cTempBUf,NUM1+NUM1+NUM2+NUM2);
			tmpfile.write(cTempBUf,NUM1+NUM1+NUM2+NUM2);
		}
		file.close();
		tmpfile.seekg(0,ios::beg);
		ofile.open("book.dat");
		ofile.seekp((iCount-1)*(NUM1+NUM1+NUM2+NUM2),ios::beg);
		for(int j=0;j<(iDataCount-iCount);j++)
		{
			memset(cTempBUf,0,NUM1+NUM1+NUM2+NUM2);
			tmpfile.read(cTempBUf,NUM1+NUM1+NUM2+NUM2);
			ofile.write(cTempBUf,NUM1+NUM1+NUM2+NUM2);
		}
	}
	tmpfile.close();
	ofile.close();
	remove("temp.dat");
}

//SetScreenGrid function
void SetScreenGrid()
{
	char sysSetBuf[80];
	sprintf(sysSetBuf,"mode con cols=%d lines=%d",CMD_COLS,CMD_LINES);
	cout<<"set screen grid"<<endl;
	system(sysSetBuf);
}

//SetSysCaption function(style 1)
void SetsysCaptionStyle1()
{
	system("title LibraryManagementSystem");
}
//SetSysCaption function(style 2)
void SetsysCaptionStyle2(const char* pText)
{
	//system("title LibraryManagementSystem");
	char sysSetBuf[80];
	sprintf(sysSetBuf, "title %s", pText);
	system(sysSetBuf);
}
//ClearSreen function
void ClearScreen()
{
	system("cls");
}

//ShowWelcome function
void ShowWelcome()
{
	for (int i = 0; i < 7; i++)
		cout << endl;
	cout << setw(55);
	cout << "**************************************" << endl;
	cout << setw(55);
	cout << "*************图书管理系统*************" << endl;
	cout << setw(55);
	cout << "**************************************" << endl;
	cout << endl;
	//cout << setfill('*') << setw(50) << "图书管理系统" << endl;
}

//ShowRootMenu function
void ShowRootMenu()
{
	cout << setw(40);
	cout << "请选择" << endl;
	cout << endl;
	cout << setw(38);
	cout << "1 添加新书" << endl;
	cout << setw(38);
	cout << "2 浏览全部" << endl;
	cout << setw(38);
	cout << "3 删除图书" << endl;
}

//WaitUser function
void WaitUser()
{	
	int ilnputPage = 0;
	cout << "enter返回主菜单 q退出" << endl;
	char buf[256];
	gets_s(buf);
	if (buf[0] == 'q')
		system("exit");
}

//GetSelect function
int GetSelect()
{
	char buf[256];
	gets_s(buf);
	return atoi(buf);
}

//GuideInput function
void GuideInput()
{

}

//ViewData function
void ViewData()
{

}

//DeleteBookFromFile function
void DeleteBookFromFile()
{


}

//main function
int main()
{
	SetScreenGrid();
	//SetsysCaptionStyle1();
	SetsysCaptionStyle2("图书管理");
	ShowWelcome();
	while (1)
	{
		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		system("pause");
		switch (GetSelect())
		{
		case 1:
			ClearScreen();
			GuideInput();
			break;
		case 2:
			ClearScreen();
			ViewData();
			break;
		case 3:
			ClearScreen();
			DeleteBookFromFile();
			break;
		default:
			break;
		}
	}
	return 0;
}
