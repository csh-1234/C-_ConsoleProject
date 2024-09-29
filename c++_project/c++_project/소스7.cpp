#include <iostream>
#include <vector>
#include <string>
#include <windows.h> // gotoxy �Լ� (Windows ����)

// ���� ���۸��� ���� �� ���� �ùķ��̼�
std::vector<std::string> backBuffer(100, std::string(100, ' ')); // 50��, �� �ٿ� 100���� ����

// �ܼ� ��ġ ���� �Լ� (Windows ����)
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// �� ���ۿ� �ؽ�Ʈ�� �׸��� �Լ�
void drawToBuffer(int x, int y, const std::string& text) {
    if (y >= 0 && y < backBuffer.size() && x >= 0 && x + text.size() < backBuffer[y].size()) {
        backBuffer[y].replace(x, text.size(), text); // (x, y) ��ġ�� �ؽ�Ʈ ����
    }
}

// ���� UI�� �׸��� �Լ�
void PrintBattleUI() {
    // ���� ȭ�� �׵θ�
    drawToBuffer(30, 10, "������������������������������������������������������������������������������");
    for (size_t i = 11; i < 29; i++) {
        drawToBuffer(30, i, "��                                     ��");
    }
    drawToBuffer(30, 29, "������������������������������������������������������������������������������");

    // �ൿ ���� â
    drawToBuffer(5, 30, "������������������������������������������������");
    for (size_t i = 31; i < 45; i++) {
        drawToBuffer(5, i, "��                      ��");
    }
    drawToBuffer(13, 32, "�ൿ ����");
    drawToBuffer(6, 34, " ���������������������������������������� ");
    drawToBuffer(10, 36, "������");
    drawToBuffer(10, 38, "��ų");
    drawToBuffer(10, 40, "�κ��丮");
    drawToBuffer(10, 42, "����ġ��");
    drawToBuffer(5, 45, "������������������������������������������������");
}

// �޽��� â�� �׸��� �Լ�
void PrintMessage() {
    // �޽��� â �׵θ�
    drawToBuffer(4, 35, "��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");
    for (size_t i = 36; i < 47; i++) {
        drawToBuffer(4, i, "��                                                                                         ��");
    }
    drawToBuffer(4, 47, "��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������");

    // �޽��� ����
    drawToBuffer(16, 41, "������ ��(��) ȹ���ϼ̽��ϴ�.");
}

// ���۸� ��ü�ϰ� �� ������ ������ ȭ�鿡 ����ϴ� �Լ�
void swapBuffers() {
    system("cls"); // �ܼ� ȭ�� ����� (Windows ����)

    for (const std::string& line : backBuffer) {
        std::cout << line << std::endl; // �� ������ ������ ���
    }
}

int main() {
    // ���� �������� ���� ���۸� �ùķ��̼�
    while (true) {
        // �� ���� �ʱ�ȭ
        //for (auto& line : backBuffer) {
        //    line.assign(100, ' '); // 100ĭ �������� ä���
        //}

        // �� ���ۿ� UI �׸���
        PrintBattleUI();

        // �� ���ۿ� �޽��� â �׸���
        //PrintMessage();

        // ���� ��ü (�� ���� ���)
        swapBuffers();

        // ������ �ӵ��� �����ϰų� �Է� ó���� �߰��� �� ����
    }

    return 0;
}