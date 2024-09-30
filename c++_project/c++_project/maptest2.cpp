#include <iostream>
#include <Windows.h>
#include "Manager.h"
#include <conio.h>
#include "Player.h"
#include "Knight.h"
#include "Monster.h"


using namespace std;

enum class EGameObject
{
    EMPTY = 0,
    // 1 ~ 10 벽
    WALL = 1,
    PLAYER = 2,
    TREE1 = 3,
    TREE2 = 4,
    MONSTER = 5,
    BOSSMONSTER,
    NPC,
    PORTAL = 9 ,
};

const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 50;

const int VIEWPORT_WIDTH = 20;  // 화면에 표시되는 너비
const int VIEWPORT_HEIGHT = 10; // 화면에 표시되는 높이

Knight* player = new Knight("홍길동");
Monster* monster;

//Monster* monster = new

int playerX = player->GetPosX();
int playerY = player->GetPosY();

string buffer[MAP_HEIGHT] = {};
int buffer2[50][50] = {};

const int ViewSizeX = 100; // 18 12
const int ViewSizeY = 100;


#pragma region 맵핵
//void DrawBuffer()
//{
//    for (size_t y = 0; y < MAP_HEIGHT; y++)
//    {
//        buffer[y] = "";
//        for (size_t x = 0; x < MAP_WIDTH; x++)
//        {
//            if (x == playerX && y == playerY)
//            {
//                buffer[y] += "★";
//            }
//            else if (map1[y][x] == 1)
//            {
//                buffer[y] += "■";
//            }
//            else if (map1[y][x] == 3)
//            {
//                buffer[y] += "♣";
//            }
//            else if (map1[y][x] == 4)
//            {
//                buffer[y] += "♠";
//            }
//            else
//            {
//                buffer[y] += "  ";
//            }
//        }
//    }
//}
//void renderBuffer()
//{
//    for (size_t y = 0; y < MAP_WIDTH; y++)
//    {
//        std::cout << buffer[y] << '\n';
//    }
//}
#pragma endregion
void PrintBattleUI();
void PrintBattleUI2();
void printRightUI();
void PrintKeyboardState();
void PrintMessage();
void printUserInfo();
void clearScreen();

void DrawBuffer2(Map* currentMap)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            buffer2[y][x] = currentMap->at(y,x);
        }
    }
}
void renderBuffer2(Map* currentMap)
{
    int startX = playerX - (ViewSizeX / 2);
    int endX = playerX + (ViewSizeX / 2);
    int startY = playerY - (ViewSizeY / 2);
    int endY = playerY + (ViewSizeY / 2);

    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            // y가 starty보다 크거나 같고 endy 보다 작거나 같다
            if ((startY <= y && y <= endY) && (startX <= x && x <= endX))
            {
                if (x == playerX && y == playerY)
                {
                    std::cout << "★";
                }
                else if (currentMap->at(y, x) == 1)
                {
                    std::cout << "■";
                }
                else if (currentMap->at(y, x) == 3)
                {
                    std::cout << "♣";
                }
                else if (currentMap->at(y, x) == 4)
                {
                    std::cout << "♠";
                }
                else if (currentMap->at(y, x) == 5)
                {
                    std::cout << "▼";
                }
                else if (currentMap->at(y, x) == 9)
                {
                    std::cout << "▩";
                }
                else
                {
                    std::cout << "  ";
                }
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << endl;
    }
}
void MovePlayer(Map* currentMap)

{
    // (y,x)  up : (-1, +0), down (+1, +0), left(0,+1), right(0,-1)
    int newPosX = playerX;
    int newPosY = playerY;
    Manager& manager = Manager::getInstance();

    if (manager.input.GetKeyDown(eKeyCode::Up)) { newPosY -= 1; }
    else if (manager.input.GetKeyDown(eKeyCode::Down)) { newPosY += 1; }
    else if (manager.input.GetKeyDown(eKeyCode::Left)) { newPosX -= 1; }
    else if (manager.input.GetKeyDown(eKeyCode::Right)) { newPosX += 1; }


    switch (currentMap->at(newPosY, newPosX))
    {
    case (int)EGameObject::PORTAL:
    {
        for (int i = 0; i < manager.map.PortalList.size(); i++)
        {
            if(manager.map.PortalList[i].CurrentMap == manager.map.GetcurrenteMap() &&
                manager.map.PortalList[i].PortalPos == make_pair(newPosY, newPosX))
            { 
                manager.map.UnloadMap(manager.map.GetcurrenteMap());
                manager.map.LoadMap(manager.map.PortalList[i].NextMap);
                playerX = manager.map.PortalList[i].PlayerStartPos.first;
                playerY = manager.map.PortalList[i].PlayerStartPos.second;
                break;
            }
        }
        break;
    }
    case (int)EGameObject::MONSTER:
    {
        monster = new Monster(MonsterType::SLIME);
        while (true)
        {
            clearScreen();
            //printUserInfo();
            //PrintKeyboardState();
            //PrintMessage();
            //PrintBattleUI();
            //PrintBattleUI2();
            
        }
        break;
    }
    case (int)EGameObject::EMPTY:
    {
        playerX = newPosX;
        playerY = newPosY;
        break;
    }
    
    default:
        break;
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

void gotoxy(int x, int y)
{
    HANDLE consolHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consolHandle, pos);
}

// 맵 -> 맵
// 맵 -> 전투씬

void printRightUI()
{
    gotoxy(104, 0);
    std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    for (size_t i = 1; i < 49; i++)
    {
        gotoxy(104, i);
        std::cout << "┃                                               ┃";
    }
    gotoxy(104, 49);
    std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";
    //clearScreen();
}
void printUserInfo()
{
    Manager& manager = Manager::getInstance();
    gotoxy(106, 5);
    std::cout << "              [플레이어  정보]" << endl;
    gotoxy(110, 6);
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    gotoxy(110, 7);
    std::cout << "이름 : " << player->GetName() << std::endl;
    gotoxy(110, 8);
    std::cout << "체력 / 최대체력 : " << player->GetHp() << " / " << player->GetMaxHp() << std::endl;
    gotoxy(110, 9);
    std::cout << "마나 / 최대마나 : " << player->GetMp() << " / " << player->GetMaxMp() << std::endl;
    gotoxy(110, 10);
    std::cout << "공격력 : " << player->GetAtk() << std::endl;
    gotoxy(110, 11);
    std::cout << "방어력 : " << player->GetDef() << std::endl;
    gotoxy(110, 12);
    std::cout << "크리티컬 확률 : " << player->GetCriRate() << std::endl;
    gotoxy(110, 13);
    std::cout << "크리티컬 데미지 : " << player->GetCriDamage() << std::endl;
    gotoxy(110, 14);
    std::cout << "회피율 : " << player->GetAvoidRate() << std::endl;
    gotoxy(110, 15);
    std::cout << "속도 : " << player->GetSpeed() << std::endl;
    gotoxy(110, 16);
    std::cout << "소지금 : " << player->GetMoney() << std::endl;
    gotoxy(110, 17);
    std::cout << "현재 위치 : " << manager.map.GetMapName(manager.map.GetcurrenteMap()) << std::endl;
    gotoxy(110, 18);
    std::cout << "스킬 : " << "스킬" << std::endl;
}
void PrintKeyboardState()
{
    Manager& manager = Manager::getInstance();
    
    gotoxy(106, 35);
    std::cout << "                [키보드  입력]";
    gotoxy(110, 36);
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
#pragma region DirectionKeys
    gotoxy(110, 38);
    std::cout << "방향키 : " << endl;
    gotoxy(122, 37);
    if (manager.input.GetKeyDown(eKeyCode::Up) || manager.input.GetKey(eKeyCode::Up))
    {
        std::cout << "■" << endl;
    }
    else
    {
        std::cout << "□" << endl;
    }
    gotoxy(120, 38);
    if (manager.input.GetKeyDown(eKeyCode::Left) || manager.input.GetKey(eKeyCode::Left))
    {
        std::cout << "■" << endl;
    }
    else
    {
        std::cout << "□" << endl;
    }
    gotoxy(122, 38);
    if (manager.input.GetKeyDown(eKeyCode::Down) || manager.input.GetKey(eKeyCode::Down))
    {
        std::cout << "■" << endl;
    }
    else
    {
        std::cout << "□" << endl;
    }
    gotoxy(124, 38);
    if (manager.input.GetKeyDown(eKeyCode::Right) || manager.input.GetKey(eKeyCode::Right))
    {
        std::cout << "■" << endl;
    }
    else
    {
        std::cout << "□" << endl;
    }

    gotoxy(128, 38);
    std::cout << "스페이스 : " << endl;
    gotoxy(140, 38);
    if (manager.input.GetKeyDown(eKeyCode::Space) || manager.input.GetKey(eKeyCode::Space))
    {
        std::cout << "■■■■" << endl;
    }
    else
    {
        std::cout << "□□□□" << endl;
    }
#pragma endregion

#pragma region KeyBoardKeys
    gotoxy(110, 40);
    if (manager.input.GetKeyDown(eKeyCode::Q) || manager.input.GetKey(eKeyCode::Q)) std::cout << "●";
    else std::cout << "ⓠ";
    gotoxy(112, 40);
    if (manager.input.GetKeyDown(eKeyCode::W) || manager.input.GetKey(eKeyCode::W)) std::cout << "●";
    else std::cout << "ⓦ";
    gotoxy(114, 40);
    if (manager.input.GetKeyDown(eKeyCode::E) || manager.input.GetKey(eKeyCode::E)) std::cout << "●";
    else std::cout << "ⓔ";
    gotoxy(116, 40);
    if (manager.input.GetKeyDown(eKeyCode::R) || manager.input.GetKey(eKeyCode::R)) std::cout << "●";
    else std::cout << "ⓡ";
    gotoxy(118, 40);
    if (manager.input.GetKeyDown(eKeyCode::T) || manager.input.GetKey(eKeyCode::T)) std::cout << "●";
    else std::cout << "ⓣ";
    gotoxy(120, 40);
    if (manager.input.GetKeyDown(eKeyCode::Y) || manager.input.GetKey(eKeyCode::Y)) std::cout << "●";
    else std::cout << "ⓨ";
    gotoxy(122, 40);
    if (manager.input.GetKeyDown(eKeyCode::U) || manager.input.GetKey(eKeyCode::U)) std::cout << "●";
    else std::cout << "ⓤ";
    gotoxy(124, 40);
    if (manager.input.GetKeyDown(eKeyCode::I) || manager.input.GetKey(eKeyCode::I)) std::cout << "●";
    else std::cout << "ⓘ";
    gotoxy(126, 40);
    if (manager.input.GetKeyDown(eKeyCode::O) || manager.input.GetKey(eKeyCode::O)) std::cout << "●";
    else std::cout << "ⓠ";
    gotoxy(128, 40);
    if (manager.input.GetKeyDown(eKeyCode::P) || manager.input.GetKey(eKeyCode::P)) std::cout << "●";
    else std::cout << "ⓟ";
    
    gotoxy(110, 41);
    if (manager.input.GetKeyDown(eKeyCode::A) || manager.input.GetKey(eKeyCode::A)) std::cout << "●";
    else std::cout << "ⓐ";
    gotoxy(112, 41);
    if (manager.input.GetKeyDown(eKeyCode::S) || manager.input.GetKey(eKeyCode::S)) std::cout << "●";
    else std::cout << "ⓢ";
    gotoxy(114, 41);
    if (manager.input.GetKeyDown(eKeyCode::D) || manager.input.GetKey(eKeyCode::D)) std::cout << "●";
    else std::cout << "ⓓ";
    gotoxy(116, 41);
    if (manager.input.GetKeyDown(eKeyCode::F) || manager.input.GetKey(eKeyCode::F)) std::cout << "●";
    else std::cout << "ⓕ";
    gotoxy(118, 41);
    if (manager.input.GetKeyDown(eKeyCode::G) || manager.input.GetKey(eKeyCode::G)) std::cout << "●";
    else std::cout << "ⓖ";
    gotoxy(120, 41);
    if (manager.input.GetKeyDown(eKeyCode::H) || manager.input.GetKey(eKeyCode::H)) std::cout << "●";
    else std::cout << "ⓗ";
    gotoxy(122, 41);
    if (manager.input.GetKeyDown(eKeyCode::J) || manager.input.GetKey(eKeyCode::J)) std::cout << "●";
    else std::cout << "ⓙ";
    gotoxy(124, 41);
    if (manager.input.GetKeyDown(eKeyCode::K) || manager.input.GetKey(eKeyCode::K)) std::cout << "●";
    else std::cout << "ⓚ";
    gotoxy(126, 41);
    if (manager.input.GetKeyDown(eKeyCode::L) || manager.input.GetKey(eKeyCode::L)) std::cout << "●";
    else std::cout << "ⓛ";

    gotoxy(110, 42);
    if (manager.input.GetKeyDown(eKeyCode::Z) || manager.input.GetKey(eKeyCode::Z)) std::cout << "●";
    else std::cout << "ⓩ";
    gotoxy(112, 42);
    if (manager.input.GetKeyDown(eKeyCode::X) || manager.input.GetKey(eKeyCode::X)) std::cout << "●";
    else std::cout << "ⓧ";
    gotoxy(114, 42);
    if (manager.input.GetKeyDown(eKeyCode::C) || manager.input.GetKey(eKeyCode::C)) std::cout << "●";
    else std::cout << "ⓒ";
    gotoxy(116, 42);
    if (manager.input.GetKeyDown(eKeyCode::V) || manager.input.GetKey(eKeyCode::V)) std::cout << "●";
    else std::cout << "ⓥ";
    gotoxy(118, 42);
    if (manager.input.GetKeyDown(eKeyCode::B) || manager.input.GetKey(eKeyCode::B)) std::cout << "●";
    else std::cout << "ⓑ";
    gotoxy(120, 42);
    if (manager.input.GetKeyDown(eKeyCode::N) || manager.input.GetKey(eKeyCode::N)) std::cout << "●";
    else std::cout << "ⓝ";
    gotoxy(122, 42);
    if (manager.input.GetKeyDown(eKeyCode::M) || manager.input.GetKey(eKeyCode::M)) std::cout << "●";
    else std::cout << "ⓜ";
    


#pragma endregion
}
void PrintMessage() //TODO
{
    
    gotoxy(4, 35);
    std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    for (size_t i = 36; i < 47; i++)
    {
        gotoxy(4, i);
        std::cout << "┃                                                                                         ┃";
    }
    gotoxy(4, 47);
    std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";

    gotoxy(16, 41);
    std::cout << "아이템 을(를) 획득하셨습니다.";
}
void PrintBattleUI()
{
    gotoxy(30, 10); 
    std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓";
    for (size_t i = 11; i < 29; i++)
    {
        gotoxy(30, i);
        std::cout << "┃                                     ┃";
    }
    gotoxy(30, 29);
    std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";


    gotoxy(5, 30);
    std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━┓";
    for (size_t i = 31; i < 45; i++)
    {
        gotoxy(5, i);
        std::cout << "┃                      ┃";
    }
    gotoxy(13, 32);
    std::cout << "행동 선택";
    gotoxy(6, 34);
    std::cout << " ━━━━━━━━━━━━━━━━━━━━ ";
    gotoxy(10, 36);
    std::cout << "공격";
    gotoxy(10, 38);
    std::cout << "스킬";
    gotoxy(10, 40);
    std::cout << "인벤토리";
    gotoxy(10, 42);
    std::cout << "도망치기";
    gotoxy(5, 45);
    std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━┛";
}

void PrintBattleUI2()
{
    gotoxy(5, 30);
    std::cout << "┏━━━━━━━━━━━━━━━━━━━━━━┓";
    for (size_t i = 31; i < 45; i++)
    {
        gotoxy(5, i);
        std::cout << "┃                      ┃";
    }
    gotoxy(13, 32);
    std::cout << "행동 선택";
    gotoxy(6, 34);
    std::cout << " ━━━━━━━━━━━━━━━━━━━━ ";
    gotoxy(10, 36);
    std::cout << "공격";
    gotoxy(10, 38);
    std::cout << "스킬";
    gotoxy(10, 40);
    std::cout << "인벤토리";
    gotoxy(10, 42);
    std::cout << "도망치기";
    gotoxy(5, 45);
    std::cout << "┗━━━━━━━━━━━━━━━━━━━━━━┛";
}

// 몬스터가 있다 -> 싸움시 동적할당?


int main()
{
    system("mode con:cols=155 lines=51");
    CursorView();
    Manager& manager = Manager::getInstance();
    manager.input.Initialize();
    manager.map.Initialize();
    manager.map.LoadMap(eMaps::Village);

    Map* currentmap;
    ////currentmap = manager.map.GetCurrentMap();
    //DrawBuffer2(currentmap);
    //renderBuffer2(currentmap);
    //PrintBattleUI();
    //printRightUI();
    //printUserInfo();
    //PrintKeyboardState();
    //PrintMessage();
    while (true)
    {
        clearScreen();
        manager.input.Update();
        currentmap = manager.map.GetCurrentMap();
        DrawBuffer2(currentmap);
        renderBuffer2(currentmap);
        MovePlayer(currentmap);
 /*       printRightUI();
        printUserInfo();
        PrintKeyboardState();*/
     
        
    }
}