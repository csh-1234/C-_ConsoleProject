#include <iostream>
#include <windows.h>
#include "Manager.h"
#include "InputManager.h"
#include <conio.h>  // _getch() ���

using namespace std;

/*
�ܼ� ������Ʈ
09/27(��) ~ 10/04(��) ��ǥ
1. ��� ����(09/26 ���۵���̺� ���ε�)
- ���� ����
- ��� ���� ���
- 000 ����( ex) 000�� Ȱ��)
2. ������Ʈ ������ ���
- ���������ϰ� �� ����������
- �ٽ����� ��ɸ� ����
*/

const int WIDTH = 50;
const int HEIGHT = 50;

char map[HEIGHT][WIDTH] = {
    {'��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��','��', '��', '��', '��', '��', '��', '��', '��', '��', '��','��', '��', '��', '��', '��', '��', '��', '��', '��', '��','��', '��', '��', '��', '��', '��', '��', '��', '��', '��'},
    {'��', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '��',},
    {'��', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '��',},
    {'��', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '��',},
    {'��', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '��',},
    {'��', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '.','.', '.', '.', '.', '.', '.', '.', '.', '.', '��',},
      {'��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��', '��','��', '��', '��', '��', '��', '��', '��', '��', '��', '��','��', '��', '��', '��', '��', '��', '��', '��', '��', '��','��', '��', '��', '��', '��', '��', '��', '��', '��', '��'},
};

void drawMap() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            // ���� ���ϴ� �Ǵ� �¿� �׵θ��� ���
            if (y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) {
                std::cout << "��";  // �׵θ��� '#'�� ǥ��
            }
            else {
                std::cout << "  ";  // ���δ� �� �������� ǥ��
            }
        }
        std::cout << std::endl;  // �ٹٲ�
    }
}

void clearScreen()
{
    std::cout << "\033[H";  // Ŀ���� �� ���� �̵�
}

// �÷��̾� ��ġ
int playerX = 1;
int playerY = 1;

// ȭ�� ���� ����
std::string buffer[HEIGHT];

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

void renderBuffer() {
    // ���ۿ� ����� ȭ���� �ֿܼ� ���
    for (int y = 0; y < HEIGHT; ++y) {
        std::cout << buffer[y] << std::endl;
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
    //drawToBuffer();

    drawMap();
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
    return 0;

    //// �ܼ� �̸� ����
    //SetConsoleTitle(TEXT("abcde"));

    //system("mode con:cols=150 lines=50");

    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 18);
    //cout << "press any key" << endl;
    //system("pause");
    
    //while (true)
    //{
    //    //InputManager::Input::Initialize();
    //    //InputManager::Input::Update();
    //    Manager& managers = Manager::getInstance();
    //    Manager::getInputManager().Initialize;
    //    Manager::getInputManager().Update;
    //}
}