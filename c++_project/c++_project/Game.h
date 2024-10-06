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




                    ���� ����, ��ȭ�ο� �� ������ �־���. 

                    �� ������ ��� ��, Ǫ�� ���� ��췯�� �Ƹ��ٿ� ������, �ֹε��� ���� ���� ��ȭ�Ӱ� ��ư��� �־���. 

                    �׷��� ��� ��, �� ��ȭ�� ���߸� ������ �ҽ��� ��������. ���� ��ó ��� ���� ������ ��� ����巡�� ��� ���̴�.

                    ����巡���� ���¢���� �ϴ��� ����������, ������ ���� �ٰ��Դ�. 

                    ���� ������� ������ �۽ο���, ������ ���� �뿡�� �¼� ���θ� ���� ���ߴ�. 

                    ����巡���� ������ ��������, ������ ���¿�� ������ Ȳ��ȭ��Ű�� �����ߴ�.
      
                    �� ��, ����巡�￡ �¼��� ���� Į�� �̾Ƶ� �ڰ� �־�����....
        
                    ����� �̸���?  
)";
#pragma endregion
};

