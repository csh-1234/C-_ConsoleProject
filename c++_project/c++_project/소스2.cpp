#include <iostream>
#include <vector>

struct Position {
    int x, y;
};

// ��ǥ�� Ŭ���� (����, �÷��̾� ��)
class Target {
public:
    Position pos;
    Target(int x, int y) : pos{ x, y } {}

    Position getPosition() { return pos; }
};

// ����ü Ŭ����
class Projectile {
public:
    Position pos;
    int dx, dy; // ���� (�ӵ�)

    Projectile(int x, int y, int dx, int dy) : pos{ x, y }, dx(dx), dy(dy) {}

    void move() {
        pos.x += dx;
        pos.y += dy;
    }

    Position getPosition() { return pos; }
};

// �浹 ���� �Լ�
bool checkCollision(Position a, Position b) {
    return a.x == b.x && a.y == b.y;
}

int main() {
    Target target(5, 5);
    Projectile projectile(0, 0, 1, 1); // (0,0)���� (1,1) �������� ����ü �߻�

    // ĳ���� ����
    // Ű �Է½� ����ü �߻� -> Ÿ��
    // Ÿ���� ������
    // Ÿ���� ������ ������ �߻�, �������� ����ü�� ����
    // 
    while (true)
    {

    }


    return 0;
}