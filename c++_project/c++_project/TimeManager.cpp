#include "TimeManager.h"
#include<Windows.h>

LARGE_INTEGER TimeManager::CpuFrequency = {};
LARGE_INTEGER TimeManager::PrevFrequency = {};
LARGE_INTEGER TimeManager::CurrentFrequency = {};
float TimeManager::DeltaTimeValue = 0.0f;

void TimeManager::Initailize()
{
	// Cpu 고유 진동수
	QueryPerformanceFrequency(&CpuFrequency);

	// 프로그램이 시작 했을 때 현재 진동수
	QueryPerformanceCounter(&PrevFrequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&CurrentFrequency);
	
	float differenceFrequency
		= static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);
	DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);
	PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
}
