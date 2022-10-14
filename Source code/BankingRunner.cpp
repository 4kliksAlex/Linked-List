// BankingRunner.cpp
#include <iostream>
#include "LinkList.h"
#include "StudentDataBase.h"
#include "Banking.h"
#include <conio.h>

#include <sstream>  // 2022年10月11日 16点59分 4ndyDufresne string streams

using namespace std;

template <typename T>
void SaveOnExit(T& link, char* filename);

int Pos(char ch, const char *str);						// 函数声明
int Choice(const char *prompt, const char *options="");	// 函数声明
void BankingAppend(Student& xStudent);
void SortBWB(LinkList<BWB>& BWBLink);

void BankingRunner(Student& xStudent)
{
	// 2022年10月11日 15点35分 4ndyDufresne 把函数先声明一遍

	LinkList<BWB>& BWBLink = xStudent.BWBLink;
	BWB xBWB;
	int key, InstantNodeNumber, n, yn;

	// 2022年10月10日 16点05分 4ndyDufresne 将用户对象转换为string类型，即姓名 
	// 2022年10月11日 17点10分 4ndyDufresne 改了。现在用id来标识用户
	stringstream filename_ss;
	filename_ss
		<< std::setw(8)
		<< std::setfill('0')
		<< int(xStudent)
		<< ".txt";

	string filename_str = filename_ss.str();

	char filename[80];
	strcpy(filename, filename_str.c_str());
	n = BWBLink.Load(filename);
	cout << "读取了" << n << "个结点的数据" << endl;

	// 2022年10月13日 23点12分 4ndyDufresne 初始化
	xStudent.BWBLink.Sort(int(0));	// 2022年10月12日 22点49分 4ndyDufresne 按时间排序
	xStudent.CalculateBWBBalance();	// 2022年10月12日 22点50分 4ndyDufresne 计算余额

	while(true)
	{
		system("cls");
		cout << "----学生卡支付 / 充值-----" << endl;
		xStudent.ShowHeading(cout);
		cout << " (1) 输出流水账  (P)" << endl;
		cout << " (2) 加流水账    (A)" << endl;
		cout << " (3) 倒置流水账  (V)" << endl;
		cout << " (4) 删除结点    (D)" << endl;
		cout << " (5) 排序        (O)" << endl;
		cout << " (6) 数据写入文件(W)" << endl;
		cout << " (7) 释放所有结点(F)" << endl;
		cout << " (8) 读取数据文件(R)" << endl;
		cout << " (0) 退出      (ESC)" << endl;
		cout << "--------------------------" << endl;
		key = Choice("请选择", "012345678\x1bpPaAwWrRfFdDoO");
		if(key==27 || key=='0')		// '\x1b'等于27，指ESC键
			break;
		switch(key)
		{
		case '1':
		case 'p':
		case 'P':
			system("cls");
			xStudent.ShowBWB(cout);
			system("pause");
			break;

		case '2':
		case 'a':
		case 'A':
			BankingAppend(xStudent);
			xStudent.BWBLink.Sort(int(0));	// 2022年10月13日 22点49分 4ndyDufresne 按时间排序
			xStudent.CalculateBWBBalance();	// 2022年10月13日 22点50分 4ndyDufresne 计算余额

			// xStudent.ShowBWB();
			// system("pause");
			break;

		case '3':
		case 'v':
		case 'V':
			system("cls");
			cout << "链表所有结点倒置。倒置之前\n"
				 << BWBLink << endl;
			BWBLink.Reverse();
			cout << "倒置之后\n"
				 << BWBLink << endl;
			system("pause");
			break;

		case '4':
		case 'd':
		case 'D':
			cout << "删除第几结点？(输入负数取消)： ";
			cin >> yn;
			if (yn >= 0 && yn < BWBLink.NumNodes())
			{
				BWBLink.Go(yn);
				BWBLink.DeleteCurNode();
				cout << "删除第 " << yn << " 个结点。现有 "
					 << BWBLink.NumNodes() << " 个结点" << endl;
				xStudent.BWBLink.Sort(int(0));
				xStudent.CalculateBWBBalance();
				xStudent.ShowBWB(cout);
			}
			else
				cout << "选择为负数或节点不存在，取消删除" << endl;
			system("pause");
			break;

		case '5':
		case 'o':
		case 'O':
			SortBWB(BWBLink);
			system("pause");
			break;

		case '6':
		case 'w':
		case 'W':
			InstantNodeNumber = BWBLink.Save(filename);
			cout << "将 " << InstantNodeNumber << " 个结点的数据写入 "
				 << filename << " 文件。" << endl;
			system("pause");
			break;

		case '7':
		case 'f':
		case 'F':
			cout << "释放所有结点。是否继续(y/[N])? ";
			yn = getche();
			if (yn == 'y' || yn == 'Y') // 默认 No
				BWBLink.FreeList();
			break;

		case '8':
		case 'r':
		case 'R':
			cout << "读取数据文件。是否先释放已有的所有结点(y/[N])? ";
			yn = getche();
			if (yn == 'y' || yn == 'Y')
				BWBLink.FreeList();
			n = BWBLink.Load(filename);
			cout << "\n从 " << filename << " 文件中读取 "
				 << n << " 个数据。现有 "
				 << BWBLink.NumNodes() << " 个结点" << endl;
			system("pause");
			break;

			
		}
	}
	if(BWBLink.NumNodes())
	{
		SaveOnExit(BWBLink, filename);
	}
	cout << "\n自动调用析构函数释放所有结点。\n" << endl;
	// free heap memory
	BWBLink.FreeList();
	return;
}

void SortBWB(LinkList<BWB>& BWBLink)
{
	int n = BWBLink.NumNodes();
	int k;
	system("cls");

	if (n <= 1)
	{
		cout << "结点数小于2，无需排序" << endl;
		return;
	}

	cout << "排序根据 1按日期 2按金额 请选择: ";
	k = getche();
	switch (k)
	{
	case '1':
		cout << "\n[1]升序 2降序 请选择: ";
		k = getche();
		switch (k)
		{
		default:
			BWBLink.Sort(int(0));
			cout << "\n按序号（升序）排序结果\n"
				 << BWBLink << endl;
			break;

		case '2':
			BWBLink.Sort(int(0), false);
			cout << "\n按序号（降序）排序结果\n"
				 << BWBLink << endl;
			break;
		}
		break;

	case '2':
		cout << "\n[1]升序 2降序 请选择: ";
		k = getche();
		switch (k)
		{
		default:
			BWBLink.Sort(double(0));
			cout << "\n按姓名（升序）排序结果\n"
				 << BWBLink << endl;
			break;

		case '2':
			BWBLink.Sort(double(0), false);
			cout << "\n按姓名（降序）排序结果\n"
				 << BWBLink << endl;
			break;
		}
		break;
	}

	return;
}

void BankingAppend(Student& xStudent)
{
	system("cls");
	// 追加新的结点
	BWB xBWB;
	int year, month, day;		// 流水单日期
	double money, balance;		// 本次流水账单金额、总余额
	char str[80];

	cout << "请输入（年 月 日 金额）: ";
	cin >> year >> month >> day >> money;
	cin.getline(str, 80);					// 处理换行字符

	xBWB.Set(year, month, day, money);
	xStudent.AppendBWB(xBWB);
	return;
}