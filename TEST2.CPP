// #include <iostream>
// #include <windows.h>
// #include <string>
// #include <vector>
// #include <conio.h>

// void gotoxy(int x, int y)
// {
//     COORD coord;
//     coord.X = x;
//     coord.Y = y;
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
// }

// void getConsoleSize(int &width, int &height)
// {
//     CONSOLE_SCREEN_BUFFER_INFO csbi;
//     GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//     width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//     height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
// }

// void clearScreen()
// {
//     COORD topLeft = {0, 0};
//     HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//     CONSOLE_SCREEN_BUFFER_INFO screen;
//     DWORD written;

//     GetConsoleScreenBufferInfo(console, &screen);
//     FillConsoleOutputCharacterA(
//         console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
//     FillConsoleOutputAttribute(
//         console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
//         screen.dwSize.X * screen.dwSize.Y, topLeft, &written);
//     SetConsoleCursorPosition(console, topLeft);
// }

// void printCentered(const std::string &str, int consoleWidth, int y)
// {
//     int startX = (consoleWidth - str.length()) / 2;
//     gotoxy(startX, y);
//     std::cout << str << std::endl;
// }

// bool menu()
// {
//     std::string title = ".-*-.-*-.-* QUAN LY THU VIEN *-.-*-.-*-.";
//     std::vector<std::string> menuOptions = {
//         "1. QUAN LY SACH",
//         "2. QUAN LY PHIEU MUON",
//         "Backspace: Back",
//         "Esc: Exit"};

//     int previousWidth = 0, previousHeight = 0;

//     while (true)
//     {
//         int width, height;
//         getConsoleSize(width, height);

//         // Chỉ cập nhật màn hình nếu kích thước console thay đổi
//         if (width != previousWidth || height != previousHeight)
//         {
//             clearScreen();

//             int menuStartY = (height - menuOptions.size()) / 2; // Cập nhật vị trí bắt đầu của menu
//             printCentered(title, width, menuStartY - 1);        // In tiêu đề ở trên các lựa chọn menu

//             for (int i = 0; i < menuOptions.size(); ++i)
//             {
//                 printCentered(menuOptions[i], width, menuStartY + i); // In các lựa chọn menu thẳng hàng dọc
//             }

//             previousWidth = width;
//             previousHeight = height;
//         }

//         if (_kbhit())
//         {
//             char key = _getch();
//             switch (key)
//             {
//             case '1':
//                 // Quản lý sách
//                 break;
//             case '2':
//                 // Quản lý phiếu mượn
//                 break;
//             case 8: // Backspace
//                 return false;
//             case 27: // Escape
//                 return true;
//             default:
//                 // Xử lý các phím khác nếu cần
//                 break;
//             }
//         }

//         Sleep(100);
//     }
// }

// int main()
// {
//     menu();
//     return 0;
// }
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <conio.h>
#include <cmath>

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

void printCentered(const std::string &title, const std::vector<std::string> &options, int consoleWidth, int consoleHeight)
{
    int titleLength = title.length();
    int titleStartX = (consoleWidth - titleLength) / 2;
    int titleStartY = (consoleHeight - options.size()) / 2; // Y position for the title

    gotoxy(titleStartX, titleStartY - 1);
    std::cout << title << std::endl;

    // Find the longest string in the options to align left
    size_t longestOptionLength = 0;
    for (const auto &option : options)
    {
        longestOptionLength = std::max(longestOptionLength, option.length());
    }

    // Calculate the start X position for the left-aligned options
    int optionsStartX = titleStartX + (titleLength - longestOptionLength) / 2;

    // Print each menu option left-aligned
    for (size_t i = 0; i < options.size(); ++i)
    {
        gotoxy(optionsStartX, titleStartY + i);
        std::cout << options[i] << std::endl;
    }
}

bool menu()
{
    std::string title = ".-*-.-*-.-* QUAN LY THU VIEN *-.-*-.-*-.";
    std::vector<std::string> menuOptions = {
        "1. QUAN LY SACH",
        "2. QUAN LY PHIEU MUON",
        "Backspace: Back",
        "Esc: Exit"};

    int previousWidth = 0, previousHeight = 0;

    while (true)
    {
        int width, height;
        getConsoleSize(width, height);

        // Only update the screen if the console size changes
        if (width != previousWidth || height != previousHeight)
        {
            // clearScreen();
            system("cls");
            printCentered(title, menuOptions, width, height);
            previousWidth = width;
            previousHeight = height;
        }

        if (_kbhit())
        {
            char key = _getch();
            switch (key)
            {
            case '1':
                // Quản lý sách
                break;
            case '2':
                // Quản lý phiếu mượn
                break;
            case 8: // Backspace
                return false;
            case 27: // Escape
                return true;
            default:
                // Handle other keys if needed
                break;
            }
        }

        Sleep(100);
    }
}

int main()
{
    menu();
    return 0;
}
