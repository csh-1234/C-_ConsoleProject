#pragma once
#include<vector>
#include<windows.h>
#include <string>
class ConsoleDraw {
private:
    std::vector<std::vector<wchar_t>> buffer; 
    int width, height;
    HANDLE hConsole;

public:
    ConsoleDraw(int w, int h);

    void Clear();

    void DrawAt(int x, int y, const std::wstring& str);

    void ChangeAt(int x, int y, const std::wstring& str);

    void Render();

    void RenderPartial(int startX, int startY, int endX, int endY);
  
    void DrawPopup(int x, int y, int w, int h, const std::wstring& title, const std::vector<std::wstring>& content);
    
};