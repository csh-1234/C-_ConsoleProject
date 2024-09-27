#pragma once
#include <iostream>
using namespace std;
class Map
{
public:
	struct Position
	{
		int x;
		int y;
	};
	Map(const int mapHeight, const int mapWidth, const int viewPointX, const int viewPointY
		, const int enterancePosX, const int enterancePosY, const int exitPosX, const int exitPosY)
		: mapSize({ mapWidth, mapWidth }), viewPointSize({viewPointSizeX, viewPointSizeY}), entrancePos(), exitPos()
	{
		map = new int* [mapHeight];
		for (size_t i = 0; i < mapHeight; i++)
		{
			map[i] = new int(mapWidth);
		}
		for (size_t i = 0; i < mapHeight; i++)
		{
			for (size_t j = 0; j < mapWidth; j++)
			{
				map[i][j] = 0;
			}
		}
		
	}
	int& at(int y, int x)
	{
		return map[y][x];
	}
	~Map()
	{
		for (size_t i = 0; i < mapSize.y; i++) delete[] map[i];
	}

private:
	int** map;
	Position mapSize;
	Position viewPointSize;
	Position entrancePos;
	Position exitPos;

};

