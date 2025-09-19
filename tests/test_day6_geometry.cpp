#include <cassert>
#include <cmath>

struct Vec2 { double x, y; };
struct Circle { Vec2 c; double r; };

double dist2(const Vec2& a, const Vec2& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx*dx + dy*dy;
}

bool pointInCircle(const Vec2& p, const Circle& c) {
    return dist2(p, c.c) <= c.r * c.r;
}

bool circleIntersect(const Circle& a, const Circle& b) {
    double rsum = a.r + b.r;
    return dist2(a.c, b.c) <= rsum * rsum;
}

int main() {
    // 点と円
    {
        Vec2 p{0,0};
        Circle c{{0,0},1};
        assert(pointInCircle(p,c)); // 中心点は必ず含まれる
    }
    // 円と円（離れている場合）
    {
        Circle c1{{0,0},1};
        Circle c2{{3,0},1};
        assert(!circleIntersect(c1,c2));
    }
    // 円と円（重なっている場合）
    {
        Circle c1{{0,0},2};
        Circle c2{{3,0},2};
        assert(circleIntersect(c1,c2));
    }
    return 0;
}
