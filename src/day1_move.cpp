#include <chrono>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <class F, class... Args>
decltype(auto) perfect_forward(F &&f, Args &&...args) {
  return std::forward<F>(f)(std::forward<Args>(args)...);
}

struct Collector {
  std::vector<std::string> data;
  void add(std::string s) {
    data.emplace_back(std::move(s));
  } // ムーブで受け取る
};

int main() {
  using clock = std::chrono::high_resolution_clock;

  std::vector<std::string> src;
  src.reserve(200000);
  for (int i = 0; i < 200000; ++i)
    src.emplace_back("str_" + std::to_string(i));

  Collector c;
  auto t0 = clock::now();
  for (auto &s : src)
    c.add(std::move(s)); // 大量ムーブ
  auto t1 = clock::now();

  // 完璧転送：ラムダに右/左値をそのまま渡す
  auto lambda = [](auto &&x) { return std::forward<decltype(x)>(x).size(); };
  std::string tmp = "abcdef";
  size_t a = perfect_forward(lambda, tmp);           // lvalue
  size_t b = perfect_forward(lambda, std::string()); // rvalue

  std::chrono::duration<double, std::milli> ms = t1 - t0;
  std::cout << "moved " << c.data.size() << " strings in " << ms.count()
            << " ms\n";
  std::cout << "sizes " << a << " " << b << "\n";
  std::cout << "day1_move OK\n";
}
