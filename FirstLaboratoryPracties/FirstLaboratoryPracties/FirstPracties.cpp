#include <iostream>
#include <climits>
#include <Windows.h>

using namespace std;
int count_qual = 0; // ��������, �� ������� ���������� �������� ���������� �������
const unsigned short qual = 32; // ���������� ����������� �������� �����
long int digit = 0; // ���� �����
int number_of_bit = 0; // ����� ����, ������� ���������� �����
bool result; // ����������, ������� ������ �������� �������������� ����� ������
char value; // ����������, ������� ������ ��������� ������ �����
int revers_array[qual]; // ������, ������� ������ ������ ����� � ������������ ����
bool counter = 0; // ��������, ������� ��������� �������������� ������ �������� ������ �����

void SetColor(int text, int bg) //������� ����� �����, ������ �� ���������
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void chooseFormat(char value, int count_qual, long int digit) // ������� �������� �������� � ����������� �� ���������� �������
{
	// ������������� ���������� �������� ��� ������ ����� � ����������� �� ��� ������� � ����� ���������, ������ �� �������� ��������� ����� � ���������� ��������
	switch (value)
	{
	case '1':
		::count_qual = 16; // ������������� ���������� �������� ��� ��������� ��������� ������� 
		cout << "Your chose is short int" << endl;
		if (digit < SHRT_MIN or digit > SHRT_MAX) // ��������� ������ �� �������� �������� � ����� ���������� �������
		{
			cout << "Is out from range"; // ������������ ��������
			exit(0);
		}
		break;

	case '2':
		cout << "Your chose is int" << endl;
		if (digit < INT_MIN or digit > INT_MAX) // ��������� ������ �� �������� �������� � ����� ���������� �������
		{
			cout << "Is out from range"; // ������������ ��������
			exit(0);
		}
		break;
	case '3':
		cout << "Your chose is unsigned int" << endl;
		if (digit < 0 or digit > UINT_MAX) // ��������� ������ �� �������� �������� � ����� ���������� �������
		{
			cout << "Is out from range"; // ������������ ��������
			exit(0);
		}
		break;
	default:
		cout << "denied" << endl; // ���� ��������� ������ �� ������������ �� ������ �� ������������
		exit(0);
	}
}

void mask_digit(int digit)
{
	// ������ ������ ����� � ������� ���������� ������ � ��������� � �����
	for (number_of_bit; number_of_bit < qual - count_qual; number_of_bit++) // ����� ���� ��� ������, ���������� ����� ���� � ���������� ��������� ��������� �������, ��������� 1 ����� ������ ��������
	{
		result = digit & (1U << number_of_bit); // ���������� ����� ����� � ���������� ��� � ����������
		revers_array[number_of_bit] = result; // ���������� � ������ ���������� �������� 
	}
	cout << endl; // ������� ������

}

void print_revers_array()
{
	// ������� �� ����� ������ �����,  ���������� ���
	for (int i = qual - 1 - count_qual; i >= 0; i = i - 1) // ����� ��������� ��� � ���������� �������� ��������� �������, ���� ����� ��������� �� ���������� �������� ����, ������� �� 1 ����� ������ ��������
	{
		if (i == qual - 1 - count_qual) // �������� ���� �� ����� ��������
		{
			cout << revers_array[i]; // ����� �������� ����
			cout << " "; // ������ ���������� ���� �����
		}
		else if (revers_array[i] == 0 and counter == 0) // ��������� ������� ��� �������� �� �������� � ������ � ��� ����� �� �������� ����. ���������� ��� ����, ����� ����� �������� ���� � �������� �� ������
		{
			cout << revers_array[i]; // ����� �������� ����
		}
		else
		{
			counter = 1; // ������������� � ������, ��� ������ �������� ������ �������� ������
			SetColor(14, 0); // ������������� ���� ������ � ������
			cout << revers_array[i]; //����� �������� ����
		}


	}
}

void print_second_task()
{
	// ��������� 2 ������� 
	cout << endl << endl << "The next task" << endl;
	cout << endl << "If digit is positve - odd bits to 0 " << endl;
	cout << "If digit is negative - even bits to 1 " << endl << endl;

	if (digit >= 0) // ���������, ������������� �� �����
	{
		result = FALSE;
	}
	else
	{
		result = TRUE;
	}
	for (int i = qual - 1 - count_qual; i >= 0; i = i - 1) // ����� ��������� ��� � ���������� �������� ��������� �������, ���� ����� ��������� �� ���������� �������� ����, ������� �� 1 ����� ������ ��������
	{
		if (i == qual - 1 - count_qual) // �������� ���� �� ����� �������� � ��������� �������� ����
		{
				cout << result; // ����� ���� ������ ������ ����
				cout << " "; // ������ ���������� ���� �����
		}
		else if (i % 2 != 0) // ��������� �������� ����. ���� ��������, �� ������� 0, ����� - ������� �������� ����
		{
				cout << result;
		}
		else
		{
				cout << revers_array[i];
		}

	}
}

int main()
{
	 // ������ �����, ������� ����� ����������� � �������� �����
	cout << "Enter your digit " << endl;
	cin >> digit;

	// �������� ������ ��������
	cout << "Choose the format value:" << endl;
	cout << "1 - short" << endl;
	cout << "2 - int" << endl;
	cout << "3 - unsigned int" << endl;

	// ��������� ��������� ��������
	cin >> value;
	cout << endl;

	chooseFormat(value, count_qual, digit); // ������� �������� �������� � ����������� �� ���������� �������

	mask_digit(digit); // ������� �������� ������ �����
	
	print_revers_array(); // ������� ������ ������� ���������� ��������, ���������� ���

	SetColor(7, 0); // ���������� ���� ������ � �����
	
	//������� � 2.
	print_second_task();

	cout << endl; // ������ ������
	return 0;
}