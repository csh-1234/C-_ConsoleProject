#pragma once
#include <iostream>
#include <Windows.h>
#include "Manager.h"
#include <conio.h>
#include "Player.h"
#include "Monster.h"
#include <string>
#include <cwchar>
#include <locale.h>
#include "Skill.h"
#include "IPotion.h"
#include "FireBall.h"
#include "Meteor.h"
#include "Heal.h"
#include "Enums.h"
#include "ConsoleDraw.h"
#include "ConsolePopup.h"
#pragma warning(disable:4996)

using namespace std;

class Game
{
public:
    int Title();
    void InGame();

    #pragma region TitleMethod
    void drawIntro();
    int menuDraw();
    void DrawOneWords(const std::string& text, int delay);
#pragma endregion

    #pragma region Util
    void gotoxy(int x, int y);
    void CursorView();
    void clearScreen();
    void inputAnyKey();
    void PlayerSetStatusByLevel();
#pragma endregion

    #pragma region MapRender
    void DrawBuffer(Map* currentMap);
    void renderBuffer(Map* currentMap);
#pragma endregion

    #pragma region UIMethod
    void DrawEmptyImage(ConsoleDraw& consoleDrawBuffer);
    void DrawSlimeImage(ConsoleDraw& consoleDrawBuffer);
    void DrawGoblinImage(ConsoleDraw& consoleDrawBuffer);
    void DrawSkeletonImage(ConsoleDraw& consoleDrawBuffer);
    void DrawInvisableDragonImage(ConsoleDraw& consoleDrawBuffer);
    void DrawBattleChoiceAttack(ConsoleDraw& consoleDrawBuffer);
    void DrawBattleChoiceSkill(ConsoleDraw& consoleDrawBuffer);
    void DrawBattleChoiceInven(ConsoleDraw& consoleDrawBuffer);
    void DrawBattleChoiceRunAway(ConsoleDraw& consoleDrawBuffer);
    bool PlayerDead(ConsoleDraw& consoleDrawBuffer);
    void DrawSkillList(ConsoleDraw& consoleDrawBuffer);
    void DrawInvenList(ConsoleDraw& consoleDrawBuffer);
    void DrawBattleUI(ConsoleDraw& consoleDrawBuffer);
    void DrawMessageBox(ConsoleDraw& consoleDraw, const std::wstring& message);
    void DrawMessageBox2(ConsoleDraw& consoleDraw, const std::wstring& message);
    void DrawMessageBox3(ConsoleDraw& consoleDraw, const std::wstring& message);
#pragma endregion

    #pragma region BattleMethod
    void MovePlayer(Map* currentMap);
    void printUserInfo(ConsoleDraw& consoleDrawBuffer);
    void MonsterTurn(ConsoleDraw& consoleDrawBuffer);
    void PlayerAttack(ConsoleDraw& consoleDrawBuffer);
    bool MonsterDead(ConsoleDraw& consoleDrawBuffer);
#pragma endregion

private:
    Player* player;
    Monster* monster;
    Map* currentMap;
    const int MAP_WIDTH = 100;
    const int MAP_HEIGHT = 50;
    int buffer[50][100];
    int playerX = 23;
    int playerY = 23;
    const int ViewSizeX = 24; 
    const int ViewSizeY = 16;
    #pragma region IntroText
    string IntroText
= R"(




                    옛날 옛적, 평화로운 한 마을이 있었다. 

                    이 마을은 산과 들, 푸른 강이 어우러진 아름다운 곳으로, 주민들은 서로 돕고 평화롭게 살아가고 있었다. 

                    그러나 어느 날, 이 평화를 깨뜨린 무서운 소식이 전해졌다. 마을 근처 산속 깊은 곳에서 살던 투명드래곤 깨어난 것이다.

                    투명드래곤은 울부짖으며 하늘을 가로지르고, 마을을 향해 다가왔다. 

                    마을 사람들은 공포에 휩싸였고, 누구도 감히 용에게 맞설 엄두를 내지 못했다. 

                    투명드래곤이 마을에 도착하자, 집들을 불태우고 들판을 황폐화시키기 시작했다.
      
                    그 때, 투명드래곤에 맞서기 위해 칼을 뽑아든 자가 있었으니....
        
                    당신의 이름은?  
)";
#pragma endregion
};

