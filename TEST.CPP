#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <conio.h>

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void getConsoleSize(int &width, int &height)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

void clearScreen()
{
    COORD topLeft = {0, 0};
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
    SetConsoleCursorPosition(console, topLeft);
}

void printTableCentered(int tableWidth, int tableHeight, int consoleWidth, int consoleHeight, int i)
{
    int startX = (consoleWidth - tableWidth) / 2;
    int startY = (consoleHeight - tableHeight) / 2;
    gotoxy(startX, startY + i);
}

void printRow(const std::string &row, int startX, int y)
{
    gotoxy(startX, y);
    std::cout << row << std::endl;
}

void runConsoleProgram()
{
    std::vector<std::string> table = {
        " MA SACH | NGAY MUON | NGAY PHAI TRA ",
        "-------------------------------------",
        " sach1   | 2/08/2023 | 9/08/2023    ",
        " sach2   | 2/08/2023 | 9/08/2023    ",
        " sach4   | 2/08/2023 | 9/08/2023    "};

    int previousWidth = 0, previousHeight = 0;

    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 27)
            {
                break;
            }
        }

        int width, height;
        getConsoleSize(width, height);

        if (width != previousWidth || height != previousHeight)
        {
            clearScreen();
            int tableWidth = table[0].length();
            int tableHeight = table.size();

            for (int i = 0; i < tableHeight; ++i)
            {
                printTableCentered(tableWidth, tableHeight, width, height, i);
                printRow(table[i], (width - tableWidth) / 2, (height - tableHeight) / 2 + i);
            }

            previousWidth = width;
            previousHeight = height;
        }

        Sleep(100);
    }
}

int main()
{
    runConsoleProgram();
    return 0;
}
