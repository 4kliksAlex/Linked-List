// Banking.cpp
#include "LinkList.h"
#include "Banking.h"
#include "StudentDataBase.h"
#include <cmath>
#include <iomanip>
#include <conio.h>

BWB::BWB(int Year, int Month, int Day, double Money) : year(Year), month(Month), day(Day), money(Money), balance(0)
{
}

void BWB::Set(int Year, int Month, int Day, double Money)
{
	year = abs(Year);
	month = abs(Month);
	day = abs(Day);
	money = Money;
}

ostream & operator<<(ostream &out, const BWB &b)
{
	out << setfill('0')
		<< setw(4) << b.year
		<< '-' << setw(2) << b.month
		<< '-' << setw(2) << b.day
		<< '\t' << b.money
		<< '\t' << b.balance;

	/*
	cout << "\t debug: "
	<< b.year << " "
	<< b.month << " "
	<< b.day << " "
	<< int(b) << " "
	<< endl;
	*/

	return out;
}

istream & operator>>(istream &in, BWB &b)
{
	int Year, Month, Day;
	in >> Year >> Month >> Day >> b.money >> b.balance;
	b.Set(Year, Month, Day, b.money);
	return in;
}

/////////////////////////////////////

Student::Student(const char *ID, const char *Name) : id(ID), name(Name)
{
}

void Student::Set(const char *ID, const char *Name)
{
	id = ID;
	name = Name;
}

void Student::AppendBWB(const BWB &b)
{
	double x;
	BWB y(b);
	if(BWBLink.NumNodes()==0)
		x = 0;
	else
	{
		BWBLink.GoBottom();
		x = BWBLink.CurData().balance;
	}
	y.balance = x + b.money;	// 计算余额
	BWBLink.Append(y);				// 添加一条流水记录
}

void Student::ShowHeading(ostream &out) const
{
	out << "账号：" << id << "\t户名：" << name << endl;
}
void Student::ShowBWB(ostream &out) const
{
	this->ShowHeading(out);
	(*this).BWBLink.PutList(out);
	cout << "日期\t\t存/取\t账户余额" << endl;
	return;
}

void Student::CalculateBWBBalance()
{
	LinkList<BWB> &BWBLink = this->BWBLink;
	// BWBLink.GoTop();
	double balance = 0;

	int n = BWBLink.NumNodes();
	if (n <= 1)
		return;

	for (int i = 0; i < n; i++)
	{
		BWBLink.Go(i);
		BWBLink.CurData().balance = balance += BWBLink.CurData().money;
	}
	return;
}

ostream & operator<<(ostream &out, const Student &u)
{
	out << std::setw(8) << std::setfill('0') << u.id
		<< '\t' << u.name;
	return out;
}

istream & operator>>(istream &in, Student &a)
{
	in >> a.id >> a.name;
	return in;
}
