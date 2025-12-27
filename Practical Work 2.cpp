#include <windows.h>;
#include <conio.h>;
#include <iostream>
#include <string>;
#include <chrono>

using namespace std;
using namespace std::chrono;

const char ARROY = -32;
const char UP = 72;
const char DOWN = 80;
const char ESC = 27;
const char ENTER = 13;
const int LEN_ARRAY = 100;

int activeMenu = 0;
char inputButton;
bool arrayExist = false;

int arr[LEN_ARRAY];
int notSortedArray[LEN_ARRAY];

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

string menu[] = { "Создать массив", "Отсортировать массив",
"Найти максимальный и минимальный элемент массива", "Найти среднее значение",
"Найти количество элементов < a", "Найти количество элементов > a",
"Найти число в массиве", "Поменять местами числа по индексам", "ИДЗ", "Выход" };

void consoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show; // изменяем видимость курсора
	structCursorInfo.dwSize = size; // изменяем размер курсора
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

void readArray(int* array) {
	for (int i = 0; i < LEN_ARRAY; i++)
		cout << array[i] << ' ';
}

int binarySearch(int* arr, int& target) {
	int start = 0, end = LEN_ARRAY - 1;
	while (start <= end) {
		int mid = start + (end - start) / 2;
		if (arr[mid] == target) return mid;
		if (arr[mid] < target) start = mid + 1;
		else end = mid - 1;
	}
	return -1;
}

void quickSort(int* arr, int begin, int end) {
	if (begin >= end) return;

	int left = begin;
	int right = end;
	int mid = arr[(left + right) / 2];

	while (left <= right) {
		while (arr[left] < mid) left++;
		while (arr[right] > mid) right--;

		if (left <= right) {
			std::swap(arr[left], arr[right]);
			left++;
			right--;
		}
	}

	if (begin < right) quickSort(arr, begin, right);
	if (left < end) quickSort(arr, left, end);
}

void bubbleSort(int* arr) {
	bool sortedFlag;
	for (int i = 0; i < LEN_ARRAY; i++) {
		sortedFlag = false;
		for (int j = 0; j < LEN_ARRAY - i - 1; j++) {
			if (arr[j + 1] < arr[j]) {
				swap(arr[j + 1], arr[j]);
				sortedFlag = true;
			}
		}
		if (!sortedFlag) break;
	}
}

void shakerSort(int* arr) {
	int left = 0, right = LEN_ARRAY - 1;
	while (left < right) {
		bool swapped = false;
		// Проход слева направо
		for (int i = left; i < right; ++i) {
			if (arr[i] > arr[i + 1]) {
				swap(arr[i], arr[i + 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
		--right;

		swapped = false;
		// Проход справа налево
		for (int i = right; i > left; --i) {
			if (arr[i] < arr[i - 1]) {
				swap(arr[i], arr[i - 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
		++left;
	}
}

void insertionSort(int* arr) {
	for (int i = 1; i < LEN_ARRAY; i++) {
		int key = arr[i];
		int j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
	}
}

void selectionSort(int* arr) {
	for (int i = 0; i < LEN_ARRAY - 1; ++i) {
		int minIdx = i;
		for (int j = i + 1; j < LEN_ARRAY; ++j) {
			if (arr[j] < arr[minIdx]) {
				minIdx = j;
			}
		}
		swap(arr[i], arr[minIdx]);
	}
}

void searchMediumIndex(int* array, int& medium) {
	int count = 0;
	cout << "Индексы: ";
	for (int i = 0; i < LEN_ARRAY; i++) {
		if (array[i] == medium) {
			cout << i << ' ';
			count++;
		}
	}
	cout << " Количество: " << count;
}

void searchMediumIndex2(int* sortedArray, int& medium) {
	int count = 0;
	int idx = binarySearch(sortedArray, medium);
	cout << "Индексы: ";
	if (idx != -1) {
		for (int i = idx; i < LEN_ARRAY; i++) {
			if (sortedArray[i] == medium) {
				cout << i << ' ';
				count++;
			}
			else {
				break;
			}
		}
		for (int i = idx - 1; i > 0; i--) {
			if (sortedArray[i] == medium) {
				cout << i << ' ';
				count++;
			}
			else {
				break;
			}
		}
	}
	cout << " Количество: " << count;
}

void createRandArray(int* array) {
	srand(time(NULL));
	for (int i = 0; i < LEN_ARRAY; ++i) {
		array[i] = rand() % 199 - 99;
	}
	arrayExist = true;
	copy(array, array + LEN_ARRAY, notSortedArray);
}

int main() {
	SetConsoleTitle(L"Practical Work 2");
	setlocale(0, "");
	consoleCursorVisible(false, 100);

	while (true)
	{
		system("CLS");

		for (int i = 0; i < size(menu); i++)
		{
			if (i == size(menu) - 1) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN |
					FOREGROUND_INTENSITY);
			}
			else if (i == activeMenu & !arrayExist & i > 0) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED |
					FOREGROUND_INTENSITY);
			}
			else if (i == activeMenu) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN |
					FOREGROUND_INTENSITY);
			}
			else if (!arrayExist & i > 0) {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
			}
			else {
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}

			cout << menu[i] << endl;
		}

		SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
		cout << "\n" << "Текущий массив: ";
		if (arrayExist) {
			readArray(notSortedArray);
		}
		else {
			cout << "Пока не создан";
		}
		SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);

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
			if (!arrayExist & activeMenu == size(menu) - 1) {
				exit(0);
			}
			if (arrayExist | activeMenu == 0)
				switch (activeMenu)
				{
				case 0:
					//Создание массива
					createRandArray(arr);
					break;
				case 1: {
					//Сортировка массива на выбор
					system("CLS");

					//Быстрая сортировка
					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start1, end1;
					nanoseconds duration1;
					start1 = high_resolution_clock::now();
					quickSort(arr, 0, LEN_ARRAY - 1);
					end1 = high_resolution_clock::now();
					duration1 = duration_cast<nanoseconds>(end1 - start1);

					readArray(arr);

					cout << "\nБыстрая сортировка завершена за "
						<< duration1.count() << " наносекунд.\n";
					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);

					//Пузырьковая сортировка
					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start2, end2;
					nanoseconds duration2;
					start2 = high_resolution_clock::now();
					bubbleSort(arr);
					end2 = high_resolution_clock::now();
					duration2 = duration_cast<nanoseconds>(end2 - start2);

					cout << "\nBubble sort завершен за "
						<< duration2.count() << " наносекунд.\n";
					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);

					//Сортировка шейкер
					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start3, end3;
					nanoseconds duration3;
					start3 = high_resolution_clock::now();
					shakerSort(arr);
					end3 = high_resolution_clock::now();
					duration3 = duration_cast<nanoseconds>(end3 - start3);

					cout << "\nСортирвока шейкер завершена за "
						<< duration3.count() << " наносекунд.\n";
					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);

					//Сортировка выбором
					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start4, end4;
					nanoseconds duration4;
					start4 = high_resolution_clock::now();
					selectionSort(arr);
					end4 = high_resolution_clock::now();
					duration4 = duration_cast<nanoseconds>(end4 - start4);

					cout << "\nСортировка выбором завершна за "
						<< duration4.count() << " наносекунд.\n";
					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);

					//Сортировка вставками
					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start5, end5;
					nanoseconds duration5;
					start5 = high_resolution_clock::now();
					insertionSort(arr);
					end5 = high_resolution_clock::now();
					duration5 = duration_cast<nanoseconds>(end5 - start5);

					cout << "\nСортирвока вставками завершена за "
						<< duration5.count() << " наносекунд.\n";
					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);

					_getch();
					break;
				}
				case 2: {
					//Найти максимальный и минимальный элемент массива
					system("CLS");

					int mini, maxi;

					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
					nanoseconds duration1;
					start = high_resolution_clock::now();

					mini = notSortedArray[0], maxi = notSortedArray[0];
					for (int i = 1; i < LEN_ARRAY; i++) {
						if (notSortedArray[i] < mini) {
							mini = notSortedArray[i];
						}
						else if (notSortedArray[i] > maxi) {
							maxi = notSortedArray[i];
						}
					}

					end = high_resolution_clock::now();
					duration1 = duration_cast<nanoseconds>(end - start);

					cout << "Поиск в неотсортированном массиве завершен за "
						<< duration1.count() << " наносекунд.\n";
					cout << "Минимальный элемент: " << mini << " Максимальный элемент: " << maxi;

					quickSort(arr, 0, LEN_ARRAY - 1);

					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start2, end2;
					nanoseconds duration2;
					start2 = high_resolution_clock::now();

					mini = arr[0], maxi = arr[LEN_ARRAY - 1];

					end2 = high_resolution_clock::now();
					duration2 = duration_cast<nanoseconds>(end2 - start2);

					cout << "\nПоиск в отсортированном массиве завершен за "
						<< duration2.count() << " наносекунд.\n";
					cout << "Минимальный элемент: " << mini << " Максимальный элемент: " << maxi;

					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);
					_getch();
					break;
				}
				case 3: {
					//Найти среднее значение
					system("CLS");

					int mini, maxi, medium;

					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
					nanoseconds duration1;
					start = high_resolution_clock::now();

					mini = notSortedArray[0], maxi = notSortedArray[0];
					for (int i = 1; i < LEN_ARRAY; i++) {
						if (notSortedArray[i] < mini) {
							mini = notSortedArray[i];
						}
						else if (notSortedArray[i] > maxi) {
							maxi = notSortedArray[i];
						}
					}

					medium = (mini + maxi) / 2;
					searchMediumIndex(notSortedArray, medium);

					end = high_resolution_clock::now();
					duration1 = duration_cast<nanoseconds>(end - start);

					cout << "\nСреднее значение: " << medium;
					cout << "\nПоиск в неотсортированном массиве завершен за "
						<< duration1.count() << " наносекунд.\n\n";

					quickSort(arr, 0, LEN_ARRAY - 1);

					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start2, end2;
					nanoseconds duration2;
					start2 = high_resolution_clock::now();

					mini = arr[0], maxi = arr[LEN_ARRAY - 1];
					medium = (mini + maxi) / 2;
					searchMediumIndex2(arr, medium);

					end2 = high_resolution_clock::now();
					duration2 = duration_cast<nanoseconds>(end2 - start2);

					cout << "\nСреднее значение: " << medium;
					cout << "\nПоиск в отсортированном массиве завершен за "
						<< duration2.count() << " наносекунд.\n";

					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);
					_getch();
					break;
				}
				case 4: {
					//Найти количество элементов < a
					system("CLS");

					quickSort(arr, 0, LEN_ARRAY - 1);

					int inputNum;
					cout << "Введите число a: ";
					cin >> inputNum;

					int count = 0;
					cout << "Числа < a: ";
					for (int i = 0; i < LEN_ARRAY; i++) {
						if (arr[i] < inputNum) {
							cout << arr[i] << ' ';
							count++;
						}
					}
					cout << "\nКоличество: " << count;

					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);
					_getch();
					break;
				}
				case 5: {
					//Найти количество элементов > a
					system("CLS");

					quickSort(arr, 0, LEN_ARRAY - 1);

					int inputNum;
					cout << "Введите число a: ";
					cin >> inputNum;

					int count = 0;
					cout << "Числа > a: ";
					for (int i = 0; i < LEN_ARRAY; i++) {
						if (arr[i] > inputNum) {
							cout << arr[i] << ' ';
							count++;
						}
					}
					cout << "\nКоличество: " << count;

					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);
					_getch();
					break;
				}
				case 6: {
					//Найти число в массиве
					system("CLS");

					quickSort(arr, 0, LEN_ARRAY - 1);
					readArray(arr);

					int inputNum;
					cout << "\n\nВведите число: ";
					cin >> inputNum;

					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
					nanoseconds duration1;
					start = steady_clock::now();
					int idxNum = binarySearch(arr, inputNum);
					end = steady_clock::now();
					duration1 = duration_cast<nanoseconds>(end - start);

					if (idxNum != -1) {
						cout << "S: Число " << inputNum << " находится в массиве под индексом "
							<< idxNum << '\n';
					}
					else {
						cout << "S: Числа " << inputNum << " нет в массиве" << '\n';
					}

					cout << "\nПоиск в отсортированном массиве завершен за "
						<< duration1.count() << " наносекунд.\n";

					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start2, end2;
					nanoseconds duration2;
					start2 = steady_clock::now();
					int idxNum1;
					for (int i = 0; i < LEN_ARRAY; i++)
					{
						if (notSortedArray[i] == inputNum) {
							idxNum1 = 1;
						}
					}
					end2 = steady_clock::now();
					duration2 = duration_cast<nanoseconds>(end2 - start2);

					cout << "\nПоиск простым перебором завершен за "
						<< duration2.count() << " наносекунд.\n";

					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);
					_getch();
					break;
				}
				case 7: {
					//Поменять местами числа по индексам
					system("CLS");

					quickSort(arr, 0, LEN_ARRAY - 1);
					readArray(arr);

					int i, j;
					cout << "\n\nВведите индексы элементов:\n";
					cin >> i >> j;

					if (i < 0 || i >= LEN_ARRAY || j < 0 || j >= LEN_ARRAY) {
						cout << "Ошибка: недопустимые индексы." << endl;
						_getch();
						break;
					}

					cout << "\nМассив до:";
					for (int k = 0; k < LEN_ARRAY; k++) {
						if (k == i || k == j) {
							cout << "\033[31m" << arr[k] << " \033[0m";
						}
						else {
							cout << "\033[32m" << arr[k] << ' ';
						}
					}

					time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
					nanoseconds duration;
					start = steady_clock::now();
					swap(arr[i], arr[j]);
					end = steady_clock::now();
					duration = duration_cast<nanoseconds>(end - start);

					cout << "\nМассив после:";
					for (int k = 0; k < LEN_ARRAY; k++) {
						if (k == i || k == j) {
							cout << "\033[31m" << arr[k] << " \033[0m";
						}
						else {
							cout << "\033[32m" << arr[k] << ' ';
						}
					}
					cout << "\n\nЗамена завершена за " << duration.count() << " наносекунд.\n";

					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);
					_getch();
					break;
				}
				case 8: {
					//ИДЗ
					system("CLS");

					cout << "Программа заменяет отрицательные числа их модулем, а положительные их квадратом";
					quickSort(arr, 0, LEN_ARRAY - 1);

					cout << "\nМассив до: ";
					readArray(arr);

					for (int i = 0; i < LEN_ARRAY; i++)
					{
						if (arr[i] < 0) {
							arr[i] = abs(arr[i]);
						}
						else {
							arr[i] = arr[i] * arr[i];
						}
					}
					cout << "\n\nМассив после: ";
					readArray(arr);

					int squares[LEN_ARRAY];

					for (int i = 0; i < LEN_ARRAY; i++)
					{
						int num = i + 1;
						squares[i] = num * num;
					}

					int count = 0;

					for (int i = 0; i < LEN_ARRAY; i++)
					{
						int result = binarySearch(squares, arr[i]);
						if (result != -1) {
							count++;
						}
					}
					cout << "\nКоличество квадратов в массиве: " << count;

					copy(notSortedArray, notSortedArray + LEN_ARRAY, arr);
					_getch();
					break;
				}
				case 9:
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