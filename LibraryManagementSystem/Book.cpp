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
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];

	cout << "请输入书名" << endl;
	cin >> inName;
	cout << "请输入Isbn" << endl;
	cin >> inIsbn;
	cout << "请输入价格" << endl;
	cin >> inPrice;
	cout << "请输入作者" << endl;
	cin >> inAuthor;

	CBook book(inName, inIsbn, inPrice, inAuthor);
	book.WriteData();
	ClearScreen();
	cout << "添加成功" << endl;
	WaitUser();
}

//GetFileLength function
long GetFileLength(ifstream &ifs)
{
	long tmppos;
	long respos;
	tmppos = (long)ifs.tellg();
	ifs.seekg(0, ios::end);
	respos = (long)ifs.tellg();
	ifs.seekg(tmppos, ios::beg);
	return respos;
}

//ViewData function
void ViewData(int iSelPage=1)
{
	int  iPage      = 0;
	int  iCurPage   = 0;
	int  iDataCount = 0;
	char inName[NUM1];
	char inIsbn[NUM1];
	char inPrice[NUM2];
	char inAuthor[NUM2];
	bool bIndex = false;
	int iFileLength;
	iCurPage = iSelPage;
	ifstream ifile;
	ifile.open("book.dat", ios::binary);
	iFileLength = GetFileLength(ifile);
	iDataCount = iFileLength / (NUM1 + NUM1 + NUM2 + NUM2);
	if (iDataCount >= 1)
		bIndex = true;
	iPage = iDataCount / 20 + 1;
	ClearScreen();
	cout << "共有记录" << iDataCount << "";
	cout << "共有页数" << iPage << "";
	cout << "当前页数" << iCurPage << "";
	cout << "n显示下一页m返回" << endl;
	cout << setw(5) << "Index";
	cout << setw(22) << "Name"<<setw(22)<<"Isbn";
	cout << setw(15) << "Price" << setw(22) << "Author";
	try
	{
		ifile.seekg((iCurPage - 1) * 20 * (NUM1 + NUM1 + NUM2 + NUM2), ios::beg);
		if (!ifile.fail())
		{
			for (int i = 1; i < 21; i++)
			{
				memset(inName, 0, 128);
				memset(inIsbn, 0, 128);
				memset(inPrice, 0, 50);
				memset(inAuthor, 0, 50);

				if (bIndex)
					cout << setw(3) << ((iCurPage - 1) * 20 + i);
				ifile.read(inName, NUM1);
				cout << setw(24) << inName;
				ifile.read(inIsbn, NUM1);
				cout << setw(24) << inIsbn;
				ifile.read(inPrice, NUM2);
				cout << setw(24) << inPrice;
				ifile.read(inAuthor, NUM2);
				cout << setw(24) << inAuthor;
				cout << endl;

				if (ifile.tellg() < 0)
					bIndex = false;
				else
					bIndex = true;
			}
		}
	}
	catch(...)
	{
		cout << "throw file exceptio" << endl;
		throw "file error occurred";
		ifile.close();
	}
	if (iCurPage < iPage)
	{
		iCurPage++;
		//WaitUser();
		WaitUser();
	}
	else
		WaitUser();
	ifile.close();
	system("pause");
}

//DeleteBookFromFile function
void DeleteBookFromFile()
{
	int iDelCount;
	cout << "Input delete index" << endl;
	cin >> iDelCount;
	CBook tmpbook;
	tmpbook.DeleteData(iDelCount);
	cout << "删除完成" << endl;
	WaitUser();
}

//main function
int main()
{
	SetScreenGrid();
	//SetsysCaptionStyle1();
	SetsysCaptionStyle2("图书管理");
	//ShowWelcome();
	while (1)
	{
		SetsysCaptionStyle2("图书管理");

		ClearScreen();
		ShowWelcome();
		ShowRootMenu();
		//system("pause");
		switch (GetSelect())
		{
		case 1:
			ClearScreen();

			SetsysCaptionStyle2("添加图书");
			ClearScreen();
			GuideInput();
			WaitUser();
			break;
		case 2:
			ClearScreen();
			ViewData();
			//system("pause");

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
