// nashel oshibku v vivode vtorogo zadaniya - rabotaet tolko pod nechetnie biti
#include <iostream>
#include <climits>
#include <Windows.h>

using namespace std;
int count_qual = 0; // значение, на которое необходимо изменить заполнение массива
const unsigned short qual = 32; // обозначает разрядность будущего числа
long int digit = 0; // само число
int number_of_bit = 0; // номер бита, которым производим сдвиг
bool result; // переменная, которая хранит значения преобразования после сдвига
char value[256]; // переменная, которая хранит выбранный формат числа
int revers_array[qual]; // массив, который хранит слепок числа в перевернутом виде
bool counter = 0; // значение, которое позволяет контролировать первый значащий разряд числа

void SetColor(int text, int bg) //Функция смены цвета, взятая из Интернета
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void chooseFormat(int count_qual, long int digit) // функция проверки значения в зависимости от выбранного формата
{
	// считываем выбранное значение
	cin >> value;
	if (strlen(value) == 1)// проверяем количество введенных символов. Если много, то просим ввести еще раз, иначе проверям выбранный формат
	{

		// устанавливаем количество значений для слепка числа в зависимости от его формата и также проверяем, входит ли значение вводимого числа в конкретный диапазон
		switch (value[0]) // проверям выбранный формат, взяв первый символ переменной value
		{
		case '1':
			::count_qual = 16; // устанавливаем глобальное значение для изменения диапазона массива 
			cout << "Your chose is short int" << endl;
			if (digit < SHRT_MIN or digit > SHRT_MAX) // проверяем входит ли вводимое значение в рамки выбранного формата
			{
				cout << "Is out from range. Try to choose another one" << endl; // недопустимое значение
				chooseFormat(count_qual, digit);
			}
			break;

		case '2':
			cout << "Your chose is int" << endl;
			if (digit < INT_MIN or digit > INT_MAX) // проверяем входит ли вводимое значение в рамки выбранного формата
			{
				cout << "Is out from range. Try to choose another one" << endl; // недопустимое значение
				chooseFormat(count_qual, digit);
			}
			break;
		case '3':
			cout << "Your chose is unsigned int" << endl;
			if (digit < 0 or digit > UINT_MAX) // проверяем входит ли вводимое значение в рамки выбранного формата
			{
				cout << "Is out from range. Try to choose another one" << endl; // недопустимое значение
				chooseFormat(count_qual, digit);
			}
			break;
		default:
			cout << "Wrong chose. Try to choose another one" << endl; // если выбранный формат не соответсвует ни одному из предложенных
			chooseFormat(count_qual, digit);
		}
	}
	else
	{
		cout << "Need to write the one symbol. Try to choose another one" << endl;
		chooseFormat(count_qual, digit);
	}
}

void mask_digit(int digit)
{
	// делаем слепок числа с помощью побитового сдвига и умножения в цикле
	for (number_of_bit; number_of_bit < qual - count_qual; number_of_bit++) // номер бита для сдвига, сравниваем номер бита с допустимым значением диапазона массива, добавляем 1 после каждой итерации
	{
		result = digit & (1U << number_of_bit); // производим сдвиг числа и записываем бит в переменную
		revers_array[number_of_bit] = result; // записываем в массив полученное значение 
	}
	cout << endl; // перевод строки

}

void print_revers_array()
{
	// выводим на экран слепок числа,  перевернув его
	for (int i = qual - 1 - count_qual; i >= 0; i = i - 1) // берем последний бит в допустимом значении диапазона массива, цикл будет проходить до последнего значения бита, снижаем на 1 после каждой итерации
	{
		if (i == qual - 1 - count_qual) // отделяем знак от числа единожды
		{
			cout << revers_array[i]; // вывод значения бита
			cout << " "; // пробел отделяющий знак числа
		}
		else if (revers_array[i] == 0 and counter == 0) // проверяем выводим бит является ли значащим и вместе с ним равен ли параметр ЛОЖЬ. Необходимо для того, чтобы найти значащие биты и выделить их цветом
		{
			cout << revers_array[i]; // вывод значения бита
		}
		else
		{
			counter = 1; // устанавливаем в истину, как только получили первый значащий разряд
			SetColor(14, 0); // устанавливаем цвет шрифта в желтый
			cout << revers_array[i]; //вывод значения бита
		}


	}
}

void print_second_task()
{
	// выполняем 2 задание 
	cout << endl << endl << "The next task" << endl;
	cout << endl << "If digit is positve - odd bits to 0 " << endl;
	cout << "If digit is negative - even bits to 1 " << endl << endl;

	if (digit >= 0) // проверяем, положительное ли число
	{
		result = FALSE;
	}
	else
	{
		result = TRUE;
	}
	for (int i = qual - 1 - count_qual; i >= 0; i = i - 1) // берем последний бит в допустимом значении диапазона массива, цикл будет проходить до последнего значения бита, снижаем на 1 после каждой итерации
	{
		if (i == qual - 1 - count_qual) // отделяем знак от числа единожды и проверяем четность бита
		{
				cout << result; // вывод нуля вместо вывода бита
				cout << " "; // пробел отделяющий знак числа
		}
		else if (i % 2 != 0) // проверяем четность бита. Если нечетное, то выводим 0, иначе - выводим значение бита
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
	 // вводим число, которое хотим представить в двоичной форме
	cout << "Enter your digit " << endl;
	cin >> digit;

	// выбираем формат значения
	cout << "Choose the format value:" << endl;
	cout << "1 - short" << endl;
	cout << "2 - int" << endl;
	cout << "3 - unsigned int" << endl;

	chooseFormat(count_qual, digit); // функция проверки значения в зависимости от выбранного формата

	mask_digit(digit); // функция создания слепка числа
	
	print_revers_array(); // функция вывода массива полученный значений, перевернув его

	SetColor(7, 0); // возвращаем цвет шрифта в белый
	
	//задание № 2.
	print_second_task();

	cout << endl; // пустая строка
	return 0;
}
