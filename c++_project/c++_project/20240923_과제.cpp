#include <iostream>
#include <Windows.h>
#include <cmath>
using namespace std;

/*

�����̵� ���� ���
��ֹ��� �뼺�뼺 ����
��ֹ��� ��������
Ű�Է����� �̵�
���� �Ա��� �����
���� ���������� ���;� �Ѵ�
*/

//���� ��ġ�� ������ �ִ� class
class StarPos
{
public:
	//�Ű������� �ִ� ������
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

//���ӱ�Ģ ���
void Lobby()
{
	std::cout << "=====================================================" << endl;
	std::cout << "�÷��̾� : ��" << endl;
	std::cout << "���� �������� : ��" << endl;
	std::cout << "���� ��Ģ : ����Ű�� ���� �÷��̾ �̵���ų �� �ֽ��ϴ�!" << endl;
	std::cout << "�÷��̾�� �� ������ ���� �� �����ϴ�!" << endl;
	std::cout << "�÷��̾�� ��ֹ��� ������ �� �����ϴ�!" << endl;
	std::cout << "�����̽��� �Է��Ͻø� ���� ������˴ϴ�.!" << endl;
	std::cout << "=====================================================" << endl;
}

//���带 ����ϴ� �޼���
void printBoard(int arr[][10])
{
	std::cout << "�ޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡ�" << endl;
	for (size_t i = 0; i < 10; i++)
	{

		std::cout << "��";
		for (size_t j = 0; j < 10; j++)
		{
			if (arr[i][j] == -1)
			{
				std::cout << "��" << "	";
			}
			else if (arr[i][j] == -2)
			{
				std::cout << "��" << "	";
			}
			else if (arr[i][j] == -10)
			{
				std::cout << "��" << "	";
			}
			else
			{
				std::cout << "	";
			}
		}

		std::cout << "��";
		std::cout << endl;
		std::cout << "��";
		std::cout << "                                                                              ��" ;
		std::cout << endl; 

	}
	std::cout << "�ޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡޡ�" << endl;
}

// ���� ���忡�� �� ��ǥ�� �����ϴ� �޼���
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

// �� ��ǥ�� �Է¹޾� �� ��ġ�� �ٲٴ� �޼���
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
	//�� ����
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

// ���� ������ �Ѿ���� �ʱ�ȭ���ִ� �޼���
void InitializeMap(Map *map, StarPos &s, int arr[][10])
{
	std::cout << "���� ������ �̵�!" << endl;
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
	
	string InputDir = ""; //�����¿� �Է¹޴� ����
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
					std::cout << "���� �̵��մϴ�." << endl;
					SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY() - 1, sPos.getX());
					sPos.setY(sPos.getY() - 1);
				}
				else
				{
					std::cout << endl;
					std::cout << "���� �̵��ؾ� ������ �� �� ���� ���Դϴ�." << endl;
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
					std::cout << "�Ʒ��� �̵��մϴ�." << endl;
					SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY() + 1, sPos.getX());
					sPos.setY(sPos.getY() + 1);
					
				}
				else
				{
					std::cout << endl;
					std::cout << "�Ʒ��� �̵��ؾ� ������ �� �� ���� ���Դϴ�." << endl;
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
					std::cout << "�������� �̵��մϴ�." << endl;
					SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY(), sPos.getX() - 1);
					sPos.setX(sPos.getX() - 1);
				}
				else
				{
					std::cout << endl;
					std::cout << "�������� �̵��ؾ� ������ �� �� ���� ���Դϴ�." << endl;
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
						std::cout << "�����ʷ� �̵��մϴ�." << endl;
						SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY(), sPos.getX() + 1);
						sPos.setX(sPos.getX() + 1);
					}
					else
					{
						std::cout << endl;
						std::cout << "���������� �̵��ؾ� ������ �� �� ���� ���Դϴ�." << endl;
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
		//std::cout << "������ ������ �Է��� �ּ���.(w(��), s(��), a(��), d(��)) : ";
		//cin >> InputDir;
		//if (InputDir == "w") // ��
		//{
		//	if (arr[sPos.getY() - 1][sPos.getX()] == -10)
		//	{
		//		InitializeMap(map, sPos, arr);
		//	}
		//	else if (sPos.getY() - 1 >= 0 && arr[sPos.getY() - 1][sPos.getX()] != -2)
		//	{
		//		std::cout << endl;
		//		std::cout << "���� �̵��մϴ�." << endl;
		//		SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY() - 1, sPos.getX());
		//		sPos.setY(sPos.getY() - 1);
		//	}
		//	else
		//	{
		//		std::cout << endl;
		//		std::cout << "���� �̵��ؾ� ������ �� �� ���� ���Դϴ�." << endl;
		//	}
		//}
		//else if (InputDir == "s") // ��
		//{
		//	if (arr[sPos.getY() + 1][sPos.getX()] == -10)
		//	{
		//		InitializeMap(map, sPos, arr);
		//	}
		//	else if (sPos.getY() + 1 < 10 && arr[sPos.getY() + 1][sPos.getX()] != -2)
		//	{
		//		std::cout << endl;
		//		std::cout << "�Ʒ��� �̵��մϴ�." << endl;
		//		SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY() + 1, sPos.getX());
		//		sPos.setY(sPos.getY() + 1);
		//	}
		//	else
		//	{
		//		std::cout << endl;
		//		std::cout << "�Ʒ��� �̵��ؾ� ������ �� �� ���� ���Դϴ�." << endl;
		//	}
		//}
		//else if (InputDir == "a") // ��
		//{
		//	if (arr[sPos.getY()][sPos.getX() - 1] == -10)
		//	{
		//		InitializeMap(map, sPos, arr);

		//	}
		//	else if (sPos.getX() - 1 >= 0 && arr[sPos.getY()][sPos.getX() - 1] != -2)
		//	{
		//		std::cout << endl;
		//		std::cout << "�������� �̵��մϴ�." << endl;
		//		SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY(), sPos.getX() - 1);
		//		sPos.setX(sPos.getX() - 1);
		//	}
		//	else
		//	{
		//		std::cout << endl;
		//		std::cout << "�������� �̵��ؾ� ������ �� �� ���� ���Դϴ�." << endl;
		//	}
		//}
		//else if (InputDir == "d") // ��
		//{
		//	if (arr[sPos.getY()][sPos.getX() + 1] == -10)
		//	{
		//		InitializeMap(map, sPos, arr);
	
		//	}
		//	else if (sPos.getX() + 1 < 10 && arr[sPos.getY()][sPos.getX() + 1] != -2)
		//	{
		//		std::cout << endl;
		//		std::cout << "�����ʷ� �̵��մϴ�." << endl;
		//		SwapPosition(arr, sPos.getY(), sPos.getX(), sPos.getY(), sPos.getX() + 1);
		//		sPos.setX(sPos.getX() + 1);
		//	}
		//	else
		//	{
		//		std::cout << endl;
		//		std::cout << "���������� �̵��ؾ� ������ �� �� ���� ���Դϴ�." << endl;
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
		//	std::cout << "exit�� �Է��ϼ̽��ϴ�. ������ �����մϴ�" << endl;
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
