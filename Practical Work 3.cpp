#include <windows.h>;
#include <conio.h>;
#include <iostream>
#include <string>;
#include <iomanip>

using namespace std;

const char ARROY = -32;
const char UP = 72;
const char DOWN = 80;
const char ESC = 27;
const char ENTER = 13;
const int LEN = 8;

int activeMenu = 0;
char inputButton;

int arr[LEN][LEN];

COORD destCoord;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

string menu[] = { "Вывести матрицу", "Заполнить матрицу по спирали",
"Заполнить матрицу змейкой", "Перестановка по квадрату",
"Перестановка по кресту", "Перестановка по вертикальной оси",
"Перестановка по горизонтальной оси", "Отсортировать", 
"Арифметические операции", "ИДЗ", "Выход" };

void consoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; // изменяем видимость курсора
	structCursorInfo.dwSize = size; // изменяем размер курсора
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void readArray(int* array) {
	int* end = *arr + LEN * LEN - 1;
	int cnt = 0;
	char a = '-';

	for (int* ptr = *arr; ptr <= end; ptr++)
	{
		if (cnt == LEN * (LEN / 2)) {
			cout << string(LEN * 3, a) << '\n';
		}
		if ((ptr - *arr + 1) % LEN == 0) {
			cout << setw(2) << setfill('0') << *ptr;
			cnt++;
			cout << '\n';
		}
		else if ((ptr - *arr + 1) % (LEN / 2) == 0) {
			cout << setw(2) << setfill('0') << *ptr << " | ";
			cnt++;
		}
		else {
			cout << setw(2) << setfill('0') << *ptr << ' ';
			cnt++;
		}
	}
}

void printSpiral(int* array) {
	int count = LEN * LEN;
	int cnt = 0;
	int* ptr = *arr;
	int k = 0;

	while (cnt < count) {
		for (int i = 0; i < LEN - 1 - k; i++)
		{
			if (cnt == count) break;
			SetConsoleCursorPosition(hStdOut, destCoord);
			cout << setw(2) << setfill('0')  << *ptr;
			cnt++;
			ptr++;
			Sleep(40);
			destCoord.X += 3;
		}
		if (k != 0) k++;
		for (int i = 0; i < LEN - 1 - k; i++)
		{
			if (cnt == count) break;
			SetConsoleCursorPosition(hStdOut, destCoord);
			cout << setw(2) << setfill('0') << *ptr;
			cnt++;
			ptr += LEN;
			Sleep(40);
			destCoord.Y += 1;
		}
		for (int i = 0; i < LEN - 1 - k; i++)
		{
			if (cnt == count) break;
			SetConsoleCursorPosition(hStdOut, destCoord);
			cout << setw(2) << setfill('0') << *ptr;
			cnt++;
			ptr--;
			Sleep(40);
			destCoord.X -= 3;
		}
		k++;
		for (int i = 0; i < LEN - 1 - k; i++)
		{
			if (cnt == count) break;
			SetConsoleCursorPosition(hStdOut, destCoord);
			cout << setw(2) << setfill('0') << *ptr;
			cnt++;
			ptr -= LEN;
			Sleep(40);
			destCoord.Y -= 1;
		}
	}
	destCoord.X = 0;
	destCoord.Y = 0;
	SetConsoleCursorPosition(hStdOut, destCoord);
}

void printSnake(int* array) {
	int count = LEN * LEN;
	int cnt = 0;
	int* ptr = *arr;
	cout << setw(2) << setfill('0') << *ptr;
	cnt++;
	while (cnt < count) {
		for (int i = 0; i < LEN - 1; i++)
		{
			if (cnt == count) break;
			ptr += LEN;
			destCoord.Y += 1;
			SetConsoleCursorPosition(hStdOut, destCoord);
			cout << setw(2) << setfill('0') << *ptr;
			cnt++;
			Sleep(40);
		}
		if (cnt == count) break;
		ptr += 1;
		destCoord.X += 3;
		SetConsoleCursorPosition(hStdOut, destCoord);
		cout << setw(2) << setfill('0') << *ptr;
		cnt++;

		for (int i = 0; i < LEN - 1; i++)
		{
			if (cnt == count) break;
			destCoord.Y -= 1;
			ptr -= LEN;
			SetConsoleCursorPosition(hStdOut, destCoord);
			cout << setw(2) << setfill('0') << *ptr;
			cnt++;
			Sleep(40);
		}

		if (cnt == count) break;
		ptr += 1;
		destCoord.X += 3;
		SetConsoleCursorPosition(hStdOut, destCoord);
		cout << setw(2) << setfill('0') << *ptr;
		cnt++;
		
	}
	destCoord.X = 0;
	destCoord.Y = 0;
	SetConsoleCursorPosition(hStdOut, destCoord);
}
void printSnake2(int* array) {
	int count = LEN * LEN;
	int cnt = 0;
	int* ptr = *arr;
	ptr += LEN * LEN;
	destCoord.Y = 0;
	destCoord.X = LEN;
	cout << setw(2) << setfill('0') << *ptr;
	cnt++;
	while (cnt < count) {
		for (int i = 0; i < LEN - 1; i++)
		{
			if (cnt == count) break;
			ptr -= 1;
			destCoord.Y += 1;
			SetConsoleCursorPosition(hStdOut, destCoord);
			cout << setw(2) << setfill('0') << *ptr;
			cnt++;
			Sleep(40);
		}
		if (cnt == count) break;
		ptr -= 1;
		destCoord.X -= 3;
		SetConsoleCursorPosition(hStdOut, destCoord);
		cout << setw(2) << setfill('0') << *ptr;
		cnt++;

		for (int i = 0; i < LEN - 1; i++)
		{
			if (cnt == count) break;
			destCoord.Y -= 1;
			ptr += LEN;
			SetConsoleCursorPosition(hStdOut, destCoord);
			cout << setw(2) << setfill('0') << *ptr;
			cnt++;
			Sleep(40);
		}

		if (cnt == count) break;
		ptr -= 1;
		destCoord.X -= 3;
		SetConsoleCursorPosition(hStdOut, destCoord);
		cout << setw(2) << setfill('0') << *ptr;
		cnt++;

	}
	destCoord.X = 0;
	destCoord.Y = 0;
	SetConsoleCursorPosition(hStdOut, destCoord);
}

void swap(int* numOne, int* numTwo) {
	int temp = *numOne;
	*numOne = *numTwo;
	*numTwo = temp;
}

void squareSwap(int* array) {
	int half = LEN / 2;
	int* ptr = *arr;
	readArray(array);
	for (int i = 0; i < LEN; i++)
	{
		for (int j = 0; j < half; j++)
		{
			int* ptr1 = ptr + half;
			swap(ptr, ptr1);
			ptr++;
		}
		ptr += half;
	}
	ptr = *arr;
	for (int i = half; i < LEN; i++)
	{
		for (int j = half; j < LEN; j++)
		{
			int* ptr1 = ptr + (LEN * half) + half;
			swap(ptr, ptr1);
			ptr++;
		}
		ptr += half;
	}

	cout << "\n";
	readArray(array);
}

void сhristianSwap(int* array) {
	int half = LEN / 2;
	int* ptr = *arr;
	readArray(array);

	for (int i = half; i < LEN; i++)
	{
		for (int j = half; j < LEN; j++)
		{
			int* ptr1 = ptr + (LEN * half) + half;
			swap(ptr, ptr1);
			ptr++;
		}
		ptr += half;
	}
	ptr = *arr + half;
	for (int i = half; i < LEN; i++)
	{
		for (int j = half; j < LEN; j++)
		{
			int* ptr1 = ptr + (LEN * half) - half;
			swap(ptr, ptr1);
			ptr++;
		}
		ptr += half;
	}

	cout << "\n";
	readArray(array);
}

void verticalSwap(int* array) {
	int half = LEN / 2;
	int* ptr = *arr;
	readArray(array);
	for (int i = 0; i < LEN; i++)
	{
		for (int j = 0; j < half; j++)
		{
			int* ptr1 = ptr + half;
			swap(ptr, ptr1);
			ptr++;
		}
		ptr += half;
	}

	cout << "\n";
	readArray(array);
}

void horizontalSwap(int* array) {
	int half = LEN / 2;
	int* ptr = *arr;
	readArray(array);

	for (int i = 0; i < half; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			int* ptr1 = ptr + (LEN * half);
			swap(ptr, ptr1);
			ptr++;
		}
	}

	cout << "\n";
	readArray(array);
}

void quickSort(int* array, int left, int right) {
	int* ptr = *arr;
	if (left < right) {
		int end = *(ptr + right);
		int indexLeast = left - 1;

		for (int i = left; i <= right - 1; i++) {
			if (*(ptr + i) < end) {
				indexLeast++;
				swap(*(ptr + indexLeast), *(ptr + i));
			}
		}
		swap(*(ptr + indexLeast + 1), *(ptr + right));
		int mid = indexLeast + 1;

		quickSort(array, left, mid - 1);
		quickSort(array, mid + 1, right);
	}
}

void operationsArrays(int* array) {
	int userChoice;
	float number;
	cout << "Выберите тип операции:\n1. Сложение\n2. Вычетание\n3. Умножение\n4. Деление\nВаш выбор: ";
	cin >> userChoice;
	cout << "Введите число: ";
	cin >> number;
	int* indexOne = *arr;
	switch (userChoice) {
	case 1:
		for (int i = 0; i < LEN; ++i) {
			for (int j = 0; j < LEN; ++j, indexOne++) {
				*indexOne += number;
			}
		}
		cout << "\n";
		readArray(*arr);
		break;
	case 2:
		for (int i = 0; i < LEN; ++i) {
			for (int j = 0; j < LEN; ++j, indexOne++) {
				*indexOne -= number;
			}
		}
		cout << "\n";
		readArray(*arr);
		break;
	case 3:
		for (int i = 0; i < LEN; ++i) {
			for (int j = 0; j < LEN; ++j, indexOne++) {
				*indexOne *= number;
			}
		}
		cout << "\n";
		readArray(*arr);
		break;
	case 4:
		for (int i = 0; i < LEN; ++i) {
			for (int j = 0; j < LEN; ++j, indexOne++) {
				*indexOne /= number;
			}
		}
		cout << "\n";
		readArray(*arr);
		break;
	default:
		cout << "\nОшибка\n";
		break;
	}
}

void createRandArray(int* array) {
	srand(time(NULL));
	int* end = *arr + LEN * LEN - 1;
	for (int* i = *arr; i < end; ++i) {
		*i = rand() % 99 + 1;
	}
}

void idz(int* array) {
	cout << "2. Заполните матрицу случайными числами (от 1 до 100).\n"  
		"Необходимо, переставляя строки и столбцы числовой квадратичной "
		"матрицы порядка N, добиться того,\n чтобы наибольший элемент "
		"оказался в верхнем левом углу.\nОтобразите все промежуточные выводы.";
	int max = 0, line = 0, column = 0;
	int* end = *arr + LEN * LEN - 1;
	int* ptr = *arr;
	for (int i = 0; i < LEN; i++)
	{
		for (int j = 0; j < LEN; j++)
		{
			if (*ptr > max) {
				max = *ptr;
				line = i;
				column = j;
			}
			ptr++;
		}
	}
	cout << "\n\nMax: " << max << " Line: " << line << " Column: " << column;
	cout << "\nПерестановка строки:\n";
	ptr = *arr;
	int* ptr1 = *arr;
	for (int i = 0; i < LEN; i++)
	{
		if (i == line) {
			for (int j = 0; j < LEN; j++)
			{
				swap(ptr, ptr1);
				ptr++;
				ptr1++;
			}
			break;
		}
		ptr1 += LEN;
	}
	cout << '\n';
	readArray(*arr);
	cout << "\nПерестановка столбца:\n";
	ptr = *arr;
	ptr1 = *arr;
	for (int j = 0; j < LEN; j++)
	{
		if (j == column) {
			for (int i = 0; i < LEN; i++)
			{
				swap(ptr, ptr1);
				ptr += LEN;
				ptr1 += LEN;
			}
			break;
		}
		ptr1++;
	}

	cout << '\n';
	readArray(*arr);
}

void bubbleSort(int* arr, int n) {
	int* ptr = arr;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (*(ptr + j) > *(ptr + j + 1)) {
				swap(*(ptr + j), *(ptr + j + 1));
			}
		}
	}
}

int main() {
	SetConsoleTitle(L"Practical Work 3");
	setlocale(0, "");
	consoleCursorVisible(false, 100);
	createRandArray(*arr);
	while (true)
	{
		system("CLS");

		cout << "---------------- MENU ----------------\n";

		for (int i = 0; i < size(menu); i++)
		{
			if (activeMenu == i) {
				cout << ">\033[93m";
			}
			cout << "  " << menu[i] << endl;
			cout << "\033[37m";
		}

		inputButton = _getch();

		if (inputButton == ARROY) {
			inputButton = _getch();
		}
		switch (inputButton)
		{
		case ESC:
			exit(0);
		case UP:
			if (activeMenu == 0) {
				activeMenu = size(menu) - 1;
			}
			else {
				activeMenu--;
			}
			break;
		case DOWN:
			if (activeMenu == size(menu) - 1) {
				activeMenu = 0;
			}
			else {
				activeMenu++;
			}
			break;
		case ENTER:
			switch (activeMenu)
			{
			case 0:
				//Вывести матрицу
				system("CLS");
				readArray(*arr);
				_getch();
				break;
			case 1:
				//Заполнить матрицу по спирали
				system("CLS");
				printSpiral(*arr);
				_getch();
				break;
			case 2:
				//Заполнить матрицу змейкой
				system("CLS");
				printSnake2(*arr);
				_getch();
				break;
			case 3:
				//Перестановка по квадрату
				system("CLS");
				squareSwap(*arr);
				_getch();
				break;
			case 4:
				//Перестановка по кресту
				system("CLS");
				сhristianSwap(*arr);
				_getch();
				break;
			case 5:
				//Перестановка по вертикальной оси
				system("CLS");
				verticalSwap(*arr);
				_getch();
				break;
			case 6:
				//Перестановка по горизонтальной оси
				system("CLS");
				horizontalSwap(*arr);
				_getch();
				break;
			case 7:
				//Отсортировать
				system("CLS");
				readArray(*arr);
				//quickSort(*arr, 0, LEN * LEN);
				bubbleSort(*arr, LEN * LEN);
				cout << '\n';
				readArray(*arr);
				_getch();
				break;
			case 8:
				//Арифметические операции
				system("CLS");
				readArray(*arr);
				cout << '\n';
				operationsArrays(*arr);
				_getch();
				break;
			case 9:
				//ИДЗ
				system("CLS");
				readArray(*arr);
				cout << '\n';
				idz(*arr);
				_getch();
				break;
			case 10:
				system("CLS");
				cout << "SEE YOU SPACE COWBOY...";
				exit(0);
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
	return 0;
}



