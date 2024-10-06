#include "Map.h"
#include <fstream>
#include <iostream>
#include <string>

Map::Map(const string inputName) : mapName(inputName)
{
    int rows = 50;  // 세로
    int cols = 100; // 가로

    mapInfo = new int* [rows];
    for (int i = 0; i < rows; ++i) {
        mapInfo[i] = new int[cols];
    }

    ifstream in(mapName + ".txt");
    string mapData;

    if (!in.is_open())
    {
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                mapInfo[row][col] = 0;
            }
        }
    }
    else
    {
        int row = 0;
        while (getline(in, mapData) && row < rows)
        {
            for (int col = 0; col < cols && col < mapData.size(); ++col)
            {
                mapInfo[row][col] = mapData[col] - '0';
            }
            row++;
        }

        for (; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                mapInfo[row][col] = 1;
            }
        }
    }
}

Map::~Map()
{
    for (size_t i = 0; i < 50; i++)
    {
        delete[] mapInfo[i];
    }
    delete[] mapInfo;
    mapInfo = nullptr;
}

int& Map::at(int y, int x)

{
    return mapInfo[y][x];
}

//사용 보류
int** Map::GenerateMap(string mapName)
{
    // 파일 읽기 준비
    ifstream in(mapName + ".txt");

    string mapData;
    int rows = 50;
    int cols = 50;

    int** array = new int* [rows];
    for (int i = 0; i < rows; ++i)
    {
        array[i] = new int[cols];
    }

    if (!in.is_open())
    {
        int col = 0;
        for (int row = 0; row < mapData.size(); ++row)
        {
            array[row][col] = 0;
        }
        col++;
        return array;
    }
    else
    {
        while (getline(in, mapData))
        {
            int col = 0;
            for (int row = 0; row < mapData.size(); ++row)
            {
                array[row][col] = mapData[row];
            }
            col++;
        }
        return array;
    }
}

//사용 보류
int** Map::GenerateMap2(string mapName)
{
    // 파일 읽기 준비
    ifstream in(mapName + ".txt");

    string mapData;
    int rows = 100;
    int cols = 50;

    int** array = new int* [rows];
    for (int i = 0; i < rows; ++i)
    {
        array[i] = new int[cols];
    }

    if (!in.is_open())
    {
        int col = 0;
        for (int row = 0; row < mapData.size(); ++row)
        {
            array[row][col] = 0;
        }
        col++;
        return array;
    }
    else
    {
        while (getline(in, mapData))
        {
            int col = 0;
            for (int row = 0; row < mapData.size(); ++row)
            {
                array[row][col] = mapData[row];
            }
            col++;
        }
        return array;
    }
}

string Map::GetMapName()
{
    return mapName;
}
