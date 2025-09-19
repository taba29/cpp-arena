#include <chrono>
#include <cmath>
#include <iostream>
#include <thread>

int main() {
  using clock = std::chrono::steady_clock;
  constexpr double dt = 1.0 / 60.0; // 60Hz
  double accumulator = 0.0;
  auto prev = clock::now();

  double t = 0.0;
  double x = 0.0; // 位置
  double v = 1.0; // 速度（1 unit/secとして）

  int steps = 0;
  while (steps < 180) { // 3秒分
    auto now = clock::now();
    std::chrono::duration<double> frame = now - prev;
    prev = now;
    accumulator += frame.count();

    while (accumulator >= dt) {
      // シンプル更新（x += v * dt）
      x += v * dt;
      t += dt;
      accumulator -= dt;
      steps++;
    }

    // ここでは描画の代わりにログ
    double alpha = accumulator / dt; // 補間率（ダミー）
    double x_interp = x + v * dt * alpha;
    if (steps % 30 == 0) {
      std::cout << "t=" << t << " x~" << x_interp << "\n";
    }

    // 軽いスリープ（実行環境により必要）
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  std::cout << "day1_time OK\n";
}
