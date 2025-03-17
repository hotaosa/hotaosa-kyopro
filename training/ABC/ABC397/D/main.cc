#include <iostream>

int64_t Cube(int64_t x) { return x * x * x; }

int main() {
  int64_t n;
  std::cin >> n;

  for (int64_t d = 1; Cube(d) <= n; ++d) {
    int64_t l = 1, r = 2;
    while (Cube(r + d) - Cube(r) <= n) r *= 2;
    while (r - l > 1) {
      int64_t y = (l + r) / 2;
      int64_t x = y + d;
      (Cube(x) - Cube(y) <= n ? l : r) = y;
    }
    int64_t y = l;
    int64_t x = y + d;
    if (Cube(x) - Cube(y) == n) {
      std::cout << x << " " << y << "\n";
      return 0;
    }
  }

  std::cout << "-1\n";
  return 0;
}