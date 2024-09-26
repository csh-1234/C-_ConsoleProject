#include "Knight.h"
#include "Player.h"

Knight::Knight(string name) : Player(CharacterClass::KNIGHT)
{
	_name = name;					// �̸�
	_characterClass = CharacterClass::KNIGHT;	// ���� ����(�÷��̾�, ����)
	_maxHp = 200;				// �ִ� ü��
	_hp = 200;					// ���� ü��
	_maxMp = 100;				// �ִ� ����
	_mp = 100;					// �⺻ ����
	_atk = 10;					// �⺻ ���ݷ�
	_def = 5;					// �⺻ ����
	_criRate = 10;				// �⺻ ũ��Ƽ�� Ȯ��
	_criDamage = 150;			// �⺻ ũ��Ƽ�� ������
	_avoidRate = 10;			// �⺻ ȸ����
	_speed = 10;				// �⺻ �ӵ�
	_money = 10000;				// ������
}

Knight::~Knight()
{
}
