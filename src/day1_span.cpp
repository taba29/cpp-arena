#include <cassert>
#include <iostream>
#include <span>
#include <vector>

int sum(std::span<const int> s) {
  int total = 0;
  for (int v : s)
    total += v;
  return total;
}

int main() {
  std::vector<int> v = {1, 2, 3, 4, 5};
  std::span<const int> sv(v);
  int s = sum(sv.subspan(1, 3)); // 2+3+4
  assert(s == 9);

  // 範囲安全：範囲外アクセスは自分で防ぐ（spanは長さを保持）
  if (sv.size() >= 5) {
    int tail = sum(sv.last(2)); // 4+5
    assert(tail == 9);
  }

  std::cout << "day1_span OK\n";
}
