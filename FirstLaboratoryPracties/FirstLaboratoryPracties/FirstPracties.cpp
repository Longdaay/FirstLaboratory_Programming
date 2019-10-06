#include <iostream>
#include <climits>
#include <Windows.h>

using namespace std;
int count_qual = 0; // значение, на которое необходимо изменить заполнение массива

void SetColor(int text, int bg) //Функция смены цвета, взятая из Интернета
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}
void chooseFormat(int count_qual, long int digit) // функция проверки значения в зависимости от выбранного формата
{
	char value[256]; // переменная, которая хранит выбранный формат числа
	// считываем выбранное значение
	cin >> value;
	if (strlen(value) == 1)// проверяем количество введенных символов. Если много, то просим ввести еще раз, иначе проверям выбранный формат
	{

		// устанавливаем количество значений для слепка числа в зависимости от его формата и также проверяем, входит ли значение вводимого числа в конкретный диапазон
		switch (value[0]) // проверям выбранный формат, взяв первый символ переменной value
		{
		case '1':
			::count_qual = 16; // устанавливаем глобальное значение для изменения диапазона массива 
			cout << "Ваш выбор short int" << endl;
			if (digit < SHRT_MIN or digit > SHRT_MAX) // проверяем входит ли вводимое значение в рамки выбранного формата
			{
				cout << "Число выходит за пределы выбранного формата. Попробуйте выбрать другой" << endl; // недопустимое значение
				chooseFormat(count_qual, digit);
			}
			break;

		case '2':
			cout << "Ваш выбор int" << endl;
			if (digit < INT_MIN or digit > INT_MAX) // проверяем входит ли вводимое значение в рамки выбранного формата
			{
				cout << "Число выходит за пределы выбранного формата. Попробуйте выбрать другой" << endl; // недопустимое значение
				chooseFormat(count_qual, digit);
			}
			break;
		case '3':
			cout << "Ваш выбор unsigned int" << endl;
			if (digit < 0 or digit > UINT_MAX) // проверяем входит ли вводимое значение в рамки выбранного формата
			{
				cout << "Число выходит за пределы выбранного формата. Попробуйте выбрать другой" << endl; // недопустимое значение
				chooseFormat(count_qual, digit);
			}
			break;
		default:
			cout << "Число введено неверное. Введите номер заново" << endl; // если выбранный формат не соответсвует ни одному из предложенных
			chooseFormat(count_qual, digit);
		}
	}
	else // если введено символов больше необходимого
	{
		cout << "Необходимо ввести один символ. Попробуйте ввести заново" << endl;
		chooseFormat(count_qual, digit);
	}
}
void mask_digit(const unsigned short qual, int revers_array[], int number_of_bit, int digit, bool result)
{
	// делаем слепок числа с помощью побитового сдвига и умножения в цикле
	for (number_of_bit; number_of_bit < qual - count_qual; number_of_bit++) // номер бита для сдвига, сравниваем номер бита с допустимым значением диапазона массива, добавляем 1 после каждой итерации
	{
		result = digit & (1U << number_of_bit); // производим сдвиг числа и записываем бит в переменную
		revers_array[number_of_bit] = result; // записываем в массив полученное значение 
	}
	cout << endl; // перевод строки

}
void print_revers_array(const unsigned short qual, int revers_array[])
{
	cout << "Двоичное представление числа: " << endl << endl;
	bool counter = 0; // значение, которое позволяет контролировать первый значащий разряд числа
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
		if (i % 8 == 0) // отделяем после 8го значения пробелом для удобного восприятия числа
			cout << " ";
	}
}
long int checkdigit()
{
	while (true)
	{
		// вводим число, которое хотим представить в двоичной форме
		cout << "Введите целое число арабскими цифрами (Пример: 10, -10, 5251, 0): " << endl;
		long int digit;

		cin >> digit;

		if (cin.fail()) // ecли предыдущее извелечение оказлось неудачным,
		{
			cin.clear(); // то возвращаем cin в обычный режим работы
			cin.ignore(32767, '\n'); // и удаляем из буфера значения предыдущего ввода 
			cout << "Недопустимое заданное число. Введите число правильно" << endl;
		}
		else
		{
			cin.ignore(32767, '\n'); // удаляем из буфера значения предыдущего ввода 
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
	// выполняем 2 задание 
	cout << endl << endl << "Второе задание" << endl;
	cout << "Если число положительное - четные биты меняем на 0" << endl;
	cout << "Если число отрицательное - нечетные биты меняем на 1" << endl;

	if (digit >= 0)
	{
		for (int i = qual - 1 - count_qual; i >= 0; i = i - 1)
		{
			if (i % 2 != 0)
				digit = digit & (~(1U << i)); // устанавлививаем четный бит в 0
		}
		mask_digit(qual, revers_array, number_of_bit, digit, result);
		print_revers_array(qual, revers_array);
		SetColor(7, 0); // возвращаем цвет шрифта в белый
		cout << "полученное значение = " << digit << endl << endl;


	}
	else
	{
		for (int i = qual - 1 - count_qual; i >= 0; i = i - 1)
		{
			if (i % 2 == 0)
				digit = digit | (1U << i); // устанавливаем нечетный бит в 1
		}
		mask_digit(qual, revers_array, number_of_bit, digit, result);
		print_revers_array(qual, revers_array);
		SetColor(7, 0); // возвращаем цвет шрифта в белый
		cout << "полученное значение = " << digit << endl << endl;

	}
}
int main()
{	
	setlocale(0, ""); // локализация
	long int digit = checkdigit(); // само число	
	int number_of_bit = 0; // номер бита, которым производим сдвиг
	bool result = checkresult(digit); // переменная, которая хранит значения преобразования после сдвига 
	const unsigned short qual = 32; // обозначает разрядность будущего числа
	int revers_array[qual]; // массив, который хранит слепок числа в перевернутом виде
	// выбираем формат значения
	cout << "Выберите формат числа:" << endl;
	cout << "1 - short" << endl;
	cout << "2 - int" << endl;
	cout << "3 - unsigned int" << endl;
	chooseFormat(count_qual, digit); // функция проверки значения в зависимости от выбранного формата
	mask_digit(qual, revers_array, number_of_bit, digit, result); // функция создания слепка числа
	print_revers_array(qual, revers_array); // функция вывода массива полученный значений, перевернув его
	SetColor(7, 0); // возвращаем цвет шрифта в белый
	print_second_task(qual, revers_array, digit, result, number_of_bit); // задание № 2
	cout << endl; // пустая строка


	return 0;
}