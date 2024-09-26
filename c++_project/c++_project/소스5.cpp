#include <iostream>
#include <vector>
#include <conio.h>  // _getch() ����� ���� �ʿ� (Windows ȯ��)

const int MAP_WIDTH = 100;  // ���� �ʺ�
const int MAP_HEIGHT = 40;  // ���� ����
const int VIEWPORT_WIDTH = 20;  // ȭ�鿡 ǥ�õǴ� �ʺ�
const int VIEWPORT_HEIGHT = 10; // ȭ�鿡 ǥ�õǴ� ����

char map[MAP_HEIGHT][MAP_WIDTH];  // ��ü ���� 2���� �迭�� ����

struct Position {
    int x, y;
};

// �÷��̾��� ���� �� �� ��ǥ
Position playerPos = { MAP_WIDTH / 2, MAP_HEIGHT / 2 };

// ����Ʈ�� ���� ��ǥ(��, ȭ�鿡 ǥ�õ� ���� ���� ��� ��ǥ)
Position viewportPos = { playerPos.x - VIEWPORT_WIDTH / 2, playerPos.y - VIEWPORT_HEIGHT / 2 };

// ���� �ʱ�ȭ�ϴ� �Լ� (�ʿ� '.'�� ä���ְ�, �Ϻ� ������ �� '#'���� ǥ��)
void initializeMap() {
    for (int i = 0; i < MAP_HEIGHT; ++i) {
        for (int j = 0; j < MAP_WIDTH; ++j) {
            if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH - 1) {
                map[i][j] = '#';  // ���� �׵θ��� ��
            }
            else {
                map[i][j] = '.';  // �������� �� �������� ǥ��
            }
        }
    }
}

// ����Ʈ�� �������� ���� ����ϴ� �Լ�
void renderMap() {
    system("cls");  // �ܼ� ȭ�� ����� (Windows���� ����)

    for (int i = 0; i < VIEWPORT_HEIGHT; ++i) {
        for (int j = 0; j < VIEWPORT_WIDTH; ++j) {
            int mapX = viewportPos.x + j;
            int mapY = viewportPos.y + i;

            // ��踦 ���� �ʾҴ��� Ȯ�� �� ���� ���
            if (mapX >= 0 && mapX < MAP_WIDTH && mapY >= 0 && mapY < MAP_HEIGHT) {
                if (mapY == playerPos.y && mapX == playerPos.x) {
                    std::cout << '@';  // �÷��̾� ��ġ�� '@'�� ǥ��
                }
                else {
                    std::cout << map[mapY][mapX];  // ���� �ش� �κ� ���
                }
            }
            else {
                std::cout << ' ';  // ��踦 �Ѿ�� ���� �� �������� ���
            }
        }
        std::cout << std::endl;
    }
}

// �÷��̾��� �������� ó���ϴ� �Լ�
void movePlayer(char direction) {
    // �̵� �� �ӽ÷� ��ġ�� ����
    Position newPos = playerPos;

    switch (direction) {
    case 'w': // ���� �̵�
        if (newPos.y > 0) newPos.y--;
        break;
    case 's': // �Ʒ��� �̵�
        if (newPos.y < MAP_HEIGHT - 1) newPos.y++;
        break;
    case 'a': // �������� �̵�
        if (newPos.x > 0) newPos.x--;
        break;
    case 'd': // ���������� �̵�
        if (newPos.x < MAP_WIDTH - 1) newPos.x++;
        break;
    }

    // �÷��̾ ���� �ε����� �ʾҴ��� Ȯ�� (���� '#')
    if (map[newPos.y][newPos.x] != '#') {
        playerPos = newPos;  // ���� �ƴϸ� ��ġ�� ������Ʈ
    }

    // ����Ʈ�� ��ǥ�� ������Ʈ
    viewportPos.x = playerPos.x - VIEWPORT_WIDTH / 2;
    viewportPos.y = playerPos.y - VIEWPORT_HEIGHT / 2;

    // ����Ʈ�� ���� ����� �ʰ� ��� ó��
    if (viewportPos.x < 0) viewportPos.x = 0;
    if (viewportPos.y < 0) viewportPos.y = 0;
    if (viewportPos.x > MAP_WIDTH - VIEWPORT_WIDTH) viewportPos.x = MAP_WIDTH - VIEWPORT_WIDTH;
    if (viewportPos.y > MAP_HEIGHT - VIEWPORT_HEIGHT) viewportPos.y = MAP_HEIGHT - VIEWPORT_HEIGHT;
}

int main() {
    initializeMap();  // �� �ʱ�ȭ

    while (true) {
        renderMap();  // ���� ������ ���� ������

        // �÷��̾� �Է� ó�� (w, a, s, d�� �̵�)
        char input = _getch();  // ������� �Է��� ��ٸ�
        if (input == 'q') break;  // 'q'�� ������ ���� ����
        movePlayer(input);  // �Է¿� ���� �÷��̾� �̵� ó��
    }

    return 0;
}