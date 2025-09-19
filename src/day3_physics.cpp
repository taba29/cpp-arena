#include <chrono>
#include <iostream>
#include <thread>

// 1D 物理オブジェクト
struct Body {
  double x; // 位置
  double v; // 速度
  double a; // 加速度

  void update(double dt) {
    v += a * dt; // 速度更新
    x += v * dt; // 位置更新
  }
};

int main() {
  Body ball{0.0, 0.0, 9.8}; // x=0, v=0, a=9.8 (重力っぽい)

  using clock = std::chrono::steady_clock;
  const double dt = 0.016; // 16ms ≈ 60Hz
  auto next = clock::now();

  for (int i = 0; i < 100; i++) {
    ball.update(dt);
    std::cout << "t=" << i * dt << "s  x=" << ball.x << "  v=" << ball.v
              << "\n";

    next += std::chrono::milliseconds(16);
    std::this_thread::sleep_until(next);
  }
  std::cout << "day3_physics OK\n";
}
