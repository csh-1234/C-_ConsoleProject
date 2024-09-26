#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
using namespace std;

const int WIDTH = 10;
const int HEIGHT = 10;


string test[3]
{
    "(a'-'a)"
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


string map[HEIGHT][WIDTH] = {
    {"□", "□", "□", "□", "□", "□", "□", "□", "□", "□"},
    {"□", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "□"},
    {"□", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "□"},
    {"□", "  ", "○" , "  ", "  ", "  ", "  ", "  ", "  ", "□"},
    {"□", " |", "▽", "| ", "  ", "  ", "  ", "  ", "  ", "□"},
    {"□", "  ", "∩" , "  ", "  ", "  ", "  ", "  ", "  ", "□"},
    {"□", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "□"},
    {"□", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "□"},
    {"□", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "  ", "□"},
    {"□", "□", "□", "□", "□", "□", "□", "□", "□", "□"}
};

int playerX = 1;
int playerY = 1;

void DrawMap()
{
    for (size_t i = 0; i < WIDTH; i++)
    {
        for (size_t j = 0; j < HEIGHT; j++)
        {
            cout << map[i][j];
        }
        cout << endl;
    }
}
void drawMap() {
    for (int y = 0; y < 14; ++y) {
        for (int x = 0; x < 56; ++x) {
            // 맵의 상하단 또는 좌우 테두리인 경우
            if (y == 0 || y == 14 - 1 || x == 0 || x == 56 - 1) {
                std::cout << "■";  // 테두리는 '#'로 표시
            }
            else {
                std::cout << "  ";  // 내부는 빈 공간으로 표시
            }
        }
        std::cout << std::endl;  // 줄바꿈
    }
}
/*
00 01 02 03
10 11 12 13
20 21 22 23
30 31 32 33
*/

void PlayerMove(char dir)
{
    int dx = playerX;
    int dy = playerY;

    if (dir == 'w'){ dy--;}
    else if (dir == 's'){dy++;}
    else if (dir == 'a'){dx++;}
    else if (dir == 'd'){dx--;}
    map[dx][dy] = 10;

}

int main()
{    
    SetConsoleTitle(TEXT("abcde"));
    system("mode con:cols=10 lines=10");
    char input = 0;

    //렌더링 순서 : 
    //for (size_t i = 0; i < 10; i++)
    //{
    //    for (size_t j = 0; j < 10; j++)
    //    {
    //        if (map2[i][j] == 1)
    //        {
    //            cout << "■";
    //        }
    //        else
    //        {
    //            cout << "  ";
    //        }
    //        
    //    }
    //    cout << endl;
    //}
    DrawMap();
    //drawMap();
    //while (true)
    //{
    //    
    //    system("cls");
    //    //input = _getch();
    //    //PlayerMove(input);
    //}
}