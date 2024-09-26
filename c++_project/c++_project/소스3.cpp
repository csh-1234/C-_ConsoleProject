#include <iostream>
#include <windows.h>
#include "Manager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include <conio.h>  // _getch() 사용


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
    std::cout << "\033[H";  // 커서를 맨 위로 이동
}

// 플레이어 위치
int playerX = 1;
int playerY = 1;

// 화면 버퍼 정의
std::string buffer[HEIGHT];

void drawMap() {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (x == playerX && y == playerY) {
                std::cout << 'P';  // 플레이어 위치
            }
            else {
                std::cout << map[y][x];  // 맵 출력
            }
        }
        std::cout << std::endl;
    }
}
void renderBuffer() {
    // 버퍼에 저장된 화면을 콘솔에 출력
    for (int y = 0; y < HEIGHT; ++y) {
        std::cout << buffer[y] << std::endl;
    }
}

void drawToBuffer() {
    for (int y = 0; y < HEIGHT; ++y) {
        buffer[y] = "";  // 버퍼 초기화
        for (int x = 0; x < WIDTH; ++x) {
            if (x == playerX && y == playerY) {
                buffer[y] += 'P';  // 플레이어 위치를 버퍼에 그리기
            }
            else {
                buffer[y] += map[y][x];  // 맵을 버퍼에 그리기
            }
        }
    }
}

void movePlayer(char input) {
    int newX = playerX;
    int newY = playerY;

    if (input == 'w') newY--;  // 위로 이동
    else if (input == 's') newY++;  // 아래로 이동
    else if (input == 'a') newX--;  // 왼쪽으로 이동
    else if (input == 'd') newX++;  // 오른쪽으로 이동

    // 경계 및 벽 충돌 검사
    if (map[newY][newX] == '.') {
        playerX = newX;
        playerY = newY;
    }
}
void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
int main()
{
    char input;
    CursorView();

    // 정사각형 비율 9:4
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
   //    // 화면을 그릴 버퍼에 맵과 플레이어 정보를 저장
   //    drawToBuffer();

   //    // 버퍼 내용을 화면에 출력
   //    //system("cls");  // 이 줄을 더블 버퍼링의 장점을 보려면 생략 가능
   //    clearScreen();
   //    renderBuffer();

   //    // 사용자 입력 받기
   //    input = _getch();
   //    movePlayer(input);
   //}
}