// Banking.h
#ifndef BANKING_H
#define BANKING_H
#include "LinkList.h"
#include "StudentDataBase.h"
#include <cstring>
#include <string>
#include <iomanip>

using namespace std;

class Student;	// 提前声明

class BWB	// Bank water bills银行流水账单
{
public:
	BWB(int Year=2020, int Month=1, int Day=1, double Money=0);
	void Set(int Year, int Month, int Day, double Money);
	friend ostream & operator<<(ostream &out, const BWB &b);
	friend istream & operator>>(istream &in, BWB &b);
	operator int() const
	{
		// YYYY0000 + MM00 + DD
		return (10000 * year + 100 * month + 1 * day);
	}
	// operator string()	const { return name;		}	// 类型转换运算符，将本对象转换为 C++字符串string（指姓名）
	operator double() const { return money; }

	friend class Student;

private:
	int year, month, day;		// 流水单日期
	double money, balance;		// 本次流水账单金额、总余额
};

class Student
{
public:
	Student(const char *ID = "00000000", const char *Name = "NoName");
	void Set(const char *ID, const char *Name);

	void AppendBWB(const BWB &b);
	void ShowHeading(ostream &out) const;
	friend ostream &operator<<(ostream &out, const Student &u);
	friend istream &operator>>(istream &in, Student &a);
	void ShowBWB(ostream &out) const;

	operator int() const { return stoi(id); }				// 类型转换运算符，将本对象转换为 int（指编号）
	operator string() const { return name; }				// 类型转换运算符，将本对象转换为 C++字符串string（指姓名）
	// operator long long() const { return atoll(phone); }	// 类型转换运算符，将本对象转换为 long long（指手机号码）

	void CalculateBWBBalance();

	LinkList<BWB> BWBLink; // 链表(该账户的流水记录)

private:
	string id, name; // 2022年10月11日 19点44分 4ndyDufresne 学号、户名
	// char phone[12];
	// string email;
};

void BankingRunner(Student& uLink);

#endif


	/*
public:
	User(int Id=0, const char *Name="NoName", const char *Phone="", const char *Email="") : id(to_string(Id))
	{
		name = Name;
		strncpy(phone, Phone, sizeof(phone));
		phone[sizeof(phone)-1] = '\0';
		email = Email;	// 相当于 email = string(Email); 将C-字符串Email转换成string然后再赋值。本句可移至冒号语法处
	}
	*/
// void BankingAppend(User uLink);

