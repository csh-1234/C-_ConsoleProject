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
#pragma warning(disable:4996)
using namespace std;
#pragma region MapSettings
Player* player = new Player("ȫ�浿");
Monster* monster;
Skill* skill;

int playerX = 23;
int playerY = 23;
const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 50;

//string buffer[MAP_HEIGHT] = {};
int buffer[50][100] = {};

const int ViewSizeX = 24; // 18 12
const int ViewSizeY = 16;
#pragma endregion
#pragma region UISettings
class ConsolePopup {
private:
    HANDLE hConsole;

public:
    ConsolePopup()
    {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void DrawUserInfo(int startX, int startY, int endX, int endY, const std::wstring& title = L"") {
        // â �׵θ� �׸���
        DrawAt(startX, startY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX, y, L"��");
            DrawAt(endX, y, L"��");
        }
        DrawAt(startX, endY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");

        // ���� �׸��� (�ִ� ���)
        if (!title.empty()) {
            //int titleX = startX + (endX - startX - title.length()) / 2;
            int titleX = startX + (endX - startX - title.length()) / 2 - 4;
            DrawAt(titleX, startY, title);
        }

        // â ���� �����
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();

        DrawAt(startX + 4, startY + 2, L"���� : " + to_wstring(player->GetLevel()));
        wstring wstr(player->GetName().size(), L'\0');
        std::mbstowcs(&wstr[0], player->GetName().c_str(), player->GetName().size());
        DrawAt(startX + 4, startY + 3, L"�̸� : " + wstr);
        DrawAt(startX + 4, startY + 4, L"ü�� / �ִ�ü�� : " + to_wstring(player->GetHp()) + L" / " + to_wstring(player->GetMaxHp()));
        DrawAt(startX + 4, startY + 5, L"���� / �ִ븶�� : " + to_wstring(player->GetMp()) + L" / " + to_wstring(player->GetMaxMp()));
        DrawAt(startX + 4, startY + 6, L"���ݷ� : " + to_wstring(player->GetAtk()));
        DrawAt(startX + 4, startY + 7, L"���� : " + to_wstring(player->GetDef()));
        DrawAt(startX + 4, startY + 8, L"ũ��Ƽ�� Ȯ�� : " + to_wstring(player->GetCriRate()) + L"%");
        DrawAt(startX + 4, startY + 9, L"ũ��Ƽ�� ������ :" + to_wstring(player->GetCriDamage()) + L"%");
        DrawAt(startX + 4, startY + 10, L"����ġ :" + to_wstring(player->GetExp()));
        string mapName = manager.map.GetMapName(manager.map.GetcurrenteMap());
        wstring wstr2(mapName.size(), L'\0');
        std::mbstowcs(&wstr2[0], mapName.c_str(), mapName.size());
        DrawAt(startX + 4, startY + 11, L"���� ��ġ :" + wstr2);
        DrawAt(startX + 4, startY + 12, L"���� ��ǥ(x,y) :" +
            to_wstring(player->GetPosX()) + L", " + to_wstring(player->GetPosY()));

    }
    void DrawUserInventory(int startX, int startY, int endX, int endY, const std::wstring& title = L"") {
        // â �׵θ� �׸���
        DrawAt(startX, startY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX, y, L"��");
            DrawAt(endX, y, L"��");
        }
        DrawAt(startX, endY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");

        // ���� �׸��� (�ִ� ���)
        if (!title.empty()) {
            //int titleX = startX + (endX - startX - title.length()) / 2;
            int titleX = startX + (endX - startX - title.length()) / 2 - 4;
            DrawAt(titleX, startY, title);
        }

        // â ���� �����
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();

        wstring wstr(player->getPotionlList()[0]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr[0], player->getPotionlList()[0]->getItemName().c_str()
            , player->getPotionlList()[0]->getItemName().size());
        DrawAt(startX + 4, startY + 2, wstr + L" : " + to_wstring(player->getPotionlList()[0]->getItemQuantity()) + L" ��");

        wstring wstr2(player->getPotionlList()[1]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr2[0], player->getPotionlList()[1]->getItemName().c_str()
            , player->getPotionlList()[1]->getItemName().size());
        DrawAt(startX + 4, startY + 3, wstr2 + L" : " + to_wstring(player->getPotionlList()[1]->getItemQuantity()) + L" ��");

        wstring wstr3(player->getPotionlList()[2]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr3[0], player->getPotionlList()[2]->getItemName().c_str()
            , player->getPotionlList()[2]->getItemName().size());
        DrawAt(startX + 4, startY + 4, wstr3 + L" : " + to_wstring(player->getPotionlList()[2]->getItemQuantity()) + L" ��");

        DrawAt(startX + 4, startY + 8, L"������ : " + to_wstring(player->GetMoney()) + L"���");
    }
    void DrawUserSkill(int startX, int startY, int endX, int endY, const std::wstring& title = L"") {
        // â �׵θ� �׸���
        DrawAt(startX, startY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX, y, L"��");
            DrawAt(endX, y, L"��");
        }
        DrawAt(startX, endY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");

        // ���� �׸��� (�ִ� ���)
        if (!title.empty()) {
            //int titleX = startX + (endX - startX - title.length()) / 2;
            int titleX = startX + (endX - startX - title.length()) / 2 - 4;
            DrawAt(titleX, startY, title);
        }

        // â ���� �����
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();

        wstring wstr(player->getActiveSkillList()[0]->getSkillName().size(), L'\0');
        std::mbstowcs(&wstr[0], player->getActiveSkillList()[0]->getSkillName().c_str()
            , player->getActiveSkillList()[0]->getSkillName().size());
        wstring wstr2(player->getActiveSkillList()[0]->gertSkillInfo().size(), L'\0');
        std::mbstowcs(&wstr2[0], player->getActiveSkillList()[0]->gertSkillInfo().c_str()
            , player->getActiveSkillList()[0]->gertSkillInfo().size());
        DrawAt(startX + 4, startY + 2, L" LV : " + to_wstring(player->getActiveSkillList()[0]->getSkillLevel()) + L"  " + wstr);
        DrawAt(startX + 4, startY + 3, L" " + wstr2);

        wstring wstr3(player->getActiveSkillList()[1]->getSkillName().size(), L'\0');
        std::mbstowcs(&wstr3[0], player->getActiveSkillList()[1]->getSkillName().c_str()
            , player->getActiveSkillList()[1]->getSkillName().size());
        wstring wstr4(player->getActiveSkillList()[1]->gertSkillInfo().size(), L'\0');
        std::mbstowcs(&wstr4[0], player->getActiveSkillList()[1]->gertSkillInfo().c_str()
            , player->getActiveSkillList()[1]->gertSkillInfo().size());
        DrawAt(startX + 4, startY + 5, L" LV : " + to_wstring(player->getActiveSkillList()[0]->getSkillLevel()) + L"  " + wstr3);
        DrawAt(startX + 4, startY + 6, L" " + wstr4);

        wstring wstr5(player->getActiveSkillList()[2]->getSkillName().size(), L'\0');
        std::mbstowcs(&wstr5[0], player->getActiveSkillList()[2]->getSkillName().c_str()
            , player->getActiveSkillList()[2]->getSkillName().size());
        wstring wstr6(player->getActiveSkillList()[2]->gertSkillInfo().size(), L'\0');
        std::mbstowcs(&wstr6[0], player->getActiveSkillList()[2]->gertSkillInfo().c_str()
            , player->getActiveSkillList()[2]->gertSkillInfo().size());
        DrawAt(startX + 4, startY + 8, L" LV : " + to_wstring(player->getActiveSkillList()[2]->getSkillLevel()) + L"  " + wstr5);
        DrawAt(startX + 4, startY + 9, L" " + wstr6);
    }
    void DrawPotionShop(int startX, int startY, int endX, int endY, const std::wstring& title = L"") {
        // â �׵θ� �׸���
        DrawAt(startX, startY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX, y, L"��");
            DrawAt(endX, y, L"��");
        }
        DrawAt(startX, endY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");

        // ���� �׸��� (�ִ� ���)
        if (!title.empty()) {
            //int titleX = startX + (endX - startX - title.length()) / 2;
            int titleX = startX + (endX - startX - title.length()) / 2 - 4;
            DrawAt(titleX, startY, title);
        }

        // â ���� �����
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();

        wstring wstr(player->getPotionlList()[0]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr[0], player->getPotionlList()[0]->getItemName().c_str()
            , player->getPotionlList()[0]->getItemName().size());
        DrawAt(startX + 4, startY + 2, L"1. " + wstr + L" : " + to_wstring(player->getPotionlList()[0]->getItemPrice()) + L" ���");

        wstring wstr2(player->getPotionlList()[1]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr2[0], player->getPotionlList()[1]->getItemName().c_str()
            , player->getPotionlList()[1]->getItemName().size());
        DrawAt(startX + 4, startY + 3, L"2. " + wstr2 + L" : " + to_wstring(player->getPotionlList()[1]->getItemPrice()) + L" ���");

        wstring wstr3(player->getPotionlList()[2]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr3[0], player->getPotionlList()[2]->getItemName().c_str()
            , player->getPotionlList()[2]->getItemName().size());
        DrawAt(startX + 4, startY + 4, L"3. " + wstr3 + L" : " + to_wstring(player->getPotionlList()[2]->getItemPrice()) + L" ���");

        DrawAt(startX + 4, startY + 5, L"4. ������ ");
    }
    void DrawBuyComplete(int startX, int startY, int endX, int endY)
    {
        DrawAt(startX, startY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX, y, L"��");
            DrawAt(endX, y, L"��");
        }
        DrawAt(startX, endY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");

        // â ���� �����
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();
        DrawAt(startX + 4, startY + 3, L"���ſϷ�!");
    }
    void DrawSkillShop(int startX, int startY, int endX, int endY, const std::wstring& title = L"") {
        // â �׵θ� �׸���
        DrawAt(startX, startY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX, y, L"��");
            DrawAt(endX, y, L"��");
        }
        DrawAt(startX, endY, L"��" + std::wstring(endX - startX - 1, L'��') + L"��");

        // ���� �׸��� (�ִ� ���)
        if (!title.empty()) {
            //int titleX = startX + (endX - startX - title.length()) / 2;
            int titleX = startX + (endX - startX - title.length()) / 2 - 4;
            DrawAt(titleX, startY, title);
        }

        // â ���� �����
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();

        wstring wstr(player->getActiveSkillList()[0]->getSkillName().size(), L'\0');
        std::mbstowcs(&wstr[0], player->getActiveSkillList()[0]->getSkillName().c_str()
            , player->getActiveSkillList()[0]->getSkillName().size());
        DrawAt(startX + 4, startY + 2, L"1. " + wstr + L" : " + to_wstring(/*player->getActiveSkillList()[0]->getSkillLevel() * */1000) + L" ���");

        wstring wstr2(player->getActiveSkillList()[1]->getSkillName().size(), L'\0');
        std::mbstowcs(&wstr2[0], player->getActiveSkillList()[1]->getSkillName().c_str()
            , player->getActiveSkillList()[1]->getSkillName().size());
        DrawAt(startX + 4, startY + 3, L"2. " + wstr2 + L" : " + to_wstring(/*player->getActiveSkillList()[1]->getSkillLevel() * */5000) + L" ���");

        wstring wstr3(player->getActiveSkillList()[2]->getSkillName().size(), L'\0');
        std::mbstowcs(&wstr3[0], player->getActiveSkillList()[2]->getSkillName().c_str()
            , player->getActiveSkillList()[2]->getSkillName().size());
        DrawAt(startX + 4, startY + 4, L"3. " + wstr3 + L" : " + to_wstring(/*player->getActiveSkillList()[1]->getSkillLevel() * */10000) + L" ���");


        DrawAt(startX + 4, startY + 5, L"4. ������ ");
    }
    void DrawAt(int x, int y, const std::wstring& str)
    {
        COORD pos = { (SHORT)x, (SHORT)y };
        DWORD written;
        WriteConsoleOutputCharacterW(hConsole, str.c_str(), str.length(), pos, &written);
    }
};
static ConsoleDraw consoleDrawBuffer(150, 51);
#pragma endregion
#pragma region DrawMonsterImage
void DrawEmptyImage(ConsoleDraw& consoleDrawBuffer) {
    consoleDrawBuffer.DrawAt(30, 10, L"������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(30, 11, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 12, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 13, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 14, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 15, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 16, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 17, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 18, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 19, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 20, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 21, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 22, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 23, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 24, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 25, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 26, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 27, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 28, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 29, L"������������������������������������������������������������������������������");
}
void DrawSlimeImage(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(50, 10, L"��������������������������������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(50, 11, L"�� ������������������ভ   ������   ��");
    consoleDrawBuffer.DrawAt(50, 12, L"�� ������������������ভ��������������������������");
    consoleDrawBuffer.DrawAt(50, 13, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 14, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 15, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 16, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 17, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 18, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 19, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 20, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 21, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 22, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 23, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 24, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 25, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 26, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 27, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 28, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 29, L"������������������������������������������������������������������������������");
}
void DrawGoblinImage(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(50, 10, L"��������������������������������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(50, 11, L"�� ������������������ভ   ���   ��");
    consoleDrawBuffer.DrawAt(50, 12, L"�� ������������������ভ��������������������������");
    consoleDrawBuffer.DrawAt(50, 13, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 14, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 15, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 16, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 17, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 18, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 19, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 20, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 21, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 22, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 23, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 24, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 25, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 26, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 27, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 28, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 29, L"������������������������������������������������������������������������������");
}
void DrawSkeletonImage(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(50, 10, L"��������������������������������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(50, 11, L"�� ������������������ভ  ���̷���  �� ");
    consoleDrawBuffer.DrawAt(50, 12, L"�� ������������������ভ��������������������������");
    consoleDrawBuffer.DrawAt(50, 13, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 14, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 15, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 16, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 17, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 18, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 19, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 20, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 21, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 22, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 23, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 24, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 25, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 26, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 27, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 28, L"�� ������������������ভ");
    consoleDrawBuffer.DrawAt(50, 29, L"������������������������������������������������������������������������������");
}
void DrawInvisableDragonImage(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(50, 10, L"����������������������������������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(50, 11, L"��                                     �� ���� �巡�� �� ");
    consoleDrawBuffer.DrawAt(50, 12, L"��                                     ������������������������������");
    consoleDrawBuffer.DrawAt(50, 13, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 14, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 15, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 16, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 17, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 18, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 19, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 20, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 21, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 22, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 23, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 24, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 25, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 26, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 27, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 28, L"��                                     ��");
    consoleDrawBuffer.DrawAt(50, 29, L"������������������������������������������������������������������������������");
}
#pragma endregion
#pragma region DrawUI
void DrawMessageBox(ConsoleDraw& consoleDraw, const std::wstring& message)
{
    consoleDrawBuffer.DrawAt(35, 30, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(35, 31, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(31, 32, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 33, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 34, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 35, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(33, 36, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(42, 37, message);
    consoleDrawBuffer.DrawAt(32, 38, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 39, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(31, 40, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 41, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(31, 42, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 43, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 44, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 45, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

}
void DrawMessageBox2(ConsoleDraw& consoleDraw, const std::wstring& message)
{
    consoleDrawBuffer.DrawAt(35, 30, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(35, 31, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(31, 32, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 33, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 34, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 35, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(32, 36, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(42, 37, message);
    consoleDrawBuffer.DrawAt(33, 38, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 39, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(31, 40, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 41, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(31, 42, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 43, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 44, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 45, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

}
void DrawMessageBox3(ConsoleDraw& consoleDraw, const std::wstring& message)
{
    consoleDrawBuffer.DrawAt(35, 30, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(35, 31, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(31, 32, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 33, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 34, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 35, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(33, 36, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(42, 37, message);
    consoleDrawBuffer.DrawAt(34, 38, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 39, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(30, 40, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 41, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(31, 42, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 43, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 44, L"��                                                                                         ��");
    consoleDrawBuffer.DrawAt(35, 45, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
}
void DrawBattleChoiceAttack(ConsoleDraw& consoleDrawBuffer) {
    consoleDrawBuffer.DrawAt(10, 30, L"������������������������������������������������");
    consoleDrawBuffer.DrawAt(10, 31, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 32, L"��       �ൿ ����      ��");
    consoleDrawBuffer.DrawAt(10, 33, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 34, L"�� ���������������������������������������� ��");
    consoleDrawBuffer.DrawAt(10, 35, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 36, L"��   �� ����            ��");
    consoleDrawBuffer.DrawAt(10, 37, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 38, L"��    ��ų              ��");
    consoleDrawBuffer.DrawAt(10, 39, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 40, L"��    �κ��丮          ��");
    consoleDrawBuffer.DrawAt(10, 41, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 42, L"��    ����ġ��          ��");
    consoleDrawBuffer.DrawAt(10, 43, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 44, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 45, L"������������������������������������������������");
}
void DrawBattleChoiceSkill(ConsoleDraw& consoleDrawBuffer) {
    consoleDrawBuffer.DrawAt(10, 30, L"������������������������������������������������");
    consoleDrawBuffer.DrawAt(10, 31, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 32, L"��       �ൿ ����      ��");
    consoleDrawBuffer.DrawAt(10, 33, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 34, L"�� ���������������������������������������� ��");
    consoleDrawBuffer.DrawAt(10, 35, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 36, L"��    ����              ��");
    consoleDrawBuffer.DrawAt(10, 37, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 38, L"��   �� ��ų            ��");
    consoleDrawBuffer.DrawAt(10, 39, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 40, L"��    �κ��丮          ��");
    consoleDrawBuffer.DrawAt(10, 41, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 42, L"��    ����ġ��          ��");
    consoleDrawBuffer.DrawAt(10, 43, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 44, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 45, L"������������������������������������������������");
}
void DrawBattleChoiceInven(ConsoleDraw& consoleDrawBuffer) {
    consoleDrawBuffer.DrawAt(10, 30, L"������������������������������������������������");
    consoleDrawBuffer.DrawAt(10, 31, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 32, L"��       �ൿ ����      ��");
    consoleDrawBuffer.DrawAt(10, 33, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 34, L"�� ���������������������������������������� ��");
    consoleDrawBuffer.DrawAt(10, 35, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 36, L"��    ����              ��");
    consoleDrawBuffer.DrawAt(10, 37, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 38, L"��    ��ų              ��");
    consoleDrawBuffer.DrawAt(10, 39, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 40, L"��   �� �κ��丮        ��");
    consoleDrawBuffer.DrawAt(10, 41, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 42, L"��    ����ġ��          ��");
    consoleDrawBuffer.DrawAt(10, 43, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 44, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 45, L"������������������������������������������������");
}
void DrawBattleChoiceRunAway(ConsoleDraw& consoleDrawBuffer) {
    consoleDrawBuffer.DrawAt(10, 30, L"������������������������������������������������");
    consoleDrawBuffer.DrawAt(10, 31, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 32, L"��       �ൿ ����      ��");
    consoleDrawBuffer.DrawAt(10, 33, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 34, L"�� ���������������������������������������� ��");
    consoleDrawBuffer.DrawAt(10, 35, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 36, L"��    ����              ��");
    consoleDrawBuffer.DrawAt(10, 37, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 38, L"��    ��ų              ��");
    consoleDrawBuffer.DrawAt(10, 39, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 40, L"��    �κ��丮          ��");
    consoleDrawBuffer.DrawAt(10, 41, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 42, L"��   �� ����ġ��        ��");
    consoleDrawBuffer.DrawAt(10, 43, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 44, L"��                      ��");
    consoleDrawBuffer.DrawAt(10, 45, L"������������������������������������������������");
}
void DrawSkillList(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(35, 30, L"������������������������������������������������������������������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(35, 31, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(31, 32, L"��        ���̾                                                   ��");
    consoleDrawBuffer.DrawAt(35, 33, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(35, 34, L"��        ��                                                         ��");
    consoleDrawBuffer.DrawAt(35, 35, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(33, 36, L"��        ���׿�                                                     ��");
    consoleDrawBuffer.DrawAt(35, 37, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(32, 38, L"��        �ڷΰ���                                                   ��");
    consoleDrawBuffer.DrawAt(35, 39, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(31, 40, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(35, 41, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(31, 42, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(35, 43, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(35, 44, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(35, 45, L"������������������������������������������������������������������������������������������������������������������������������������������");
}
void DrawInvenList(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(34, 30, L"������������������������������������������������������������������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(34, 31, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(30, 32, L"��        ü�¹���                                                   ��");
    consoleDrawBuffer.DrawAt(34, 33, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(34, 34, L"��        ��������                                                   ��");
    consoleDrawBuffer.DrawAt(34, 35, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(32, 36, L"��        ������                                                     ��");
    consoleDrawBuffer.DrawAt(34, 37, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(32, 38, L"��        �ڷΰ���                                                   ��");
    consoleDrawBuffer.DrawAt(34, 39, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(29, 40, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(34, 41, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(30, 42, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(34, 43, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(34, 44, L"��                                                                   ��");
    consoleDrawBuffer.DrawAt(34, 45, L"������������������������������������������������������������������������������������������������������������������������������������������");
}
void DrawBattleUI(ConsoleDraw& consoleDrawBuffer) {
    consoleDrawBuffer.DrawAt(30, 10, L"������������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(30, 12, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 13, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 14, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 15, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 16, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 17, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 18, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 19, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 20, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 21, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 22, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 23, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 24, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 25, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 26, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 27, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 28, L"��                                     ��");
    consoleDrawBuffer.DrawAt(30, 29, L"������������������������������������������������������������������������������");
}
void printRightUI2(ConsoleDraw& buffer)
{
    buffer.DrawAt(104, 0, L"��������������������������������������������������������������������������������������������������");
    for (size_t i = 1; i < 49; i++)
    {
        buffer.DrawAt(104, i, L"��                                               ��");
    }
    buffer.DrawAt(104, 49, L"��������������������������������������������������������������������������������������������������");
}
void printUserInfo2(ConsoleDraw& consoleDrawBuffer)
{
    Manager& manager = Manager::getInstance();
    consoleDrawBuffer.DrawAt(8, 1, L"������������������������������������������������������������������������");
    consoleDrawBuffer.DrawAt(8, 2, L"          [�÷��̾�  ����]");
    consoleDrawBuffer.DrawAt(10, 3, L"������������������������������������������������������������������");

    wstring wstr(player->GetName().size(), L'\0');
    std::mbstowcs(&wstr[0], player->GetName().c_str(), player->GetName().size());
    consoleDrawBuffer.DrawAt(10, 4, L"�̸� : " + wstr);
    consoleDrawBuffer.DrawAt(10, 5, L"ü�� / �ִ�ü�� : " + to_wstring(player->GetHp()) + L" / " + to_wstring(player->GetMaxHp()));
    consoleDrawBuffer.DrawAt(10, 6, L"���� / �ִ븶�� : " + to_wstring(player->GetMp()) + L" / " + to_wstring(player->GetMaxMp()));
    consoleDrawBuffer.DrawAt(10, 7, L"���ݷ� : " + to_wstring(player->GetAtk()));
    consoleDrawBuffer.DrawAt(10, 8, L"���� : " + to_wstring(player->GetDef()));
    consoleDrawBuffer.DrawAt(8, 9, L"������������������������������������������������������������������������");
    //buffer.DrawAt(10, 8, L"ũ��Ƽ�� Ȯ�� : " + to_wstring(player->GetCriRate()) + L"%");
    //buffer.DrawAt(10, 9, L"ũ��Ƽ�� ������ :" + to_wstring(player->GetCriDamage()) + L"%");
    /*buffer.DrawAt(70, 9, L"ȸ���� :" + to_wstring(player->GetAvoidRate()) + L"%");
    buffer.DrawAt(70, 10, L"�ӵ� :" + to_wstring(player->GetSpeed()));*/
    //buffer.DrawAt(10, 10, L"������ :" + to_wstring(player->GetMoney()) + L"���");

    string mapName = manager.map.GetMapName(manager.map.GetcurrenteMap());
    wstring wstr2(mapName.size(), L'\0');
    std::mbstowcs(&wstr2[0], mapName.c_str(), mapName.size());
    //buffer.DrawAt(10, 11, L"���� ��ġ :" + wstr2);
}
#pragma endregion
#pragma region Utils
void drawIntro()
{
    cout << R"(


             
             
             
             
                            8888888 888b    888 888     888 8888888  .d8888b.  8888888 888888b.   888      8888888888
                              888   8888b   888 888     888   888   d88P  Y88b   888   888  "88b  888      888
                              888   88888b  888 888     888   888   Y88b.        888   888  .88P  888      888
                              888   888Y88b 888 Y88b   d88P   888    "Y888b.     888   8888888K.  888      8888888
                              888   888 Y88b888  Y88b d88P    888       "Y88b.   888   888  "Y88b 888      888
                              888   888  Y88888   Y88o88P     888         "888   888   888    888 888      888
                              888   888   Y8888    Y888P      888   Y88b  d88P   888   888   d88P 888      888
                            8888888 888    Y888     Y8P     8888888  "Y8888P"  8888888 8888888P"  88888888 8888888888
                    
                    
                    
                     8888888b.                                                   .d88888b.                             888
                     888  "Y88b                                                 d88P" "Y88b                            888
                     888    888                                                 888     888                            888
                     888    888 888d888  8888b.   .d88b.   .d88b.  88888b.      888     888 888  888  .d88b.  .d8888b  888888
                     888    888 888P"       "88b d88P"88b d88""88b 888 "88b     888     888 888  888 d8P  Y8b 88K      888
                     888    888 888     .d888888 888  888 888  888 888  888     888 Y8b 888 888  888 88888888 "Y8888b. 888
                     888  .d88P 888     888  888 Y88b 888 Y88..88P 888  888     Y88b.Y8b88P Y88b 888 Y8b.          X88 Y88b.
                     8888888P"  888     "Y888888  "Y88888  "Y88P"  888  888      "Y888888"   "Y88888  "Y8888   88888P'  "Y888
                                                      888                              Y8b
                                                 Y8b d88P
                                                  "Y88P"
             
                                      
                                                      
)";


}
void DrawOneWords(const std::string& text, int delay_ms) {
    for (char ch : text) {
        std::cout << ch;
        Sleep(10);
    }
}
void gotoxy(int x, int y);
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
int menuDraw()
{
    int x = 64;
    int y = 32;
    gotoxy(62, 32);
    cout << "������ ����";
    gotoxy(64, 33);
    cout << "���� ����";
    Manager& manager = Manager::getInstance();
    manager.input.Initialize();
    while (true)
    {
        manager.input.Update();
        if (manager.input.GetKeyDown(eKeyCode::Down))
        {
            if (y == 32)
            {
                gotoxy(x - 2, y);
                cout << "  ";
                gotoxy(x - 2, ++y);
                cout << "��";
            }
        }
        else if (manager.input.GetKeyDown(eKeyCode::Up))
        {
            if (y == 33)
            {
                gotoxy(x - 2, y);
                cout << "  ";
                gotoxy(x - 2, --y);
                cout << "��";
            }
        }

        if (manager.input.GetKeyDown(eKeyCode::Space))
        {
            if (y == 32)
            {
                return 1;
            }
            else if (y == 33)
            {
                return 0;
            }
        }
    }
}
void inputAnyKey()
{
    Manager& manager = manager.getInstance();
    while (true)
    {
        manager.input.Update();
        if (manager.input.GetKeyDown(eKeyCode::Space)) return;
    }
}
void MonsterTurn()
{
    int damage = monster->GetAtk() - player->GetDef();
    if (damage <= 0) damage = 1;
    DrawMessageBox2(consoleDrawBuffer, L"                                                    ");
    DrawMessageBox2(consoleDrawBuffer, L"������ ����!");
    consoleDrawBuffer.Render();
    inputAnyKey();
    DrawMessageBox2(consoleDrawBuffer, L"                                                                      ");

    DrawMessageBox2(consoleDrawBuffer, L"�÷��̾�� " + to_wstring(damage) + L"�������� ���ظ� ����! ");
    player->SetHp(player->GetHp() - damage);
    consoleDrawBuffer.Render();
    inputAnyKey();
    DrawMessageBox2(consoleDrawBuffer, L"                                                                      ");
}
void PlayerAttack()
{
    int damage = player->GetAtk() - monster->GetDef();
    if (damage <= 0) damage = 0;

    DrawMessageBox2(consoleDrawBuffer, L"�÷��̾��� ����!");
    consoleDrawBuffer.Render();
    inputAnyKey();
    DrawMessageBox2(consoleDrawBuffer, L"                                                                      ");

    wstring wstr(monster->GetName().size(), L'\0');
    std::mbstowcs(&wstr[0], monster->GetName().c_str(), monster->GetName().size());
    DrawMessageBox2(consoleDrawBuffer, wstr + L"���� " + to_wstring(damage) + L"�������� ���ظ� ����!");
    monster->SetHp(monster->GetHp() - damage);
    consoleDrawBuffer.Render();
    inputAnyKey();
    DrawMessageBox2(consoleDrawBuffer, L"                                                                      ");
}
bool MonsterDead()
{
    if (monster->GetHp() <= 0)
    {
        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
        DrawMessageBox(consoleDrawBuffer, L"���͸� ����Ʈ��");
        consoleDrawBuffer.Render();
        inputAnyKey();
        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
        DrawMessageBox(consoleDrawBuffer, to_wstring(monster->GetMoney()) + L"��� ȹ��");
        consoleDrawBuffer.Render();
        inputAnyKey();
        DrawMessageBox(consoleDrawBuffer, to_wstring(monster->GetExp()) + L"����ġ ȹ��");
        player->SetMoney(player->GetMoney() + monster->GetMoney());
        player->SetExp(player->GetExp() + monster->GetExp());
        consoleDrawBuffer.Render();
        inputAnyKey();
        system("cls");
        return true;
    }
    return false;
}
bool PlayerDead()
{
    if (player->GetHp() <= 0)
    {
        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
        DrawMessageBox(consoleDrawBuffer, L"�÷��̾ ������");
        consoleDrawBuffer.Render();
        inputAnyKey();
        system("cls");
        return true;
    }
    return false;
}
void PlayerSetStatusByLevel()
{
    int playerLv = (player->GetExp() / 100) + 1;
    if (playerLv != 1)
    {
        player->SetLevel(playerLv);
        player->SetAtk(10 + playerLv * 2);
        player->SetDef(5 + playerLv * 1);
        player->SetCriRate(10 + playerLv / 10);
        player->SetMaxHp(200 + (playerLv) * 50);
        player->SetMaxMp(200 + (playerLv) * 30);
    }
}


void DrawBuffer2(Map* currentMap)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            buffer[y][x] = currentMap->at(y, x);
        }
    }
}
void renderBuffer2(Map* currentMap)
{
    // �ܼ� â ũ�� ���
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth, consoleHeight;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int startX = playerX - (ViewSizeX / 2); // �÷��̾ �߽����� viewSize�� ũ�� ���ݾ� �¿� ������ ����
    int endX = playerX + (ViewSizeX / 2);
    int startY = playerY - (ViewSizeY / 2); // �÷��̾ �߽����� viewSize�� ũ�� ���ݾ� ���� ������ ����
    int endY = playerY + (ViewSizeY / 2);


    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX >= MAP_WIDTH) endX = MAP_WIDTH - 1;
    if (endY >= MAP_HEIGHT) endY = MAP_HEIGHT - 1;

    // ���� ����, ���� ũ��
    int mapWidth = endX - startX + 1;
    int mapHeight = endY - startY + 1;

    //// �ܼ� �߾ӿ� ���߱� ���� ��ǥ ���
    int offsetX = (consoleWidth - mapWidth) / 2 - 20;
    int offsetY = (consoleHeight - mapHeight) / 2;

    //// �� ���߱� ���� ���ʿ� �� �� ���
    for (int i = 0; i < offsetY; ++i)
    {
        std::cout << std::endl;
    }

    // �þ� ���� ������ ��� (X�࿡ ���� �߰�)
    for (int y = startY; y <= endY; ++y)
    {
        //// ���ʿ� ���� �߰��Ͽ� X�� �߾� ����
        for (int i = 0; i < offsetX; ++i)
        {
            std::cout << " ";
        }

        for (int x = startX; x <= endX; ++x)
        {

            /*EMPTY = 0,
              WALL = 1,
              PLAYER = 2,
              TREE1 = 3,
              TREE2 = 4,
              MONSTER = 5,
              BOSSMONSTER = 6,
              NPC = 7,
              TILE1 = 8,
              PORTAL = 9,*/
            if (x == playerX && y == playerY)
            {
                std::cout << "��";
            }
            else if (currentMap->at(y, x) == 1)
            {
                std::cout << "��";
            }
            else if (currentMap->at(y, x) == 3)
            {
                std::cout << "��";
            }
            else if (currentMap->at(y, x) == 4)
            {
                std::cout << "��";
            }
            else if (currentMap->at(y, x) == 5)
            {
                std::cout << "��";

            }
            else if (currentMap->at(y, x) == 7)
            {
                std::cout << "��";
            }
            else if (currentMap->at(y, x) == 9)
            {
                std::cout << "��";
            }
            else
            {
                std::cout << "  ";
            }
        }
        std::cout << std::endl;
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
    case (int)EGameObject::EMPTY:
    {
        playerX = newPosX;
        playerY = newPosY;
        player->SetPosX(newPosX);
        player->SetPosY(newPosY);
        break;
    }
    case (int)EGameObject::PORTAL:
    {
        for (int i = 0; i < manager.map.PortalList.size(); i++)
        {
            if (manager.map.PortalList[i].CurrentMap == manager.map.GetcurrenteMap() &&
                manager.map.PortalList[i].PortalPos == make_pair(newPosY, newPosX))
            {
                manager.map.UnloadMap(manager.map.GetcurrenteMap());
                manager.map.LoadMap(manager.map.PortalList[i].NextMap);
                system("cls");
                playerX = manager.map.PortalList[i].PlayerStartPos.first;
                playerY = manager.map.PortalList[i].PlayerStartPos.second;
                break;
            }
        }
        break;
    }
    case (int)EGameObject::MONSTER:
    {
        //31 14 
        Manager& manager = Manager::getInstance();
        if (manager.map.GetcurrenteMap() == eMaps::BossRoom && newPosX == 31 && newPosY == 14)
        {
            monster = new Monster(MonsterType::INVISIBLEDRAGON);
        }
        else
        {
            switch (rand() % 3)
            {
            case 0:
                monster = new Monster(MonsterType::SLIME);
                break;
            case 1:
                monster = new Monster(MonsterType::GOBLIN);
                break;
            case 2:
                monster = new Monster(MonsterType::SKELETON);
                break;
            default:
                monster = new Monster(MonsterType::SLIME);
                break;
            }
        }

        bool IsdrawSkillList = false;
        bool IsdrawInvenList = false;

        // 1 = attack; 2 = skill 3 = inven; 4 = runawy
        int menuSelect = 1;
        while (true)
        {
            manager.input.Update();

            consoleDrawBuffer.Clear();

            printUserInfo2(consoleDrawBuffer);
            if (monster->GetMonsterType() == MonsterType::SLIME) DrawSlimeImage(consoleDrawBuffer);
            else if (monster->GetMonsterType() == MonsterType::GOBLIN) DrawGoblinImage(consoleDrawBuffer);
            else if (monster->GetMonsterType() == MonsterType::SKELETON)DrawSkeletonImage(consoleDrawBuffer);
            else if (monster->GetMonsterType() == MonsterType::INVISIBLEDRAGON)DrawInvisableDragonImage(consoleDrawBuffer);

            switch (menuSelect)
            {
            case 1: DrawBattleChoiceAttack(consoleDrawBuffer); break;
            case 2: DrawBattleChoiceSkill(consoleDrawBuffer); break;
            case 3: DrawBattleChoiceInven(consoleDrawBuffer); break;
            case 4: DrawBattleChoiceRunAway(consoleDrawBuffer); break;
            default: DrawBattleChoiceAttack(consoleDrawBuffer); break;
            }

            if (manager.input.GetKeyDown(eKeyCode::Down))
            {
                menuSelect++;
                IsdrawSkillList = false;
                IsdrawInvenList = false;
                if (menuSelect == 5) menuSelect = 4;
            }

            if (manager.input.GetKeyDown(eKeyCode::Up))
            {
                menuSelect--;
                IsdrawSkillList = false;
                IsdrawInvenList = false;
                if (menuSelect == 0) menuSelect = 1;
            }

            bool isPlayerDie = false;
            bool isMonsterDie = false;
            if (manager.input.GetKeyDown(eKeyCode::Space))
            {
                //����
                if (menuSelect == 1)
                {
                    int damage;

                    while (true)
                    {
                        manager.input.Initialize();
                        manager.input.Update();

                        PlayerAttack(); //�÷��̾� �Ϲݰ���
                        if (PlayerDead())
                        {
                            isPlayerDie = true;
                            break;
                        }
                        else if (MonsterDead())
                        {
                            isMonsterDie = true;
                            break;
                        }

                        MonsterTurn();
                        if (PlayerDead())
                        {
                            isPlayerDie = true;
                            break;
                        }
                        else if (MonsterDead())
                        {
                            isMonsterDie = true;
                            break;
                        }
                        break;
                    }
                }
                //��ų
                else if (menuSelect == 2)
                {
                    IsdrawSkillList = true;
                    int skillNum = 0;
                    while (true)
                    {
                        manager.input.Update();
                        if (manager.input.GetKeyDown(eKeyCode::Down))
                        {
                            skillNum++;
                            if (skillNum == 4) skillNum = 3;
                        }
                        if (manager.input.GetKeyDown(eKeyCode::Up))
                        {
                            skillNum--;
                            if (skillNum == -1) skillNum = 0;
                        }

                        DrawSkillList(consoleDrawBuffer);

                        switch (skillNum)
                        {
                        case 0: consoleDrawBuffer.DrawAt(38, 32, L"�� ���̾"); break;
                        case 1: consoleDrawBuffer.DrawAt(42, 34, L"�� ��"); break;
                        case 2: consoleDrawBuffer.DrawAt(40, 36, L"�� ���׿�"); break;
                        case 3: consoleDrawBuffer.DrawAt(40, 38, L"�� �ڷΰ���"); break;
                        default:break;
                        }

                        if (manager.input.GetKeyDown(eKeyCode::Space))
                        {
                            consoleDrawBuffer.Clear();

                            if (monster->GetMonsterType() == MonsterType::SLIME) DrawSlimeImage(consoleDrawBuffer);
                            else if (monster->GetMonsterType() == MonsterType::GOBLIN) DrawGoblinImage(consoleDrawBuffer);
                            else if (monster->GetMonsterType() == MonsterType::SKELETON) DrawSkeletonImage(consoleDrawBuffer);
                            DrawBattleChoiceSkill(consoleDrawBuffer);
                            printUserInfo2(consoleDrawBuffer);

                            if (skillNum == 0)
                            {
                                while (true)
                                {
                                    int damage = 0;
                                    manager.input.Initialize();
                                    manager.input.Update();

                                    if (player->GetMp() < player->getActiveSkillList()[0]->getSkillCost())
                                    {
                                        while (true)
                                        {
                                            DrawMessageBox(consoleDrawBuffer, L"��ų ��뿡 �ʿ��� ������ �����մϴ�! ");
                                            consoleDrawBuffer.Render();
                                            inputAnyKey();
                                            break;
                                        }
                                        break;
                                    }
                                    vector<wstring> vec = player->getActiveSkillList()[0]->ActiveSkillCast(player, monster);
                                    for (size_t i = 0; i < vec.size(); i++)
                                    {
                                        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
                                        DrawMessageBox(consoleDrawBuffer, vec[i]);
                                        consoleDrawBuffer.Render();
                                        inputAnyKey();
                                    }

                                    if (PlayerDead())
                                    {
                                        isPlayerDie = true;
                                        break;
                                    }
                                    else if (MonsterDead())
                                    {
                                        isMonsterDie = true;
                                        break;
                                    }
                                    MonsterTurn();
                                    if (PlayerDead())
                                    {
                                        isPlayerDie = true;
                                        break;
                                    }
                                    else if (MonsterDead())
                                    {
                                        isMonsterDie = true;
                                        break;
                                    }
                                    consoleDrawBuffer.Clear();

                                    break;
                                }
                            }
                            else if (skillNum == 1)
                            {
                                while (true)
                                {
                                    int damage = 0;
                                    manager.input.Initialize();
                                    manager.input.Update();

                                    if (player->GetMp() < player->getActiveSkillList()[1]->getSkillCost())
                                    {
                                        while (true)
                                        {
                                            DrawMessageBox(consoleDrawBuffer, L"��ų ��뿡 �ʿ��� ������ �����մϴ�! ");
                                            consoleDrawBuffer.Render();
                                            inputAnyKey();
                                            break;
                                        }
                                        break;
                                    }
                                    vector<wstring> vec = player->getActiveSkillList()[1]->ActiveSkillCast(player, monster);
                                    for (size_t i = 0; i < vec.size(); i++)
                                    {
                                        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
                                        DrawMessageBox(consoleDrawBuffer, vec[i]);
                                        consoleDrawBuffer.Render();
                                        inputAnyKey();
                                    }

                                    if (PlayerDead())
                                    {
                                        isPlayerDie = true;
                                        break;
                                    }
                                    else if (MonsterDead())
                                    {
                                        isMonsterDie = true;
                                        break;
                                    }
                                    MonsterTurn();
                                    if (PlayerDead())
                                    {
                                        isPlayerDie = true;
                                        break;
                                    }
                                    else if (MonsterDead())
                                    {
                                        isMonsterDie = true;
                                        break;
                                    }
                                    consoleDrawBuffer.Clear();
                                    break;
                                }
                            }
                            else if (skillNum == 2)
                            {
                                while (true)
                                {
                                    int damage = 0;
                                    manager.input.Initialize();
                                    manager.input.Update();

                                    if (player->GetMp() < player->getActiveSkillList()[2]->getSkillCost())
                                    {
                                        while (true)
                                        {
                                            DrawMessageBox(consoleDrawBuffer, L"��ų ��뿡 �ʿ��� ������ �����մϴ�! ");
                                            consoleDrawBuffer.Render();
                                            inputAnyKey();
                                            break;
                                        }
                                        break;
                                    }
                                    vector<wstring> vec = player->getActiveSkillList()[2]->ActiveSkillCast(player, monster);
                                    for (size_t i = 0; i < vec.size(); i++)
                                    {
                                        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
                                        DrawMessageBox(consoleDrawBuffer, vec[i]);
                                        consoleDrawBuffer.Render();
                                        inputAnyKey();
                                    }

                                    if (PlayerDead())
                                    {
                                        isPlayerDie = true;
                                        break;
                                    }
                                    else if (MonsterDead())
                                    {
                                        isMonsterDie = true;
                                        break;
                                    }
                                    MonsterTurn();
                                    if (PlayerDead())
                                    {
                                        isPlayerDie = true;
                                        break;
                                    }
                                    else if (MonsterDead())
                                    {
                                        isMonsterDie = true;
                                        break;
                                    }
                                    consoleDrawBuffer.Clear();
                                    break;
                                }
                            }
                            else if (skillNum == 3)
                            {
                                IsdrawSkillList = false;
                                break;
                            }
                            break;
                        }
                        if (monster->GetMonsterType() == MonsterType::SLIME) DrawSlimeImage(consoleDrawBuffer);
                        else if (monster->GetMonsterType() == MonsterType::GOBLIN) DrawGoblinImage(consoleDrawBuffer);
                        else if (monster->GetMonsterType() == MonsterType::SKELETON) DrawSkeletonImage(consoleDrawBuffer);
                        IsdrawSkillList = false;
                        printUserInfo2(consoleDrawBuffer);
                        consoleDrawBuffer.Render();
                    }
                }
                //�κ�
                else if (menuSelect == 3)
                {
                    IsdrawInvenList = true;
                    int itemNum = 0;
                    while (true)
                    {
                        manager.input.Update();
                        if (manager.input.GetKeyDown(eKeyCode::Down))
                        {
                            itemNum++;
                            if (itemNum == 4)
                            {
                                itemNum = 3;
                            }
                        }
                        if (manager.input.GetKeyDown(eKeyCode::Up))
                        {
                            itemNum--;
                            if (itemNum == -1)
                            {
                                itemNum = 0;
                            }
                        }
                        DrawInvenList(consoleDrawBuffer);
                        switch (itemNum)
                        {
                        case 0:
                            consoleDrawBuffer.DrawAt(37, 32, L"�� ü�¹���");
                            break;
                        case 1:
                            consoleDrawBuffer.DrawAt(41, 34, L"�� ��������");
                            break;
                        case 2:
                            consoleDrawBuffer.DrawAt(39, 36, L"�� ������");
                            break;
                        case 3:
                            consoleDrawBuffer.DrawAt(39, 38, L"�� �ڷΰ���");
                            break;
                        default:
                            break;
                        }
                        if (manager.input.GetKeyDown(eKeyCode::Space))
                        {
                            consoleDrawBuffer.Clear();
                            if (monster->GetMonsterType() == MonsterType::SLIME) DrawSlimeImage(consoleDrawBuffer);
                            else if (monster->GetMonsterType() == MonsterType::GOBLIN) DrawGoblinImage(consoleDrawBuffer);
                            else if (monster->GetMonsterType() == MonsterType::SKELETON) DrawSkeletonImage(consoleDrawBuffer);
                            DrawBattleChoiceInven(consoleDrawBuffer);
                            printUserInfo2(consoleDrawBuffer);
                            if (itemNum == 0)
                            {
                                if (player->getPotionlList()[0]->getItemQuantity() == 0)
                                {
                                    while (true)
                                    {
                                        DrawMessageBox3(consoleDrawBuffer, L"����ϰ��� �ϴ� ������ ������ ���ڶ��ϴ�! ");
                                        consoleDrawBuffer.Render();
                                        inputAnyKey();
                                        break;
                                    }
                                    break;
                                }
                                else
                                {
                                    vector<wstring> vec = player->getPotionlList()[0]->UsePotion(player);
                                    for (size_t i = 0; i < vec.size(); i++)
                                    {
                                        DrawMessageBox3(consoleDrawBuffer, L"                                                                      ");
                                        DrawMessageBox3(consoleDrawBuffer, vec[i]);
                                        consoleDrawBuffer.Render(); // ���⼭ ��ų�� �ö�
                                        inputAnyKey();
                                    }
                                    player->getPotionlList()[0]->setItemQuantity();
                                }

                                MonsterTurn();
                                if (PlayerDead())
                                {
                                    isPlayerDie = true;
                                    break;
                                }
                                else if (MonsterDead())
                                {
                                    isMonsterDie = true;
                                    break;
                                }
                                consoleDrawBuffer.Clear();
                                break;
                            }
                            else if (itemNum == 1)
                            {
                                if (player->getPotionlList()[1]->getItemQuantity() == 0)
                                {
                                    while (true)
                                    {
                                        DrawMessageBox(consoleDrawBuffer, L"�ش� ������ �����ϴ�! ");
                                        consoleDrawBuffer.Render();
                                        inputAnyKey();
                                        break;
                                    }
                                    break;
                                }
                                else
                                {
                                    vector<wstring> vec = player->getPotionlList()[1]->UsePotion(player);
                                    for (size_t i = 0; i < vec.size(); i++)
                                    {
                                        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
                                        DrawMessageBox(consoleDrawBuffer, vec[i]);
                                        consoleDrawBuffer.Render();
                                        inputAnyKey();
                                    }
                                    player->getPotionlList()[1]->setItemQuantity();
                                }

                                MonsterTurn();
                                if (PlayerDead())
                                {
                                    isPlayerDie = true;
                                    break;
                                }
                                else if (MonsterDead())
                                {
                                    isMonsterDie = true;
                                    break;
                                }
                                consoleDrawBuffer.Clear();
                                break;
                            }
                            else if (itemNum == 2)
                            {
                                if (player->getPotionlList()[2]->getItemQuantity() == 0)
                                {
                                    while (true)
                                    {
                                        DrawMessageBox(consoleDrawBuffer, L"�ش� ������ �����ϴ�! ");
                                        consoleDrawBuffer.Render();
                                        inputAnyKey();
                                        break;
                                    }
                                    break;
                                }
                                else
                                {
                                    vector<wstring> vec = player->getPotionlList()[2]->UsePotion(player);
                                    for (size_t i = 0; i < vec.size(); i++)
                                    {
                                        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
                                        DrawMessageBox(consoleDrawBuffer, vec[i]);
                                        consoleDrawBuffer.Render();
                                        inputAnyKey();
                                    }
                                    player->getPotionlList()[2]->setItemQuantity();
                                }

                                MonsterTurn();
                                if (PlayerDead())
                                {
                                    isPlayerDie = true;
                                    break;
                                }
                                else if (MonsterDead())
                                {
                                    isMonsterDie = true;
                                    break;
                                }
                                consoleDrawBuffer.Clear();
                                break;
                            }
                            else if (itemNum == 3)
                            {
                                IsdrawInvenList = false;
                                break;
                            }
                            break;
                        }
                        if (monster->GetMonsterType() == MonsterType::SLIME) DrawSlimeImage(consoleDrawBuffer);
                        if (monster->GetMonsterType() == MonsterType::SLIME) DrawSlimeImage(consoleDrawBuffer);
                        else if (monster->GetMonsterType() == MonsterType::GOBLIN) DrawGoblinImage(consoleDrawBuffer);
                        else if (monster->GetMonsterType() == MonsterType::SKELETON) DrawSkeletonImage(consoleDrawBuffer);
                        IsdrawInvenList = false;
                        printUserInfo2(consoleDrawBuffer);
                        consoleDrawBuffer.Render();
                    }
                }
                //����
                else if (menuSelect == 4)
                {
                    //TODO ����, ���н� ���Ϳ��� ���� �°�, �ڽ��� ���ư�
                    if (rand() % 2 == 0)
                    {
                        DrawMessageBox(consoleDrawBuffer, L"����ġ�⸦ �����߽��ϴ�!");
                        consoleDrawBuffer.Render();
                        inputAnyKey();
                        MonsterTurn();
                        if (PlayerDead())
                        {
                            isPlayerDie = true;
                        }
                    }
                    else
                    {
                        system("cls");
                        break;
                    }
                }


                if (isMonsterDie == true)
                {
                    currentMap->at(newPosY, newPosX) = 0;
                    break;
                }
                else if (isPlayerDie == true)
                {
                    player->SetPosX(23);
                    player->SetPosY(23);
                    playerX = 23;
                    playerY = 23;
                    while (true)
                    {
                        DrawMessageBox(consoleDrawBuffer, L"                                           ");
                        DrawMessageBox(consoleDrawBuffer, L"����ϼ̽��ϴ�.");
                        consoleDrawBuffer.Render();
                        inputAnyKey();
                        DrawMessageBox(consoleDrawBuffer, L"                                            ");
                        DrawMessageBox(consoleDrawBuffer, L"�������� �ٽ� ��Ȱ�մϴ�.");
                        consoleDrawBuffer.Render();
                        inputAnyKey();
                        system("cls");
                        break;
                    }
                    player->SetHp(player->GetMaxHp());
                    player->SetMp(player->GetMaxMp());
                    manager.map.UnloadMap(manager.map.GetcurrenteMap());
                    manager.map.LoadMap(eMaps::Village);
                    break;
                }
            }

            if (IsdrawSkillList == true)
            {
                DrawSkillList(consoleDrawBuffer);
            }

            if (IsdrawInvenList == true)
            {
                DrawInvenList(consoleDrawBuffer);
            }


            consoleDrawBuffer.Render();
        }
        delete monster;
        break;
    }
    case (int)EGameObject::NPC:
    {
        Manager& manager = Manager::getInstance();
        ConsolePopup popup;
        if (manager.map.GetcurrenteMap() == eMaps::Village && newPosX == 28 && newPosY == 31)
        {
            while (1)
            {
                popup.DrawPotionShop(40, 10, 100, 30, L" <���ǻ���>");
                bool isEnd = false;
                while (true)
                {
                    manager.input.Update();
                    int count;
                    gotoxy(44, 26);
                    cout << "������ : " + to_string(player->GetMoney()) + " ���";
                    gotoxy(44, 27);
                    cout << "�����Ͻ� ������ ��ȣ�� �Է����ּ���.";
                    while (true)
                    {
                        manager.input.Update();
                        if (manager.input.GetKeyDown(eKeyCode::Num1))
                        {
                            if (player->GetMoney() < player->getPotionlList()[0]->getItemPrice())
                            {
                                gotoxy(44, 28);
                                cout << "���� ���� : �ܾ��� ���ڶ��ϴ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                               ";
                                system("cls");
                            }
                            else
                            {
                                player->SetMoney(player->GetMoney() - player->getPotionlList()[0]->getItemPrice());
                                player->getPotionlList()[0]->setItemQuantity(1);
                                gotoxy(44, 28);
                                cout << "���� �Ϸ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                     ";
                                gotoxy(44, 26);
                                cout << "                                                 ";
                                gotoxy(44, 26);
                                cout << "������ : " + to_string(player->GetMoney()) + " ���";
                            }
                        }
                        else if (manager.input.GetKeyDown(eKeyCode::Num2))
                        {
                            if (player->GetMoney() < player->getPotionlList()[1]->getItemPrice())
                            {
                                gotoxy(44, 28);
                                cout << "���� ���� : �ܾ��� ���ڶ��ϴ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                               ";
                            }
                            else
                            {
                                player->SetMoney(player->GetMoney() - player->getPotionlList()[1]->getItemPrice());
                                player->getPotionlList()[1]->setItemQuantity(1);
                                gotoxy(44, 28);
                                cout << "���� �Ϸ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                     ";
                                gotoxy(44, 26);
                                cout << "                                                 ";
                                gotoxy(44, 26);
                                cout << "������ : " + to_string(player->GetMoney()) + " ���";
                            }
                        }
                        else if (manager.input.GetKeyDown(eKeyCode::Num3))
                        {
                            if (player->GetMoney() < player->getPotionlList()[2]->getItemPrice())
                            {
                                gotoxy(44, 28);
                                cout << "���� ���� : �ܾ��� ���ڶ��ϴ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                               ";
                            }
                            else
                            {
                                player->SetMoney(player->GetMoney() - player->getPotionlList()[2]->getItemPrice());
                                player->getPotionlList()[2]->setItemQuantity(1);
                                gotoxy(44, 28);
                                cout << "���� �Ϸ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                     ";
                                gotoxy(44, 26);
                                cout << "                                                 ";
                                gotoxy(44, 26);
                                cout << "������ : " + to_string(player->GetMoney()) + " ���";
                            }
                        }
                        else if (manager.input.GetKeyDown(eKeyCode::Num4))
                        {
                            isEnd = true;
                            break;
                        }
                        if (isEnd)
                        {
                            break;
                        }
                    }
                    if (isEnd)
                    {
                        break;
                    }
                }
                if (isEnd)
                {
                    system("cls");
                    break;
                }
            }
        }
        else if (manager.map.GetcurrenteMap() == eMaps::Village && newPosX == 36 && newPosY == 31)
        {
            while (1)
            {
                popup.DrawSkillShop(40, 10, 100, 30, L" <��ų���� ����>");
                bool isEnd = false;
                while (true)
                {
                    manager.input.Update();
                    int count;
                    gotoxy(44, 26);
                    cout << "������ : " + to_string(player->GetMoney()) + " ���";
                    gotoxy(44, 27);
                    cout << "�����Ͻ� ��ų�� ��ȣ�� �Է����ּ���.";
                    while (true)
                    {
                        manager.input.Update();
                        if (manager.input.GetKeyDown(eKeyCode::Num1))
                        {
                            if (player->GetMoney() < 1000)
                            {
                                gotoxy(44, 28);
                                cout << "���� ���� : �ܾ��� ���ڶ��ϴ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                               ";
                                system("cls");
                            }
                            else
                            {
                                player->SetMoney(player->GetMoney() - 1000);
                                player->getActiveSkillList()[0]->setSkillLevel(1);
                                gotoxy(44, 28);
                                cout << "���� �Ϸ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                     ";
                                gotoxy(44, 26);
                                cout << "                                                 ";
                                gotoxy(44, 26);
                                cout << "������ : " + to_string(player->GetMoney()) + " ���";
                            }
                        }
                        else if (manager.input.GetKeyDown(eKeyCode::Num2))
                        {
                            if (player->GetMoney() < 5000)
                            {
                                gotoxy(44, 28);
                                cout << "���� ���� : �ܾ��� ���ڶ��ϴ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                               ";
                            }
                            else
                            {
                                player->SetMoney(player->GetMoney() - 5000);
                                player->getActiveSkillList()[1]->setSkillLevel(1);
                                gotoxy(44, 28);
                                cout << "���� �Ϸ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                     ";
                                gotoxy(44, 26);
                                cout << "                                                 ";
                                gotoxy(44, 26);
                                cout << "������ : " + to_string(player->GetMoney()) + " ���";
                            }
                        }
                        else if (manager.input.GetKeyDown(eKeyCode::Num3))
                        {
                            if (player->GetMoney() < 10000)
                            {
                                gotoxy(44, 28);
                                cout << "���� ���� : �ܾ��� ���ڶ��ϴ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                               ";
                            }
                            else
                            {
                                player->SetMoney(player->GetMoney() - 10000);
                                player->getActiveSkillList()[2]->setSkillLevel(1);
                                gotoxy(44, 28);
                                cout << "���� �Ϸ�!";
                                Sleep(1000);
                                gotoxy(44, 28);
                                cout << "                     ";
                                gotoxy(44, 26);
                                cout << "                                                 ";
                                gotoxy(44, 26);
                                cout << "������ : " + to_string(player->GetMoney()) + " ���";
                            }
                        }
                        else if (manager.input.GetKeyDown(eKeyCode::Num4))
                        {
                            isEnd = true;
                            break;
                        }
                        if (isEnd)
                        {
                            break;
                        }
                    }
                    if (isEnd)
                    {
                        break;
                    }
                }
                if (isEnd)
                {
                    system("cls");
                    break;
                }
            }
        }
        break;
    }

    default:
        break;
    }
}

void CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void clearScreen()
{
    // Ŀ���� �� ���� �̵�
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
#pragma endregion
#pragma region ������ ����
void printRightUI()
{
    gotoxy(104, 0);
    std::cout << "��������������������������������������������������������������������������������������������������";
    for (size_t i = 1; i < 49; i++)
    {
        gotoxy(104, i);
        std::cout << "��                                               ��";
    }
    gotoxy(104, 49);
    std::cout << "��������������������������������������������������������������������������������������������������";
    //clearScreen();
}
void printUserInfo()
{
    Manager& manager = Manager::getInstance();
    gotoxy(106, 5);
    std::cout << "              [�÷��̾�  ����]" << endl;
    gotoxy(110, 6);
    std::cout << "������������������������������������������������������������������������" << endl;

    gotoxy(110, 7);
    std::cout << "�̸� : " << player->GetName() << std::endl;
    gotoxy(110, 8);
    std::cout << "ü�� / �ִ�ü�� : " << player->GetHp() << " / " << player->GetMaxHp() << std::endl;
    gotoxy(110, 9);
    std::cout << "���� / �ִ븶�� : " << player->GetMp() << " / " << player->GetMaxMp() << std::endl;
    gotoxy(110, 10);
    std::cout << "���ݷ� : " << player->GetAtk() << std::endl;
    gotoxy(110, 11);
    std::cout << "���� : " << player->GetDef() << std::endl;
    gotoxy(110, 12);
    std::cout << "ũ��Ƽ�� Ȯ�� : " << player->GetCriRate() << std::endl;
    gotoxy(110, 13);
    std::cout << "ũ��Ƽ�� ������ : " << player->GetCriDamage() << std::endl;
    gotoxy(110, 14);
    std::cout << "������ : " << player->GetMoney() << std::endl;
    gotoxy(110, 17);
    std::cout << "���� ��ġ : " << manager.map.GetMapName(manager.map.GetcurrenteMap()) << std::endl;
    gotoxy(110, 18);
    std::cout << "��ų : " << "��ų" << std::endl;
}
void PrintKeyboardState()
{
    Manager& manager = Manager::getInstance();

    gotoxy(106, 35);
    std::cout << "                [Ű����  �Է�]";
    gotoxy(110, 36);
    std::cout << "������������������������������������������������������������������������" << endl;
#pragma region DirectionKeys
    gotoxy(110, 38);
    std::cout << "����Ű : " << endl;
    gotoxy(122, 37);
    if (manager.input.GetKeyDown(eKeyCode::Up) || manager.input.GetKey(eKeyCode::Up))
    {
        std::cout << "��" << endl;
    }
    else
    {
        std::cout << "��" << endl;
    }
    gotoxy(120, 38);
    if (manager.input.GetKeyDown(eKeyCode::Left) || manager.input.GetKey(eKeyCode::Left))
    {
        std::cout << "��" << endl;
    }
    else
    {
        std::cout << "��" << endl;
    }
    gotoxy(122, 38);
    if (manager.input.GetKeyDown(eKeyCode::Down) || manager.input.GetKey(eKeyCode::Down))
    {
        std::cout << "��" << endl;
    }
    else
    {
        std::cout << "��" << endl;
    }
    gotoxy(124, 38);
    if (manager.input.GetKeyDown(eKeyCode::Right) || manager.input.GetKey(eKeyCode::Right))
    {
        std::cout << "��" << endl;
    }
    else
    {
        std::cout << "��" << endl;
    }

    gotoxy(128, 38);
    std::cout << "�����̽� : " << endl;
    gotoxy(140, 38);
    if (manager.input.GetKeyDown(eKeyCode::Space) || manager.input.GetKey(eKeyCode::Space))
    {
        std::cout << "�����" << endl;
    }
    else
    {
        std::cout << "�����" << endl;
    }
#pragma endregion

#pragma region KeyBoardKeys
    gotoxy(110, 40);
    if (manager.input.GetKeyDown(eKeyCode::Q) || manager.input.GetKey(eKeyCode::Q)) std::cout << "��";
    else std::cout << "��";
    gotoxy(112, 40);
    if (manager.input.GetKeyDown(eKeyCode::W) || manager.input.GetKey(eKeyCode::W)) std::cout << "��";
    else std::cout << "��";
    gotoxy(114, 40);
    if (manager.input.GetKeyDown(eKeyCode::E) || manager.input.GetKey(eKeyCode::E)) std::cout << "��";
    else std::cout << "��";
    gotoxy(116, 40);
    if (manager.input.GetKeyDown(eKeyCode::R) || manager.input.GetKey(eKeyCode::R)) std::cout << "��";
    else std::cout << "��";
    gotoxy(118, 40);
    if (manager.input.GetKeyDown(eKeyCode::T) || manager.input.GetKey(eKeyCode::T)) std::cout << "��";
    else std::cout << "��";
    gotoxy(120, 40);
    if (manager.input.GetKeyDown(eKeyCode::Y) || manager.input.GetKey(eKeyCode::Y)) std::cout << "��";
    else std::cout << "��";
    gotoxy(122, 40);
    if (manager.input.GetKeyDown(eKeyCode::U) || manager.input.GetKey(eKeyCode::U)) std::cout << "��";
    else std::cout << "��";
    gotoxy(124, 40);
    if (manager.input.GetKeyDown(eKeyCode::I) || manager.input.GetKey(eKeyCode::I)) std::cout << "��";
    else std::cout << "��";
    gotoxy(126, 40);
    if (manager.input.GetKeyDown(eKeyCode::O) || manager.input.GetKey(eKeyCode::O)) std::cout << "��";
    else std::cout << "��";
    gotoxy(128, 40);
    if (manager.input.GetKeyDown(eKeyCode::P) || manager.input.GetKey(eKeyCode::P)) std::cout << "��";
    else std::cout << "��";

    gotoxy(110, 41);
    if (manager.input.GetKeyDown(eKeyCode::A) || manager.input.GetKey(eKeyCode::A)) std::cout << "��";
    else std::cout << "��";
    gotoxy(112, 41);
    if (manager.input.GetKeyDown(eKeyCode::S) || manager.input.GetKey(eKeyCode::S)) std::cout << "��";
    else std::cout << "��";
    gotoxy(114, 41);
    if (manager.input.GetKeyDown(eKeyCode::D) || manager.input.GetKey(eKeyCode::D)) std::cout << "��";
    else std::cout << "��";
    gotoxy(116, 41);
    if (manager.input.GetKeyDown(eKeyCode::F) || manager.input.GetKey(eKeyCode::F)) std::cout << "��";
    else std::cout << "��";
    gotoxy(118, 41);
    if (manager.input.GetKeyDown(eKeyCode::G) || manager.input.GetKey(eKeyCode::G)) std::cout << "��";
    else std::cout << "��";
    gotoxy(120, 41);
    if (manager.input.GetKeyDown(eKeyCode::H) || manager.input.GetKey(eKeyCode::H)) std::cout << "��";
    else std::cout << "��";
    gotoxy(122, 41);
    if (manager.input.GetKeyDown(eKeyCode::J) || manager.input.GetKey(eKeyCode::J)) std::cout << "��";
    else std::cout << "��";
    gotoxy(124, 41);
    if (manager.input.GetKeyDown(eKeyCode::K) || manager.input.GetKey(eKeyCode::K)) std::cout << "��";
    else std::cout << "��";
    gotoxy(126, 41);
    if (manager.input.GetKeyDown(eKeyCode::L) || manager.input.GetKey(eKeyCode::L)) std::cout << "��";
    else std::cout << "��";

    gotoxy(110, 42);
    if (manager.input.GetKeyDown(eKeyCode::Z) || manager.input.GetKey(eKeyCode::Z)) std::cout << "��";
    else std::cout << "��";
    gotoxy(112, 42);
    if (manager.input.GetKeyDown(eKeyCode::X) || manager.input.GetKey(eKeyCode::X)) std::cout << "��";
    else std::cout << "��";
    gotoxy(114, 42);
    if (manager.input.GetKeyDown(eKeyCode::C) || manager.input.GetKey(eKeyCode::C)) std::cout << "��";
    else std::cout << "��";
    gotoxy(116, 42);
    if (manager.input.GetKeyDown(eKeyCode::V) || manager.input.GetKey(eKeyCode::V)) std::cout << "��";
    else std::cout << "��";
    gotoxy(118, 42);
    if (manager.input.GetKeyDown(eKeyCode::B) || manager.input.GetKey(eKeyCode::B)) std::cout << "��";
    else std::cout << "��";
    gotoxy(120, 42);
    if (manager.input.GetKeyDown(eKeyCode::N) || manager.input.GetKey(eKeyCode::N)) std::cout << "��";
    else std::cout << "��";
    gotoxy(122, 42);
    if (manager.input.GetKeyDown(eKeyCode::M) || manager.input.GetKey(eKeyCode::M)) std::cout << "��";
    else std::cout << "��";



#pragma endregion
}
void PrintMessage() //TODO
{

    gotoxy(4, 35);
    std::cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";
    for (size_t i = 36; i < 47; i++)
    {
        gotoxy(4, i);
        std::cout << "��                                                                                         ��";
    }
    gotoxy(4, 47);
    std::cout << "��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������";

    gotoxy(16, 41);
    std::cout << "������ ��(��) ȹ���ϼ̽��ϴ�.";
}
void PrintBattleUI()
{
    gotoxy(30, 10);
    std::cout << "������������������������������������������������������������������������������";
    for (size_t i = 11; i < 29; i++)
    {
        gotoxy(30, i);
        std::cout << "��                                     ��";
    }
    gotoxy(30, 29);
    std::cout << "������������������������������������������������������������������������������";


    gotoxy(5, 30);
    std::cout << "������������������������������������������������";
    for (size_t i = 31; i < 45; i++)
    {
        gotoxy(5, i);
        std::cout << "��                      ��";
    }
    gotoxy(13, 32);
    std::cout << "�ൿ ����";
    gotoxy(6, 34);
    std::cout << " ���������������������������������������� ";
    gotoxy(8, 36);
    std::cout << "������";
    gotoxy(10, 38);
    std::cout << "��ų";
    gotoxy(10, 40);
    std::cout << "�κ��丮";
    gotoxy(10, 42);
    std::cout << "����ġ��";
    gotoxy(5, 45);
    std::cout << "������������������������������������������������";
}
void PrintBattleUI2()
{
    gotoxy(5, 30);
    std::cout << "������������������������������������������������";
    for (size_t i = 31; i < 45; i++)
    {
        gotoxy(5, i);
        std::cout << "��                      ��";
    }
    gotoxy(13, 32);
    std::cout << "�ൿ ����";
    gotoxy(6, 34);
    std::cout << " ���������������������������������������� ";
    gotoxy(10, 36);
    std::cout << "����";
    gotoxy(10, 38);
    std::cout << "��ų";
    gotoxy(10, 40);
    std::cout << "�κ��丮";
    gotoxy(10, 42);
    std::cout << "����ġ��";
    gotoxy(5, 45);
    std::cout << "������������������������������������������������";
}
#pragma endregion

int main()
{
#pragma region Settings
    system("mode con:cols=150 lines=51");
    CursorView();
    drawIntro();
    if (!menuDraw())return 0;
    system("cls");
    while (true)
    {
        string name;
        DrawOneWords(IntroText, 50);
        gotoxy(19, 21);
        cin >> name;
        player->SetName(name);
        break;
    }
    system("cls");
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    setlocale(LC_ALL, "korean");
    _wsetlocale(LC_ALL, L"korean");
    srand((unsigned)time(NULL));
#pragma endregion

#pragma region Initialize
    Manager& manager = Manager::getInstance();
    manager.input.Initialize();
    manager.map.Initialize();
    manager.map.LoadMap(eMaps::Village);
    Map* currentMap;
    ConsolePopup popup;
    FireBall* fireball = new FireBall();
    Heal* heal = new Heal();
    Meteor* meteor = new Meteor();
    player->addActiveSkill(fireball);
    player->addActiveSkill(heal);
    player->addActiveSkill(meteor);
    HalthIPotion* hpotion = new HalthIPotion();
    ManaIPotion* mpotion = new ManaIPotion();
    Elixir* elixir = new Elixir();
    player->addPotion(hpotion, 1);
    player->addPotion(mpotion, 1);
    player->addPotion(elixir, 1);
#pragma endregion
    while (true)
    {
        CursorView();
        manager.input.Update();
        clearScreen();
        PlayerSetStatusByLevel();
        currentMap = manager.map.GetCurrentMap();
        DrawBuffer2(currentMap);
        MovePlayer(currentMap);
        currentMap = manager.map.GetCurrentMap();
        renderBuffer2(currentMap);

#pragma region Popup
        if (manager.input.GetKeyDown(eKeyCode::P))
        {
            popup.DrawUserInfo(5, 5, 50, 20, L" �÷��̾� ����");
            inputAnyKey();
            system("cls");
        }
        if (manager.input.GetKeyDown(eKeyCode::I))
        {
            popup.DrawUserInventory(70, 5, 100, 15, L" �κ��丮");
            inputAnyKey();
            system("cls");
        }
        if (manager.input.GetKeyDown(eKeyCode::S))
        {
            popup.DrawUserSkill(30, 25, 140, 40, L" ��ų����");
            inputAnyKey();
            system("cls");
        }
#pragma endregion
#pragma region DevelopMode
        if (manager.input.GetKeyDown(eKeyCode::A) && manager.input.GetKeyDown(eKeyCode::M))
        {
            player->SetMoney(player->GetMoney() + 1000000);
        }
        if (manager.input.GetKeyDown(eKeyCode::A) && manager.input.GetKeyDown(eKeyCode::E))
        {
            player->SetExp(10000);
        }
#pragma endregion
    }
}
