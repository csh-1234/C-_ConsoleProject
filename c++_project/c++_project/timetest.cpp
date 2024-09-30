#include <iostream>
#include "TimeManager.h"
#include <Windows.h>

using namespace std;

int main()
{
    LARGE_INTEGER CpuFrequency = {};
    LARGE_INTEGER PrevFrequency = {};
    LARGE_INTEGER CurrentFrequency = {};

    float DiffereneceFrequency = {};
    float DeltaTimeValue = 0.0f;

    QueryPerformanceFrequency(&CpuFrequency);
    QueryPerformanceCounter(&PrevFrequency);

    float time = 0.0f;
    char input;

    while (true)
    {
        QueryPerformanceCounter(&CurrentFrequency);
        DiffereneceFrequency = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);
        DeltaTimeValue = DiffereneceFrequency / static_cast<float>(CpuFrequency.QuadPart);
        //cout << DeltaTimeValue << endl;
        PrevFrequency.QuadPart = CurrentFrequency.QuadPart;

        time += DeltaTimeValue;
        //cout << time << endl;
        float fps = 1.0f / DeltaTimeValue;

        cout << (int)time << endl;
        PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
        /*cout << CpuFrequency.QuadPart << endl;
        cout << PrevFrequency.QuadPart << endl;
        cout << DeltaTimeValue << endl;*/
    }
}