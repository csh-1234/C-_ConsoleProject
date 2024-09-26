#include <iostream>
#include <windows.h>
#include "Manager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include <conio.h>  // _getch() ���


const int WIDTH = 50;
const int HEIGHT = 50;

char map[HEIGHT][WIDTH] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '#', '#', '#', '#', '#', '.', '.', '#'},
    {'#', '.', '.', '.', '.', '.', '#', '.', '.', '#'},
    {'#', '#', '#', '#', '#', '.', '#', '.', '.', '#'},
    {'#', '.', '.', '.', '#', '.', '#', '.', '.', '#'},
    {'#', '.', '#', '.', '#', '.', '#', '#', '#', '#'},
    {'#', '.', '#', '.', '.', '.', '.', '.', '.', '#'},
    {'#', '.', '.', '.', '#', '#', '#', '#', '.', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

void clearScreen()
{
    std::cout << "\033[H";  // Ŀ���� �� ���� �̵�
}

// �÷��̾� ��ġ
int playerX = 1;
int playerY = 1;

// ȭ�� ���� ����
std::string buffer[HEIGHT];

void drawMap() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == playerX && y == playerY) {
                std::cout << 'P';  // �÷��̾� ��ġ
            }
            else {
                std::cout << map[y][x];  // �� ���
            }
        }
        std::cout << std::endl;
    }
}
void renderBuffer() {
    // ���ۿ� ����� ȭ���� �ֿܼ� ���
    for (int y = 0; y < HEIGHT; ++y) {
        std::cout << buffer[y] << std::endl;
    }
}

void drawToBuffer() {
    for (int y = 0; y < HEIGHT; ++y) {
        buffer[y] = "";  // ���� �ʱ�ȭ
        for (int x = 0; x < WIDTH; ++x) {
            if (x == playerX && y == playerY) {
                buffer[y] += 'P';  // �÷��̾� ��ġ�� ���ۿ� �׸���
            }
            else {
                buffer[y] += map[y][x];  // ���� ���ۿ� �׸���
            }
        }
    }
}

void movePlayer(char input) {
    int newX = playerX;
    int newY = playerY;

    if (input == 'w') newY--;  // ���� �̵�
    else if (input == 's') newY++;  // �Ʒ��� �̵�
    else if (input == 'a') newX--;  // �������� �̵�
    else if (input == 'd') newX++;  // ���������� �̵�

    // ��� �� �� �浹 �˻�
    if (map[newY][newX] == '.') {
        playerX = newX;
        playerY = newY;
    }
}
void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
int main()
{
    char input;
    CursorView();

    // ���簢�� ���� 9:4
    SetConsoleTitle(TEXT("abcde"));
    system("mode con:cols=45 lines=20");

    drawMap();
    while (true) {  
        drawToBuffer();
        system("cls");
        renderBuffer();
        //clearScreen();
        input = _getch();
        movePlayer(input);
    }
    return 0;

    //while (true) {  
   //    // ȭ���� �׸� ���ۿ� �ʰ� �÷��̾� ������ ����
   //    drawToBuffer();

   //    // ���� ������ ȭ�鿡 ���
   //    //system("cls");  // �� ���� ���� ���۸��� ������ ������ ���� ����
   //    clearScreen();
   //    renderBuffer();

   //    // ����� �Է� �ޱ�
   //    input = _getch();
   //    movePlayer(input);
   //}
}