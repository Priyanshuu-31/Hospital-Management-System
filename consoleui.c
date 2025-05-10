// consoleui.c
#include <windows.h>
#include <stdio.h>
#include "consoleui.h"

void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    system("pause");
}
