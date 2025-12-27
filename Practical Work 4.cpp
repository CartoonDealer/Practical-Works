#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>;
#include <conio.h>;
#include <iomanip>
#include <cstring>

using namespace std;

const char ARROY = -32;
const char UP = 72;
const char DOWN = 80;
const char ESC = 27;
const char ENTER = 13;
const int LEN = 300;

int activeMenu = 0;
char inputButton;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

char s[LEN] = {'\0'};
char pattern[LEN] = {'\0'};
char fileName[56] = "C:\\Users\\nusha\\source\\repos\\PracticalWork4\\texttt.txt";

char alph[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
char endMask[] = { '!', '?', '.', ','};
char numb[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

string menu[] = { "Ввести последовательность вручную", "Открыть файл", "Редактировать текст",
"Вывести на экран слова последовательности, не содержащие цифр", 
"Вывести на экран ту же последовательность, удалив из всех слов заданный набор букв и (или) цифр",
"Найти подстроку", "Выход" };

void consoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show; 
    structCursorInfo.dwSize = size; 
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

bool readFile(char* FileName)
{
    ifstream File;   
    File.open(FileName);  
    if (!File.is_open())  
    {
        cout << "Открыть файл не удалось!\n";
        return 0;   
    }
    File.getline(s, LEN);
    File.close();
    return 1;
}

unsigned myStrLen(char* S) {
    unsigned L = 0;
    while (S[L])  
        ++L;
    return L;
}

void delChar(char* s, int idx) {
    for (int i = idx; i < strlen(s) - 1; i++) {
        s[i] = s[i + 1];
    }
    s[strlen(s) - 1] = '\0';
}

void delSomeChars(char* s, int idx, int len) {
    for (int i = idx; i < strlen(s) - len; i++) {
        s[i] = s[i + len];
    }
    s[strlen(s) - len] = '\0';
}

int isLetter(char b) {
    char a = tolower(b);
    for (int k = 0; k <= size(alph) - 1; k++) {
        if (a == alph[k]) {
            return 1;
        }
    }
    return 0;
}

int isNumber(char a) {
    for (int k = 0; k <= size(numb) - 1; k++) {
        if (a == numb[k]) {
            return 1;
        }
    }
    return 0;
}

int isEndSign(char a) {
    for (int k = 0; k <= size(endMask) - 1; k++) {
        if (a == endMask[k]) {
            return 1;
        }
    }
    return 0;
}

void editString(char* str) {
    if (str == nullptr) return;

    char* src = str;
    char* dst = str;
    bool inWhitespace = false;
    bool inPunctuation = false;
    int dotCount = 0; 

    while (*src) {
        if (*src == ' ') {
            if (!inWhitespace) {
                *dst++ = *src; 
                inWhitespace = true;
            }
        }
        else if (isEndSign(*src)) {
            if (*src == '.') {
                dotCount++;
                if (dotCount <= 3) { 
                    *dst++ = *src;
                }
            }
            else {
                if (!inPunctuation) {
                    *dst++ = *src;
                    inPunctuation = true;
                }
                dotCount = 0; 
            }
        }
        else {
            *dst++ = *src; 
            inWhitespace = false;
            inPunctuation = false;
            dotCount = 0; 
        }
        src++;
    }
    *dst = '0';

    bool newSentence = true;
    for (char* p = str; *p; ++p) {
        if (newSentence && isLetter(*p)) {
            *p = toupper(*p); 
            newSentence = false;
        }
        else if (*p == '.' || *p == '!' || *p == '?') {
            newSentence = true; 
        }
        else {
            *p = tolower(*p); 
        }
    }

    cout << "\nИзмененнная строка:\n" << s;
}

int searchSubstringLinearly(char* s, char* pattern) {
    int n = strlen(s); 
    int m = strlen(pattern); 

    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (s[i + j] != pattern[j])
                break;
        }

        if (j == m) 
            return i; 
    }

    return -1; 
}

void printWithNoNums(char* s) {
    for (int i = 0; i < strlen(s) - 1; i++) {
        if (isNumber(s[i])) {
            continue;
        }
        cout << s[i];
    }
}

void delInputSymbols(char* s, char* pattern) {
    int start = searchSubstringLinearly(s, pattern);
    int len = myStrLen(pattern);
    delSomeChars(s, start, len);
}

int* computeLps(char* pattern, int n) {
    int* lpsArr = new int[n];
    lpsArr[0] = 0;

    int len = 0;
    int i = 1;

    while (i < n) {
        if (pattern[i] == pattern[len]) {
            len++;
            lpsArr[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lpsArr[len - 1];
            }
            else {
                lpsArr[i] = 0;
                i++;
            }
        }
    }

    return lpsArr;
}

void kmp(char* s, char* pattern, int patternLen) {
    int* lps = computeLps(pattern, patternLen);
    int n = strlen(s);
    int m = patternLen;

    int i = 0; // индекс по тексту
    int j = 0; // индекс по шаблону

    while (i < n) {
        if (s[i] == pattern[j]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << (i - j) << ' ';
            j = lps[j - 1];
        }
        else if (i < n && s[i] != pattern[j]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
}

int main()
{
    SetConsoleTitle(L"Practical Work 4");
    setlocale(0, "");
    consoleCursorVisible(false, 100);
    
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
                //Ввести последовательность вручную
                system("CLS");
                cin.getline(s, LEN);
                cout << s;
                _getch();
                break;
            case 1:
                //Открыть файл
                system("CLS");
                readFile(fileName);
                cout << s;
                _getch();
                break;
            case 2:
            {
                //Редактировать текст
                system("CLS");
                cout << "Исходная строка:\n" << s;
                editString(s);
                _getch();
                break;
            }
            case 3:
                //Вывести на экран слова последовательности, не содержащие цифр
                system("CLS");
                printWithNoNums(s);
                _getch();
                break;
            case 4:
            {
                //Вывести на экран ту же последовательность, 
                //удалив из всех слов заданный набор букв и (или) цифр
                system("CLS");
                cout << "Исходная строка:\n" << s;
                cout << "\nВведите последовательность, которую нужно удалить: ";
                cin.getline(pattern, LEN);
                delInputSymbols(s, pattern);
                cout << s;
                _getch();
                break;
            }
            case 5:
            {
                //Найти подстроку
                system("CLS");
                cout << "Исходная строка:\n" << s;
                cout << "\nВведите последовательность, которую нужно найти: ";
                cin.getline(pattern, LEN);

                cout << "\nЛинейный поиск:";

                int result = searchSubstringLinearly(s, pattern);
                if (result == -1)
                    cout << "\nПодстрока не найдена" << endl;
                else
                    cout << "\nПодстрока найдена в позиции: " << result << endl;

                cout << "\nАлгоритм Кнута:";

                int patternLen = myStrLen(pattern);
                kmp(s, pattern, patternLen);

                _getch();
                break;
            }
            case 6:
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
}