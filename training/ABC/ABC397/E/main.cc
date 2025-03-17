#include <iostream>
#include <vector>

int main() {
  int n, k;
  std::cin >> n >> k;

  std::vector g(n * k, std::vector<int>{});
  for (int i = 0; i < n * k - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    g[--u].emplace_back(--v);
    g[v].emplace_back(u);
  }

  auto Judge = [&](auto self, int v, int p) -> int {
    std::vector<int> s;
    for (int nv : g[v]) {
      if (nv == p) continue;
      int nx = self(self, nv, v);
      if (nx == -1) return -1;
      if (nx > 0) s.emplace_back(nx);
    }
    if (s.empty()) return 1 % k;
    if (s.size() == 1) return (s[0] + 1) % k;
    if (s.size() == 2) return s[0] + s[1] + 1 == k ? 0 : -1;
    return -1;
  };

  std::cout << (Judge(Judge, 0, -1) == 0 ? "Yes\n" : "No\n");
  return 0;
}