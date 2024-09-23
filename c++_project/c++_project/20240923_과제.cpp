#include <iostream>
#include <Windows.h>
#include <cmath>
using namespace std;

/*

슬라이드 퍼즐 비슷
장애물이 듬성듬성 있음
장애물은 못지나감
키입력으로 이동
던전 입구를 만든다
들어가면 다음맵으로 나와야 한다
*/

//별의 위치를 가지고 있는 class
class StarPos
{
public:
	//매개변수가 있는 생성자
	StarPos(int inputX, int inputY)
	{
		this->x = inputX;
		this->y = inputY;
	}
	int getY()
	{
		return y;
	}
	void setY(int inputY)
	{
		this->y = inputY;
	}
	int getX()
	{
		return this->x;
	}
	void setX(int inputX)
	{
		this->x = inputX;
	}
private:
	int x;
	int y;
};

class Map
{
public:
	void SetMap(int inputMap[][10])
	{
		for (size_t i = 0; i < 9; i++)
		{
			for (size_t j = 0; j < 9; j++)
			{
				map[i][j] = inputMap[i][j];
			}
		}
		
	}
private:

	int map[9][9] = {};
};

//게임규칙 출력
void Lobby()
{
	std::cout << "=====================================================" << endl;
	std::cout << "플레이어 : ★" << endl;
	std::cout << "다음 스테이지 : ◎" << endl;
	std::cout << "게임 규칙 : 방향키를 눌러 플레이어를 이동시킬 수 있습니다!" << endl;
	std::cout << "플레이어는 맵 밖으로 나갈 수 없습니다!" << endl;
	std::cout << "플레이어는 장애물을 지나갈 수 없습니다!" << endl;
	std::cout << "스페이스를 입력하시면 맵이 재생성됩니다.!" << endl;
	std::cout << "=====================================================" << endl;
}

//보드를 출력하는 메서드
void printBoard(int arr[][10])
{
	std::cout << "◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇" << endl;
	for (size_t i = 0; i < 10; i++)
	{

		std::cout << "◇";
		for (size_t j = 0; j < 10; j++)
		{
			if (arr[i][j] == -1)
			{
				std::cout << "★" << "	";
			}
			else if (arr[i][j] == -2)
			{
				std::cout << "■" << "	";
			}
			else if (arr[i][j] == -10)
			{
				std::cout << "◎" << "	";
			}
			else
			{
				std::cout << "	";
			}
		}

		std::cout << "◇";
		std::cout << endl;
		std::cout << "◇";
		std::cout << "                                                                              ◇" ;
		std::cout << endl; 

	}
	std::cout << "◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇" << endl;
}

// 현재 보드에서 별 좌표를 갱신하는 메서드
void FindStarPosition(int arr[][10], int& inputY, int& inputX)
{
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (arr[i][j] == -1)
			{
				inputY = i;
				inputX = j;
				break;
			}
		}
	}
}

// 두 좌표를 입력받아 별 위치를 바꾸는 메서드
void SwapPosition(int arr[][10], int starY, int starX, int changeY, int changeX)
{
	int temp;
	temp = arr[starY][starX];
	arr[starY][starX] = arr[changeY][changeX];
	arr[changeY][changeX] = temp;
}

void GenerateMap(int map[][10])
{
	srand(time(NULL));
	StarPos sPos(9, 9);
	//맵 생성
	int idx = 1;
	
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			map[i][j] = 0;
			int randValue = rand() % 3;
			if (randValue % 5 == 1)
				map[i][j] = -2;
		}
	}
	map[9][9] = -1;
	map[rand() % 9][rand() % 8] = -10;
	
	printBoard(map);
}

// 다음 맵으로 넘어가기전 초기화해주는 메서드
void InitializeMap(Map *map, StarPos &s, int arr[][10])
{
	std::cout << "다음 맵으로 이동!" << endl;
	GenerateMap(arr);
	map->SetMap(arr);
	s.setX(9);
	s.setY(9);
}

void InGame()
{
	srand(time(NULL));
	StarPos sPos(9, 9);

	Map* map = new Map;
	int arr[10][10] = {};

	GenerateMap(arr);
	map->SetMap(arr);
	
	string InputDir = ""; //상하좌우 입력받는 변수
	while (1)
	{
		while (true)
		{
			Sleep(100);
			if (GetAsyncKeyState(VK_UP) & 0x8000)
			{
				if (arr[sPos.getY() - 1][sPos.getX()] == -10)
				{
					InitializeMap(map, sPos, arr);
				}
				else if (sPos.getY() - 1 >= 0 && arr[sPos.getY() - 1][sPos.getX()] != -2)
				{
					std::cout << endl;
					std::cout << "위로 이동합니다." << endl;
					SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY() - 1, sPos.getX());
					sPos.setY(sPos.getY() - 1);
				}
				else
				{
					std::cout << endl;
					std::cout << "위로 이동해야 하지만 갈 수 없는 곳입니다." << endl;
				}
				system("cls");
				Lobby();
				printBoard(arr);
			}
			else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
			{
				if (arr[sPos.getY() + 1][sPos.getX()] == -10)
				{
					InitializeMap(map, sPos, arr);
				}
				else if (sPos.getY() + 1 < 10 && arr[sPos.getY() + 1][sPos.getX()] != -2)
				{
					std::cout << endl;
					std::cout << "아래로 이동합니다." << endl;
					SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY() + 1, sPos.getX());
					sPos.setY(sPos.getY() + 1);
					
				}
				else
				{
					std::cout << endl;
					std::cout << "아래로 이동해야 하지만 갈 수 없는 곳입니다." << endl;
				}
				system("cls");
				Lobby();
				printBoard(arr);
			}
			else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
			{
				if (arr[sPos.getY()][sPos.getX() - 1] == -10)
				{
					InitializeMap(map, sPos, arr);

				}
				else if (sPos.getX() - 1 >= 0 && arr[sPos.getY()][sPos.getX() - 1] != -2)
				{
					std::cout << endl;
					std::cout << "왼쪽으로 이동합니다." << endl;
					SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY(), sPos.getX() - 1);
					sPos.setX(sPos.getX() - 1);
				}
				else
				{
					std::cout << endl;
					std::cout << "왼쪽으로 이동해야 하지만 갈 수 없는 곳입니다." << endl;
				}
				system("cls");
				Lobby();
				printBoard(arr);
			}
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
			{
				if (arr[sPos.getY()][sPos.getX() + 1] == -10)
					{
						InitializeMap(map, sPos, arr);

					}
					else if (sPos.getX() + 1 < 10 && arr[sPos.getY()][sPos.getX() + 1] != -2)
					{
						std::cout << endl;
						std::cout << "오른쪽로 이동합니다." << endl;
						SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY(), sPos.getX() + 1);
						sPos.setX(sPos.getX() + 1);
					}
					else
					{
						std::cout << endl;
						std::cout << "오른쪽으로 이동해야 하지만 갈 수 없는 곳입니다." << endl;
					}
				system("cls");
				Lobby();
				printBoard(arr);
				}
			else if (GetAsyncKeyState(VK_SPACE) & 0x8000)
			{
				InitializeMap(map, sPos, arr);
			}
			
		}
		
		////(y, x)
		//std::cout << "움직일 방향을 입력해 주세요.(w(상), s(하), a(좌), d(우)) : ";
		//cin >> InputDir;
		//if (InputDir == "w") // 상
		//{
		//	if (arr[sPos.getY() - 1][sPos.getX()] == -10)
		//	{
		//		InitializeMap(map, sPos, arr);
		//	}
		//	else if (sPos.getY() - 1 >= 0 && arr[sPos.getY() - 1][sPos.getX()] != -2)
		//	{
		//		std::cout << endl;
		//		std::cout << "위로 이동합니다." << endl;
		//		SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY() - 1, sPos.getX());
		//		sPos.setY(sPos.getY() - 1);
		//	}
		//	else
		//	{
		//		std::cout << endl;
		//		std::cout << "위로 이동해야 하지만 갈 수 없는 곳입니다." << endl;
		//	}
		//}
		//else if (InputDir == "s") // 하
		//{
		//	if (arr[sPos.getY() + 1][sPos.getX()] == -10)
		//	{
		//		InitializeMap(map, sPos, arr);
		//	}
		//	else if (sPos.getY() + 1 < 10 && arr[sPos.getY() + 1][sPos.getX()] != -2)
		//	{
		//		std::cout << endl;
		//		std::cout << "아래로 이동합니다." << endl;
		//		SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY() + 1, sPos.getX());
		//		sPos.setY(sPos.getY() + 1);
		//	}
		//	else
		//	{
		//		std::cout << endl;
		//		std::cout << "아래로 이동해야 하지만 갈 수 없는 곳입니다." << endl;
		//	}
		//}
		//else if (InputDir == "a") // 좌
		//{
		//	if (arr[sPos.getY()][sPos.getX() - 1] == -10)
		//	{
		//		InitializeMap(map, sPos, arr);

		//	}
		//	else if (sPos.getX() - 1 >= 0 && arr[sPos.getY()][sPos.getX() - 1] != -2)
		//	{
		//		std::cout << endl;
		//		std::cout << "왼쪽으로 이동합니다." << endl;
		//		SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY(), sPos.getX() - 1);
		//		sPos.setX(sPos.getX() - 1);
		//	}
		//	else
		//	{
		//		std::cout << endl;
		//		std::cout << "왼쪽으로 이동해야 하지만 갈 수 없는 곳입니다." << endl;
		//	}
		//}
		//else if (InputDir == "d") // 우
		//{
		//	if (arr[sPos.getY()][sPos.getX() + 1] == -10)
		//	{
		//		InitializeMap(map, sPos, arr);
	
		//	}
		//	else if (sPos.getX() + 1 < 10 && arr[sPos.getY()][sPos.getX() + 1] != -2)
		//	{
		//		std::cout << endl;
		//		std::cout << "오른쪽로 이동합니다." << endl;
		//		SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY(), sPos.getX() + 1);
		//		sPos.setX(sPos.getX() + 1);
		//	}
		//	else
		//	{
		//		std::cout << endl;
		//		std::cout << "오른쪽으로 이동해야 하지만 갈 수 없는 곳입니다." << endl;
		//	}
		//}
		//else if (InputDir == "mix")
		//{
		//	InitializeMap(map, sPos, arr);
		//}
		//else if (InputDir == "exit")
		//{
		//	std::cout << endl;
		//	std::cout << "=========================" << endl;
		//	std::cout << endl;
		//	std::cout << "exit를 입력하셨습니다. 게임을 종료합니다" << endl;
		//	std::cout << endl;
		//	std::cout << "=========================" << endl;
		//	std::cout << endl;
		//	break;
		//}
		/*system("cls");
		Lobby();
		printBoard(arr);*/
	}
}

int main()
{
	Lobby();
	InGame();
}
