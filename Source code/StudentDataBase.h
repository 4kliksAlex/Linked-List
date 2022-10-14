#pragma once
#include "LinkList.h"
#include "Banking.h"
#include <cstring>
#include <iomanip>

class Student;	// ��ǰ����

int Pos(char ch, const char *str);			// ����ָ���ַ�ch���ַ���str�е��±ꡣ������ʱ����-1
int Choice(const char *prompt, const char *options);		// �������塣�����ʾ��Ϣprompt������ѡ����ַ������ء�
template <typename T>
void Search(LinkList<Student> &link, const T &t);
void Find(LinkList<Student> &link, int flag);

void AddressBookTest();

bool SelectUser(LinkList<Student>& link, Student& xUser);

template <typename T>
void SaveOnExit(T& link, char* filename)
{
	int key, k, n, yn;
	cout << "\n��������������������������δ���?" << endl
			<< " 0 :������\n 1 :����\n[2]:���ΪԴ�ļ�+\"(1)\"\n 3 :���Ϊ�Զ����ļ���" << endl
			<< "\n��ѡ��(0/1/2): ";

	yn = getche();
	switch(yn)
	{
	case '0':
		break;

	case '1':
		n = link.Save(filename);
		cout << "�ѽ� " << n << " ����������д�� "
				<< filename << " �ļ���" << endl;
		break;
	
	default:	
		filename[Pos('.', filename)] = '\0';		// ȥ���ļ���չ��.txt
		strcat(filename, "(1).txt");				// ƴ�ӳ��µ��ļ���
		n = link.Save(filename);
		cout << "\n�ѽ� " << n << " ���������ݴ��� " << filename << " �ļ���" << endl;
		break;

	case '3':
		cout << "�������µ��ļ���: ";
		cin >> filename;
		n = link.Save(filename);
		cout << "\n�ѽ� " << n << " ����������д�� "
				<< filename << " �ļ���" << endl;
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
		strncpy(name, Name, sizeof(name));		// Ϊ�˰�ȫ���ϣ�ָ�����ȿ����ַ���
		name[sizeof(name)-1] = '\0';			// �Կ��ܳ������ַ������нض�
		strncpy(phone, Phone, sizeof(phone));
		phone[sizeof(phone)-1] = '\0';
		email = Email;	// �൱�� email = string(Email); ��C-�ַ���Emailת����stringȻ���ٸ�ֵ�����������ð���﷨��
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
	operator int()		const { return id; 			}	// ����ת�����������������ת��Ϊ int��ָ��ţ�
	operator string()	const { return name;		}	// ����ת�����������������ת��Ϊ C++�ַ���string��ָ������
	operator long long()const { return atoll(phone);}	// ����ת�����������������ת��Ϊ long long��ָ�ֻ����룩
private:
	int id;
	char name[21], phone[12];
	string email;
};*/

