#define NUM1 128
#define NUM2 50

class CBook
{
public:
	CBook(){}
	CBook(char* cName,char* cIsbn,char* cPrice,char* cAuthor);
	~CBook(){}
public:
	char* GetName();               //获取图书名称
	void  SetName(char* cName);    //设置图书名称
	char* GetIsbn();               //获取图书ISBN编号
	void  SetIsbn(char* cIsbn);    //设置图示ISBN编号
	char* GetPrice();			   //获取图书价格
	void  SetPrice(char* cPrice);  //设置图书价格
	char* GetAuthor();			   //获取图书作者
	void  SetAuthor(char* cAuthor);//设置图书作者

	void  WriteData();
	void  DeleteData(int iCount);
	void  GetBookFromFile(int iCount);
protected:
	char m_cName[NUM1];
	char m_cIsbn[NUM1];
	char m_cPrice[NUM2];
	char m_cAuthor[NUM2];
};
