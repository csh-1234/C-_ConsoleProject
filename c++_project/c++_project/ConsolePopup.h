#pragma once
#include<string>
#include<Windows.h>
class Player;
class ConsolePopup
{
public:
    ConsolePopup();

    void DrawUserInfo(int startX, int startY, int endX, int endY, const std::wstring& title = L"", Player* player = nullptr);

    void DrawUserInventory(int startX, int startY, int endX, int endY, const std::wstring& title = L"", Player* player = nullptr);
  
    void DrawUserSkill(int startX, int startY, int endX, int endY, const std::wstring& title = L"", Player* player = nullptr);
   
    void DrawPotionShop(int startX, int startY, int endX, int endY, const std::wstring& title = L"", Player* player = nullptr);
    
    void DrawBuyComplete(int startX, int startY, int endX, int endY);
   
    void DrawSkillShop(int startX, int startY, int endX, int endY, const std::wstring& title = L"", Player* player = nullptr);

    void DrawAt(int x, int y, const std::wstring& str);

	private:
    HANDLE hConsole;

};

