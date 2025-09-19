#include <cassert>
#include <cmath>

double theoretical_position(double v0, double a, double t) {
    return v0 * t + 0.5 * a * t * t;
}

int main() {
    double v0 = 10.0;
    double a = -9.8;
    double t = 1.0;
    double expected = theoretical_position(v0, a, t); // ≈ 5.1

    // 実測値（簡易：オイラー法の近似）
    double dt = 0.016;
    double x = 0.0, v = v0;
    double time = 0.0;
    while (time < t) {
        x += v * dt;
        v += a * dt;
        time += dt;
    }

    // 誤差 ±0.2 の範囲でOKとする
    assert(std::fabs(x - expected) < 0.2);
    return 0;
}
