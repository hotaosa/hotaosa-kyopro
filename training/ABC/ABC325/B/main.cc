#include <algorithm>
#include <array>
#include <iostream>

int main() {
  int n;
  std::cin >> n;

  std::array<int, 24> c{};
  for (int i = 0; i < n; ++i) {
    int w, x;
    std::cin >> w >> x;
    for (int d = 0; d < 9; ++d) {
      c[(x + d) % 24] += w;
    }
  }

  std::cout << *std::max_element(c.begin(), c.end()) << "\n";
  return 0;
}