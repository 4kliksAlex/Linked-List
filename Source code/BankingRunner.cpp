// BankingRunner.cpp
#include <iostream>
#include "LinkList.h"
#include "StudentDataBase.h"
#include "Banking.h"
#include <conio.h>

#include <sstream>  // 2022��10��11�� 16��59�� 4ndyDufresne string streams

using namespace std;

template <typename T>
void SaveOnExit(T& link, char* filename);

int Pos(char ch, const char *str);						// ��������
int Choice(const char *prompt, const char *options="");	// ��������
void BankingAppend(Student& xStudent);
void SortBWB(LinkList<BWB>& BWBLink);

void BankingRunner(Student& xStudent)
{
	// 2022��10��11�� 15��35�� 4ndyDufresne �Ѻ���������һ��

	LinkList<BWB>& BWBLink = xStudent.BWBLink;
	BWB xBWB;
	int key, InstantNodeNumber, n, yn;

	// 2022��10��10�� 16��05�� 4ndyDufresne ���û�����ת��Ϊstring���ͣ������� 
	// 2022��10��11�� 17��10�� 4ndyDufresne ���ˡ�������id����ʶ�û�
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
	cout << "��ȡ��" << n << "����������" << endl;

	// 2022��10��13�� 23��12�� 4ndyDufresne ��ʼ��
	xStudent.BWBLink.Sort(int(0));	// 2022��10��12�� 22��49�� 4ndyDufresne ��ʱ������
	xStudent.CalculateBWBBalance();	// 2022��10��12�� 22��50�� 4ndyDufresne �������

	while(true)
	{
		system("cls");
		cout << "----ѧ����֧�� / ��ֵ-----" << endl;
		xStudent.ShowHeading(cout);
		cout << " (1) �����ˮ��  (P)" << endl;
		cout << " (2) ����ˮ��    (A)" << endl;
		cout << " (3) ������ˮ��  (V)" << endl;
		cout << " (4) ɾ�����    (D)" << endl;
		cout << " (5) ����        (O)" << endl;
		cout << " (6) ����д���ļ�(W)" << endl;
		cout << " (7) �ͷ����н��(F)" << endl;
		cout << " (8) ��ȡ�����ļ�(R)" << endl;
		cout << " (0) �˳�      (ESC)" << endl;
		cout << "--------------------------" << endl;
		key = Choice("��ѡ��", "012345678\x1bpPaAwWrRfFdDoO");
		if(key==27 || key=='0')		// '\x1b'����27��ָESC��
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
			xStudent.BWBLink.Sort(int(0));	// 2022��10��13�� 22��49�� 4ndyDufresne ��ʱ������
			xStudent.CalculateBWBBalance();	// 2022��10��13�� 22��50�� 4ndyDufresne �������

			// xStudent.ShowBWB();
			// system("pause");
			break;

		case '3':
		case 'v':
		case 'V':
			system("cls");
			cout << "�������н�㵹�á�����֮ǰ\n"
				 << BWBLink << endl;
			BWBLink.Reverse();
			cout << "����֮��\n"
				 << BWBLink << endl;
			system("pause");
			break;

		case '4':
		case 'd':
		case 'D':
			cout << "ɾ���ڼ���㣿(���븺��ȡ��)�� ";
			cin >> yn;
			if (yn >= 0 && yn < BWBLink.NumNodes())
			{
				BWBLink.Go(yn);
				BWBLink.DeleteCurNode();
				cout << "ɾ���� " << yn << " ����㡣���� "
					 << BWBLink.NumNodes() << " �����" << endl;
				xStudent.BWBLink.Sort(int(0));
				xStudent.CalculateBWBBalance();
				xStudent.ShowBWB(cout);
			}
			else
				cout << "ѡ��Ϊ������ڵ㲻���ڣ�ȡ��ɾ��" << endl;
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
			cout << "�� " << InstantNodeNumber << " ����������д�� "
				 << filename << " �ļ���" << endl;
			system("pause");
			break;

		case '7':
		case 'f':
		case 'F':
			cout << "�ͷ����н�㡣�Ƿ����(y/[N])? ";
			yn = getche();
			if (yn == 'y' || yn == 'Y') // Ĭ�� No
				BWBLink.FreeList();
			break;

		case '8':
		case 'r':
		case 'R':
			cout << "��ȡ�����ļ����Ƿ����ͷ����е����н��(y/[N])? ";
			yn = getche();
			if (yn == 'y' || yn == 'Y')
				BWBLink.FreeList();
			n = BWBLink.Load(filename);
			cout << "\n�� " << filename << " �ļ��ж�ȡ "
				 << n << " �����ݡ����� "
				 << BWBLink.NumNodes() << " �����" << endl;
			system("pause");
			break;

			
		}
	}
	if(BWBLink.NumNodes())
	{
		SaveOnExit(BWBLink, filename);
	}
	cout << "\n�Զ��������������ͷ����н�㡣\n" << endl;
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
		cout << "�����С��2����������" << endl;
		return;
	}

	cout << "������� 1������ 2����� ��ѡ��: ";
	k = getche();
	switch (k)
	{
	case '1':
		cout << "\n[1]���� 2���� ��ѡ��: ";
		k = getche();
		switch (k)
		{
		default:
			BWBLink.Sort(int(0));
			cout << "\n����ţ�����������\n"
				 << BWBLink << endl;
			break;

		case '2':
			BWBLink.Sort(int(0), false);
			cout << "\n����ţ�����������\n"
				 << BWBLink << endl;
			break;
		}
		break;

	case '2':
		cout << "\n[1]���� 2���� ��ѡ��: ";
		k = getche();
		switch (k)
		{
		default:
			BWBLink.Sort(double(0));
			cout << "\n������������������\n"
				 << BWBLink << endl;
			break;

		case '2':
			BWBLink.Sort(double(0), false);
			cout << "\n������������������\n"
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
	// ׷���µĽ��
	BWB xBWB;
	int year, month, day;		// ��ˮ������
	double money, balance;		// ������ˮ�˵��������
	char str[80];

	cout << "�����루�� �� �� ��: ";
	cin >> year >> month >> day >> money;
	cin.getline(str, 80);					// �������ַ�

	xBWB.Set(year, month, day, money);
	xStudent.AppendBWB(xBWB);
	return;
}