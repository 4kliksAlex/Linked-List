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
	int Pos(char ch, const char *str);						// ��������
	int Choice(const char *prompt, const char *options="");	// ��������
	LinkList<Student> StudentLink;
	char filename[80] = "StudentDataBase.txt";
	Student xStudent;
	int key, k, n, yn;
	n = StudentLink.Load(filename);
	cout << "\n�Ѵ� " << filename << " �ļ��ж�ȡ�� " << n << " ����������" << endl;

	while(true)
	{
		system("cls");
		cout << "--�Ϻ���ѧѧ��������ϵͳ--" << endl;
		cout << " (1) ���ѧ����  (P)" << endl;
		cout << " (B) ѧ����֧��/��ֵ"<< endl;
		cout << " (2) ����ѧ�����(I)" << endl;
		cout << " (3) ׷���������(A)" << endl;
		cout << " (4) ��ѯ        (S)" << endl;
		cout << " (5) ɾ��        (D)" << endl;
		cout << " (6) ����        (O)" << endl;
		cout << " (7) ��������    (W)" << endl;
		cout << " (8) ��ȡ�����ļ�(R)" << endl;
		cout << " (9) �ͷ����н��(F)" << endl;
		cout << " (0) �˳�      (ESC)" << endl;
		cout << "--------------------------" << endl;
		key = Choice("��ѡ��", "0123456789\x1bpPbBiIaAsSdDoOwWrRfF");
		if(key==27 || key=='0')		// '\x1b'����27��ָESC��
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
		case 'I':	cout << "����һ��ѧ����㵽������ѧ�����ǰ��" << endl;
					cout << "����������������(ѧ�� Tab ���� ����): ";
					cin >> xStudent;
					StudentLink.Insert(xStudent);
					// system("pause");
					break;
		case '3':
		case 'a':
		case 'A':
			cout << "׷��һ�����(��β����)��";
			cout << "����������������(ѧ�� Tab ���� ����): " << endl;
			cin >> xStudent;
			StudentLink.Append(xStudent);
			// system("pause");
			break;
		case '4':
		case 's':
		case 'S':	cout << "�������������ݲ�ѯ���ɸ����������ַ�ʽ��ѯ��" << endl;
					cout << "1 ��� 2 ���� ��ѡ��: ";
					k = getche();
					Find(StudentLink, k);
					system("pause");
					break;
		case '5':
		case 'v':
		case 'V':	cout << "��ѡ��Ҫɾ����ѧ��\n" << StudentLink << endl;
					SelectUser(StudentLink, xStudent);
					StudentLink.DeleteCurNode();
					cout << "��ɾ��\n" << StudentLink << endl;
					system("pause");
					break;
		case '6':
		case 'o':
		case 'O':

			system("cls");
			cout << "������� 1����� 2������ ��ѡ��: ";
			k = getche();
			switch (k)
			{
			case '1':
				cout << "\n[1]���� 2���� ��ѡ��: ";
				k = getche();
				switch (k)
				{
				default:
					StudentLink.Sort(int(0)); // ��һ���������ݵ���ֵ����Ҫ����Ҫ������������
					cout << "\n����ţ�����������\n"
						 << StudentLink << endl;
					break;
				
				case '2':
					StudentLink.Sort(int(0), false);
					cout << "\n����ţ�����������\n"
						 << StudentLink << endl;
					break;
				}
			break;

			case '2':
				cout << "\n[1]���� 2���� ��ѡ��: ";
				k = getche();
				switch (k)
				{
				case '2':
					StudentLink.Sort(string(""), false);
					cout << "\n������������������\n"
						 << StudentLink << endl;
					break;

				default:
					StudentLink.Sort(string(""));
					cout << "\n������������������\n"
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
			cout << "�� " << n << " ����������д�� "
				 << filename << " �ļ���" << endl;
			system("pause");
			break;
		case '8':
		case 'r':
		case 'R':
			cout << "��ȡ�����ļ����Ƿ����ͷ����е����н��(y/[N])? ";
			yn = getche();
			if (yn == 'y' || yn == 'Y')
				StudentLink.FreeList();
			n = StudentLink.Load(filename);
			cout << "\n�� " << filename << " �ļ��ж�ȡ "
				 << n << " �����ݡ����� "
				 << StudentLink.NumNodes() << " �����" << endl;
			system("pause");
			break;
		case '9':
		case 'f':
		case 'F':
			cout << "�ͷ����н�㡣�Ƿ����(y/[N])? ";
			yn = getche();
			if (yn == 'y' || yn == 'Y') // Ĭ�� No
				StudentLink.FreeList();
			// system("pause");
			break;
		}
	}

	if (StudentLink.NumNodes())
	{
		SaveOnExit(StudentLink, filename);
	}
	cout << "\n�Զ��������������ͷ����н�㡣\n"
		 << endl;
	StudentLink.FreeList();
	return 0;
}
