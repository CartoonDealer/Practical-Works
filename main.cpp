#include <iostream>
#include <conio.h>
using namespace std;

union FloatUnion {
	int tool;
	float num;
};
FloatUnion floatUnion;

union DoubleUnion {
	int tool[2];
	double num;
};
DoubleUnion doubleUnion;

void clear() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void convertToBits(int num, bool isFloat = false) {
	int bits;
	unsigned int mask;

	if (isFloat) {
		bits = sizeof(float) * 8;
	}
	else {
		bits = sizeof(int) * 8;
	}

	mask = 1u << (bits - 1);

	for (int i = 0; i < bits; i++)
	{
		if (((i == 1) || (i % 8 == 0)) && i != 0) {
			cout << ' ';
		}

		if (i == 0) { 
			cout << "\033[31m";
		}
		else if (isFloat && i < 8) {
			cout << "\033[91m";
		}
		else { 
			cout << "\033[93m"; 
		}
			putchar(num & mask ? '1' : '0');
			num <<= 1;

		cout << "\033[37m";
	}
	_getch();
}

void printDataTypesInBits() {
	clear();
	int dataType;

	cout << "Программа выводит количество бит, которое занимает в памяти выбранный тип данных.\n" 
		"Выберите номер из списка:\n";
	cout << "1 - int\n";
	cout << "2 - short int \n";
	cout << "3 - long int\n";
	cout << "4 - float\n";
	cout << "5 - double\n";
	cout << "6 - long double\n";
	cout << "7 - char\n";
	cout << "8 - bool\n";
	cout << "9 - все типы сразу\n";
	cout << "0 - выход в меню\n";
	cin >> dataType;

	switch (dataType)
	{
	case 0:
		break;
	case 1:
		cout << "int занимает в памяти " << sizeof(int) << " байта";
		break;
	case 2: 
		cout << "short int занимает в памяти " << sizeof(short int) << " байта";
		break;
	case 3: 
		cout << "long int занимает в памяти " << sizeof(long int) << " байта";
		break;
	case 4: 
		cout << "float занимает в памяти " << sizeof(float) << " байта";
		break;
	case 5: 
		cout << "double занимает в памяти " << sizeof(double) << " байт";
		break;
	case 6: 
		cout << "long double занимает в памяти " << sizeof(long double) << " байт";
		break;
	case 7: 
		cout << "char занимает в памяти " << sizeof(char) << " байт";
		break;
	case 8: 
		cout << "bool занимает в памяти " << sizeof(bool) << " байт";
		break;
	case 9:
		cout << "int занимает в памяти " << sizeof(int) << " байта\n";
		cout << "short int занимает в памяти " << sizeof(short int) << " байта\n";
		cout << "long int занимает в памяти " << sizeof(long int) << " байта\n";
		cout << "float занимает в памяти " << sizeof(float) << " байта\n";
		cout << "double занимает в памяти " << sizeof(double) << " байт\n";
		cout << "long double занимает в памяти " << sizeof(long double) << " байт\n";
		cout << "char занимает в памяти " << sizeof(char) << " байт\n";
		cout << "bool занимает в памяти " << sizeof(bool) << " байт\n";
		break;
	default:
		cout << "К сожалению, вы указали неправильное число\n";
	}
	_getch();
}

void convertDoubleToBits() {
	int bits = sizeof(int) * 8;

	for (int j(1); j > -1; j--) {
		unsigned int mask = 1 << (bits - 1);
		for (int i(0); i < bits; i++) {
			int global_bit_index = (1 - j) * 32 + i;

			if (global_bit_index == 1 || global_bit_index == 12) {
				cout << "\033[0m "; 
			}
			else if (i % 4 == 0 && !(global_bit_index == 1 || global_bit_index == 12)) { 
				cout << ' '; 
			}

			if (global_bit_index == 0) { 
				cout << "\033[31m"; 
			}
			else if (global_bit_index >= 1 && global_bit_index <= 11) { 
				cout << "\033[91m"; 
			}
			else { 
				cout << "\033[93m"; 
			}

			cout << ((doubleUnion.tool[j] & mask) ? '1' : '0');
			mask >>= 1;
		}

		cout << "\033[37m";
	}
	
	_getch();
};

void changeBit() {
	int dataType;
	int sizeInt = sizeof(int) * 8;
	int sizeFloat = sizeof(float) * 8;
	int sizeDouble = sizeof(double) * 8;

	std::cout << "\nВыберите тип данных:\n"
		<< "1. int\n"
		<< "2. float\n"
		<< "3. double\n"
		<< "Ваш выбор: ";
	std::cin >> dataType;

	if (dataType == 1) {
		int inputValue;

		std::cout << "Введите int число: ";
		std::cin >> inputValue;

		cout << "Введи номер бита, который нужно инвертировать\n";
		int idx;
		cin >> idx;

		cout << "BIN ";
		convertToBits(inputValue);
		
		cout << "\nBIN ";
		inputValue ^= (1u << (sizeInt - idx));

		convertToBits(inputValue);
		cout << "\nНовое число: " << inputValue;

		_getch();
	}
	else if (dataType == 2) {
		float inputValue;

		std::cout << "Введите float число: ";
		std::cin >> inputValue;
		floatUnion.num = inputValue;

		cout << "Введи номер бита, который нужно инвертировать\n";
		int idx;
		cin >> idx;

		cout << "BIN ";
		convertToBits(floatUnion.tool, true);

		cout << "\nBIN ";
		floatUnion.tool ^= (1u << (sizeFloat - idx));

		convertToBits(floatUnion.tool, true);
		cout << "\nНовое число: " << floatUnion.num;

		_getch();
	}
	else if (dataType == 3) {
		double inputValue;

		std::cout << "Введите double число: ";
		std::cin >> inputValue;
		doubleUnion.num = inputValue;

		cout << "Введи номер бита, который нужно инвертировать\n";
		int idx;
		cin >> idx;

		cout << "BIN ";
		convertDoubleToBits();

		cout << "\nBIN ";

		if (idx >= 32) {
			doubleUnion.tool[0] ^= (1u << (sizeDouble - idx));
		}
		else {
			doubleUnion.tool[1] ^= (1u << (sizeDouble - idx));
		}

		convertDoubleToBits();
		cout << "\nНовое число: " << doubleUnion.num;

		_getch();
	}
	else {
		std::cout << "Неверный выбор типа данных\n\n";
	}
}

void makeInfitiny() {
	float inputValue;
	std::cout << "Введите float число: ";
	std::cin >> inputValue;
	floatUnion.num = inputValue;

	cout << "BIN ";
	convertToBits(floatUnion.tool, true);

	for (int idx = 2; idx <= 32; idx++)
	{
		if (idx < 9) {
			floatUnion.tool |= (1u << (32 - idx));
		}
		else {
			floatUnion.tool &= ~(1u << (32 - idx));
		}
	}

	cout << "\nBIN ";
	convertToBits(floatUnion.tool, true);
	cout << '\n';
	cout << floatUnion.num;

	_getch();
}

int main() {
	setlocale(0, "");

	int a = -234;
	unsigned b = a;
	while (true) {
		clear();
		short imputNum;
		cout << "Выбор действия:\n1 - Вывести объём памяти под типы данных"
			"\n2 - Вывести на экран двоичное представление в памяти целого числа."
			"\n3 - Вывести на экран двоичное представление в памяти типа float."
			"\n4 - Вывести на экран двоичное представление в памяти типа double."
			"\n5 - Изменить произвольный бит числа."
			"\n6 - Превратить число в бесконечность."
			"\n0 - Выход\n\n";
		cin >> imputNum;

		switch (imputNum) {
		case 0:
			return 0;
			break;
		case 1:
			printDataTypesInBits();
			break;
		case 2:
			int userInt;

			clear();
			cout << "Введите целое число: ";
			cin >> userInt;

			convertToBits(userInt);
			break;
		case 3:
			float userFloat;

			clear();
			cout << "Введите число типа float: ";
			cin >> userFloat;

			floatUnion.num = userFloat;

			convertToBits(floatUnion.tool, true);
			break;
		case 4:
			double userDouble;

			clear();
			cout << "Введите число типа double: ";
			cin >> userDouble;
			doubleUnion.num = userDouble;

			convertDoubleToBits();
			break;
		case 5:
			clear();
			changeBit();
			break;
		case 6:
			clear();
			makeInfitiny();
			break;
		}
	}
}


