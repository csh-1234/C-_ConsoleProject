#include "Player.h"

Player::Player(string playerName) : Creature(PLAYER)
{
	_name = playerName;					// �̸�
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

Player::~Player()
{
}

