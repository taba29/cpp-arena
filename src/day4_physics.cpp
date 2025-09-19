#include <iostream>
#include <iomanip>

int main() {
    const double dt = 0.016;   // 60Hz
    const double a = -9.8;     // 加速度 [m/s^2]
    double x = 0.0;            // 位置
    double v = 10.0;           // 初速度
    double t = 0.0;

    std::cout << std::fixed << std::setprecision(3);

    std::cout << "== Euler ==" << std::endl;
    x = 0.0; v = 10.0; t = 0.0;
    while (t <= 2.0) {
        std::cout << "t=" << t << "  x=" << x << "  v=" << v << "\n";
        x += v * dt;
        v += a * dt;
        t += dt;
    }

    std::cout << "\n== Symplectic Euler ==" << std::endl;
    x = 0.0; v = 10.0; t = 0.0;
    while (t <= 2.0) {
        std::cout << "t=" << t << "  x=" << x << "  v=" << v << "\n";
        v += a * dt;
        x += v * dt;
        t += dt;
    }

    return 0;
}
