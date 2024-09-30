#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

class ConsoleBuffer {
private:
    std::vector<std::vector<wchar_t>> buffer;  // ���̵� ���ڿ� ���
    int width, height;
    HANDLE hConsole;

public:
    ConsoleBuffer(int w, int h) : width(w), height(h), buffer(h, std::vector<wchar_t>(w, L' ')) 
    {
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

    void Render() {
        COORD topLeft = { 0, 0 };
        DWORD written;

        for (const auto& row : buffer) {
            WriteConsoleOutputCharacterW(hConsole, row.data(), width, topLeft, &written);  // �����ڵ� ���� ���
            topLeft.Y++;
        }
    }
};

void DrawMessageBox(ConsoleBuffer& buffer, const std::wstring& message) {
    buffer.DrawAt(4, 35, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
    for (int i = 36; i < 47; ++i) {
        buffer.DrawAt(4, i, L"��                                                                                         ��");
    }
    buffer.DrawAt(4, 47, L"��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

    buffer.DrawAt(16, 41, message);
}

void DrawSkillList(ConsoleBuffer& buffer) 
{
    buffer.DrawAt(30, 30, L"������������������������������������������������������������������������������������������������������������������������������������������");
    buffer.DrawAt(30, 31, L"��                                                                   ��");
    buffer.DrawAt(26, 32, L"��        ���̾                                                    ��");
    buffer.DrawAt(30, 33, L"��                                                                   ��");
    buffer.DrawAt(30, 34, L"��        ��                                                         ��");
    buffer.DrawAt(30, 35, L"��                                                                   ��");
    buffer.DrawAt(30, 36, L"��        ���׿�                                                      ��");
    buffer.DrawAt(30, 37, L"��                                                                   ��");
    buffer.DrawAt(30, 38, L"��        �ڷΰ���                                                    ��");
    buffer.DrawAt(30, 39, L"��                                                                   ��");
    buffer.DrawAt(30, 40, L"��                                                                   ��");
    buffer.DrawAt(30, 41, L"��                                                                   ��");
    buffer.DrawAt(30, 42, L"��                                                                   ��");
    buffer.DrawAt(30, 43, L"��                                                                   ��");
    buffer.DrawAt(30, 44, L"��                                                                   ��");
    buffer.DrawAt(30, 45, L"������������������������������������������������������������������������������������������������������������������������������������������");
}

void DrawBattleChoiceUI(ConsoleBuffer& buffer) {
    buffer.DrawAt(5, 30, L"������������������������������������������������ ������������������������������������������������������������������������������������������������������������������������������������������ ");
    buffer.DrawAt(5, 31, L"��                      �� ��                                                                   �� ");
    buffer.DrawAt(5, 32, L"��       �ൿ ����      �� ��                                                                   ��");
    buffer.DrawAt(5, 33, L"��                      �� ��                                                                   �� ");
    buffer.DrawAt(5, 34, L"�� ���������������������������������������� �� ��                                                                   �� ");
    buffer.DrawAt(5, 35, L"��                      �� ��                                                                   �� ");
    buffer.DrawAt(5, 36, L"�� �� ����              �� ��                                                                   ��");
    buffer.DrawAt(5, 37, L"��                      �� ��                                                                   �� ");
    buffer.DrawAt(5, 38, L"��    ��ų              �� ��                                                                   �� ");
    buffer.DrawAt(5, 39, L"��                      �� ��                                                                   �� ");
    buffer.DrawAt(5, 40, L"��    �κ��丮          �� ��                                                                   ��");
    buffer.DrawAt(5, 41, L"��                      �� ��                                                                   �� ");
    buffer.DrawAt(5, 42, L"��    ����ġ��          �� ��                                                                   ��");
    buffer.DrawAt(5, 43, L"��                      �� ��                                                                   �� ");
    buffer.DrawAt(5, 44, L"��                      �� ��                                                                   �� ");
    buffer.DrawAt(5, 45, L"������������������������������������������������ ������������������������������������������������������������������������������������������������������������������������������������������ ");
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

    //buffer.DrawAt(13, 32, L"�ൿ ����");
    //buffer.DrawAt(6, 34, L" ���������������������������������������� ");
    //buffer.DrawAt(10, 36, L"����");
    //buffer.DrawAt(10, 38, L"��ų");
    //buffer.DrawAt(10, 40, L"�κ��丮");
    //buffer.DrawAt(10, 42, L"����ġ��");
    
    buffer.DrawAt(5, 30, L"������������������������������������������������");
    for (int i = 31; i < 45; ++i) {
        buffer.DrawAt(5, i, L"��                      ��");
    }
    buffer.DrawAt(5, 45, L"������������������������������������������������");
}

int main() {
    ConsoleBuffer buffer(100, 50);  // �ܼ� ũ�⸦ �����߽��ϴ�

    bool showBattleUI = true;
    bool showMessage = false;
    std::wstring currentMessage = L"";

    bool bKeyDown = false; // 'B' Ű �Է� ����
    bool mKeyDown = false; // 'M' Ű �Է� ����

    while (true) {
        buffer.Clear();
        DrawSlimeImage(buffer);
        DrawBattleChoiceUI(buffer);
        //DrawSkillList(buffer);
        buffer.Render();
        //if (showBattleUI) {
        //    DrawBattleUI(buffer);
        //}

        //if (showMessage) {
        //    DrawMessageBox(buffer, currentMessage);
        //}

        //buffer.Render();

        //// ����� �Է� ó��
        //if (GetAsyncKeyState('B') & 0x8000) {
        //    if (!bKeyDown) {
        //        showBattleUI = !showBattleUI;
        //        bKeyDown = true;  // Ű�� �������� ���
        //    }
        //}
        //else {
        //    bKeyDown = false; // Ű�� �������� �� ���� �ʱ�ȭ
        //}

        //if (GetAsyncKeyState('M') & 0x8000) {
        //    if (!mKeyDown) {
        //        showMessage = !showMessage;
        //        //if (showMessage) {
        //        //    currentMessage = L"��������(��) ȹ���ϼ̽��ϴ�.";  // �����ڵ� ���ڿ��� ����
        //        //}
        //        mKeyDown = true;  // Ű�� �������� ���
        //    }
        //}
        //else {
        //    mKeyDown = false;  // Ű�� �������� �� ���� �ʱ�ȭ
        //}

        //Sleep(100);  // CPU ��뷮 ���Ҹ� ���� ª�� ��� �ð�
    }

    return 0;
}