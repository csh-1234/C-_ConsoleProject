#include <iostream>
#include <Windows.h>
#include "Manager.h"
#include <conio.h>
using namespace std;

enum class EGameObject
{
    EMPTY = 0,
    WALL = 1,
    PLAYER = 2,
    TREE1 = 3,
    TREE2 = 4,
    MONSTER,
    BOSSMONSTER,
    NPC,
    OBSTACLE,
    STRUCTURE,
    PORTAL,
};

int map1[10][10] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 3, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 3, 3, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 0, 0, 0, 0, 0, 0, 1},
    {1, 4, 4, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int map2[10][10] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};


/*
00 01 02 03 04
10 11 12 13 14
20 21 22 23 24
30 31 32 33 34
40 41 42 43 44
*/

// 좌표를 어떻게 할 것인가
// (y,x) => x값 가로(정방향), y값 세로(반대)
// up : (-1, +0), down (+1, +0), left(0,+1), right(0,-1)
//void DrawMap()
//{
//    map1[playerY][playerX] = 2;
//    for (size_t y = 0; y < 10; y++)
//    {
//        for (size_t x = 0; x < 10; x++)
//        {
//            if (map1[y][x] == 1) cout << "■";
//            else if (map1[y][x] == 2)cout << "★";
//            else cout << "  ";
//        }
//        cout << '\n';
//    }
//}


int playerX = 1;
int playerY = 1;
string buffer[10] = {};



void MovePlayer()
{
    // (y,x)  up : (-1, +0), down (+1, +0), left(0,+1), right(0,-1)
    int newPosX = playerX;
    int newPosY = playerY;
    Manager& manager = Manager::getInstance();

    if (manager.input.GetKeyDown(eKeyCode::Up)) { newPosY -= 1; }
    else if (manager.input.GetKeyDown(eKeyCode::Down)) { newPosY += 1; }
    else if (manager.input.GetKeyDown(eKeyCode::Left)) { newPosX -= 1; }
    else if (manager.input.GetKeyDown(eKeyCode::Right)) { newPosX += 1; }

    if (map1[newPosY][newPosX] == (int)EGameObject::EMPTY)
    {
        playerX = newPosX;
        playerY = newPosY;
    }
    
}

void DrawBuffer()
{
    for (size_t y = 0; y < 10; y++)
    {
        buffer[y] = "";
        for (size_t x = 0; x < 10; x++)
        {
            if (x == playerX && y == playerY)
            {
                buffer[y] += "★";
            }
            else if(map1[y][x] == 1)
            {
                buffer[y] += "■";
            }
            else if (map1[y][x] == 3)
            {
                buffer[y] += "♣";
            }
            else if (map1[y][x] == 4)
            {
                buffer[y] += "♠";
            }
            else
            {
                buffer[y] += "  ";
            }
        }
    }
}
void renderBuffer()
{
    for (size_t y = 0; y < 10; y++)
    {
        cout << buffer[y] << endl;
    }
}

void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void clearScreen()
{
    // 커서를 맨 위로 이동
    std::cout << "\033[H";
}
int main()
{
    CursorView();
    Manager& manager = Manager::getInstance();
    manager.input.Initialize();
    while (true)
    {
        manager.input.Update();
        DrawBuffer();
        renderBuffer();
        clearScreen();
        MovePlayer();
    }
}