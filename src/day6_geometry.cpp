#include <iostream>
#include <cmath>

struct Vec2 {
    double x, y;
};

struct Circle {
    Vec2 c;
    double r;
};

// 距離の2乗を返す（sqrt を避けて効率化）
double dist2(const Vec2& a, const Vec2& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx*dx + dy*dy;
}

// 点と円の衝突判定
bool pointInCircle(const Vec2& p, const Circle& c) {
    return dist2(p, c.c) <= c.r * c.r;
}

// 円と円の衝突判定
bool circleIntersect(const Circle& a, const Circle& b) {
    double rsum = a.r + b.r;
    return dist2(a.c, b.c) <= rsum * rsum;
}

int main() {
    Vec2 p{0, 0};
    Circle c1{{3, 0}, 5};
    Circle c2{{0, 0}, 3};
    Circle c3{{5, 0}, 2};

    std::cout << std::boolalpha;

    std::cout << "pointInCircle(p, c1) = " << pointInCircle(p, c1) << "\n"; // true
    std::cout << "circleIntersect(c2, c3) = " << circleIntersect(c2, c3) << "\n"; // true (接触)
    std::cout << "day6_geometry OK\n";

    return 0;
}
