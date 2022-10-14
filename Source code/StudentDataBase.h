#pragma once
#include "LinkList.h"
#include "Banking.h"
#include <cstring>
#include <iomanip>

class Student;	// 提前声明

int Pos(char ch, const char *str);			// 返回指定字符ch在字符串str中的下标。不存在时返回-1
int Choice(const char *prompt, const char *options);		// 函数定义。输出提示信息prompt，输入选择的字符并返回。
template <typename T>
void Search(LinkList<Student> &link, const T &t);
void Find(LinkList<Student> &link, int flag);

void AddressBookTest();

bool SelectUser(LinkList<Student>& link, Student& xUser);

template <typename T>
void SaveOnExit(T& link, char* filename)
{
	int key, k, n, yn;
	cout << "\n即将返回主函数，链表数据如何存盘?" << endl
			<< " 0 :不存盘\n 1 :存盘\n[2]:另存为源文件+\"(1)\"\n 3 :另存为自定义文件名" << endl
			<< "\n请选择(0/1/2): ";

	yn = getche();
	switch(yn)
	{
	case '0':
		break;

	case '1':
		n = link.Save(filename);
		cout << "已将 " << n << " 个结点的数据写入 "
				<< filename << " 文件。" << endl;
		break;
	
	default:	
		filename[Pos('.', filename)] = '\0';		// 去掉文件扩展名.txt
		strcat(filename, "(1).txt");				// 拼接成新的文件名
		n = link.Save(filename);
		cout << "\n已将 " << n << " 个结点的数据存入 " << filename << " 文件。" << endl;
		break;

	case '3':
		cout << "请输入新的文件名: ";
		cin >> filename;
		n = link.Save(filename);
		cout << "\n已将 " << n << " 个结点的数据写入 "
				<< filename << " 文件。" << endl;
		break;
	}
	return;
}

/*
class AddressBook
{
public:
	AddressBook(int Id=0, const char *Name="NoName", const char *Phone="", const char *Email="") : id(Id)
	{
		strncpy(name, Name, sizeof(name));		// 为了安全保障，指定长度拷贝字符串
		name[sizeof(name)-1] = '\0';			// 对可能超长的字符串进行截断
		strncpy(phone, Phone, sizeof(phone));
		phone[sizeof(phone)-1] = '\0';
		email = Email;	// 相当于 email = string(Email); 将C-字符串Email转换成string然后再赋值。本句可移至冒号语法处
	}
	friend ostream & operator<<(ostream &out, const AddressBook &a)
	{
		out << setfill('0') << setw(8) << a.id << '\t' << a.name << '\t' 
			<< setfill(' ') << setw(11) << a.phone << '\t' << a.email;
		return out;
	}
	friend istream & operator>>(istream &in, AddressBook &a)
	{
		char str[80];
		in.getline(str, 80, '\t');	a.id = atoi(str);
		in.getline(str, 80, '\t');	strncpy(a.name, str, sizeof(a.name));	a.name[sizeof(a.name)-1] = '\0';
		in.getline(str, 80, '\t');	strncpy(a.phone, str, sizeof(a.phone));	a.phone[sizeof(a.phone)-1] = '\0';
		in.getline(str, 80);		a.email = str;
		return in;
	}
	operator int()		const { return id; 			}	// 类型转换运算符，将本对象转换为 int（指编号）
	operator string()	const { return name;		}	// 类型转换运算符，将本对象转换为 C++字符串string（指姓名）
	operator long long()const { return atoll(phone);}	// 类型转换运算符，将本对象转换为 long long（指手机号码）
private:
	int id;
	char name[21], phone[12];
	string email;
};*/

