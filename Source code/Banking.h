// Banking.h
#ifndef BANKING_H
#define BANKING_H
#include "LinkList.h"
#include "StudentDataBase.h"
#include <cstring>
#include <string>
#include <iomanip>

using namespace std;

class Student;	// ��ǰ����

class BWB	// Bank water bills������ˮ�˵�
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
	// operator string()	const { return name;		}	// ����ת�����������������ת��Ϊ C++�ַ���string��ָ������
	operator double() const { return money; }

	friend class Student;

private:
	int year, month, day;		// ��ˮ������
	double money, balance;		// ������ˮ�˵��������
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

	operator int() const { return stoi(id); }				// ����ת�����������������ת��Ϊ int��ָ��ţ�
	operator string() const { return name; }				// ����ת�����������������ת��Ϊ C++�ַ���string��ָ������
	// operator long long() const { return atoll(phone); }	// ����ת�����������������ת��Ϊ long long��ָ�ֻ����룩

	void CalculateBWBBalance();

	LinkList<BWB> BWBLink; // ����(���˻�����ˮ��¼)

private:
	string id, name; // 2022��10��11�� 19��44�� 4ndyDufresne ѧ�š�����
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
		email = Email;	// �൱�� email = string(Email); ��C-�ַ���Emailת����stringȻ���ٸ�ֵ�����������ð���﷨��
	}
	*/
// void BankingAppend(User uLink);

