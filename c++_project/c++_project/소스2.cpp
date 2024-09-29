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
    // 1 ~ 10 漁
    WALL = 1,
    PLAYER = 2,
    TREE1 = 3,
    TREE2 = 4,
    MONSTER = 5,
    BOSSMONSTER,
    NPC,
    PORTAL = 9 ,
};

class ConsoleBuffer {
private:
    std::vector<std::vector<wchar_t>> buffer;  // 諦檜萄 僥濠翮 餌辨
    int width, height;
    HANDLE hConsole;

public:
    ConsoleBuffer(int w, int h) : width(w), height(h), buffer(h, std::vector<wchar_t>(w, L' ')) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleScreenBufferSize(hConsole, { (SHORT)w, (SHORT)h });
    }

    void Clear() {
        for (auto& row : buffer) {
            std::fill(row.begin(), row.end(), L' ');  // 諦檜萄 奢寥 餌辨
        }
    }

    void DrawAt(int x, int y, const std::wstring& str) {  // 諦檜萄 僥濠翮 餌辨
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
            WriteConsoleOutputCharacterW(hConsole, row.data(), width, topLeft, &written);  // 嶸棲囀萄 幗瞪 餌辨
            topLeft.Y++;
        }
    }
};

const int MAP_WIDTH = 50;
const int MAP_HEIGHT = 50;

const int VIEWPORT_WIDTH = 20;  // �飛橦� ル衛腎朝 傘綠
const int VIEWPORT_HEIGHT = 10; // �飛橦� ル衛腎朝 堪檜

Knight* player = new Knight("�垮瘚�");
Monster* monster;
int playerX = player->GetPosX();
int playerY = player->GetPosY();

string buffer[MAP_HEIGHT] = {};
int buffer2[50][50] = {};

const int ViewSizeX = 100; // 18 12
const int ViewSizeY = 100;

void DrawMessageBox(ConsoleBuffer& buffer, const std::wstring& message) {
    buffer.DrawAt(4, 35, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
    for (int i = 36; i < 47; ++i) {
        buffer.DrawAt(4, i, L"早                                                                                         早");
    }
    buffer.DrawAt(4, 47, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

    buffer.DrawAt(16, 41, message);
}
void DrawBattleUI(ConsoleBuffer& buffer) {
    buffer.DrawAt(30, 10, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
    for (int i = 11; i < 29; ++i) {
        buffer.DrawAt(30, i, L"早                                     早");
    }
    buffer.DrawAt(30, 29, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

    //buffer.DrawAt(13, 32, L"ч翕 摹鷗");
    //buffer.DrawAt(6, 34, L" 收收收收收收收收收收收收收收收收收收收收 ");
    //buffer.DrawAt(10, 36, L"奢問");  // 斜傖 奢問
    //buffer.DrawAt(10, 38, L"蝶鑒");  // 蝶鑒 葬蝶お蒂 銑溥輿堅 殮溘 嫡嬴撿 й蛭
    //buffer.DrawAt(10, 40, L"檣漸饜葬"); // 嬴檜蠱 葬蝶お蒂 銑溥輿堅 殮溘 嫡嬴撿 й蛭
    //buffer.DrawAt(10, 42, L"紫蜂纂晦");

    buffer.DrawAt(5, 30, L"旨收收收收收收收收收收收收收收收收收收收收收收旬");
    for (int i = 31; i < 45; ++i) {
        buffer.DrawAt(5, i, L"早                      早");
    }
    buffer.DrawAt(5, 45, L"曲收收收收收收收收收收收收收收收收收收收收收收旭");
}


vector<string> backBuffer(50, string(100, ' ')); // 50還, и 還縑 100偃曖 奢寥
void drawToBuffer(int x, int y, const std::string& text) {
    if (y >= 0 && y < backBuffer.size() && x >= 0 && x + text.size() < backBuffer[y].size()) 
    {
        backBuffer[y].replace(x, text.size(), text); // (x, y) 嬪纂縑 臢蝶お 噙晦
    }
}

#pragma region 裘р
//void DrawBuffer()
//{
//    for (size_t y = 0; y < MAP_HEIGHT; y++)
//    {
//        buffer[y] = "";
//        for (size_t x = 0; x < MAP_WIDTH; x++)
//        {
//            if (x == playerX && y == playerY)
//            {
//                buffer[y] += "≠";
//            }
//            else if (map1[y][x] == 1)
//            {
//                buffer[y] += "﹥";
//            }
//            else if (map1[y][x] == 3)
//            {
//                buffer[y] += "Ⅷ";
//            }
//            else if (map1[y][x] == 4)
//            {
//                buffer[y] += "Ⅳ";
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
void gotoxy(int x, int y);

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
            // y陛 starty爾棻 觼剪釭 偽堅 endy 爾棻 濛剪釭 偽棻
            if ((startY <= y && y <= endY) && (startX <= x && x <= endX))
            {
                if (x == playerX && y == playerY)
                {
                    std::cout << "≠";
                }
                else if (currentMap->at(y, x) == 1)
                {
                    std::cout << "﹥";
                }
                else if (currentMap->at(y, x) == 3)
                {
                    std::cout << "Ⅷ";
                }
                else if (currentMap->at(y, x) == 4)
                {
                    std::cout << "Ⅳ";
                }
                else if (currentMap->at(y, x) == 5)
                {
                    std::cout << "∪";
                }
                else if (currentMap->at(y, x) == 9)
                {
                    std::cout << "十";
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
        ConsoleBuffer buffer(100, 50);  // 夔樂 觼晦蒂 撲薑ц蝗棲棻

        bool showBattleUI = true;
        bool showMessage = false;
        std::wstring currentMessage = L"";

        bool bKeyDown = false; // 'B' 酈 殮溘 鼻鷓
        bool mKeyDown = false; // 'M' 酈 殮溘 鼻鷓

        while (true) 
        {
#pragma region MyRegion



            //buffer.Clear();

            //DrawBattleUI(buffer);
            ////DrawMessageBox(buffer, currentMessage);

            //buffer.Render();

            ////// 餌辨濠 殮溘 籀葬
            ////if (GetAsyncKeyState('B') & 0x8000) {
            ////    if (!bKeyDown) {
            ////        showBattleUI = !showBattleUI;
            ////        bKeyDown = true;  // 酈陛 揚溜擠擊 晦煙
            ////    }
            ////}
            ////else {
            ////    bKeyDown = false; // 酈陛 飲橫螺擊 陽 鼻鷓 蟾晦��
            ////}

            ////if (GetAsyncKeyState('M') & 0x8000) {
            ////    if (!mKeyDown) {
            ////        showMessage = !showMessage;
            ////        //if (showMessage) {
            ////        //    currentMessage = L"嬴檜蠱擊(蒂) �僱磈牳抻懂炴�.";  // 嶸棲囀萄 僥濠翮煎 滲唳
            ////        //}
            ////        mKeyDown = true;  // 酈陛 揚溜擠擊 晦煙
            ////    }
            ////}
            ////else {
            ////    mKeyDown = false;  // 酈陛 飲橫螺擊 陽 鼻鷓 蟾晦��
            ////}

            ////Sleep(100);  // CPU 餌辨榆 馬模蒂 嬪и 穠擎 渠晦 衛除
            //if (GetAsyncKeyState('M') & 0x8000)
            //{
            //    break;
            //}
#pragma endregion
            clearScreen();
            manager.input.Update();
            PrintBattleUI();
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
    cursorInfo.dwSize = 1; //醴憮 掃晦 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //醴憮 Visible TRUE(爾歜) FALSE(獗梯)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void clearScreen()
{
    // 醴憮蒂 裔 嬪煎 檜翕
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

// 裘 -> 裘
// 裘 -> 瞪癱壁

void printRightUI()
{
    gotoxy(104, 0);
    std::cout << "旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬";
    for (size_t i = 1; i < 49; i++)
    {
        gotoxy(104, i);
        std::cout << "早                                               早";
    }
    gotoxy(104, 49);
    std::cout << "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭";
    //clearScreen();
}
void printUserInfo()
{
    Manager& manager = Manager::getInstance();
    gotoxy(106, 5);
    std::cout << "              [Ы溯檜橫  薑爾]" << endl;
    gotoxy(110, 6);
    std::cout << "收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收" << endl;
    
    gotoxy(110, 7);
    std::cout << "檜葷 : " << player->GetName() << std::endl;
    gotoxy(110, 8);
    std::cout << "羹溘 / 譆渠羹溘 : " << player->GetHp() << " / " << player->GetMaxHp() << std::endl;
    gotoxy(110, 9);
    std::cout << "葆釭 / 譆渠葆釭 : " << player->GetMp() << " / " << player->GetMaxMp() << std::endl;
    gotoxy(110, 10);
    std::cout << "奢問溘 : " << player->GetAtk() << std::endl;
    gotoxy(110, 11);
    std::cout << "寞橫溘 : " << player->GetDef() << std::endl;
    gotoxy(110, 12);
    std::cout << "觼葬じ鏽 �捕� : " << player->GetCriRate() << std::endl;
    gotoxy(110, 13);
    std::cout << "觼葬じ鏽 等嘐雖 : " << player->GetCriDamage() << std::endl;
    gotoxy(110, 14);
    std::cout << "�裔Ш� : " << player->GetAvoidRate() << std::endl;
    gotoxy(110, 15);
    std::cout << "樓紫 : " << player->GetSpeed() << std::endl;
    gotoxy(110, 16);
    std::cout << "模雖旎 : " << player->GetMoney() << std::endl;
    gotoxy(110, 17);
    std::cout << "⑷營 嬪纂 : " << manager.map.GetMapName(manager.map.GetcurrenteMap()) << std::endl;
    gotoxy(110, 18);
    std::cout << "蝶鑒 : " << "蝶鑒" << std::endl;
}
void PrintKeyboardState()
{
    Manager& manager = Manager::getInstance();
    
    gotoxy(106, 35);
    std::cout << "                [酈爾萄  殮溘]";
    gotoxy(110, 36);
    std::cout << "收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收" << endl;
#pragma region DirectionKeys
    gotoxy(110, 38);
    std::cout << "寞щ酈 : " << endl;
    gotoxy(122, 37);
    if (manager.input.GetKeyDown(eKeyCode::Up) || manager.input.GetKey(eKeyCode::Up))
    {
        std::cout << "﹥" << endl;
    }
    else
    {
        std::cout << "﹤" << endl;
    }
    gotoxy(120, 38);
    if (manager.input.GetKeyDown(eKeyCode::Left) || manager.input.GetKey(eKeyCode::Left))
    {
        std::cout << "﹥" << endl;
    }
    else
    {
        std::cout << "﹤" << endl;
    }
    gotoxy(122, 38);
    if (manager.input.GetKeyDown(eKeyCode::Down) || manager.input.GetKey(eKeyCode::Down))
    {
        std::cout << "﹥" << endl;
    }
    else
    {
        std::cout << "﹤" << endl;
    }
    gotoxy(124, 38);
    if (manager.input.GetKeyDown(eKeyCode::Right) || manager.input.GetKey(eKeyCode::Right))
    {
        std::cout << "﹥" << endl;
    }
    else
    {
        std::cout << "﹤" << endl;
    }

    gotoxy(128, 38);
    std::cout << "蝶む檜蝶 : " << endl;
    gotoxy(140, 38);
    if (manager.input.GetKeyDown(eKeyCode::Space) || manager.input.GetKey(eKeyCode::Space))
    {
        std::cout << "﹥﹥﹥﹥" << endl;
    }
    else
    {
        std::cout << "﹤﹤﹤﹤" << endl;
    }
#pragma endregion

#pragma region KeyBoardKeys
    gotoxy(110, 40);
    if (manager.input.GetKeyDown(eKeyCode::Q) || manager.input.GetKey(eKeyCode::Q)) std::cout << "≒";
    else std::cout << "侑";
    gotoxy(112, 40);
    if (manager.input.GetKeyDown(eKeyCode::W) || manager.input.GetKey(eKeyCode::W)) std::cout << "≒";
    else std::cout << "具";
    gotoxy(114, 40);
    if (manager.input.GetKeyDown(eKeyCode::E) || manager.input.GetKey(eKeyCode::E)) std::cout << "≒";
    else std::cout << "供";
    gotoxy(116, 40);
    if (manager.input.GetKeyDown(eKeyCode::R) || manager.input.GetKey(eKeyCode::R)) std::cout << "≒";
    else std::cout << "佺";
    gotoxy(118, 40);
    if (manager.input.GetKeyDown(eKeyCode::T) || manager.input.GetKey(eKeyCode::T)) std::cout << "≒";
    else std::cout << "兒";
    gotoxy(120, 40);
    if (manager.input.GetKeyDown(eKeyCode::Y) || manager.input.GetKey(eKeyCode::Y)) std::cout << "≒";
    else std::cout << "典";
    gotoxy(122, 40);
    if (manager.input.GetKeyDown(eKeyCode::U) || manager.input.GetKey(eKeyCode::U)) std::cout << "≒";
    else std::cout << "兕";
    gotoxy(124, 40);
    if (manager.input.GetKeyDown(eKeyCode::I) || manager.input.GetKey(eKeyCode::I)) std::cout << "≒";
    else std::cout << "佰";
    gotoxy(126, 40);
    if (manager.input.GetKeyDown(eKeyCode::O) || manager.input.GetKey(eKeyCode::O)) std::cout << "≒";
    else std::cout << "侑";
    gotoxy(128, 40);
    if (manager.input.GetKeyDown(eKeyCode::P) || manager.input.GetKey(eKeyCode::P)) std::cout << "≒";
    else std::cout << "侏";
    
    gotoxy(110, 41);
    if (manager.input.GetKeyDown(eKeyCode::A) || manager.input.GetKey(eKeyCode::A)) std::cout << "≒";
    else std::cout << "侍";
    gotoxy(112, 41);
    if (manager.input.GetKeyDown(eKeyCode::S) || manager.input.GetKey(eKeyCode::S)) std::cout << "≒";
    else std::cout << "兔";
    gotoxy(114, 41);
    if (manager.input.GetKeyDown(eKeyCode::D) || manager.input.GetKey(eKeyCode::D)) std::cout << "≒";
    else std::cout << "佬";
    gotoxy(116, 41);
    if (manager.input.GetKeyDown(eKeyCode::F) || manager.input.GetKey(eKeyCode::F)) std::cout << "≒";
    else std::cout << "例";
    gotoxy(118, 41);
    if (manager.input.GetKeyDown(eKeyCode::G) || manager.input.GetKey(eKeyCode::G)) std::cout << "≒";
    else std::cout << "來";
    gotoxy(120, 41);
    if (manager.input.GetKeyDown(eKeyCode::H) || manager.input.GetKey(eKeyCode::H)) std::cout << "≒";
    else std::cout << "侃";
    gotoxy(122, 41);
    if (manager.input.GetKeyDown(eKeyCode::J) || manager.input.GetKey(eKeyCode::J)) std::cout << "≒";
    else std::cout << "併";
    gotoxy(124, 41);
    if (manager.input.GetKeyDown(eKeyCode::K) || manager.input.GetKey(eKeyCode::K)) std::cout << "≒";
    else std::cout << "侈";
    gotoxy(126, 41);
    if (manager.input.GetKeyDown(eKeyCode::L) || manager.input.GetKey(eKeyCode::L)) std::cout << "≒";
    else std::cout << "佩";

    gotoxy(110, 42);
    if (manager.input.GetKeyDown(eKeyCode::Z) || manager.input.GetKey(eKeyCode::Z)) std::cout << "≒";
    else std::cout << "冽";
    gotoxy(112, 42);
    if (manager.input.GetKeyDown(eKeyCode::X) || manager.input.GetKey(eKeyCode::X)) std::cout << "≒";
    else std::cout << "其";
    gotoxy(114, 42);
    if (manager.input.GetKeyDown(eKeyCode::C) || manager.input.GetKey(eKeyCode::C)) std::cout << "≒";
    else std::cout << "使";
    gotoxy(116, 42);
    if (manager.input.GetKeyDown(eKeyCode::V) || manager.input.GetKey(eKeyCode::V)) std::cout << "≒";
    else std::cout << "兩";
    gotoxy(118, 42);
    if (manager.input.GetKeyDown(eKeyCode::B) || manager.input.GetKey(eKeyCode::B)) std::cout << "≒";
    else std::cout << "佳";
    gotoxy(120, 42);
    if (manager.input.GetKeyDown(eKeyCode::N) || manager.input.GetKey(eKeyCode::N)) std::cout << "≒";
    else std::cout << "侖";
    gotoxy(122, 42);
    if (manager.input.GetKeyDown(eKeyCode::M) || manager.input.GetKey(eKeyCode::M)) std::cout << "≒";
    else std::cout << "佻";
    


#pragma endregion
}
void PrintMessage() //TODO
{
    
    gotoxy(4, 35);
    std::cout << "旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬";
    for (size_t i = 36; i < 47; i++)
    {
        gotoxy(4, i);
        std::cout << "早                                                                                         早";
    }
    gotoxy(4, 47);
    std::cout << "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭";

    gotoxy(16, 41);
    std::cout << "嬴檜蠱 擊(蒂) �僱磈牳抻懂炴�.";
}
void PrintBattleUI()
{
    gotoxy(30, 10); 
    std::cout << "旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬";
    for (size_t i = 11; i < 29; i++)
    {
        gotoxy(30, i);
        std::cout << "早                                     早";
    }
    gotoxy(30, 29);
    std::cout << "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭";


    gotoxy(5, 30);
    std::cout << "旨收收收收收收收收收收收收收收收收收收收收收收旬";
    for (size_t i = 31; i < 45; i++)
    {
        gotoxy(5, i);
        std::cout << "早                      早";
    }
    gotoxy(13, 32);
    std::cout << "ч翕 摹鷗";
    gotoxy(6, 34);
    std::cout << " 收收收收收收收收收收收收收收收收收收收收 ";
    gotoxy(8, 36);
    std::cout << "Ⅱ奢問";
    gotoxy(10, 38);
    std::cout << "蝶鑒";
    gotoxy(10, 40);
    std::cout << "檣漸饜葬";
    gotoxy(10, 42);
    std::cout << "紫蜂纂晦";
    gotoxy(5, 45);
    std::cout << "曲收收收收收收收收收收收收收收收收收收收收收收旭";
}

void PrintBattleUI2()
{
    gotoxy(5, 30);
    std::cout << "旨收收收收收收收收收收收收收收收收收收收收收收旬";
    for (size_t i = 31; i < 45; i++)
    {
        gotoxy(5, i);
        std::cout << "早                      早";
    }
    gotoxy(13, 32);
    std::cout << "ч翕 摹鷗";
    gotoxy(6, 34);
    std::cout << " 收收收收收收收收收收收收收收收收收收收收 ";
    gotoxy(10, 36);
    std::cout << "奢問";
    gotoxy(10, 38);
    std::cout << "蝶鑒";
    gotoxy(10, 40);
    std::cout << "檣漸饜葬";
    gotoxy(10, 42);
    std::cout << "紫蜂纂晦";
    gotoxy(5, 45);
    std::cout << "曲收收收收收收收收收收收收收收收收收收收收收收旭";
}



int main()
{
    system("mode con:cols=155 lines=51");
    CursorView();
    Manager& manager = Manager::getInstance();
    manager.input.Initialize();
    manager.map.Initialize();
    manager.map.LoadMap(eMaps::Village);

    Map* currentmap;
    //currentmap = manager.map.GetCurrentMap();
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
        printRightUI();
        printUserInfo();
        PrintKeyboardState();
        //PrintMessage();
        //PrintBattleUI();
        
    }
}