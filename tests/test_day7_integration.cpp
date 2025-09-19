#include <cassert>
#include <cmath>


enum class State { Idle, Attack, Flee };
static double dist2(double ax,double ay,double bx,double by){double dx=ax-bx,dy=ay-by;return dx*dx+dy*dy;}

int main(){
    double px=0, py=0, ex=15, ey=0;
    double vpx=1.0,  vex=-0.5;
    State s=State::Idle;
    const double attackRange=10.0;
    for(int i=0;i<200;i++){
        px+=vpx*0.1; ex+=vex*0.1;
        double d=std::sqrt(dist2(px,py,ex,ey));
        if(s==State::Idle && d<=attackRange){ s=State::Attack; break; }
    }
    assert(s==State::Attack);
    return 0;
}
