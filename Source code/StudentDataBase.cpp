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
	cout << "�������ѯ�ı��: ";
	cin >> id;
	
	Node<Student> *p;
	p = link.Locate(id, true);
	if (p == NULL)
	{
		cout << "û���ҵ����Ϊ " << id << " �Ľ��" << endl;
		return false;
	}

	cout << "�ҵ����Ϊ " << id << " �Ľ��" << endl;
	xStudent = link.CurData();
	return true;
}


int Pos(char ch, const char *str)			// ����ָ���ַ�ch���ַ���str�е��±ꡣ������ʱ����-1
{
	int i;
	for(i=0; str[i]!='\0'; i++)
		if(ch==str[i])
			return i;
	return -1;
}


/////////////////////////////////////////


int Choice(const char *prompt, const char *options="");	// ��������
int Choice(const char *prompt, const char *options)		// �������塣�����ʾ��Ϣprompt������ѡ����ַ������ء�
{
	int key;
	cout << prompt << "{";
	for(int i=0; options[i]!='\0'; i++)
	{
		if(' ' < (options[i] & 0x7f) && (options[i] & 0x7f) < 127)	// ѡ��options�еĿɴ�ӡ�ַ�
			cout << options[i] << ' ';
		else														// ѡ��options�еĲ��ֿ����ַ�
		{
			switch(options[i])
			{
			case '\t':   cout << "[Tab] ";   break;					// ѡ���е�Tab�ַ�'\t'����ASCII����9��
			case '\x1b': cout << "[Esc] ";   break;					// ѡ���е�Esc�ַ�'\x1b'����ASCII����27��
			case ' ':    cout << "[Space] "; break;					// ѡ���еĿո��ַ�' '����ASCII����32��
			}
		}
	}
	cout << "\b}: ";					// '\b'�˸�����һ��������һ�����
	do
	{
		key = getch();
	}while(options[0]!='\0' && Pos(key, options)<0); // ��optionsΪ�ճ���Ϊ0���ַ����������������ƣ�����������Ӧ����optins�С�
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
	cout << "�ҵ� " << n << " �����������Ľ��" << endl;
}

void Find(LinkList<Student> &link, int flag)
{
	char str[80];
	switch(flag)
	{
	case '1':	cout << "\n�������ѯ�ı��: ";
				cin.getline(str, 80);
				Search(link, atoi(str));				break;
				
	case '2':	cout << "\n�������ѯ������: ";
				cin.getline(str, 80);
				Search(link, string(str));				break;
				
	case '3':	cout << "\n�������ѯ���ֻ�����: ";
				cin.getline(str, 80);
				Search(link, atoll(str));				break;
	}
}
