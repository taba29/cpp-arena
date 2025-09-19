#include <cassert>

enum class State { Idle, Attack, Flee };

static State step(State s, int& hp, int& dist) {
    // 遷移
    if (s == State::Idle && dist < 10) s = State::Attack;
    else if (s == State::Attack && hp < 50) s = State::Flee;
    else if (s == State::Flee && dist > 15) s = State::Idle;

    // 行動
    if (s == State::Attack) { hp -= 10; dist -= 2; }
    else if (s == State::Flee) { dist += 3; }
    else { dist -= 1; }

    if (dist < 0) dist = 0;
    if (hp < 0) hp = 0;
    return s;
}

int main() {
    // ケース1: Idle -> Attack
    {
        State s = State::Idle;
        int hp = 100, dist = 9; // 近いと攻撃に入る
        s = step(s, hp, dist);
        assert(s == State::Attack);
    }
    // ケース2: Attack -> Flee（HPしきい値）
    {
        State s = State::Attack;
        int hp = 49, dist = 5;
        s = step(s, hp, dist);
        assert(s == State::Flee);
    }
    // ケース3: Flee -> Idle（距離が十分に開く）
    {
        State s = State::Flee;
        int hp = 80, dist = 16;
        s = step(s, hp, dist);
        assert(s == State::Idle);
    }
    return 0;
}
