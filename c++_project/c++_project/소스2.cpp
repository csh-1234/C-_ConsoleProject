#include <iostream>
#include <vector>

struct Position {
    int x, y;
};

// 목표물 클래스 (몬스터, 플레이어 등)
class Target {
public:
    Position pos;
    Target(int x, int y) : pos{ x, y } {}

    Position getPosition() { return pos; }
};

// 투사체 클래스
class Projectile {
public:
    Position pos;
    int dx, dy; // 방향 (속도)

    Projectile(int x, int y, int dx, int dy) : pos{ x, y }, dx(dx), dy(dy) {}

    void move() {
        pos.x += dx;
        pos.y += dy;
    }

    Position getPosition() { return pos; }
};

// 충돌 판정 함수
bool checkCollision(Position a, Position b) {
    return a.x == b.x && a.y == b.y;
}

int main() {
    Target target(5, 5);
    Projectile projectile(0, 0, 1, 1); // (0,0)에서 (1,1) 방향으로 투사체 발사

    // 캐릭터 있음
    // 키 입력시 투사체 발사 -> 타겟
    // 타겟이 움직임
    // 타겟이 맞으면 데미지 발생, 데미지는 투사체가 소유
    // 
    while (true)
    {

    }


    return 0;
}