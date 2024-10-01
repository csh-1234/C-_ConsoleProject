#include <iostream>
#include <Windows.h>
#include "Manager.h"
#include <conio.h>
#include "Player.h"
#include "Knight.h"
#include "Monster.h"
#include <string>
#include <cwchar>
#include <locale.h>


using namespace std;
#pragma warning(disable:4996)
enum class EGameObject
{
    EMPTY = 0,
    // 1 ~ 10 ��
    WALL = 1,
    PLAYER = 2,
    TREE1 = 3,
    TREE2 = 4,
    MONSTER = 5,
    BOSSMONSTER,
    NPC,
    PORTAL = 9,
};

class ConsoleBuffer2 {
private:
    HANDLE hConsole;

public:
    ConsoleBuffer2() 
    {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void DrawWindow(int startX, int startY, int endX, int endY, const std::wstring& title = L"") {
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
            int titleX = startX + 5;
            DrawAt(titleX, startY, title);
        }

        // â ���� �����
        for (int y = startY + 1; y < endY; y++) {
            DrawAt(startX + 1, y, std::wstring(endX - startX - 1, L' '));
        }
    }

    void DrawAt(int x, int y, const std::wstring& str) 
    {
        COORD pos = { (SHORT)x, (SHORT)y };
        DWORD written;
        WriteConsoleOutputCharacterW(hConsole, str.c_str(), str.length(), pos, &written);
    }
};

class ConsoleBuffer {
private:
    std::vector<std::vector<wchar_t>> buffer;  // ���̵� ���ڿ� ���
    int width, height;
    HANDLE hConsole;

public:
    ConsoleBuffer(int w, int h) : width(w), height(h), buffer(h, std::vector<wchar_t>(w, L' ')) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleScreenBufferSize(hConsole, { (SHORT)w, (SHORT)h });
    }

    void Clear() {
        for (auto& row : buffer) {
            std::fill(row.begin(), row.end(), L' ');  // ���̵� ���� ���
        }
    }

    void DrawAt(int x, int y, const std::wstring& str) {  // ���̵� ���ڿ� ���
        for (size_t i = 0; i < str.length() && x + i < width; ++i) {
            if (y >= 0 && y < height && x + i >= 0) {
                buffer[y][x + i] = str[i];
            }
        }
    }

    void ChangeAt(int x, int y, const std::wstring& str) {  // ���̵� ���ڿ� ���
        for (size_t i = 0; i < str.length() && x + i < width; ++i) {
            if (y >= 0 && y < height && x + i >= 0) {
                buffer[y][x + i] = str[i];
            }
        }
    }

    void Render() {
        COORD topLeft = { 0, 0 };
        DWORD written;

        for (const auto& row : buffer) {
            WriteConsoleOutputCharacterW(hConsole, row.data(), width, topLeft, &written);  // �����ڵ� ���� ���
            topLeft.Y++;
        }
    }
    void RenderPartial(int startX, int startY, int endX, int endY) {
        COORD topLeft = { (SHORT)startX, (SHORT)startY };
        DWORD written;

        for (int y = startY; y <= endY && y < height; ++y) {
            if (y >= 0) {
                WriteConsoleOutputCharacterW(hConsole, &buffer[y][startX], endX - startX + 1, topLeft, &written);
            }
            topLeft.Y++;
        }
    }

    void DrawPopup(int x, int y, int w, int h, const std::wstring& title, const std::vector<std::wstring>& content) {
        // �˾� ������ ���� ������ ����
        std::vector<std::vector<wchar_t>> background(h, std::vector<wchar_t>(w));
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (y + i < height && x + j < width) {
                    background[i][j] = buffer[y + i][x + j];
                }
            }
        }

        // �˾� �׵θ� �׸���
        DrawAt(x, y, L"��" + std::wstring(w - 2, L'��') + L"��");
        for (int i = 1; i < h - 1; ++i) {
            DrawAt(x, y + i, L"��" + std::wstring(w - 2, L' ') + L"��");
        }
        DrawAt(x, y + h - 1, L"��" + std::wstring(w - 2, L'��') + L"��");

        // ���� �׸���
        if (!title.empty()) {
            DrawAt(x + (w - title.length()) / 2, y, title);
        }

        // ���� �׸���
        for (size_t i = 0; i < content.size() && i < h - 2; ++i) {
            DrawAt(x + 1, y + i + 1, content[i]);
        }

        // ���� �˾��� ����
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (y + i < height && x + j < width) {
                    if (buffer[y + i][x + j] == L' ' && background[i][j] != L' ') {
                        buffer[y + i][x + j] = background[i][j];
                    }
                }
            }
        }

        // �˾� ������ ������
        RenderPartial(x, y, x + w - 1, y + h - 1);
    }
};

const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 50;

const int VIEWPORT_WIDTH = 20;  // ȭ�鿡 ǥ�õǴ� �ʺ�
const int VIEWPORT_HEIGHT = 10; // ȭ�鿡 ǥ�õǴ� ����

Knight* player = new Knight("ȫ�浿");
Slime* slime;
Monster* monster;
int playerX = player->GetPosX();
int playerY = player->GetPosY();

string buffer[MAP_HEIGHT] = {};
int buffer2[50][50] = {};

const int ViewSizeX = 100; // 18 12
const int ViewSizeY = 100;

void DrawMessageBox(ConsoleBuffer& buffer, const std::wstring& message) {
    buffer.DrawAt(4, 35, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
    buffer.DrawAt(4, 36, L"��                                                                                         ��");
    buffer.DrawAt(4, 37, L"��                                                                                         ��");
    buffer.DrawAt(4, 38, L"��                                                                                         ��");
    buffer.DrawAt(4, 39, L"��                                                                                         ��");
    buffer.DrawAt(4, 40, L"��                                                                                         ��");
    buffer.DrawAt(4, 41, L"                                                                                           ");
    buffer.DrawAt(4, 42, L"��                                                                                         ��");
    buffer.DrawAt(4, 43, L"��                                                                                         ��");
    buffer.DrawAt(4, 44, L"��                                                                                         ��");
    buffer.DrawAt(4, 45, L"��                                                                                         ��");
    buffer.DrawAt(4, 46, L"��                                                                                         ��");
    buffer.DrawAt(4, 47, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
    buffer.DrawAt(16, 41, message);
}

void DrawMessageBox(ConsoleBuffer& buffer) {
    buffer.DrawAt(4, 35, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
    buffer.DrawAt(4, 36, L"��                                                                                         ��");
    buffer.DrawAt(4, 37, L"��                                                                                         ��");
    buffer.DrawAt(4, 38, L"��                                                                                         ��");
    buffer.DrawAt(4, 39, L"��                                                                                         ��");
    buffer.DrawAt(4, 40, L"��                                                                                         ��");
    buffer.DrawAt(4, 41, L"                                                                                           ");
    buffer.DrawAt(4, 42, L"��                                                                                         ��");
    buffer.DrawAt(4, 43, L"��                                                                                         ��");
    buffer.DrawAt(4, 44, L"��                                                                                         ��");
    buffer.DrawAt(4, 45, L"��                                                                                         ��");
    buffer.DrawAt(4, 46, L"��                                                                                         ��");
    buffer.DrawAt(4, 47, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
}
void DrawBattleChoiceAttack(ConsoleBuffer& buffer) {
    buffer.DrawAt(5, 30, L"������������������������������������������������");
    buffer.DrawAt(5, 31, L"��                      ��");
    buffer.DrawAt(5, 32, L"��       �ൿ ����      ��");
    buffer.DrawAt(5, 33, L"��                      ��");
    buffer.DrawAt(5, 34, L"�� ���������������������������������������� ��");
    buffer.DrawAt(5, 35, L"��                      ��");
    buffer.DrawAt(5, 36, L"��   �� ����            ��");
    buffer.DrawAt(5, 37, L"��                      ��");
    buffer.DrawAt(5, 38, L"��    ��ų              ��");
    buffer.DrawAt(5, 39, L"��                      ��");
    buffer.DrawAt(5, 40, L"��    �κ��丮          ��");
    buffer.DrawAt(5, 41, L"��                      ��");
    buffer.DrawAt(5, 42, L"��    ����ġ��          ��");
    buffer.DrawAt(5, 43, L"��                      ��");
    buffer.DrawAt(5, 44, L"��                      ��");
    buffer.DrawAt(5, 45, L"������������������������������������������������");
}
void DrawBattleChoiceSkill(ConsoleBuffer& buffer) {
    buffer.DrawAt(5, 30, L"������������������������������������������������");
    buffer.DrawAt(5, 31, L"��                      ��");
    buffer.DrawAt(5, 32, L"��       �ൿ ����      ��");
    buffer.DrawAt(5, 33, L"��                      ��");
    buffer.DrawAt(5, 34, L"�� ���������������������������������������� ��");
    buffer.DrawAt(5, 35, L"��                      ��");
    buffer.DrawAt(5, 36, L"��    ����              ��");
    buffer.DrawAt(5, 37, L"��                      ��");
    buffer.DrawAt(5, 38, L"��   �� ��ų            ��");
    buffer.DrawAt(5, 39, L"��                      ��");
    buffer.DrawAt(5, 40, L"��    �κ��丮          ��");
    buffer.DrawAt(5, 41, L"��                      ��");
    buffer.DrawAt(5, 42, L"��    ����ġ��          ��");
    buffer.DrawAt(5, 43, L"��                      ��");
    buffer.DrawAt(5, 44, L"��                      ��");
    buffer.DrawAt(5, 45, L"������������������������������������������������");
}
void DrawBattleChoiceInven(ConsoleBuffer& buffer) {
    buffer.DrawAt(5, 30, L"������������������������������������������������");
    buffer.DrawAt(5, 31, L"��                      ��");
    buffer.DrawAt(5, 32, L"��       �ൿ ����      ��");
    buffer.DrawAt(5, 33, L"��                      ��");
    buffer.DrawAt(5, 34, L"�� ���������������������������������������� ��");
    buffer.DrawAt(5, 35, L"��                      ��");
    buffer.DrawAt(5, 36, L"��    ����              ��");
    buffer.DrawAt(5, 37, L"��                      ��");
    buffer.DrawAt(5, 38, L"��    ��ų              ��");
    buffer.DrawAt(5, 39, L"��                      ��");
    buffer.DrawAt(5, 40, L"��   �� �κ��丮        ��");
    buffer.DrawAt(5, 41, L"��                      ��");
    buffer.DrawAt(5, 42, L"��    ����ġ��          ��");
    buffer.DrawAt(5, 43, L"��                      ��");
    buffer.DrawAt(5, 44, L"��                      ��");
    buffer.DrawAt(5, 45, L"������������������������������������������������");
}

void DrawBattleChoiceRunAway(ConsoleBuffer& buffer) {
    buffer.DrawAt(5, 30, L"������������������������������������������������");
    buffer.DrawAt(5, 31, L"��                      ��");
    buffer.DrawAt(5, 32, L"��       �ൿ ����      ��");
    buffer.DrawAt(5, 33, L"��                      ��");
    buffer.DrawAt(5, 34, L"�� ���������������������������������������� ��");
    buffer.DrawAt(5, 35, L"��                      ��");
    buffer.DrawAt(5, 36, L"��    ����              ��");
    buffer.DrawAt(5, 37, L"��                      ��");
    buffer.DrawAt(5, 38, L"��    ��ų              ��");
    buffer.DrawAt(5, 39, L"��                      ��");
    buffer.DrawAt(5, 40, L"��    �κ��丮          ��");
    buffer.DrawAt(5, 41, L"��                      ��");
    buffer.DrawAt(5, 42, L"��   �� ����ġ��        ��");
    buffer.DrawAt(5, 43, L"��                      ��");
    buffer.DrawAt(5, 44, L"��                      ��");
    buffer.DrawAt(5, 45, L"������������������������������������������������");
}

void DrawEmptyImage(ConsoleBuffer& buffer) {
    buffer.DrawAt(30, 10, L"������������������������������������������������������������������������������");
    buffer.DrawAt(30, 12, L"��                                     ��");
    buffer.DrawAt(30, 13, L"��                                     ��");
    buffer.DrawAt(30, 14, L"��                                     ��");
    buffer.DrawAt(30, 15, L"��                                     ��");
    buffer.DrawAt(30, 16, L"��                                     ��");
    buffer.DrawAt(30, 17, L"��                                     ��");
    buffer.DrawAt(30, 18, L"��                                     ��");
    buffer.DrawAt(30, 19, L"��                                     ��");
    buffer.DrawAt(30, 20, L"��                                     ��");
    buffer.DrawAt(30, 21, L"��                                     ��");
    buffer.DrawAt(30, 22, L"��                                     ��");
    buffer.DrawAt(30, 23, L"��                                     ��");
    buffer.DrawAt(30, 24, L"��                                     ��");
    buffer.DrawAt(30, 25, L"��                                     ��");
    buffer.DrawAt(30, 26, L"��                                     ��");
    buffer.DrawAt(30, 27, L"��                                     ��");
    buffer.DrawAt(30, 28, L"��                                     ��");
    buffer.DrawAt(30, 29, L"������������������������������������������������������������������������������");
}
void DrawSlimeImage(ConsoleBuffer& buffer)
{
    buffer.DrawAt(30, 10, L"������������������������������������������������������������������������������");
    buffer.DrawAt(30, 11, L"��                                     ��");
    buffer.DrawAt(30, 12, L"��                                     ��");
    buffer.DrawAt(30, 13, L"��                                     ��");
    buffer.DrawAt(30, 14, L"��                                     ��");
    buffer.DrawAt(30, 15, L"��                                     ��");
    buffer.DrawAt(30, 16, L"��                                     ��");
    buffer.DrawAt(30, 17, L"��                 ��                  ��");
    buffer.DrawAt(30, 18, L"��             ��       ��             ��");
    buffer.DrawAt(30, 19, L"��         ��               ��         ��");
    buffer.DrawAt(30, 20, L"��       ��                   ��       ��");
    buffer.DrawAt(30, 21, L"��     ��                       ��     ��");
    buffer.DrawAt(30, 22, L"��    ��       ��         ��     ��    ��");
    buffer.DrawAt(30, 23, L"��    ��       ��         ��     ��    ��");
    buffer.DrawAt(30, 24, L"��     ��                       ��     ��");
    buffer.DrawAt(30, 25, L"��      ��                     ��      ��");
    buffer.DrawAt(30, 26, L"��        ��                 ��        ��");
    buffer.DrawAt(30, 27, L"��          �� �� �� �� �� ��          ��");
    buffer.DrawAt(30, 28, L"��                                     ��");
    buffer.DrawAt(30, 29, L"������������������������������������������������������������������������������");
}
void DrawSkillList(ConsoleBuffer& buffer)
{
    buffer.DrawAt(30, 30, L"������������������������������������������������������������������������������������������������������������������������������������������");
    buffer.DrawAt(30, 31, L"��                                                                   ��");
    buffer.DrawAt(26, 32, L"��        ���̾                                                   ��");
    buffer.DrawAt(30, 33, L"��                                                                   ��");
    buffer.DrawAt(30, 34, L"��        ��                                                         ��");
    buffer.DrawAt(30, 35, L"��                                                                   ��");
    buffer.DrawAt(28, 36, L"��        ���׿�                                                     ��");
    buffer.DrawAt(30, 37, L"��                                                                   ��");
    buffer.DrawAt(27, 38, L"��        �ڷΰ���                                                   ��");
    buffer.DrawAt(30, 39, L"��                                                                   ��");
    buffer.DrawAt(26, 40, L"��                                                                   ��");
    buffer.DrawAt(30, 41, L"��                                                                   ��");
    buffer.DrawAt(26, 42, L"��                                                                   ��");
    buffer.DrawAt(30, 43, L"��                                                                   ��");
    buffer.DrawAt(30, 44, L"��                                                                   ��");
    buffer.DrawAt(30, 45, L"������������������������������������������������������������������������������������������������������������������������������������������");
}
void DrawInvenList(ConsoleBuffer& buffer)
{
    buffer.DrawAt(30, 30, L"������������������������������������������������������������������������������������������������������������������������������������������");
    buffer.DrawAt(30, 31, L"��                                                                   ��");
    buffer.DrawAt(26, 32, L"��        ü�¹���                                                   ��");
    buffer.DrawAt(30, 33, L"��                                                                   ��");
    buffer.DrawAt(30, 34, L"��        ��������                                                   ��");
    buffer.DrawAt(30, 35, L"��                                                                   ��");
    buffer.DrawAt(28, 36, L"��        ������                                                     ��");
    buffer.DrawAt(30, 37, L"��                                                                   ��");
    buffer.DrawAt(28, 38, L"��        �ڷΰ���                                                   ��");
    buffer.DrawAt(30, 39, L"��                                                                   ��");
    buffer.DrawAt(25, 40, L"��                                                                   ��");
    buffer.DrawAt(30, 41, L"��                                                                   ��");
    buffer.DrawAt(26, 42, L"��                                                                   ��");
    buffer.DrawAt(30, 43, L"��                                                                   ��");
    buffer.DrawAt(30, 44, L"��                                                                   ��");
    buffer.DrawAt(30, 45, L"������������������������������������������������������������������������������������������������������������������������������������������");
}
void DrawBattleUI(ConsoleBuffer& buffer) {
    buffer.DrawAt(30, 10, L"������������������������������������������������������������������������������");
    buffer.DrawAt(30, 12, L"��                                     ��");
    buffer.DrawAt(30, 13, L"��                                     ��");
    buffer.DrawAt(30, 14, L"��                                     ��");
    buffer.DrawAt(30, 15, L"��                                     ��");
    buffer.DrawAt(30, 16, L"��                                     ��");
    buffer.DrawAt(30, 17, L"��                                     ��");
    buffer.DrawAt(30, 18, L"��                                     ��");
    buffer.DrawAt(30, 19, L"��                                     ��");
    buffer.DrawAt(30, 20, L"��                                     ��");
    buffer.DrawAt(30, 21, L"��                                     ��");
    buffer.DrawAt(30, 22, L"��                                     ��");
    buffer.DrawAt(30, 23, L"��                                     ��");
    buffer.DrawAt(30, 24, L"��                                     ��");
    buffer.DrawAt(30, 25, L"��                                     ��");
    buffer.DrawAt(30, 26, L"��                                     ��");
    buffer.DrawAt(30, 27, L"��                                     ��");
    buffer.DrawAt(30, 28, L"��                                     ��");
    buffer.DrawAt(30, 29, L"������������������������������������������������������������������������������");
}

#pragma region ����
//void DrawBuffer()
//{
//    for (size_t y = 0; y < MAP_HEIGHT; y++)
//    {
//        buffer[y] = "";
//        for (size_t x = 0; x < MAP_WIDTH; x++)
//        {
//            if (x == playerX && y == playerY)
//            {
//                buffer[y] += "��";
//            }
//            else if (map1[y][x] == 1)
//            {
//                buffer[y] += "��";
//            }
//            else if (map1[y][x] == 3)
//            {
//                buffer[y] += "��";
//            }
//            else if (map1[y][x] == 4)
//            {
//                buffer[y] += "��";
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
void PrintKeyboardState();
void PrintMessage();
void printUserInfo();

void gotoxy(int x, int y);

void inputAnyKey()
{
    Manager& manager = manager.getInstance();
    while (true)
    {
        manager.input.Update();
        if (manager.input.GetKeyDown(eKeyCode::Space)) return;
    }
}
void printRightUI2(ConsoleBuffer& buffer)
{
    buffer.DrawAt(104, 0, L"��������������������������������������������������������������������������������������������������");
    for (size_t i = 1; i < 49; i++)
    {
        buffer.DrawAt(104, i, L"��                                               ��");
    }
    buffer.DrawAt(104, 49, L"��������������������������������������������������������������������������������������������������");
}
void printUserInfo2(ConsoleBuffer& buffer)
{
    Manager& manager = Manager::getInstance();
    buffer.DrawAt(70, 1, L"         [�÷��̾�  ����]");
    buffer.DrawAt(70, 2, L"������������������������������������������������������������������");

    wstring wstr(player->GetName().size(), L'\0');
    std::mbstowcs(&wstr[0], player->GetName().c_str(), player->GetName().size());
    buffer.DrawAt(70, 3, L"�̸� : " + wstr);
    buffer.DrawAt(70, 4, L"ü�� / �ִ�ü�� : " + to_wstring(player->GetHp()) + L" / " + to_wstring(player->GetMaxHp()));
    buffer.DrawAt(70, 5, L"���� / �ִ븶�� : " + to_wstring(player->GetMp()) + L" / " + to_wstring(player->GetMaxMp()));
    buffer.DrawAt(70, 6, L"���ݷ� : " + to_wstring(player->GetAtk()));
    buffer.DrawAt(70, 7, L"���� : " + to_wstring(player->GetDef()));
    buffer.DrawAt(70, 8, L"ũ��Ƽ�� Ȯ�� : " + to_wstring(player->GetCriRate()) + L"%");
    buffer.DrawAt(70, 9, L"ũ��Ƽ�� ������ :" + to_wstring(player->GetCriDamage()) + L"%");
    /*buffer.DrawAt(70, 9, L"ȸ���� :" + to_wstring(player->GetAvoidRate()) + L"%");
    buffer.DrawAt(70, 10, L"�ӵ� :" + to_wstring(player->GetSpeed()));*/
    buffer.DrawAt(70, 10, L"������ :" + to_wstring(player->GetMoney()) + L"���");

    string mapName = manager.map.GetMapName(manager.map.GetcurrenteMap());
    wstring wstr2(mapName.size(), L'\0');
    std::mbstowcs(&wstr2[0], mapName.c_str(),mapName.size());
    buffer.DrawAt(70, 11, L"���� ��ġ :" + wstr2);
}

void DrawBuffer2(Map* currentMap)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            buffer2[y][x] = currentMap->at(y, x);
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
            // y�� starty���� ũ�ų� ���� endy ���� �۰ų� ����
            if ((startY <= y && y <= endY) && (startX <= x && x <= endX))
            {
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
                else if (currentMap->at(y, x) == 9)
                {
                    std::cout << "��";
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
            if (manager.map.PortalList[i].CurrentMap == manager.map.GetcurrenteMap() &&
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
        //�� ���Ͱ� � �������� ��� �˾ƾ� �ϴ°�?
        //�� �ʿ䰡 ������ �����. �������� �����ϸ�ȴ�.
        //�׿��� ���� �׳� �� �󿡼� ����������.

     /*   switch (rand() % 3)
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
        }*/
        slime = new Slime();

        ConsoleBuffer buffer(200, 51);  // �ܼ� ũ�⸦ �����߽��ϴ�

        std::wstring currentMessage = L"";
        bool showBattleUI = false;
        bool showMessage = false;

        bool IsdrawSkillList = false;
        bool IsdrawInvenList = false;

        bool bKeyDown = false; // 'B' Ű �Է� ����
        bool mKeyDown = false; // 'M' Ű �Է� ����
        int menuSelect = 1;
        // 1 = attack; 2 = skill 3 = inven; 4 = runawy
        //bool showBattleUI = true;
        while (true)
        {
            manager.input.Update();
            //clearScreen();
            buffer.Clear();
            //DrawSlimeImage(buffer);
            printUserInfo2(buffer);
            DrawSlimeImage(buffer);
            switch (menuSelect)
            {
            case 1:
                DrawBattleChoiceAttack(buffer);
                break;
            case 2:
                DrawBattleChoiceSkill(buffer);
                break;
            case 3:
                DrawBattleChoiceInven(buffer);
                break;
            case 4:
                DrawBattleChoiceRunAway(buffer);
                break;
            default:
                DrawBattleChoiceAttack(buffer);
                break;
            }

            if (manager.input.GetKeyDown(eKeyCode::Down))
            {
                menuSelect++;
                IsdrawSkillList = false;
                IsdrawInvenList = false;
                if (menuSelect == 5)
                {
                    menuSelect = 4;
                }
            }
            if (manager.input.GetKeyDown(eKeyCode::Up))
            {
                menuSelect--;
                IsdrawSkillList = false;
                IsdrawInvenList = false;
                if (menuSelect == 0)
                {
                    menuSelect = 1;
                }
            }

            bool death = false;
            if (manager.input.GetKeyDown(eKeyCode::Space))
            {
                if (menuSelect == 1)
                {
                    int damage;

                    while (true)
                    {
                        manager.input.Initialize();
                        manager.input.Update();
                        damage = player->GetAtk() - slime->GetDef();
                        if (damage <= 0) damage = 0;
                        DrawMessageBox(buffer, L"�÷��̾��� ����!                                                               ");
                        buffer.Render();
                        inputAnyKey();

                        DrawMessageBox(buffer, L"���Ϳ��� " + to_wstring(damage) + L"�������� ����!                                                    ");
                        slime->SetHp(slime->GetHp() - damage);
                        buffer.Render();
                        inputAnyKey();

                        if (slime->GetHp() <= 0 || player->GetHp() <= 0)
                        {
                            DrawMessageBox(buffer, L"���͸� ����Ʈ��                                                    ");
                            buffer.Render();
                            inputAnyKey();
                            death = true;
                            break;
                        }

                        DrawMessageBox(buffer, L"                                                                                           ");
                        DrawMessageBox(buffer, L"���� ü�� " + to_wstring(slime->GetHp()));
                        buffer.Render();
                        inputAnyKey();

                        damage = slime->GetAtk() - player->GetDef();
                        if (damage <= 0) damage = 1;
                        DrawMessageBox(buffer, L"������ ����!                                                                 ");
                        buffer.Render();
                        inputAnyKey();

                        DrawMessageBox(buffer, L"�÷��̾�� " + to_wstring(damage) + L"�������� ����!                                                    ");
                        player->SetHp(player ->GetHp() - damage);
                        buffer.Render();
                        inputAnyKey();

                        DrawMessageBox(buffer, L"��                                                                                          ");
                        DrawMessageBox(buffer, L"�÷��̾� ü�� " + to_wstring(player->GetHp()));
                        buffer.Render();
                        inputAnyKey();
                        break;


                    }
                }
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
                            if (skillNum == 3)
                            {
                                skillNum = 3;
                            }
                        }
                        if (manager.input.GetKeyDown(eKeyCode::Up))
                        {
                            skillNum--;
                            if (skillNum == -1)
                            {
                                skillNum = 0;
                            }
                        }
                        DrawSkillList(buffer);
                        switch (skillNum)
                        {
                        case 0:
                            buffer.DrawAt(33, 32, L"�� ���̾");
                            break;
                        case 1:
                            buffer.DrawAt(37, 34, L"�� ��");
                            break;
                        case 2:
                            buffer.DrawAt(35, 36, L"�� ���׿�");
                            break;
                        case 3:
                            buffer.DrawAt(35, 38, L"�� �ڷΰ���");
                            break;
                        default:
                            break;
                        }
                        if (manager.input.GetKeyDown(eKeyCode::Space))
                        {
                            if (skillNum == 0)
                            {

                            }
                            else if (skillNum == 3)
                            {
                                IsdrawSkillList = false;
                                break;
                            }
                        }

                        buffer.Render();
                    }
                }
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
                        DrawInvenList(buffer);
                        switch (itemNum)
                        {
                        case 0:
                            buffer.DrawAt(33, 32, L"�� ü�¹���");
                            break;
                        case 1:
                            buffer.DrawAt(37, 34, L"�� ��������");
                            break;
                        case 2:
                            buffer.DrawAt(35, 36, L"�� ������");
                            break;
                        case 3:
                            buffer.DrawAt(35, 38, L"�� �ڷΰ���");
                            break;
                        default:
                            break;
                        }
                        if (manager.input.GetKeyDown(eKeyCode::Space))
                        {
                            if (itemNum == 3)
                            {
                                IsdrawInvenList = false;
                                break;
                            }
                        }


                        buffer.Render();
                    }
                }
                else if (menuSelect == 4)
                {
                    //TODO ����, ���н� ���Ϳ��� ���� �°�, �ڽ��� ���ư�
                    break;
                }
                if (death == true)
                {
                    currentMap->at(newPosY, newPosX) = 0;
                    break;
                }
            }

            if (IsdrawSkillList == true)
            {
                DrawSkillList(buffer);
            }

            if (IsdrawInvenList == true)
            {
                DrawInvenList(buffer);
            }


            buffer.Render();

#pragma region MyRegion
            //buffer.Clear();

            //DrawBattleUI(buffer);
            ////DrawMessageBox(buffer, currentMessage);

            //buffer.Render();

            ////// ����� �Է� ó��
            ////if (GetAsyncKeyState('B') & 0x8000) {
            ////    if (!bKeyDown) {
            ////        showBattleUI = !showBattleUI;
            ////        bKeyDown = true;  // Ű�� �������� ���
            ////    }
            ////}
            ////else {
            ////    bKeyDown = false; // Ű�� �������� �� ���� �ʱ�ȭ
            ////}

            ////if (GetAsyncKeyState('M') & 0x8000) {
            ////    if (!mKeyDown) {
            ////        showMessage = !showMessage;
            ////        //if (showMessage) {
            ////        //    currentMessage = L"��������(��) ȹ���ϼ̽��ϴ�.";  // �����ڵ� ���ڿ��� ����
            ////        //}
            ////        mKeyDown = true;  // Ű�� �������� ���
            ////    }
            ////}
            ////else {
            ////    mKeyDown = false;  // Ű�� �������� �� ���� �ʱ�ȭ
            ////}

            ////Sleep(100);  // CPU ��뷮 ���Ҹ� ���� ª�� ��� �ð�
            //if (GetAsyncKeyState('M') & 0x8000)
            //{
            //    break;
            //}
#pragma endregion

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
    std::cout << "ȸ���� : " << player->GetAvoidRate() << std::endl;
    gotoxy(110, 15);
    std::cout << "�ӵ� : " << player->GetSpeed() << std::endl;
    gotoxy(110, 16);
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



int main()
{
    setlocale(LC_ALL, "korean");
    _wsetlocale(LC_ALL, L"korean");
    srand((unsigned)time(NULL));
    system("mode con:cols=160 lines=51");
    CursorView();
    Manager& manager = Manager::getInstance();
    manager.input.Initialize();
    manager.map.Initialize();
    manager.map.LoadMap(eMaps::Village);

    //ConsoleBuffer buffer(200, 200);
    ConsoleBuffer buffer(50, 25 );  // �ܼ� ũ�⸦ �����߽��ϴ�
    ConsoleBuffer2 buffer2;
    ConsoleBuffer2 buffer3;
    while (true)
    {
        clearScreen();
        manager.input.Update();
        DrawBuffer2(manager.map.GetCurrentMap());
        MovePlayer(manager.map.GetCurrentMap());
        renderBuffer2(manager.map.GetCurrentMap());

        if (manager.input.GetKeyDown(eKeyCode::I))
        {
            buffer2.DrawWindow(5,5, 60, 20);
            inputAnyKey();

        }
        
       /* printRightUI();
        printUserInfo();
        PrintKeyboardState();*/
        clearScreen();
    }
}