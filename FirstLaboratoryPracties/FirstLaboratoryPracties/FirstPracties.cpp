#include <iostream>
#include <climits>
#include <Windows.h>

using namespace std;
int count_qual = 0; // ��������, �� ������� ���������� �������� ���������� �������

void SetColor(int text, int bg) //������� ����� �����, ������ �� ���������
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}
void chooseFormat(int count_qual, long int digit) // ������� �������� �������� � ����������� �� ���������� �������
{
	char value[256]; // ����������, ������� ������ ��������� ������ �����
	// ��������� ��������� ��������
	cin >> value;
	if (strlen(value) == 1)// ��������� ���������� ��������� ��������. ���� �����, �� ������ ������ ��� ���, ����� �������� ��������� ������
	{

		// ������������� ���������� �������� ��� ������ ����� � ����������� �� ��� ������� � ����� ���������, ������ �� �������� ��������� ����� � ���������� ��������
		switch (value[0]) // �������� ��������� ������, ���� ������ ������ ���������� value
		{
		case '1':
			::count_qual = 16; // ������������� ���������� �������� ��� ��������� ��������� ������� 
			cout << "��� ����� short int" << endl;
			if (digit < SHRT_MIN or digit > SHRT_MAX) // ��������� ������ �� �������� �������� � ����� ���������� �������
			{
				cout << "����� ������� �� ������� ���������� �������. ���������� ������� ������" << endl; // ������������ ��������
				chooseFormat(count_qual, digit);
			}
			break;

		case '2':
			cout << "��� ����� int" << endl;
			if (digit < INT_MIN or digit > INT_MAX) // ��������� ������ �� �������� �������� � ����� ���������� �������
			{
				cout << "����� ������� �� ������� ���������� �������. ���������� ������� ������" << endl; // ������������ ��������
				chooseFormat(count_qual, digit);
			}
			break;
		case '3':
			cout << "��� ����� unsigned int" << endl;
			if (digit < 0 or digit > UINT_MAX) // ��������� ������ �� �������� �������� � ����� ���������� �������
			{
				cout << "����� ������� �� ������� ���������� �������. ���������� ������� ������" << endl; // ������������ ��������
				chooseFormat(count_qual, digit);
			}
			break;
		default:
			cout << "����� ������� ��������. ������� ����� ������" << endl; // ���� ��������� ������ �� ������������ �� ������ �� ������������
			chooseFormat(count_qual, digit);
		}
	}
	else // ���� ������� �������� ������ ������������
	{
		cout << "���������� ������ ���� ������. ���������� ������ ������" << endl;
		chooseFormat(count_qual, digit);
	}
}
void mask_digit(const unsigned short qual, int revers_array[], int number_of_bit, int digit, bool result)
{
	// ������ ������ ����� � ������� ���������� ������ � ��������� � �����
	for (number_of_bit; number_of_bit < qual - count_qual; number_of_bit++) // ����� ���� ��� ������, ���������� ����� ���� � ���������� ��������� ��������� �������, ��������� 1 ����� ������ ��������
	{
		result = digit & (1U << number_of_bit); // ���������� ����� ����� � ���������� ��� � ����������
		revers_array[number_of_bit] = result; // ���������� � ������ ���������� �������� 
	}
	cout << endl; // ������� ������

}
void print_revers_array(const unsigned short qual, int revers_array[])
{
	cout << "�������� ������������� �����: " << endl << endl;
	bool counter = 0; // ��������, ������� ��������� �������������� ������ �������� ������ �����
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
		if (i % 8 == 0) // �������� ����� 8�� �������� �������� ��� �������� ���������� �����
			cout << " ";
	}
}
long int checkdigit()
{
	while (true)
	{
		// ������ �����, ������� ����� ����������� � �������� �����
		cout << "������� ����� ����� ��������� ������� (������: 10, -10, 5251, 0): " << endl;
		long int digit;

		cin >> digit;

		if (cin.fail()) // ec�� ���������� ����������� �������� ���������,
		{
			cin.clear(); // �� ���������� cin � ������� ����� ������
			cin.ignore(32767, '\n'); // � ������� �� ������ �������� ����������� ����� 
			cout << "������������ �������� �����. ������� ����� ���������" << endl;
		}
		else
		{
			cin.ignore(32767, '\n'); // ������� �� ������ �������� ����������� ����� 
			return digit;
		}

	}

}
bool checkresult(long int digit)
{
	bool result;
	if (digit >= 0)
		result = FALSE;
	else
		result = TRUE;
	
	return result;
}
void print_second_task(const unsigned short qual, int revers_array[], long int digit, bool result, int number_of_bit)
{
	// ��������� 2 ������� 
	cout << endl << endl << "������ �������" << endl;
	cout << "���� ����� ������������� - ������ ���� ������ �� 0" << endl;
	cout << "���� ����� ������������� - �������� ���� ������ �� 1" << endl;

	if (digit >= 0)
	{
		for (int i = qual - 1 - count_qual; i >= 0; i = i - 1)
		{
			if (i % 2 != 0)
				digit = digit & (~(1U << i)); // ��������������� ������ ��� � 0
		}
		mask_digit(qual, revers_array, number_of_bit, digit, result);
		print_revers_array(qual, revers_array);
		SetColor(7, 0); // ���������� ���� ������ � �����
		cout << "���������� �������� = " << digit << endl << endl;


	}
	else
	{
		for (int i = qual - 1 - count_qual; i >= 0; i = i - 1)
		{
			if (i % 2 == 0)
				digit = digit | (1U << i); // ������������� �������� ��� � 1
		}
		mask_digit(qual, revers_array, number_of_bit, digit, result);
		print_revers_array(qual, revers_array);
		SetColor(7, 0); // ���������� ���� ������ � �����
		cout << "���������� �������� = " << digit << endl << endl;

	}
}
int main()
{	
	setlocale(0, ""); // �����������
	long int digit = checkdigit(); // ���� �����	
	int number_of_bit = 0; // ����� ����, ������� ���������� �����
	bool result = checkresult(digit); // ����������, ������� ������ �������� �������������� ����� ������ 
	const unsigned short qual = 32; // ���������� ����������� �������� �����
	int revers_array[qual]; // ������, ������� ������ ������ ����� � ������������ ����
	// �������� ������ ��������
	cout << "�������� ������ �����:" << endl;
	cout << "1 - short" << endl;
	cout << "2 - int" << endl;
	cout << "3 - unsigned int" << endl;
	chooseFormat(count_qual, digit); // ������� �������� �������� � ����������� �� ���������� �������
	mask_digit(qual, revers_array, number_of_bit, digit, result); // ������� �������� ������ �����
	print_revers_array(qual, revers_array); // ������� ������ ������� ���������� ��������, ���������� ���
	SetColor(7, 0); // ���������� ���� ������ � �����
	print_second_task(qual, revers_array, digit, result, number_of_bit); // ������� � 2
	cout << endl; // ������ ������


	return 0;
}