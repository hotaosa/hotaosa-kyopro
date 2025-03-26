#include <array>
#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int to;
  int w;
};

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector g(n, std::vector<Edge>());
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g[--u].emplace_back(--v, w);
    g[v].emplace_back(u, w);
  }

  std::vector<int> res(n, -1);

  auto Solve = [&](int s) -> bool {
    res[s] = 0;
    std::vector<int> nodes;
    std::array<int, 30> c{};
    std::queue<int> que({s});
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      nodes.emplace_back(u);
      for (int i = 0; i < 30; ++i) {
        c[i] += res[u] >> i & 1 ? 1 : -1;
      }
      for (auto [v, w] : g[u]) {
        if (res[v] == -1) {
          res[v] = res[u] ^ w;
          que.emplace(v);
        } else if (res[v] != (res[u] ^ w)) {
          return false;
        }
      }
    }
    int x = 0;
    for (int i = 0; i < 30; ++i) {
      if (c[i] > 0) x ^= (1 << i);
    }
    for (int v : nodes) {
      res[v] ^= x;
    }
    return true;
  };

  for (int i = 0; i < n; ++i) {
    if (res[i] == -1 && !Solve(i)) {
      std::cout << "-1\n";
      return 0;
    }
  }

  for (int r : res) {
    std::cout << r << " ";
  }
  std::cout << "\n";

  return 0;
}