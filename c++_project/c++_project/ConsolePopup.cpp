#include "ConsolePopup.h"
#include <windows.h>
#include "Manager.h"
#include "Player.h"
#include "IPotion.h"
#pragma warning(disable:4996)

ConsolePopup::ConsolePopup()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ConsolePopup::DrawAt(int x, int y, const std::wstring& str)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    DWORD written;
    WriteConsoleOutputCharacterW(hConsole, str.c_str(), str.length(), pos, &written);
}

void ConsolePopup::DrawUserInfo(int startX, int startY, int endX, int endY, const std::wstring& title, Player* player)
{
        DrawAt(startX, startY, L"┏" + std::wstring(endX - startX - 1, L'━') + L"┓");
        for (int y = startY + 1; y < endY; y++)
        {
            DrawAt(startX, y, L"┃");
            DrawAt(endX, y, L"┃");
        }
        DrawAt(startX, endY, L"┗" + std::wstring(endX - startX - 1, L'━') + L"┛");

        if (!title.empty())
        {
            int titleX = startX + (endX - startX - title.length()) / 2 - 4;
            DrawAt(titleX, startY, title);
        }

        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();

        DrawAt(startX + 4, startY + 2, L"레벨 : " + to_wstring(player->GetLevel()));
        wstring wstr(player->GetName().size(), L'\0');
        std::mbstowcs(&wstr[0], player->GetName().c_str(), player->GetName().size());
        DrawAt(startX + 4, startY + 3, L"이름 : " + wstr);
        DrawAt(startX + 4, startY + 4, L"체력 / 최대체력 : " + to_wstring(player->GetHp()) + L" / " + to_wstring(player->GetMaxHp()));
        DrawAt(startX + 4, startY + 5, L"마나 / 최대마나 : " + to_wstring(player->GetMp()) + L" / " + to_wstring(player->GetMaxMp()));
        DrawAt(startX + 4, startY + 6, L"공격력 : " + to_wstring(player->GetAtk()));
        DrawAt(startX + 4, startY + 7, L"방어력 : " + to_wstring(player->GetDef()));
        DrawAt(startX + 4, startY + 8, L"크리티컬 확률 : " + to_wstring(player->GetCriRate()) + L"%");
        DrawAt(startX + 4, startY + 9, L"크리티컬 데미지 :" + to_wstring(player->GetCriDamage()) + L"%");
        DrawAt(startX + 4, startY + 10, L"경험치 :" + to_wstring(player->GetExp()));
        string mapName = manager.map.GetMapName(manager.map.GetcurrenteMap());
        wstring wstr2(mapName.size(), L'\0');
        std::mbstowcs(&wstr2[0], mapName.c_str(), mapName.size());
        DrawAt(startX + 4, startY + 11, L"현재 위치 :" + wstr2);
        DrawAt(startX + 4, startY + 12, L"현재 좌표(x,y) :" +
            to_wstring(player->GetPosX()) + L", " + to_wstring(player->GetPosY()));

}

void ConsolePopup::DrawUserInventory(int startX, int startY, int endX, int endY, const std::wstring& title, Player* player)
{
    {
        DrawAt(startX, startY, L"┏" + std::wstring(endX - startX - 1, L'━') + L"┓");
        for (int y = startY + 1; y < endY; y++)
        {
            DrawAt(startX, y, L"┃");
            DrawAt(endX, y, L"┃");
        }
        DrawAt(startX, endY, L"┗" + std::wstring(endX - startX - 1, L'━') + L"┛");

        if (!title.empty())
        {
            int titleX = startX + (endX - startX - title.length()) / 2 - 4;
            DrawAt(titleX, startY, title);
        }

        for (int y = startY + 1; y < endY; y++)
        {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();

        wstring wstr(player->getPotionlList()[0]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr[0], player->getPotionlList()[0]->getItemName().c_str()
            , player->getPotionlList()[0]->getItemName().size());
        DrawAt(startX + 4, startY + 2, wstr + L" : " + to_wstring(player->getPotionlList()[0]->getItemQuantity()) + L" 개");

        wstring wstr2(player->getPotionlList()[1]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr2[0], player->getPotionlList()[1]->getItemName().c_str()
            , player->getPotionlList()[1]->getItemName().size());
        DrawAt(startX + 4, startY + 3, wstr2 + L" : " + to_wstring(player->getPotionlList()[1]->getItemQuantity()) + L" 개");

        wstring wstr3(player->getPotionlList()[2]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr3[0], player->getPotionlList()[2]->getItemName().c_str()
            , player->getPotionlList()[2]->getItemName().size());
        DrawAt(startX + 4, startY + 4, wstr3 + L" : " + to_wstring(player->getPotionlList()[2]->getItemQuantity()) + L" 개");

        DrawAt(startX + 4, startY + 8, L"소지금 : " + to_wstring(player->GetMoney()) + L"골드");
    }
}

void ConsolePopup::DrawUserSkill(int startX, int startY, int endX, int endY, const std::wstring& title, Player* player)
{
    {
        DrawAt(startX, startY, L"┏" + std::wstring(endX - startX - 1, L'━') + L"┓");
        for (int y = startY + 1; y < endY; y++)
        {
            DrawAt(startX, y, L"┃");
            DrawAt(endX, y, L"┃");
        }
        DrawAt(startX, endY, L"┗" + std::wstring(endX - startX - 1, L'━') + L"┛");

        if (!title.empty())
        {
            int titleX = startX + (endX - startX - title.length()) / 2 - 4;
            DrawAt(titleX, startY, title);
        }

        for (int y = startY + 1; y < endY; y++)
        {
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
}

void ConsolePopup::DrawPotionShop(int startX, int startY, int endX, int endY, const std::wstring& title, Player* player)
{
    {
        DrawAt(startX, startY, L"┏" + std::wstring(endX - startX - 1, L'━') + L"┓");
        for (int y = startY + 1; y < endY; y++)
        {
            DrawAt(startX, y, L"┃");
            DrawAt(endX, y, L"┃");
        }
        DrawAt(startX, endY, L"┗" + std::wstring(endX - startX - 1, L'━') + L"┛");

        if (!title.empty())
        {
            int titleX = startX + (endX - startX - title.length()) / 2 - 4;
            DrawAt(titleX, startY, title);
        }

        for (int y = startY + 1; y < endY; y++)
        {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();

        wstring wstr(player->getPotionlList()[0]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr[0], player->getPotionlList()[0]->getItemName().c_str()
            , player->getPotionlList()[0]->getItemName().size());
        DrawAt(startX + 4, startY + 2, L"1. " + wstr + L" : " + to_wstring(player->getPotionlList()[0]->getItemPrice()) + L" 골드");

        wstring wstr2(player->getPotionlList()[1]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr2[0], player->getPotionlList()[1]->getItemName().c_str()
            , player->getPotionlList()[1]->getItemName().size());
        DrawAt(startX + 4, startY + 3, L"2. " + wstr2 + L" : " + to_wstring(player->getPotionlList()[1]->getItemPrice()) + L" 골드");

        wstring wstr3(player->getPotionlList()[2]->getItemName().size(), L'\0');
        std::mbstowcs(&wstr3[0], player->getPotionlList()[2]->getItemName().c_str()
            , player->getPotionlList()[2]->getItemName().size());
        DrawAt(startX + 4, startY + 4, L"3. " + wstr3 + L" : " + to_wstring(player->getPotionlList()[2]->getItemPrice()) + L" 골드");

        DrawAt(startX + 4, startY + 5, L"4. 나가기 ");
    }
}

void ConsolePopup::DrawBuyComplete(int startX, int startY, int endX, int endY)
{
    {
        DrawAt(startX, startY, L"┏" + std::wstring(endX - startX - 1, L'━') + L"┓");
        for (int y = startY + 1; y < endY; y++)
        {
            DrawAt(startX, y, L"┃");
            DrawAt(endX, y, L"┃");
        }
        DrawAt(startX, endY, L"┗" + std::wstring(endX - startX - 1, L'━') + L"┛");

        for (int y = startY + 1; y < endY; y++)
        {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();
        DrawAt(startX + 4, startY + 3, L"구매완료!");
    }
}

void ConsolePopup::DrawSkillShop(int startX, int startY, int endX, int endY, const std::wstring& title, Player* player)
{
    {

        DrawAt(startX, startY, L"┏" + std::wstring(endX - startX - 1, L'━') + L"┓");
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX, y, L"┃");
            DrawAt(endX, y, L"┃");
        }
        DrawAt(startX, endY, L"┗" + std::wstring(endX - startX - 1, L'━') + L"┛");

        if (!title.empty()) {
            int titleX = startX + (endX - startX - title.length()) / 2 - 4;
            DrawAt(titleX, startY, title);
        }

        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
        Manager& manager = Manager::getInstance();

        wstring wstr(player->getActiveSkillList()[0]->getSkillName().size(), L'\0');
        std::mbstowcs(&wstr[0], player->getActiveSkillList()[0]->getSkillName().c_str()
            , player->getActiveSkillList()[0]->getSkillName().size());
        DrawAt(startX + 4, startY + 2, L"1. " + wstr + L" : " + to_wstring(/*player->getActiveSkillList()[0]->getSkillLevel() * */1000) + L" 골드");

        wstring wstr2(player->getActiveSkillList()[1]->getSkillName().size(), L'\0');
        std::mbstowcs(&wstr2[0], player->getActiveSkillList()[1]->getSkillName().c_str()
            , player->getActiveSkillList()[1]->getSkillName().size());
        DrawAt(startX + 4, startY + 3, L"2. " + wstr2 + L" : " + to_wstring(/*player->getActiveSkillList()[1]->getSkillLevel() * */5000) + L" 골드");

        wstring wstr3(player->getActiveSkillList()[2]->getSkillName().size(), L'\0');
        std::mbstowcs(&wstr3[0], player->getActiveSkillList()[2]->getSkillName().c_str()
            , player->getActiveSkillList()[2]->getSkillName().size());
        DrawAt(startX + 4, startY + 4, L"3. " + wstr3 + L" : " + to_wstring(/*player->getActiveSkillList()[1]->getSkillLevel() * */10000) + L" 골드");


        DrawAt(startX + 4, startY + 5, L"4. 나가기 ");
    }
}