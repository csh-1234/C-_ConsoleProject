#include <iostream>
#include <windows.h>
#include <conio.h>

#define UP 0;
#define DOWN 1;
#define LEFT 2;
#define RIGHT 3;
#define SUBMIT 4;

using namespace std;
void init();
void titleDraw();
void gotoxy(int, int);
int menuDraw();
int keyControl();

int main()
{
	init();
	titleDraw();
	menuDraw();
	int keyCode = keyControl();
	cout << keyCode;

	return 0;
}

void init()
{
	system("mode con cols=56 line=20 | title 게임제목");
}

void titleDraw()
{
	cout << '\n' << '\n' << '\n' << '\n';
	cout << "================================" << endl;
	cout << "================================" << endl;
	cout << "================================" << endl;
	cout << "================================" << endl;
	cout << "================================" << endl;
}

void gotoxy(int x, int y)
{
	HANDLE consolHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(consolHandle, pos);
}

int menuDraw()
{
	int x = 24;
	int y = 12;
	gotoxy(24 - 2, 12);
	cout << "▶게임시작";
	gotoxy(24, 13);
	printf("게임정보");
	gotoxy(24, 14);
	printf("종료");
	while (true)
	{
		int n = keyControl();
		switch (keyControl())
		{
		case 0:
			if (y > 12)
			{
				gotoxy(x - 2, y);
				cout << "  ";
				gotoxy(x - 2, --y);
				cout << "▶";
			}
			break;
		case 1:
			if (y < 14)
			{
				gotoxy(x - 2, y);
				cout << "  ";
				gotoxy(x - 2, ++y);
				cout << "▶";
			}
			break;
		case 4:
		{
			return y - 12;
		}
		default:
			break;
		}
		
	}

}

int keyControl()
{
	char temp = _getch();
	if (temp == 'w' || temp == 'W')
	{
		return UP;
	}
	else if (temp == 'a' || temp == 'A')
	{
		return LEFT;
	}
	else if (temp == 's' || temp == 'S')
	{
		return DOWN;
	}
	else if (temp == 'd' || temp == 'D')
	{
		return RIGHT;
	}
	else if(temp == ' ')
	{
		return SUBMIT;
	}
}