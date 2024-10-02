#pragma once
#include<vector>
#include<windows.h>
#include <string>
class ConsoleDraw {
private:
    std::vector<std::vector<wchar_t>> buffer;  // ���̵� ���ڿ� ���
    int width, height;
    HANDLE hConsole;

public:
    ConsoleDraw(int w, int h) : width(w), height(h), buffer(h, std::vector<wchar_t>(w, L' ')) {
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

    void ChangeAt(int x, int y, const std::wstring& str) {  // ���̵� ���ڿ� ���
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
    void RenderPartial(int startX, int startY, int endX, int endY) {
        COORD topLeft = { (SHORT)startX, (SHORT)startY };
        DWORD written;

        for (int y = startY; y <= endY && y < height; ++y) {
            if (y >= 0) {
                WriteConsoleOutputCharacterW(hConsole, &buffer[y][startX], endX - startX + 1, topLeft, &written);
            }
            topLeft.Y++;
        }
    }

    void DrawPopup(int x, int y, int w, int h, const std::wstring& title, const std::vector<std::wstring>& content) {
        // �˾� ������ ���� ������ ����
        std::vector<std::vector<wchar_t>> background(h, std::vector<wchar_t>(w));
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (y + i < height && x + j < width) {
                    background[i][j] = buffer[y + i][x + j];
                }
            }
        }

        // �˾� �׵θ� �׸���
        DrawAt(x, y, L"��" + std::wstring(w - 2, L'��') + L"��");
        for (int i = 1; i < h - 1; ++i) {
            DrawAt(x, y + i, L"��" + std::wstring(w - 2, L' ') + L"��");
        }
        DrawAt(x, y + h - 1, L"��" + std::wstring(w - 2, L'��') + L"��");

        // ���� �׸���
        if (!title.empty()) {
            DrawAt(x + (w - title.length()) / 2, y, title);
        }

        // ���� �׸���
        for (size_t i = 0; i < content.size() && i < h - 2; ++i) {
            DrawAt(x + 1, y + i + 1, content[i]);
        }

        // ���� �˾��� ����
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                if (y + i < height && x + j < width) {
                    if (buffer[y + i][x + j] == L' ' && background[i][j] != L' ') {
                        buffer[y + i][x + j] = background[i][j];
                    }
                }
            }
        }

        // �˾� ������ ������
        RenderPartial(x, y, x + w - 1, y + h - 1);
    }
};

