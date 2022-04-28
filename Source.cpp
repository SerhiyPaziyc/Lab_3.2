#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Spec {
	COMPUTER_SCIENCE, INFORMATICS, MATH_ECONOMICS,
	PHYSICS_INFORMATICS, WORK_TRAINING
};

string specStr[] = { "����\'����� �����", "�����������",
"���������� �� ��������", "Գ���� �� �����������","������� ��������" };

struct Student
{
	string secondname;
	unsigned kurs;
	Spec spec;
	int physics;
	int math;
	union
	{
		int prog;
		int nummeth;
		int pedag;
	};
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
void Sort(Student* s, const int N);
int BinSearch(Student* s, const int N, const int profpred, const int kurs, const string secondname);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;

	cout << "������ N = "; cin >> N;

	Student* s = new Student[N];

	int math;
	int spec;
	string secondname;
	int found;

	int menuItem;

	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << "\t[1] - �������� ����� � ���������" << endl;
		cout << "\t[2] - ���� ����� �� �����" << endl;
		cout << "\t[3] - Գ����� ������������� �����" << endl;
		cout << "\t[4] - ���� ������������� �����" << endl;
		cout << "\t[5] - �������� ����� ��������" << endl << endl;
		cout << "\t[0] - Exit" << endl << endl;
		cout << "��� ����: "; cin >> menuItem;
		cout << endl << endl << endl;

		switch (menuItem)
		{
		case 1:
			Create(s, N);
			break;
		case 2:
			Print(s, N);
			break;
		case 3:
			Sort(s, N);
			break;
		case 4:
			PrintIndexSorted(s, IndexSort(s, N), N);
			break;
		case 5:
			cout << "������ ����� ������: " << endl;
			cout << "\t������ ������ � ����������: "; cin >> math;
			cout << "\t������������: "; cin >> spec;

			cin.get();
			cin.sync();

			cout << "\t�������: "; getline(cin, secondname);
			cout << endl;
			if ((found = BinSearch(s, N, math, spec, secondname)) != -1)
			{
				cout << "�������� �������� � ������� " << found + 1 << endl;
			}
			else
			{
				cout << "�������� ���������� �� ��������" << endl;
			}
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				<< "��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);

	system("pause");
	return 0;
}

void Create(Student* s, const int N)
{
	int spec;

	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;

		cin.get();
		cin.sync();

		cout << "\t�������: "; getline(cin, s[i].secondname);
		cout << "\t����: "; cin >> s[i].kurs;
		cout << "\t������������:\n [0]����\'����� �����\n [1]�����������\n"
			<< " [2]���������� �� ��������\n [3]Գ���� �� �����������\n"
			<< " [4]������� ��������\n ��� ����: "; cin >> spec;

		s[i].spec = (Spec)spec;

		switch (s[i].spec)
		{
		case COMPUTER_SCIENCE:
			cout << "\t������ � ������: "; cin >> s[i].physics;
			cout << "\t������ � ����������: "; cin >> s[i].math;
			cout << "\t������ � �������������: "; cin >> s[i].prog;
			break;
		case INFORMATICS:
			cout << "\t������ � ������: "; cin >> s[i].physics;
			cout << "\t������ � ����������: "; cin >> s[i].math;
			cout << "\t������ � ��������� ������: "; cin >> s[i].nummeth;
			break;
		case MATH_ECONOMICS:
		case PHYSICS_INFORMATICS:
		case WORK_TRAINING:
			cout << "\t������ � ������: "; cin >> s[i].physics;
			cout << "\t������ � ����������: "; cin >> s[i].math;
			cout << "\t������ � ���������: "; cin >> s[i].pedag;
			break;
		}
		cout << endl;
	}
}

void Print(Student* s, const int N)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| � |   �������   | ���� |      ������������      | Գ���� | ���������� | ������������� | ��������� ������ | ��������� |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(12) << left << s[i].secondname << " "
			<< "|   " << setw(1) << right << s[i].kurs << "  "
			<< "| " << setw(23) << left << specStr[s[i].spec] << " "
			<< "|    " << setw(1) << right << s[i].physics << "   "
			<< "|      " << setw(1) << left << s[i].math << "     ";

		switch (s[i].spec)
		{
		case COMPUTER_SCIENCE:
			cout << "|       " << setw(1) << right << s[i].prog << "       |"
				<< setw(20) << right << "|" << setw(13) << right << "|" << endl;
			break;
		case INFORMATICS:
			cout << "|" << setw(26) << right << "|          "
				<< setw(1) << left << s[i].nummeth << "        |" << setw(13) << right << "|" << endl;
			break;
		case MATH_ECONOMICS:
		case PHYSICS_INFORMATICS:
		case WORK_TRAINING:
			cout << "| " << setw(15) << right << "|"
				<< setw(26) << right << "|      " << setw(1) << right << s[i].pedag << "     |" << endl;
			break;
		}
	}
	cout << "----------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	cout << endl;
}
/*�������� �� ���� ������������ ��������� ������� ������������ ����� � ����� 
����� � �� ������ ������������, � ����� ����� (��� ��������� ��������������) � �� 
��������� ������ � ����������, � ������� ����� (��� ��������� �������������� �
������ � ����������) � �� �������� �� ���������� � � ���������� �������.
*/

void Sort(Student* s, const int N)
{
	Student temp;

	for (int i = 0; i < N - 1; i++)
	{
		for (int j = 0; j < N - i - 1; j++)
		{
			if ((s[j].spec > s[j + 1].spec)
				||
				(s[j].spec == s[j + 1].spec &&
					s[j].math > s[j + 1].math)
				||
				(s[j].spec == s[j + 1].spec &&
					s[j].math == s[j + 1].math &&
					s[j].secondname > s[j + 1].secondname))
			{
				temp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = temp;
			}
		}
	}
}
/*�� ��������� �������� ������ ���������, �� ��������� ������� �� ��������
������������ �������� �� ������� ������������ �� �������� ������� �
����������.*/

int BinSearch(Student* s, const int N, const int math, const int spec, const string secondname)
{
	int L = 0, R = N - 1, m;

	do {
		m = (L + R) / 2;
		if (s[m].math == math && s[m].spec == spec && s[m].secondname == secondname)
		{
			return m;
		}
		if ((s[m].math < math)
			||
			(s[m].math == math &&
				s[m].spec < spec)
			||
			(s[m].math == math &&
				s[m].spec == spec &&
				s[m].secondname < secondname))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);

	return -1;
}
/*�������� �� �������� ��������� �����, ���� ��������� �������� �������� 
�������������: � ����� ����� � �� ������ ������������, � ����� ����� (��� 
��������� ��������������) � �� ��������� ������ � ����������, � ������� ����� (��� 
��������� �������������� � ������ � ����������) � �� ��������.
*/

int* IndexSort(Student* s, const int N)
{
	int value, i, j;
	int* I = new int[N];

	for (int i = 0; i < N; i++)
	{
		I[i] = i;
	}

	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1; j >= 0 && (s[I[j]].spec > s[value].spec) ||
			(s[I[j]].spec == s[value].spec &&
				s[I[j]].math > s[value].math) ||
			(s[I[j]].spec == s[value].spec &&
				s[I[j]].math == s[value].math &&
				s[I[j]].secondname > s[value].secondname); j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}


void PrintIndexSorted(Student* s, int* I, const int N)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| � |   �������   | ���� |      ������������      | Գ���� | ���������� | ������������� | ��������� ������ | ��������� |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------"
		<< endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(12) << left << s[i].secondname << " "
			<< "|   " << setw(1) << right << s[i].kurs << "  "
			<< "| " << setw(23) << left << specStr[s[i].spec] << " "
			<< "|    " << setw(1) << right << s[i].physics << "   "
			<< "|      " << setw(1) << left << s[i].math << "     ";

		switch (s[I[i]].spec)
		{
		case COMPUTER_SCIENCE:
			cout << "|       " << setw(1) << right << s[I[i]].prog << "       |"
				<< setw(20) << right << "|" << setw(13) << right << "|" << endl;
			break;
		case INFORMATICS:
			cout << "|" << setw(26) << right << "|          "
				<< setw(1) << left << s[I[i]].nummeth << "        |" << setw(13) << right << "|" << endl;
			break;
		case MATH_ECONOMICS:
		case PHYSICS_INFORMATICS:
		case WORK_TRAINING:
			cout << "| " << setw(15) << right << "|"
				<< setw(26) << right << "|      " << setw(1) << right << s[I[i]].pedag << "     |" << endl;
			break;
		}
	}
	cout << "----------------------------------------------------------------------------------------------------------------------------"
		<< endl;
	cout << endl;
}