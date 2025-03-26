#include <iostream>
#include <vector>

struct Edge {
  int to;
  int64_t w;
};

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector g(n, std::vector<Edge>());
  for (int i = 0; i < m; ++i) {
    int u, v;
    int64_t w;
    std::cin >> u >> v >> w;
    g[--u].emplace_back(--v, w);
    g[v].emplace_back(u, w);
  }

  auto Solve = [&](auto self, int v, int b, int64_t cur) -> int64_t {
    if (v == n - 1) return cur;
    int64_t res{1LL << 60};
    for (auto e : g[v]) {
      if (b >> e.to & 1) continue;
      res = std::min(res, self(self, e.to, b | (1 << e.to), cur ^ e.w));
    }
    return res;
  };

  std::cout << Solve(Solve, 0, 1, 0) << "\n";
  return 0;
}