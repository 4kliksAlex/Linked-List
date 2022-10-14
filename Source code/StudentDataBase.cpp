// StudentDataBase.cpp
#include "LinkList.h"
#include "StudentDataBase.h"
#include "Banking.h"
#include <iomanip>
#include <cstring>
#include <string>
#include <conio.h>

bool SelectUser(LinkList<Student>& link, Student& xStudent)
{
	int id;
	cout << "请输入查询的编号: ";
	cin >> id;
	
	Node<Student> *p;
	p = link.Locate(id, true);
	if (p == NULL)
	{
		cout << "没有找到编号为 " << id << " 的结点" << endl;
		return false;
	}

	cout << "找到编号为 " << id << " 的结点" << endl;
	xStudent = link.CurData();
	return true;
}


int Pos(char ch, const char *str)			// 返回指定字符ch在字符串str中的下标。不存在时返回-1
{
	int i;
	for(i=0; str[i]!='\0'; i++)
		if(ch==str[i])
			return i;
	return -1;
}


/////////////////////////////////////////


int Choice(const char *prompt, const char *options="");	// 函数声明
int Choice(const char *prompt, const char *options)		// 函数定义。输出提示信息prompt，输入选择的字符并返回。
{
	int key;
	cout << prompt << "{";
	for(int i=0; options[i]!='\0'; i++)
	{
		if(' ' < (options[i] & 0x7f) && (options[i] & 0x7f) < 127)	// 选项options中的可打印字符
			cout << options[i] << ' ';
		else														// 选项options中的部分控制字符
		{
			switch(options[i])
			{
			case '\t':   cout << "[Tab] ";   break;					// 选项中的Tab字符'\t'（即ASCII编码9）
			case '\x1b': cout << "[Esc] ";   break;					// 选项中的Esc字符'\x1b'（即ASCII编码27）
			case ' ':    cout << "[Space] "; break;					// 选项中的空格字符' '（即ASCII编码32）
			}
		}
	}
	cout << "\b}: ";					// '\b'退格。先退一格，在输出右花括号
	do
	{
		key = getch();
	}while(options[0]!='\0' && Pos(key, options)<0); // 若options为空长度为0的字符串，则输入无限制；否则输入项应该在optins中。
	cout << endl;
	return key;
}


template <typename T>
void Search(LinkList<Student> &link, const T &t)
{
	int n=0;
	Node<Student> *p;
	p = link.Locate(t, true);
	while(p!=NULL)
	{
		n++;
		cout << link.CurData() << endl;
		p = link.Locate(t);
	}
	cout << "找到 " << n << " 个满足条件的结点" << endl;
}

void Find(LinkList<Student> &link, int flag)
{
	char str[80];
	switch(flag)
	{
	case '1':	cout << "\n请输入查询的编号: ";
				cin.getline(str, 80);
				Search(link, atoi(str));				break;
				
	case '2':	cout << "\n请输入查询的姓名: ";
				cin.getline(str, 80);
				Search(link, string(str));				break;
				
	case '3':	cout << "\n请输入查询的手机号码: ";
				cin.getline(str, 80);
				Search(link, atoll(str));				break;
	}
}
