#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<int64_t> b(n), w(m);
  for (auto &e : b) std::cin >> e;
  for (auto &e : w) std::cin >> e;
  std::sort(std::rbegin(b), std::rend(b));
  std::sort(std::rbegin(w), std::rend(w));
  for (int i = 1; i < n; ++i) b[i] += b[i - 1];
  for (int i = 1; i < m; ++i) w[i] += w[i - 1];
  for (int i = n - 2; i >= 0; --i) b[i] = std::max(b[i], b[i + 1]);

  int64_t res = std::max(int64_t{0}, b[0]);
  for (int i = 0; i < std::min(n, m); ++i) {
    res = std::max(res, w[i] + b[i]);
  }

  std::cout << res << "\n";
  return 0;
}