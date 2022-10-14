#include "LinkList.h"
#include "StudentDataBase.h"
#include "Banking.h"
#include <iomanip>
#include <cstring>
#include <string>
#include <conio.h>

// void AddressBookTest()
int main()
{
	int Pos(char ch, const char *str);						// 函数声明
	int Choice(const char *prompt, const char *options="");	// 函数声明
	LinkList<Student> StudentLink;
	char filename[80] = "StudentDataBase.txt";
	Student xStudent;
	int key, k, n, yn;
	n = StudentLink.Load(filename);
	cout << "\n已从 " << filename << " 文件中读取了 " << n << " 个结点的数据" << endl;

	while(true)
	{
		system("cls");
		cout << "--上海大学学生卡管理系统--" << endl;
		cout << " (1) 输出学生表  (P)" << endl;
		cout << " (B) 学生卡支付/充值"<< endl;
		cout << " (2) 插入学生结点(I)" << endl;
		cout << " (3) 追加新生结点(A)" << endl;
		cout << " (4) 查询        (S)" << endl;
		cout << " (5) 删除        (D)" << endl;
		cout << " (6) 排序        (O)" << endl;
		cout << " (7) 保存数据    (W)" << endl;
		cout << " (8) 读取数据文件(R)" << endl;
		cout << " (9) 释放所有结点(F)" << endl;
		cout << " (0) 退出      (ESC)" << endl;
		cout << "--------------------------" << endl;
		key = Choice("请选择", "0123456789\x1bpPbBiIaAsSdDoOwWrRfF");
		if(key==27 || key=='0')		// '\x1b'等于27，指ESC键
			break;
		switch(key)
		{
		case '1':
		case 'p':
		case 'P':
			// system("cls");
			cout << StudentLink << endl;
			system("pause");
			break;

		case 'b':
		case 'B':

			if (SelectUser(StudentLink, xStudent))
			{
				// system("cls");
				// xStudent.ShowBWB();
				system("pause");
				BankingRunner(xStudent);
			}
			system("pause");
			break;

		case '2':
		case 'i':
		case 'I':	cout << "插入一个学生结点到链表首学生结点前。" << endl;
					cout << "请输入数据域数据(学号 Tab 姓名 换行): ";
					cin >> xStudent;
					StudentLink.Insert(xStudent);
					// system("pause");
					break;
		case '3':
		case 'a':
		case 'A':
			cout << "追加一个结点(至尾结点后)。";
			cout << "请输入数据域数据(学号 Tab 姓名 换行): " << endl;
			cin >> xStudent;
			StudentLink.Append(xStudent);
			// system("pause");
			break;
		case '4':
		case 's':
		case 'S':	cout << "根据数据域数据查询。可根据如下三种方式查询。" << endl;
					cout << "1 序号 2 姓名 请选择: ";
					k = getche();
					Find(StudentLink, k);
					system("pause");
					break;
		case '5':
		case 'v':
		case 'V':	cout << "请选择要删除的学生\n" << StudentLink << endl;
					SelectUser(StudentLink, xStudent);
					StudentLink.DeleteCurNode();
					cout << "已删除\n" << StudentLink << endl;
					system("pause");
					break;
		case '6':
		case 'o':
		case 'O':

			system("cls");
			cout << "排序根据 1按序号 2按姓名 请选择: ";
			k = getche();
			switch (k)
			{
			case '1':
				cout << "\n[1]升序 2降序 请选择: ";
				k = getche();
				switch (k)
				{
				default:
					StudentLink.Sort(int(0)); // 第一个参数传递的数值不重要，重要的是数据类型
					cout << "\n按序号（升序）排序结果\n"
						 << StudentLink << endl;
					break;
				
				case '2':
					StudentLink.Sort(int(0), false);
					cout << "\n按序号（降序）排序结果\n"
						 << StudentLink << endl;
					break;
				}
			break;

			case '2':
				cout << "\n[1]升序 2降序 请选择: ";
				k = getche();
				switch (k)
				{
				case '2':
					StudentLink.Sort(string(""), false);
					cout << "\n按姓名（降序）排序结果\n"
						 << StudentLink << endl;
					break;

				default:
					StudentLink.Sort(string(""));
					cout << "\n按姓名（升序）排序结果\n"
						 << StudentLink << endl;
					break;
				}
				break;
			}

			system("pause");
			break;


		case '7':
		case 'w':
		case 'W':
			n = StudentLink.Save(filename);
			cout << "将 " << n << " 个结点的数据写入 "
				 << filename << " 文件。" << endl;
			system("pause");
			break;
		case '8':
		case 'r':
		case 'R':
			cout << "读取数据文件。是否先释放已有的所有结点(y/[N])? ";
			yn = getche();
			if (yn == 'y' || yn == 'Y')
				StudentLink.FreeList();
			n = StudentLink.Load(filename);
			cout << "\n从 " << filename << " 文件中读取 "
				 << n << " 个数据。现有 "
				 << StudentLink.NumNodes() << " 个结点" << endl;
			system("pause");
			break;
		case '9':
		case 'f':
		case 'F':
			cout << "释放所有结点。是否继续(y/[N])? ";
			yn = getche();
			if (yn == 'y' || yn == 'Y') // 默认 No
				StudentLink.FreeList();
			// system("pause");
			break;
		}
	}

	if (StudentLink.NumNodes())
	{
		SaveOnExit(StudentLink, filename);
	}
	cout << "\n自动调用析构函数释放所有结点。\n"
		 << endl;
	StudentLink.FreeList();
	return 0;
}
