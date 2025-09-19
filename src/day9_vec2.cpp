#include <cmath>
#include <iostream>

struct Vec2 {
    double x, y;

    Vec2 operator+(const Vec2& other) const { return {x + other.x, y + other.y}; }
    Vec2 operator-(const Vec2& other) const { return {x - other.x, y - other.y}; }
    double length() const { return std::sqrt(x * x + y * y); }
};

int main() {
    Vec2 a{3, 4}, b{1, 2};
    auto c = a + b;
    auto d = a - b;
    std::cout << "c=(" << c.x << "," << c.y << ")\n";
    std::cout << "d=(" << d.x << "," << d.y << ")\n";
    std::cout << "len(a)=" << a.length() << "\n";
}

