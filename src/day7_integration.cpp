#include <iostream>
#include <cmath>
#include <string>
#include <fstream>   // 先頭の #include 群に追加


struct Vec2 { double x,y; };
struct Circle { Vec2 c; double r; };

static double dist2(const Vec2& a, const Vec2& b){
    double dx=a.x-b.x, dy=a.y-b.y; return dx*dx+dy*dy;
}

enum class State { Idle, Attack, Flee };
static std::string to_string(State s){
    switch(s){case State::Idle:return "Idle";case State::Attack:return "Attack";case State::Flee:return "Flee";}
    return "?";
}



int main(){
    std::ofstream csv("day7_log.csv");
    csv << "t,d,state,hp,px,py,ex,ey\n";
    auto state_id = [](State s){ return (s==State::Idle?0:(s==State::Attack?1:2)); };



    // プレイヤーと敵（円とみなす）
    Circle player{{0,0}, 0.5};
    Circle enemy {{15,0}, 0.5};
    Vec2   vPlayer{ 1.0, 0.0};  // プレイヤーは右へ移動
    Vec2   vEnemy {-0.5, 0.0};  // 敵は左へ移動

    // FSM パラメータ
    State state = State::Idle;
    int   hp    = 100;
    const double attackRange = 10.0;   // 距離<=10で攻撃
    const double safeRange   = 15.0;   // 距離>=15で安全→Idle
    const int fleeHP         = 50;     // HP<50で逃走

    const double dt = 0.1; // 簡易ステップ（秒）
    std::cout.setf(std::ios::fixed); std::cout.precision(2);

    State prev = state;

    for(int step=0; step<120; ++step){ // 12秒ぶん
        // 物理更新
        player.c.x += vPlayer.x * dt; player.c.y += vPlayer.y * dt;
        enemy .c.x += vEnemy .x * dt; enemy .c.y += vEnemy .y * dt;

        // 幾何：実距離
        double d = std::sqrt(dist2(player.c, enemy.c));

        // 遷移（距離に基づく）
        if(state==State::Idle   && d<=attackRange) state=State::Attack;
        else if(state==State::Attack && hp<fleeHP) state=State::Flee;
        else if(state==State::Flee   && d>=safeRange) state=State::Idle;

        // 行動
        if(state==State::Attack){
            hp -= 5;                        // 戦闘でHP低下
            vPlayer = { 0.5, 0.0};          // 押し合いでやや減速
            vEnemy  = {-0.2, 0.0};
        }else if(state==State::Flee){
            vPlayer = {-1.5, 0.0};          // 逃走で逆方向へ加速
            vEnemy  = {-0.2, 0.0};
        }else{ // Idle
            vPlayer = { 1.0, 0.0};
            vEnemy  = {-0.5, 0.0};
        }
        if(hp<0) hp=0;

        csv << step*dt << "," << d << "," << state_id(state) << "," << hp << ","
            << player.c.x << "," << player.c.y << ","
            << enemy.c.x  << "," << enemy.c.y  << "\n";

        


        if(step%5==0){ // ログ間引き
            std::cout<<"t="<<step*dt<<"s  d="<<d
                     <<"  State="<<to_string(state)
                     <<"  HP="<<hp
                     <<"  P=("<<player.c.x<<","<<player.c.y<<")"
                     <<"  E=("<<enemy.c.x<<","<<enemy.c.y<<")\n";
        }
        if (state != prev) {
            std::cout << "TRANSITION: " << to_string(prev) << " -> " << to_string(state)
            << " at t=" << step*dt << " d=" << d << " HP=" << hp << "\n";
            prev = state;
        }

    }
    csv.close();
    std::cout<<"day7_integration OK\n";
    return 0; 
}
