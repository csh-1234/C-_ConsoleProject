#include<iostream>
#include<conio.h>
#include<windows.h>

using namespace std;

enum direction { LEFT, RIGHT, UP, DOWN , NONE };
direction dir;
void InputTest()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			cout << "click left" << endl;
			break;
		case 'd':
			dir = RIGHT;
			cout << "click right" << endl;
			break;
		case 'w':
			dir = UP;
			cout << "click up" << endl;
			break;
		case 's':
			dir = DOWN;
			cout << "click down" << endl;
			break;
			/*case 'x':
				gameOver = true;
				break;*/
		}
	}
}

void InputTest2()
{
	if (GetAsyncKeyState(VK_UP))
	{
		cout << "click up" << endl;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		cout << "click down" << endl;
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		cout << "click left" << endl;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		cout << "click right" << endl;
	}

}

void gotoxy(int x, int y)
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

int arr[50][50] = {};

void printmap(int arr[][50])
{
	for (size_t i = 0; i < 50; i++)
	{
		for (size_t j = 0; j < 50; j++)
		{
			
			cout << "бр";
		}
		cout << endl;
	}
}



int main()
{

	


	//int x = 0;
	//int y = 0;


	//
	printmap(arr);

	//while (true) {
	//	gotoxy(x, y);
	//	//putch('@');
	//	if (GetAsyncKeyState(VK_UP) & 0x8000) y--;
	//	if (GetAsyncKeyState(VK_DOWN) & 0x8000) y++;
	//	if (GetAsyncKeyState(VK_LEFT) & 0x8000) x--;
	//	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) x++;
	//	Sleep(50);
	//}
	//return 0;
	//system("cls");
	//while (1)
	//{
	//	if (_kbhit())
	//	{
	//		InputTest2();
	//	}
	//		cout << x << " " << y << endl;
	//}
}



