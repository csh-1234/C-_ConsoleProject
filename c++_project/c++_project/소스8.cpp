#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

class ConsoleBuffer {
private:
    std::vector<std::vector<wchar_t>> buffer;  // 와이드 문자열 사용
    int width, height;
    HANDLE hConsole;

public:
    ConsoleBuffer(int w, int h) : width(w), height(h), buffer(h, std::vector<wchar_t>(w, L' ')) {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleScreenBufferSize(hConsole, { (SHORT)w, (SHORT)h });
    }

    void Clear() {
        for (auto& row : buffer) {
            std::fill(row.begin(), row.end(), L' ');  // 와이드 공백 사용
        }
    }

    void DrawAt(int x, int y, const std::wstring& str) {  // 와이드 문자열 사용
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
            WriteConsoleOutputCharacterW(hConsole, row.data(), width, topLeft, &written);  // 유니코드 버전 사용
            topLeft.Y++;
        }
    }
};

void DrawMessageBox(ConsoleBuffer& buffer, const std::wstring& message) {
    buffer.DrawAt(4, 35, L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    for (int i = 36; i < 47; ++i) {
        buffer.DrawAt(4, i, L"┃                                                                                         ┃");
    }
    buffer.DrawAt(4, 47, L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

    buffer.DrawAt(16, 41, message);
}

void DrawBattleUI(ConsoleBuffer& buffer) {
    buffer.DrawAt(30, 10, L"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    for (int i = 11; i < 29; ++i) {
        buffer.DrawAt(30, i, L"┃                                     ┃");
    }
    buffer.DrawAt(30, 29, L"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

    //buffer.DrawAt(13, 32, L"행동 선택");
    //buffer.DrawAt(6, 34, L" ━━━━━━━━━━━━━━━━━━━━ ");
    //buffer.DrawAt(10, 36, L"공격");
    //buffer.DrawAt(10, 38, L"스킬");
    //buffer.DrawAt(10, 40, L"인벤토리");
    //buffer.DrawAt(10, 42, L"도망치기");
    
    buffer.DrawAt(5, 30, L"┏━━━━━━━━━━━━━━━━━━━━━━┓");
    for (int i = 31; i < 45; ++i) {
        buffer.DrawAt(5, i, L"┃                      ┃");
    }
    buffer.DrawAt(5, 45, L"┗━━━━━━━━━━━━━━━━━━━━━━┛");
}

int main() {
    ConsoleBuffer buffer(100, 50);  // 콘솔 크기를 설정했습니다

    bool showBattleUI = true;
    bool showMessage = false;
    std::wstring currentMessage = L"";

    bool bKeyDown = false; // 'B' 키 입력 상태
    bool mKeyDown = false; // 'M' 키 입력 상태

    while (true) {
        buffer.Clear();

        if (showBattleUI) {
            DrawBattleUI(buffer);
        }

        if (showMessage) {
            DrawMessageBox(buffer, currentMessage);
        }

        buffer.Render();

        // 사용자 입력 처리
        if (GetAsyncKeyState('B') & 0x8000) {
            if (!bKeyDown) {
                showBattleUI = !showBattleUI;
                bKeyDown = true;  // 키가 눌렸음을 기록
            }
        }
        else {
            bKeyDown = false; // 키가 떼어졌을 때 상태 초기화
        }

        if (GetAsyncKeyState('M') & 0x8000) {
            if (!mKeyDown) {
                showMessage = !showMessage;
                //if (showMessage) {
                //    currentMessage = L"아이템을(를) 획득하셨습니다.";  // 유니코드 문자열로 변경
                //}
                mKeyDown = true;  // 키가 눌렸음을 기록
            }
        }
        else {
            mKeyDown = false;  // 키가 떼어졌을 때 상태 초기화
        }

        Sleep(100);  // CPU 사용량 감소를 위한 짧은 대기 시간
    }

    return 0;
}