#include <iostream>
#include <set>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector exist_edge(n, std::vector<bool>(n, false));
  std::vector<std::vector<int>> graph(n);

  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    std::cin >> u >> v;
    graph[--u].emplace_back(--v);
    graph[v].emplace_back(u);
    exist_edge[u][v] = exist_edge[v][u] = true;
  }

  std::vector<int> color(n, 0);
  auto Walk = [&](auto self, int v, int p) -> void {
    for (int nv : graph[v]) {
      if (nv == p) continue;
      color[nv] = color[v] ^ 1;
      self(self, nv, v);
    }
  };
  Walk(Walk, 0, -1);

  std::set<std::pair<int, int>> s;
  for (int u = 0; u < n - 1; ++u) {
    for (int v = u + 1; v < n; ++v) {
      if (!exist_edge[u][v] && color[u] != color[v]) {
        s.insert({u + 1, v + 1});
      }
    }
  }

  if (s.size() & 1) {
    auto it = s.begin();
    std::cout << "First\n";
    std::cout << it->first << " " << it->second << std::endl;
    s.erase(it);
  } else {
    std::cout << "Second" << std::endl;
  }

  while (true) {
    int u, v;
    std::cin >> u >> v;
    if (u == -1) return 0;
    if (u > v) std::swap(u, v);
    s.erase(s.find({u, v}));
    auto it = s.begin();
    std::cout << it->first << " " << it->second << std::endl;
    s.erase(it);
  }

  return 0;
}