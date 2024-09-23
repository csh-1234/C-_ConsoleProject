#include <iostream>
#include <windows.h>
using namespace std;

/*
콘솔 프로젝트
09/27(금) ~ 10/04(금) 발표
1. 기능 명세서(09/26 구글드라이브 업로드)
- 주제 선정
- 기능 구현 목록
- 000 구현( ex) 000을 활용)
2. 프로젝트 영상을 찍기
- 구구절절하게 다 설명하지마
- 핵심적인 기능만 노출
*/



int main()
{
    // 콘솔 이름 변경
    SetConsoleTitle(TEXT("abcde"));

    system("mode con:cols=150 lines=50");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 18);
    cout << "press any key" << endl;
    system("pause");



    return 0;
}