#include "Map.h"
#include <fstream>
#include <iostream>
#include <string>

Map::Map(const string inputName) : mapName(inputName)
{
    // TODO - 변동 맵사이즈 필요할 수 있음
    int rows = 50;
    int cols = 50;
    mapInfo = new int* [50];

    // 파일 읽기 준비
    ifstream in(mapName + ".txt");

    int readMapDate[50][50] = {};
    string mapDataBuffer;
    int col = 0;

    if (!in.is_open())
    {
        for (int row = 0; row < 50; ++row)
        {
            readMapDate[row][col] = 0;
        }
        col++;
    }
    else
    {
        while (getline(in, mapDataBuffer))
        {
            for (int row = 0; row < 50; ++row)
            {
                readMapDate[col][row] = mapDataBuffer[row] -'0';
            }
            col += 1;
        }
    }

    for (size_t i = 0; i < cols; i++)
    {
        mapInfo[i] = new int[50];
        for (size_t j = 0; j < rows; j++)
        {
            mapInfo[i][j] = readMapDate[i][j];
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

string Map::GetMapName()
{
    return mapName;
}






