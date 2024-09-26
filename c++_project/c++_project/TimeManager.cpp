#include "TimeManager.h"
#include<Windows.h>

LARGE_INTEGER TimeManager::CpuFrequency = {};
LARGE_INTEGER TimeManager::PrevFrequency = {};
LARGE_INTEGER TimeManager::CurrentFrequency = {};
float TimeManager::DeltaTimeValue = 0.0f;

void TimeManager::Initalize()
{
	QueryPerformanceFrequency(&CpuFrequency);

}

void TimeManager::Update()
{
}  
