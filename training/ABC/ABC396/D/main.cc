#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector g(n, std::vector<int64_t>(n, -1));
  for (int i = 0; i < m; ++i) {
    int u, v;
    int64_t w;
    std::cin >> u >> v >> w;
    g[--u][--v] = w;
    g[v][u] = w;
  }

  std::vector<int> o(n - 1);
  std::iota(std::begin(o), std::end(o), 1);
  int64_t res{1LL << 60};
  do {
    int v = 0;
    int64_t cur{0};
    for (int nv : o) {
      if (g[v][nv] == -1) break;
      cur ^= g[v][nv];
      v = nv;
      if (v == n - 1) {
        res = std::min(res, cur);
        break;
      }
    }
  } while (std::next_permutation(std::begin(o), std::end(o)));

  std::cout << res << "\n";
  return 0;
}