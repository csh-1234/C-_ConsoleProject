#include <iostream>
#include <vector>
#include <string>
#include <windows.h> // gotoxy 함수 (Windows 전용)

// 더블 버퍼링을 위한 백 버퍼 시뮬레이션
std::vector<std::string> backBuffer(100, std::string(100, ' ')); // 50줄, 한 줄에 100개의 공백

// 콘솔 위치 지정 함수 (Windows 전용)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// 백 버퍼에 텍스트를 그리는 함수
void drawToBuffer(int x, int y, const std::string& text) {
    if (y >= 0 && y < backBuffer.size() && x >= 0 && x + text.size() < backBuffer[y].size()) {
        backBuffer[y].replace(x, text.size(), text); // (x, y) 위치에 텍스트 쓰기
    }
}

// 전투 UI를 그리는 함수
void PrintBattleUI() {
    // 전투 화면 테두리
    drawToBuffer(30, 10, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    for (size_t i = 11; i < 29; i++) {
        drawToBuffer(30, i, "┃                                     ┃");
    }
    drawToBuffer(30, 29, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

    // 행동 선택 창
    drawToBuffer(5, 30, "┏━━━━━━━━━━━━━━━━━━━━━━┓");
    for (size_t i = 31; i < 45; i++) {
        drawToBuffer(5, i, "┃                      ┃");
    }
    drawToBuffer(13, 32, "행동 선택");
    drawToBuffer(6, 34, " ━━━━━━━━━━━━━━━━━━━━ ");
    drawToBuffer(10, 36, "▶공격");
    drawToBuffer(10, 38, "스킬");
    drawToBuffer(10, 40, "인벤토리");
    drawToBuffer(10, 42, "도망치기");
    drawToBuffer(5, 45, "┗━━━━━━━━━━━━━━━━━━━━━━┛");
}

// 메시지 창을 그리는 함수
void PrintMessage() {
    // 메시지 창 테두리
    drawToBuffer(4, 35, "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
    for (size_t i = 36; i < 47; i++) {
        drawToBuffer(4, i, "┃                                                                                         ┃");
    }
    drawToBuffer(4, 47, "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");

    // 메시지 내용
    drawToBuffer(16, 41, "아이템 을(를) 획득하셨습니다.");
}

// 버퍼를 교체하고 백 버퍼의 내용을 화면에 출력하는 함수
void swapBuffers() {
    system("cls"); // 콘솔 화면 지우기 (Windows 전용)

    for (const std::string& line : backBuffer) {
        std::cout << line << std::endl; // 백 버퍼의 내용을 출력
    }
}

int main() {
    // 메인 루프에서 더블 버퍼링 시뮬레이션
    while (true) {
        // 백 버퍼 초기화
        //for (auto& line : backBuffer) {
        //    line.assign(100, ' '); // 100칸 공백으로 채우기
        //}

        // 백 버퍼에 UI 그리기
        PrintBattleUI();

        // 백 버퍼에 메시지 창 그리기
        //PrintMessage();

        // 버퍼 교체 (백 버퍼 출력)
        swapBuffers();

        // 프레임 속도를 조절하거나 입력 처리를 추가할 수 있음
    }

    return 0;
}