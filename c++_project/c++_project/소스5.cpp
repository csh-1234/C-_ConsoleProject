#include <iostream>
#include <vector>
#include <conio.h>  // _getch() 사용을 위해 필요 (Windows 환경)

const int MAP_WIDTH = 100;  // 맵의 너비
const int MAP_HEIGHT = 40;  // 맵의 높이
const int VIEWPORT_WIDTH = 20;  // 화면에 표시되는 너비
const int VIEWPORT_HEIGHT = 10; // 화면에 표시되는 높이

char map[MAP_HEIGHT][MAP_WIDTH];  // 전체 맵을 2차원 배열로 선언

struct Position {
    int x, y;
};

// 플레이어의 실제 맵 상 좌표
Position playerPos = { MAP_WIDTH / 2, MAP_HEIGHT / 2 };

// 뷰포트의 시작 좌표(즉, 화면에 표시될 맵의 좌측 상단 좌표)
Position viewportPos = { playerPos.x - VIEWPORT_WIDTH / 2, playerPos.y - VIEWPORT_HEIGHT / 2 };

// 맵을 초기화하는 함수 (맵에 '.'을 채워넣고, 일부 지역은 벽 '#'으로 표시)
void initializeMap() {
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1) {
                map[i][j] = '#';  // 맵의 테두리는 벽
            }
            else {
                map[i][j] = '.';  // 나머지는 빈 공간으로 표시
            }
        }
    }
}

// 뷰포트를 기준으로 맵을 출력하는 함수
void renderMap() {
    system("cls");  // 콘솔 화면 지우기 (Windows에서 동작)

    for (int i = 0; i < VIEWPORT_HEIGHT; ++i) {
        for (int j = 0; j < VIEWPORT_WIDTH; ++j) {
            int mapX = viewportPos.x + j;
            int mapY = viewportPos.y + i;

            // 경계를 넘지 않았는지 확인 후 맵을 출력
            if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT) {
                if (mapY == playerPos.y && mapX == playerPos.x) {
                    std::cout << '@';  // 플레이어 위치는 '@'로 표시
                }
                else {
                    std::cout << map[mapY][mapX];  // 맵의 해당 부분 출력
                }
            }
            else {
                std::cout << ' ';  // 경계를 넘어가는 경우는 빈 공간으로 출력
            }
        }
        std::cout << std::endl;
    }
}

// 플레이어의 움직임을 처리하는 함수
void movePlayer(char direction) {
    // 이동 전 임시로 위치를 저장
    Position newPos = playerPos;

    switch (direction) {
    case 'w': // 위로 이동
        if (newPos.y > 0) newPos.y--;
        break;
    case 's': // 아래로 이동
        if (newPos.y < MAP_HEIGHT - 1) newPos.y++;
        break;
    case 'a': // 왼쪽으로 이동
        if (newPos.x > 0) newPos.x--;
        break;
    case 'd': // 오른쪽으로 이동
        if (newPos.x < MAP_WIDTH - 1) newPos.x++;
        break;
    }

    // 플레이어가 벽에 부딪히지 않았는지 확인 (벽은 '#')
    if (map[newPos.y][newPos.x] != '#') {
        playerPos = newPos;  // 벽이 아니면 위치를 업데이트
    }

    // 뷰포트의 좌표를 업데이트
    viewportPos.x = playerPos.x - VIEWPORT_WIDTH / 2;
    viewportPos.y = playerPos.y - VIEWPORT_HEIGHT / 2;

    // 뷰포트가 맵을 벗어나지 않게 경계 처리
    if (viewportPos.x < 0) viewportPos.x = 0;
    if (viewportPos.y < 0) viewportPos.y = 0;
    if (viewportPos.x > MAP_WIDTH - VIEWPORT_WIDTH) viewportPos.x = MAP_WIDTH - VIEWPORT_WIDTH;
    if (viewportPos.y > MAP_HEIGHT - VIEWPORT_HEIGHT) viewportPos.y = MAP_HEIGHT - VIEWPORT_HEIGHT;
}

int main() {
    initializeMap();  // 맵 초기화

    while (true) {
        renderMap();  // 현재 상태의 맵을 렌더링

        // 플레이어 입력 처리 (w, a, s, d로 이동)
        char input = _getch();  // 사용자의 입력을 기다림
        if (input == 'q') break;  // 'q'를 누르면 게임 종료
        movePlayer(input);  // 입력에 따라 플레이어 이동 처리
    }

    return 0;
}