#include "Game.h"


int Game::Title()
{
    system("mode con:cols=150 lines=51");
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    setlocale(LC_ALL, "korean");
    _wsetlocale(LC_ALL, L"korean");
    srand((unsigned)time(NULL));
    CursorView();
    drawIntro();
    if (!menuDraw()) return 0;
    system("cls");
    while (true)
    {
        string name;
        DrawOneWords(IntroText, 10);
        gotoxy(19, 21);
        cin >> name;
        player = new Player(name);
        break;
    }
    system("cls");
}
void Game::InGame()
{
    Manager& manager = Manager::getInstance();
    ConsolePopup popup;
    manager.input.Initialize();
    manager.map.Initialize();
    manager.map.LoadMap(eMaps::Village);
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
    while (true)
    {
        CursorView();
        manager.input.Update();
        clearScreen();
        PlayerSetStatusByLevel();
        currentMap = manager.map.GetCurrentMap();
        DrawBuffer(currentMap);
        MovePlayer(currentMap);
        currentMap = manager.map.GetCurrentMap();
        renderBuffer(currentMap);

        #pragma region Popup
        if (manager.input.GetKeyDown(eKeyCode::P))
        {
            popup.DrawUserInfo(5, 5, 50, 20, L" Ы溯檜橫 薑爾", player);
            inputAnyKey();
            system("cls");
        }
        if (manager.input.GetKeyDown(eKeyCode::I))
        {
            popup.DrawUserInventory(70, 5, 100, 15, L" 檣漸饜葬", player);
            inputAnyKey();
            system("cls");
        }
        if (manager.input.GetKeyDown(eKeyCode::S))
        {
            popup.DrawUserSkill(30, 25, 140, 40, L" 蝶鑒薑爾", player);
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

#pragma region TitleMethod
void Game::drawIntro()
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
int Game::menuDraw()
{
    int x = 64;
    int y = 32;
    gotoxy(62, 32);
    cout << "Ⅱ啪歜 衛濛";
    gotoxy(64, 33);
    cout << "啪歜 謙猿";
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
                cout << "Ⅱ";
            }
        }
        else if (manager.input.GetKeyDown(eKeyCode::Up))
        {
            if (y == 33)
            {
                gotoxy(x - 2, y);
                cout << "  ";
                gotoxy(x - 2, --y);
                cout << "Ⅱ";
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
void Game::DrawOneWords(const std::string& text, int delay)
{
    for (char ch : text) 
    {
        std::cout << ch;
        Sleep(delay);
    }
}
#pragma endregion

#pragma region Utils
void Game::gotoxy(int x, int y)
{
    HANDLE consolHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(consolHandle, pos);
}
void Game::CursorView()
{
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //醴憮 掃晦 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //醴憮 Visible TRUE(爾歜) FALSE(獗梯)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
void Game::clearScreen()
{
    // 醴憮蒂 裔 嬪煎 檜翕
    std::cout << "\033[H";
}
void Game::inputAnyKey()
{
    Manager& manager = manager.getInstance();
    while (true)
    {
        manager.input.Update();
        if (manager.input.GetKeyDown(eKeyCode::Space)) return;
    }
}
void Game::PlayerSetStatusByLevel()
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
#pragma endregion

#pragma region MapRender
void Game::DrawBuffer(Map* currentMap)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            buffer[y][x] = currentMap->at(y, x);
        }
    }
}
void Game::renderBuffer(Map* currentMap)
{
    // 夔樂 璽 觼晦 橢晦
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth, consoleHeight;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int startX = playerX - (ViewSizeX / 2); // Ы溯檜橫蒂 醞褕戲煎 viewSize曖 觼晦 瞰奩噶 謝辦 溶渦葭 彰嬪
    int endX = playerX + (ViewSizeX / 2);
    int startY = playerY - (ViewSizeY / 2); // Ы溯檜橫蒂 醞褕戲煎 viewSize曖 觼晦 瞰奩噶 鼻ж 溶渦葭 彰嬪
    int endY = playerY + (ViewSizeY / 2);


    if (startX < 0) startX = 0;
    if (startY < 0) startY = 0;
    if (endX >= MAP_WIDTH) endX = MAP_WIDTH - 1;
    if (endY >= MAP_HEIGHT) endY = MAP_HEIGHT - 1;

    // 裘曖 陛煎, 撮煎 觼晦
    int mapWidth = endX - startX + 1;
    int mapHeight = endY - startY + 1;

    //// 夔樂 醞懈縑 蜃蹺晦 嬪п 謝ル 啗骯
    int offsetX = (consoleWidth - mapWidth) / 2 - 20;
    int offsetY = (consoleHeight - mapHeight) / 2;

    //// 還 蜃蹺晦 嬪п 嬪薹縑 綴 還 轎溘
    for (int i = 0; i < offsetY; ++i)
    {
        std::cout << std::endl;
    }

    // 衛撿 彰嬪 頂縑憮 轎溘 (X蹴縑 奢寥 蹺陛)
    for (int y = startY; y <= endY; ++y)
    {
        //// 豭薹縑 奢寥 蹺陛ж罹 X蹴 醞懈 蜃辭
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
            else if (currentMap->at(y, x) == 7)
            {
                std::cout << "≒";
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
        std::cout << "\n";
    }
}
#pragma endregion

#pragma region UIMethod
void Game::printUserInfo(ConsoleDraw& consoleDrawBuffer)
{
    Manager& manager = Manager::getInstance();
    consoleDrawBuffer.DrawAt(8, 1, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(8, 2, L"          [Ы溯檜橫  薑爾]");
    consoleDrawBuffer.DrawAt(10, 3, L"收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收");

    wstring wstr(player->GetName().size(), L'\0');
    std::mbstowcs(&wstr[0], player->GetName().c_str(), player->GetName().size());
    consoleDrawBuffer.DrawAt(10, 4, L"檜葷 : " + wstr);
    consoleDrawBuffer.DrawAt(10, 5, L"羹溘 / 譆渠羹溘 : " + to_wstring(player->GetHp()) + L" / " + to_wstring(player->GetMaxHp()));
    consoleDrawBuffer.DrawAt(10, 6, L"葆釭 / 譆渠葆釭 : " + to_wstring(player->GetMp()) + L" / " + to_wstring(player->GetMaxMp()));
    consoleDrawBuffer.DrawAt(10, 7, L"奢問溘 : " + to_wstring(player->GetAtk()));
    consoleDrawBuffer.DrawAt(10, 8, L"寞橫溘 : " + to_wstring(player->GetDef()));
    consoleDrawBuffer.DrawAt(8, 9, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
    //buffer.DrawAt(10, 8, L"觼葬じ鏽 �捕� : " + to_wstring(player->GetCriRate()) + L"%");
    //buffer.DrawAt(10, 9, L"觼葬じ鏽 等嘐雖 :" + to_wstring(player->GetCriDamage()) + L"%");
    /*buffer.DrawAt(70, 9, L"�裔Ш� :" + to_wstring(player->GetAvoidRate()) + L"%");
    buffer.DrawAt(70, 10, L"樓紫 :" + to_wstring(player->GetSpeed()));*/
    //buffer.DrawAt(10, 10, L"模雖旎 :" + to_wstring(player->GetMoney()) + L"埤萄");

    string mapName = manager.map.GetMapName(manager.map.GetcurrenteMap());
    wstring wstr2(mapName.size(), L'\0');
    std::mbstowcs(&wstr2[0], mapName.c_str(), mapName.size());
    //buffer.DrawAt(10, 11, L"⑷營 嬪纂 :" + wstr2);
}
void Game::DrawEmptyImage(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(30, 10, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(30, 11, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 12, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 13, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 14, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 15, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 16, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 17, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 18, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 19, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 20, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 21, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 22, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 23, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 24, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 25, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 26, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 27, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 28, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 29, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawSlimeImage(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(50, 10, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(50, 11, L"早 ﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤早   蝸塭歜   早");
    consoleDrawBuffer.DrawAt(50, 12, L"早 ﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤早收收收收收收收收收收收收旭");
    consoleDrawBuffer.DrawAt(50, 13, L"早 ﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 14, L"早 ﹤﹤﹤﹤﹤﹤﹤﹤﹥﹥﹤﹤﹤﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 15, L"早 ﹤﹤﹤﹤﹤﹤﹤﹥﹥﹥﹥﹤﹤﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 16, L"早 ﹤﹤﹤﹤﹤﹤﹥﹤﹤﹤﹤﹥﹤﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 17, L"早 ﹤﹤﹤﹤﹥﹥﹤﹤﹤﹤﹤﹤﹥﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 18, L"早 ﹤﹤﹤﹥﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹥﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 19, L"早 ﹤﹤﹤﹥﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹥﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 20, L"早 ﹤﹤﹥﹥﹤﹤﹥﹤﹤﹤﹤﹥﹤﹤﹥﹥﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 21, L"早 ﹤﹤﹥﹤﹤﹤﹥﹤﹤﹤﹤﹥﹤﹤﹤﹥﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 22, L"早 ﹤﹤﹥﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹥﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 23, L"早 ﹤﹤﹥﹤﹤﹤﹥﹤﹤﹤﹤﹥﹤﹤﹤﹥﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 24, L"早 ﹤﹤﹥﹥﹤﹤﹤﹥﹥﹥﹥﹤﹤﹤﹥﹥﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 25, L"早 ﹤﹤﹤﹥﹥﹤﹤﹤﹤﹤﹤﹤﹤﹥﹥﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 26, L"早 ﹤﹤﹤﹤﹤﹥﹥﹥﹥﹥﹥﹥﹥﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 27, L"早 ﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 28, L"早 ﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 29, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawGoblinImage(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(50, 10, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(50, 11, L"早 ﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤早   堅綰萼   早");
    consoleDrawBuffer.DrawAt(50, 12, L"早 ﹤﹤﹤﹤﹤﹤﹤﹥﹤﹤﹤﹤﹤﹥﹤﹤﹤﹤早收收收收收收收收收收收收旭");
    consoleDrawBuffer.DrawAt(50, 13, L"早 ﹤﹤﹤﹥﹤﹤﹤﹥﹥﹥﹥﹥﹥﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 14, L"早 ﹤﹤﹥﹤﹥﹤﹤﹥﹥﹤﹤﹤﹥﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 15, L"早 ﹤﹥﹥﹥﹥﹥﹤﹥﹤﹤﹤﹤﹤﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 16, L"早 ﹤﹤﹤﹥﹤﹤﹤﹥﹥﹤﹤﹤﹥﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 17, L"早 ﹤﹤﹤﹥﹤﹤﹤﹤﹤﹥﹥﹥﹤﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 18, L"早 ﹤﹤﹤﹥﹤﹤﹤﹤﹥﹥﹥﹥﹥﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 19, L"早 ﹤﹤﹤﹥﹤﹤﹥﹥﹤﹤﹤﹤﹤﹥﹥﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 20, L"早 ﹤﹤﹤﹥﹤﹥﹤﹥﹤﹤﹤﹤﹤﹥﹤﹥﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 21, L"早 ﹤﹤﹤﹥﹥﹤﹤﹥﹤﹤﹤﹤﹤﹥﹤﹥﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 22, L"早 ﹤﹤﹤﹥﹤﹤﹤﹥﹤﹤﹤﹤﹤﹥﹤﹥﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 23, L"早 ﹤﹤﹤﹥﹤﹤﹤﹥﹥﹥﹥﹥﹥﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 24, L"早 ﹤﹤﹤﹥﹤﹤﹤﹤﹥﹤﹤﹤﹥﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 25, L"早 ﹤﹤﹤﹥﹤﹤﹤﹤﹥﹤﹤﹤﹥﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 26, L"早 ﹤﹤﹤﹥﹤﹤﹤﹤﹥﹤﹤﹤﹥﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 27, L"早 ﹤﹤﹤﹤﹤﹤﹤﹥﹥﹤﹤﹥﹥﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 28, L"早 ﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 29, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawSkeletonImage(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(50, 10, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(50, 11, L"早 ﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤早  蝶騷溯驛  早 ");
    consoleDrawBuffer.DrawAt(50, 12, L"早 ﹤﹤﹤﹤﹤﹤﹤﹥﹥﹥﹥﹥﹤﹤﹤﹤﹤﹤早收收收收收收收收收收收收旭");
    consoleDrawBuffer.DrawAt(50, 13, L"早 ﹤﹤﹤﹤﹤﹥﹥﹤﹤﹤﹤﹤﹥﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 14, L"早 ﹤﹤﹤﹥﹥﹤﹤﹤﹤﹤﹤﹤﹤﹤﹥﹥﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 15, L"早 ﹤﹤﹥﹥﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹥﹥﹤早");
    consoleDrawBuffer.DrawAt(50, 16, L"早 ﹤﹤﹥﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹥﹤早");
    consoleDrawBuffer.DrawAt(50, 17, L"早 ﹤﹤﹥﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹥﹤早");
    consoleDrawBuffer.DrawAt(50, 18, L"早 ﹤﹤﹥﹤﹤﹥﹥﹤﹤﹤﹤﹤﹥﹥﹤﹤﹥﹤早");
    consoleDrawBuffer.DrawAt(50, 19, L"早 ﹤﹤﹥﹤﹤﹥﹥﹤﹤﹤﹤﹤﹥﹥﹤﹤﹥﹤早");
    consoleDrawBuffer.DrawAt(50, 20, L"早 ﹤﹤﹥﹥﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹥﹥﹤早");
    consoleDrawBuffer.DrawAt(50, 21, L"早 ﹤﹤﹤﹥﹥﹤﹤﹤﹤﹤﹤﹤﹤﹤﹥﹥﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 22, L"早 ﹤﹤﹤﹤﹥﹥﹤﹤﹤﹤﹤﹤﹤﹥﹥﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 23, L"早 ﹤﹤﹤﹤﹤﹥﹤﹤﹤﹤﹤﹤﹤﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 24, L"早 ﹤﹤﹤﹤﹤﹥﹤﹤﹤﹥﹤﹤﹤﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 25, L"早 ﹤﹤﹤﹤﹤﹥﹤﹤﹤﹥﹤﹤﹤﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 26, L"早 ﹤﹤﹤﹤﹤﹥﹤﹤﹥﹤﹥﹤﹤﹥﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 27, L"早 ﹤﹤﹤﹤﹤﹤﹥﹥﹥﹤﹥﹥﹥﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 28, L"早 ﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤﹤早");
    consoleDrawBuffer.DrawAt(50, 29, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawInvisableDragonImage(ConsoleDraw& consoleDrawBuffer)
{
    {
        consoleDrawBuffer.DrawAt(50, 10, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬收收收收收收收收收收收收收旬");
        consoleDrawBuffer.DrawAt(50, 11, L"早                                     早 癱貲 萄楚堆 早 ");
        consoleDrawBuffer.DrawAt(50, 12, L"早                                     早收收收收收收收收收收收收收旭");
        consoleDrawBuffer.DrawAt(50, 13, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 14, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 15, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 16, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 17, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 18, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 19, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 20, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 21, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 22, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 23, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 24, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 25, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 26, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 27, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 28, L"早                                     早");
        consoleDrawBuffer.DrawAt(50, 29, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
    }
}
void Game::DrawBattleChoiceAttack(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(10, 30, L"旨收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(10, 31, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 32, L"早       ч翕 摹鷗      早");
    consoleDrawBuffer.DrawAt(10, 33, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 34, L"早 收收收收收收收收收收收收收收收收收收收收 早");
    consoleDrawBuffer.DrawAt(10, 35, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 36, L"早   Ⅱ 奢問            早");
    consoleDrawBuffer.DrawAt(10, 37, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 38, L"早    蝶鑒              早");
    consoleDrawBuffer.DrawAt(10, 39, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 40, L"早    檣漸饜葬          早");
    consoleDrawBuffer.DrawAt(10, 41, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 42, L"早    紫蜂纂晦          早");
    consoleDrawBuffer.DrawAt(10, 43, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 44, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 45, L"曲收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawBattleChoiceSkill(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(10, 30, L"旨收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(10, 31, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 32, L"早       ч翕 摹鷗      早");
    consoleDrawBuffer.DrawAt(10, 33, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 34, L"早 收收收收收收收收收收收收收收收收收收收收 早");
    consoleDrawBuffer.DrawAt(10, 35, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 36, L"早    奢問              早");
    consoleDrawBuffer.DrawAt(10, 37, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 38, L"早   Ⅱ 蝶鑒            早");
    consoleDrawBuffer.DrawAt(10, 39, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 40, L"早    檣漸饜葬          早");
    consoleDrawBuffer.DrawAt(10, 41, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 42, L"早    紫蜂纂晦          早");
    consoleDrawBuffer.DrawAt(10, 43, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 44, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 45, L"曲收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawBattleChoiceInven(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(10, 30, L"旨收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(10, 31, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 32, L"早       ч翕 摹鷗      早");
    consoleDrawBuffer.DrawAt(10, 33, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 34, L"早 收收收收收收收收收收收收收收收收收收收收 早");
    consoleDrawBuffer.DrawAt(10, 35, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 36, L"早    奢問              早");
    consoleDrawBuffer.DrawAt(10, 37, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 38, L"早    蝶鑒              早");
    consoleDrawBuffer.DrawAt(10, 39, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 40, L"早   Ⅱ 檣漸饜葬        早");
    consoleDrawBuffer.DrawAt(10, 41, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 42, L"早    紫蜂纂晦          早");
    consoleDrawBuffer.DrawAt(10, 43, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 44, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 45, L"曲收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawBattleChoiceRunAway(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(10, 30, L"旨收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(10, 31, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 32, L"早       ч翕 摹鷗      早");
    consoleDrawBuffer.DrawAt(10, 33, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 34, L"早 收收收收收收收收收收收收收收收收收收收收 早");
    consoleDrawBuffer.DrawAt(10, 35, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 36, L"早    奢問              早");
    consoleDrawBuffer.DrawAt(10, 37, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 38, L"早    蝶鑒              早");
    consoleDrawBuffer.DrawAt(10, 39, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 40, L"早    檣漸饜葬          早");
    consoleDrawBuffer.DrawAt(10, 41, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 42, L"早   Ⅱ 紫蜂纂晦        早");
    consoleDrawBuffer.DrawAt(10, 43, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 44, L"早                      早");
    consoleDrawBuffer.DrawAt(10, 45, L"曲收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawSkillList(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(35, 30, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(35, 31, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(31, 32, L"早        だ檜橫獐                                                   早");
    consoleDrawBuffer.DrawAt(35, 33, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(35, 34, L"早        ��                                                         早");
    consoleDrawBuffer.DrawAt(35, 35, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(33, 36, L"早        詭纔螃                                                     早");
    consoleDrawBuffer.DrawAt(35, 37, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(32, 38, L"早        菴煎陛晦                                                   早");
    consoleDrawBuffer.DrawAt(35, 39, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(31, 40, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(35, 41, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(31, 42, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(35, 43, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(35, 44, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(35, 45, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawInvenList(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(34, 30, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(34, 31, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(30, 32, L"早        羹溘僭擒                                                   早");
    consoleDrawBuffer.DrawAt(34, 33, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(34, 34, L"早        葆釭僭擒                                                   早");
    consoleDrawBuffer.DrawAt(34, 35, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(32, 36, L"早        縣葛憮                                                     早");
    consoleDrawBuffer.DrawAt(34, 37, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(32, 38, L"早        菴煎陛晦                                                   早");
    consoleDrawBuffer.DrawAt(34, 39, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(29, 40, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(34, 41, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(30, 42, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(34, 43, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(34, 44, L"早                                                                   早");
    consoleDrawBuffer.DrawAt(34, 45, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawBattleUI(ConsoleDraw& consoleDrawBuffer)
{
    consoleDrawBuffer.DrawAt(30, 10, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDrawBuffer.DrawAt(30, 12, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 13, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 14, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 15, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 16, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 17, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 18, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 19, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 20, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 21, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 22, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 23, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 24, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 25, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 26, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 27, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 28, L"早                                     早");
    consoleDrawBuffer.DrawAt(30, 29, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawMessageBox(ConsoleDraw& consoleDraw, const std::wstring& message)
{
    consoleDraw.DrawAt(35, 30, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDraw.DrawAt(35, 31, L"早                                                                                         早");
    consoleDraw.DrawAt(31, 32, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 33, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 34, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 35, L"早                                                                                         早");
    consoleDraw.DrawAt(33, 36, L"早                                                                                         早");
    consoleDraw.DrawAt(42, 37, message);
    consoleDraw.DrawAt(32, 38, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 39, L"早                                                                                         早");
    consoleDraw.DrawAt(31, 40, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 41, L"早                                                                                         早");
    consoleDraw.DrawAt(31, 42, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 43, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 44, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 45, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
void Game::DrawMessageBox2(ConsoleDraw& consoleDraw, const std::wstring& message)
{
    consoleDraw.DrawAt(35, 30, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDraw.DrawAt(35, 31, L"早                                                                                         早");
    consoleDraw.DrawAt(31, 32, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 33, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 34, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 35, L"早                                                                                         早");
    consoleDraw.DrawAt(32, 36, L"早                                                                                         早");
    consoleDraw.DrawAt(42, 37, message);
    consoleDraw.DrawAt(33, 38, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 39, L"早                                                                                         早");
    consoleDraw.DrawAt(31, 40, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 41, L"早                                                                                         早");
    consoleDraw.DrawAt(31, 42, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 43, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 44, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 45, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");

}
void Game::DrawMessageBox3(ConsoleDraw& consoleDraw, const std::wstring& message)
{
    consoleDraw.DrawAt(35, 30, L"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬");
    consoleDraw.DrawAt(35, 31, L"早                                                                                         早");
    consoleDraw.DrawAt(31, 32, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 33, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 34, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 35, L"早                                                                                         早");
    consoleDraw.DrawAt(33, 36, L"早                                                                                         早");
    consoleDraw.DrawAt(42, 37, message);
    consoleDraw.DrawAt(34, 38, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 39, L"早                                                                                         早");
    consoleDraw.DrawAt(30, 40, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 41, L"早                                                                                         早");
    consoleDraw.DrawAt(31, 42, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 43, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 44, L"早                                                                                         早");
    consoleDraw.DrawAt(35, 45, L"曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭");
}
#pragma endregion

#pragma region BattleMethod
bool Game::PlayerDead(ConsoleDraw& consoleDrawBuffer)
{
    if (player->GetHp() <= 0)
    {
        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
        DrawMessageBox(consoleDrawBuffer, L"Ы溯檜橫陛 噙楝颶");
        consoleDrawBuffer.Render();
        inputAnyKey();
        system("cls");
        return true;
    }
    return false;
}
void Game::MonsterTurn(ConsoleDraw& consoleDrawBuffer)
{
    int damage = monster->GetAtk() - player->GetDef();
    if (damage <= 0) damage = 1;
    DrawMessageBox2(consoleDrawBuffer, L"                                                    ");
    DrawMessageBox2(consoleDrawBuffer, L"跨蝶攪曖 奢問!");
    consoleDrawBuffer.Render();
    inputAnyKey();
    DrawMessageBox2(consoleDrawBuffer, L"                                                                      ");
    
    DrawMessageBox2(consoleDrawBuffer, L"Ы溯檜橫縑啪 " + to_wstring(damage) + L"等嘐雖曖 Яп蒂 殮��! ");
    player->SetHp(player->GetHp() - damage);
    consoleDrawBuffer.Render();
    inputAnyKey();
    DrawMessageBox2(consoleDrawBuffer, L"                                                                      ");
}
void Game::PlayerAttack(ConsoleDraw& consoleDrawBuffer)
{
        int damage = player->GetAtk() - monster->GetDef();
        if (damage <= 0) damage = 0;

        DrawMessageBox2(consoleDrawBuffer, L"Ы溯檜橫曖 奢問!");
        consoleDrawBuffer.Render();
        inputAnyKey();
        DrawMessageBox2(consoleDrawBuffer, L"                                                                      ");

        wstring wstr(monster->GetName().size(), L'\0');
        std::mbstowcs(&wstr[0], monster->GetName().c_str(), monster->GetName().size());
        DrawMessageBox2(consoleDrawBuffer, wstr + L"縑啪 " + to_wstring(damage) + L"等嘐雖曖 Яп蒂 殮��!");
        monster->SetHp(monster->GetHp() - damage);
        consoleDrawBuffer.Render();
        inputAnyKey();
        DrawMessageBox2(consoleDrawBuffer, L"                                                                      ");
}
bool Game::MonsterDead(ConsoleDraw& consoleDrawBuffer)
{
    if (monster->GetHp() <= 0)
    {
        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
        DrawMessageBox(consoleDrawBuffer, L"跨蝶攪蒂 噙楝お葡");
        consoleDrawBuffer.Render();
        inputAnyKey();
        DrawMessageBox(consoleDrawBuffer, L"                                                                      ");
        DrawMessageBox(consoleDrawBuffer, to_wstring(monster->GetMoney()) + L"埤萄 �僱�");
        consoleDrawBuffer.Render();
        inputAnyKey();
        DrawMessageBox(consoleDrawBuffer, to_wstring(monster->GetExp()) + L"唳я纂 �僱�");
        player->SetMoney(player->GetMoney() + monster->GetMoney());
        player->SetExp(player->GetExp() + monster->GetExp());
        consoleDrawBuffer.Render();
        inputAnyKey();
        system("cls");
        return true;
    }
    return false;
}
void Game::MovePlayer(Map* currentMap)
{
    {
        // (y,x)  up : (-1, +0), down (+1, +0), left(0,+1), right(0,-1)
        int newPosX = playerX;
        int newPosY = playerY;
        ConsoleDraw consoleDrawBuffer(150, 51);
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
                printUserInfo(consoleDrawBuffer);
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
                    //奢問
                    if (menuSelect == 1)
                    {
                        int damage;

                        while (true)
                        {
                            manager.input.Initialize();
                            manager.input.Update();

                            PlayerAttack(consoleDrawBuffer); //Ы溯檜橫 橾奩奢問
                            if (PlayerDead(consoleDrawBuffer))
                            {
                                isPlayerDie = true;
                                break;
                            }
                            else if (MonsterDead(consoleDrawBuffer))
                            {
                                isMonsterDie = true;
                                break;
                            }

                            MonsterTurn(consoleDrawBuffer);
                            if (PlayerDead(consoleDrawBuffer))
                            {
                                isPlayerDie = true;
                                break;
                            }
                            else if (MonsterDead(consoleDrawBuffer))
                            {
                                isMonsterDie = true;
                                break;
                            }
                            break;
                        }
                    }
                    //蝶鑒
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
                            case 0: consoleDrawBuffer.DrawAt(38, 32, L"Ⅱ だ檜橫獐"); break;
                            case 1: consoleDrawBuffer.DrawAt(42, 34, L"Ⅱ ��"); break;
                            case 2: consoleDrawBuffer.DrawAt(40, 36, L"Ⅱ 詭纔螃"); break;
                            case 3: consoleDrawBuffer.DrawAt(40, 38, L"Ⅱ 菴煎陛晦"); break;
                            default:break;
                            }

                            if (manager.input.GetKeyDown(eKeyCode::Space))
                            {
                                consoleDrawBuffer.Clear();

                                if (monster->GetMonsterType() == MonsterType::SLIME) DrawSlimeImage(consoleDrawBuffer);
                                else if (monster->GetMonsterType() == MonsterType::GOBLIN) DrawGoblinImage(consoleDrawBuffer);
                                else if (monster->GetMonsterType() == MonsterType::SKELETON) DrawSkeletonImage(consoleDrawBuffer);
                                DrawBattleChoiceSkill(consoleDrawBuffer);
                                printUserInfo(consoleDrawBuffer);

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
                                                DrawMessageBox(consoleDrawBuffer, L"蝶鑒 餌辨縑 в蹂и 葆釭陛 睡褶м棲棻! ");
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

                                        if (PlayerDead(consoleDrawBuffer))
                                        {
                                            isPlayerDie = true;
                                            break;
                                        }
                                        else if (MonsterDead(consoleDrawBuffer))
                                        {
                                            isMonsterDie = true;
                                            break;
                                        }
                                        MonsterTurn(consoleDrawBuffer);
                                        if (PlayerDead(consoleDrawBuffer))
                                        {
                                            isPlayerDie = true;
                                            break;
                                        }
                                        else if (MonsterDead(consoleDrawBuffer))
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
                                                DrawMessageBox(consoleDrawBuffer, L"蝶鑒 餌辨縑 в蹂и 葆釭陛 睡褶м棲棻! ");
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

                                        if (PlayerDead(consoleDrawBuffer))
                                        {
                                            isPlayerDie = true;
                                            break;
                                        }
                                        else if (MonsterDead(consoleDrawBuffer))
                                        {
                                            isMonsterDie = true;
                                            break;
                                        }
                                        MonsterTurn(consoleDrawBuffer);
                                        if (PlayerDead(consoleDrawBuffer))
                                        {
                                            isPlayerDie = true;
                                            break;
                                        }
                                        else if (MonsterDead(consoleDrawBuffer))
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
                                                DrawMessageBox(consoleDrawBuffer, L"蝶鑒 餌辨縑 в蹂и 葆釭陛 睡褶м棲棻! ");
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

                                        if (PlayerDead(consoleDrawBuffer))
                                        {
                                            isPlayerDie = true;
                                            break;
                                        }
                                        else if (MonsterDead(consoleDrawBuffer))
                                        {
                                            isMonsterDie = true;
                                            break;
                                        }
                                        MonsterTurn(consoleDrawBuffer);
                                        if (PlayerDead(consoleDrawBuffer))
                                        {
                                            isPlayerDie = true;
                                            break;
                                        }
                                        else if (MonsterDead(consoleDrawBuffer))
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
                            printUserInfo(consoleDrawBuffer);
                            consoleDrawBuffer.Render();
                        }
                    }
                    //檣漸
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
                                consoleDrawBuffer.DrawAt(37, 32, L"Ⅱ 羹溘僭擒");
                                break;
                            case 1:
                                consoleDrawBuffer.DrawAt(41, 34, L"Ⅱ 葆釭僭擒");
                                break;
                            case 2:
                                consoleDrawBuffer.DrawAt(39, 36, L"Ⅱ 縣葛憮");
                                break;
                            case 3:
                                consoleDrawBuffer.DrawAt(39, 38, L"Ⅱ 菴煎陛晦");
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
                                printUserInfo(consoleDrawBuffer);
                                if (itemNum == 0)
                                {
                                    if (player->getPotionlList()[0]->getItemQuantity() == 0)
                                    {
                                        while (true)
                                        {
                                            DrawMessageBox3(consoleDrawBuffer, L"餌辨ж堅濠 ж朝 ん暮曖 偃熱陛 賅濠奧棲棻! ");
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
                                            consoleDrawBuffer.Render(); // 罹晦憮 蝶鑒煎 螢塭馬
                                            inputAnyKey();
                                        }
                                        player->getPotionlList()[0]->setItemQuantity();
                                    }

                                    MonsterTurn(consoleDrawBuffer);
                                    if (PlayerDead(consoleDrawBuffer))
                                    {
                                        isPlayerDie = true;
                                        break;
                                    }
                                    else if (MonsterDead(consoleDrawBuffer))
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
                                            DrawMessageBox(consoleDrawBuffer, L"п渡 ん暮檜 橈蝗棲棻! ");
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

                                    MonsterTurn(consoleDrawBuffer);
                                    if (PlayerDead(consoleDrawBuffer))
                                    {
                                        isPlayerDie = true;
                                        break;
                                    }
                                    else if (MonsterDead(consoleDrawBuffer))
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
                                            DrawMessageBox(consoleDrawBuffer, L"п渡 ん暮檜 橈蝗棲棻! ");
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

                                    MonsterTurn(consoleDrawBuffer);
                                    if (PlayerDead(consoleDrawBuffer))
                                    {
                                        isPlayerDie = true;
                                        break;
                                    }
                                    else if (MonsterDead(consoleDrawBuffer))
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
                            printUserInfo(consoleDrawBuffer);
                            consoleDrawBuffer.Render();
                        }
                    }
                    //紫蜂
                    else if (menuSelect == 4)
                    {
                        //TODO 紫蜂, 褒ぬ衛 跨蝶攪縑啪 и欐 蜃堅, 濠褐欐 陳嬴馬
                        if (rand() % 2 == 0)
                        {
                            DrawMessageBox(consoleDrawBuffer, L"紫蜂纂晦蒂 褒ぬц蝗棲棻!");
                            consoleDrawBuffer.Render();
                            inputAnyKey();
                            MonsterTurn(consoleDrawBuffer);
                            if (PlayerDead(consoleDrawBuffer))
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
                            DrawMessageBox(consoleDrawBuffer, L"餌蜂ж樟蝗棲棻.");
                            consoleDrawBuffer.Render();
                            inputAnyKey();
                            DrawMessageBox(consoleDrawBuffer, L"                                            ");
                            DrawMessageBox(consoleDrawBuffer, L"葆擊縑憮 棻衛 睡�勒桭炴�.");
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
                    popup.DrawPotionShop(40, 10, 100, 30, L" <ん暮鼻薄>", player);
                    bool isEnd = false;
                    while (true)
                    {
                        manager.input.Update();
                        int count;
                        gotoxy(44, 26);
                        cout << "模雖旎 : " + to_string(player->GetMoney()) + " 埤萄";
                        gotoxy(44, 27);
                        cout << "掘衙ж褒 ん暮曖 廓�ㄧ� 殮溘п輿撮蹂.";
                        while (true)
                        {
                            manager.input.Update();
                            if (manager.input.GetKeyDown(eKeyCode::Num1))
                            {
                                if (player->GetMoney() < player->getPotionlList()[0]->getItemPrice())
                                {
                                    gotoxy(44, 28);
                                    cout << "掘衙 褒ぬ : 濤擋檜 賅濠奧棲棻!";
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
                                    cout << "掘衙 諫猿!";
                                    Sleep(1000);
                                    gotoxy(44, 28);
                                    cout << "                     ";
                                    gotoxy(44, 26);
                                    cout << "                                                 ";
                                    gotoxy(44, 26);
                                    cout << "模雖旎 : " + to_string(player->GetMoney()) + " 埤萄";
                                }
                            }
                            else if (manager.input.GetKeyDown(eKeyCode::Num2))
                            {
                                if (player->GetMoney() < player->getPotionlList()[1]->getItemPrice())
                                {
                                    gotoxy(44, 28);
                                    cout << "掘衙 褒ぬ : 濤擋檜 賅濠奧棲棻!";
                                    Sleep(1000);
                                    gotoxy(44, 28);
                                    cout << "                               ";
                                }
                                else
                                {
                                    player->SetMoney(player->GetMoney() - player->getPotionlList()[1]->getItemPrice());
                                    player->getPotionlList()[1]->setItemQuantity(1);
                                    gotoxy(44, 28);
                                    cout << "掘衙 諫猿!";
                                    Sleep(1000);
                                    gotoxy(44, 28);
                                    cout << "                     ";
                                    gotoxy(44, 26);
                                    cout << "                                                 ";
                                    gotoxy(44, 26);
                                    cout << "模雖旎 : " + to_string(player->GetMoney()) + " 埤萄";
                                }
                            }
                            else if (manager.input.GetKeyDown(eKeyCode::Num3))
                            {
                                if (player->GetMoney() < player->getPotionlList()[2]->getItemPrice())
                                {
                                    gotoxy(44, 28);
                                    cout << "掘衙 褒ぬ : 濤擋檜 賅濠奧棲棻!";
                                    Sleep(1000);
                                    gotoxy(44, 28);
                                    cout << "                               ";
                                }
                                else
                                {
                                    player->SetMoney(player->GetMoney() - player->getPotionlList()[2]->getItemPrice());
                                    player->getPotionlList()[2]->setItemQuantity(1);
                                    gotoxy(44, 28);
                                    cout << "掘衙 諫猿!";
                                    Sleep(1000);
                                    gotoxy(44, 28);
                                    cout << "                     ";
                                    gotoxy(44, 26);
                                    cout << "                                                 ";
                                    gotoxy(44, 26);
                                    cout << "模雖旎 : " + to_string(player->GetMoney()) + " 埤萄";
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
                    popup.DrawSkillShop(40, 10, 100, 30, L" <蝶鑒溯漣 鼻薄>", player);
                    bool isEnd = false;
                    while (true)
                    {
                        manager.input.Update();
                        int count;
                        gotoxy(44, 26);
                        cout << "模雖旎 : " + to_string(player->GetMoney()) + " 埤萄";
                        gotoxy(44, 27);
                        cout << "掘衙ж褒 蝶鑒曖 廓�ㄧ� 殮溘п輿撮蹂.";
                        while (true)
                        {
                            manager.input.Update();
                            if (manager.input.GetKeyDown(eKeyCode::Num1))
                            {
                                if (player->GetMoney() < 1000)
                                {
                                    gotoxy(44, 28);
                                    cout << "掘衙 褒ぬ : 濤擋檜 賅濠奧棲棻!";
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
                                    cout << "掘衙 諫猿!";
                                    Sleep(1000);
                                    gotoxy(44, 28);
                                    cout << "                     ";
                                    gotoxy(44, 26);
                                    cout << "                                                 ";
                                    gotoxy(44, 26);
                                    cout << "模雖旎 : " + to_string(player->GetMoney()) + " 埤萄";
                                }
                            }
                            else if (manager.input.GetKeyDown(eKeyCode::Num2))
                            {
                                if (player->GetMoney() < 5000)
                                {
                                    gotoxy(44, 28);
                                    cout << "掘衙 褒ぬ : 濤擋檜 賅濠奧棲棻!";
                                    Sleep(1000);
                                    gotoxy(44, 28);
                                    cout << "                               ";
                                }
                                else
                                {
                                    player->SetMoney(player->GetMoney() - 5000);
                                    player->getActiveSkillList()[1]->setSkillLevel(1);
                                    gotoxy(44, 28);
                                    cout << "掘衙 諫猿!";
                                    Sleep(1000);
                                    gotoxy(44, 28);
                                    cout << "                     ";
                                    gotoxy(44, 26);
                                    cout << "                                                 ";
                                    gotoxy(44, 26);
                                    cout << "模雖旎 : " + to_string(player->GetMoney()) + " 埤萄";
                                }
                            }
                            else if (manager.input.GetKeyDown(eKeyCode::Num3))
                            {
                                if (player->GetMoney() < 10000)
                                {
                                    gotoxy(44, 28);
                                    cout << "掘衙 褒ぬ : 濤擋檜 賅濠奧棲棻!";
                                    Sleep(1000);
                                    gotoxy(44, 28);
                                    cout << "                               ";
                                }
                                else
                                {
                                    player->SetMoney(player->GetMoney() - 10000);
                                    player->getActiveSkillList()[2]->setSkillLevel(1);
                                    gotoxy(44, 28);
                                    cout << "掘衙 諫猿!";
                                    Sleep(1000);
                                    gotoxy(44, 28);
                                    cout << "                     ";
                                    gotoxy(44, 26);
                                    cout << "                                                 ";
                                    gotoxy(44, 26);
                                    cout << "模雖旎 : " + to_string(player->GetMoney()) + " 埤萄";
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
}
#pragma endregion