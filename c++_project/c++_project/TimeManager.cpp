#include "TimeManager.h"
#include<Windows.h>

LARGE_INTEGER TimeManager::CpuFrequency = {};
LARGE_INTEGER TimeManager::PrevFrequency = {};
LARGE_INTEGER TimeManager::CurrentFrequency = {};
float TimeManager::DeltaTimeValue = 0.0f;

void TimeManager::Initalize()
{
	// ���� Ŭ����
	QueryPerformanceFrequency(&CpuFrequency);
	// ���α׷� ����� Ŭ����(����)
	QueryPerformanceCounter(&CpuFrequency);
}

void TimeManager::Update()
{
	// Ŭ�� ���� ����
	QueryPerformanceCounter(&CurrentFrequency);

	float differenceFrequency
		= static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart); // �ֱ� Ŭ�� - ���� Ŭ��
	DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart); // deltatime = �� Ŭ���� Ƚ�� / �⺻Ŭ����
	PrevFrequency.QuadPart = CurrentFrequency.QuadPart; // �� ����Ŭ�� �������Ƿ� ���� Ŭ���� �ֽ�ȭ
}  
