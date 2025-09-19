#include <cassert>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

// 模擬リソース：FILE* をRAIIで管理
class File {
  std::FILE *fp_{nullptr};

public:
  explicit File(const char *path, const char *mode) {
    fp_ = std::fopen(path, mode);
    if (!fp_)
      throw std::runtime_error("fopen failed");
  }
  ~File() {
    if (fp_)
      std::fclose(fp_);
  }

  File(const File &) = delete;
  File &operator=(const File &) = delete;

  File(File &&other) noexcept : fp_(other.fp_) { other.fp_ = nullptr; }
  File &operator=(File &&other) noexcept {
    if (this != &other) {
      if (fp_)
        std::fclose(fp_);
      fp_ = other.fp_;
      other.fp_ = nullptr;
    }
    return *this;
  }

  std::FILE *get() const noexcept { return fp_; }
};

struct Big {
  std::string s;
  explicit Big(std::string v) : s(std::move(v)) {}
};

int main() {
  try {
    // unique_ptr 基本
    auto p = std::make_unique<Big>("hello");
    assert(p && p->s == "hello");

    // shared_ptr: 複数共有
    auto sp1 = std::make_shared<Big>("shared");
    auto sp2 = sp1;
    assert(sp1.use_count() == 2 && sp2->s == "shared");

    // RAII: ファイルを開いて書く
    File f("day1_tmp.txt", "wb");
    const char *msg = "RAII works.\n";
    std::fwrite(msg, 1, std::char_traits<char>::length(msg), f.get());

    std::cout << "day1_smartptr OK\n";
    return 0;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
