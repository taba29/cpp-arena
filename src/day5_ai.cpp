#include <iostream>
#include <string>

enum class State { Idle, Attack, Flee };

static std::string to_string(State s) {
    switch (s) {
        case State::Idle: return "Idle";
        case State::Attack: return "Attack";
        case State::Flee: return "Flee";
    }
    return "?";
}

int main() {
    // ゲーム内の簡易パラメータ
    State state = State::Idle;
    int hp = 100;     // 体力
    int dist = 20;    // 敵との距離（小さいほど近い）

    // 10ターン分、状態遷移＋行動をログ
    for (int t = 0; t < 10; ++t) {
        // --- 状態遷移ルール ---
        // Idle: 敵が近づいたら攻撃
        if (state == State::Idle && dist <  10) {
            state = State::Attack;
        }
        // Attack: HPが減ったら逃走
        else if (state == State::Attack && hp < 50) {
            state = State::Flee;
        }
        // Flee: 十分に距離が離れたら待機へ戻る
        else if (state == State::Flee && dist > 15) {
            state = State::Idle;
        }

        // --- 行動（状態に応じてパラメータ変化） ---
        if (state == State::Attack) {
            hp -= 10;     // 戦ってHPが減る
            dist -= 2;    // 押し合いでやや接近
        } else if (state == State::Flee) {
            dist += 3;    // 逃げて距離が開く
        } else { // Idle
            dist -= 1;    // 敵が近づいてくる想定
        }

        // 見やすくクランプ（負の距離を避ける）
        if (dist < 0) dist = 0;
        if (hp < 0) hp = 0;

        std::cout << "t=" << t
                  << " State=" << to_string(state)
                  << " HP=" << hp
                  << " Dist=" << dist << "\n";
    }

    std::cout << "day5_ai OK\n";
    return 0;
}
