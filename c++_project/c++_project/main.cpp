#include <iostream>
#include <windows.h>
using namespace std;

/*
�ܼ� ������Ʈ
09/27(��) ~ 10/04(��) ��ǥ
1. ��� ����(09/26 ���۵���̺� ���ε�)
- ���� ����
- ��� ���� ���
- 000 ����( ex) 000�� Ȱ��)
2. ������Ʈ ������ ���
- ���������ϰ� �� ����������
- �ٽ����� ��ɸ� ����
*/



int main()
{
    // �ܼ� �̸� ����
    SetConsoleTitle(TEXT("abcde"));

    system("mode con:cols=150 lines=50");

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 18);
    cout << "press any key" << endl;
    system("pause");



    return 0;
}