#include <cassert>
#include <cmath>

struct Body {
  double x, v, a;
  void update(double dt) {
    v += a * dt;
    x += v * dt;
  }
};

int main() {
  Body b{0.0, 0.0, 1.0};
  b.update(1.0); // 1秒
  assert(std::fabs(b.x - 1.0) < 1e-6);
  return 0;
}
