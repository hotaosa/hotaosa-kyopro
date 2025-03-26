#include <iostream>
#include <queue>
#include <vector>

struct Edge {
  int to;
  int64_t w;
};

std::vector<int64_t> Dijcstra(const std::vector<std::vector<Edge>> &g, int s) {
  const int n = std::size(g);
  std::vector<int64_t> dist(n, 1LL << 60);
  dist[s] = 0;

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>>
      pque;
  pque.emplace(std::make_pair(dist[s], s));

  while (!pque.empty()) {
    const auto [d, v] = pque.top();
    pque.pop();
    if (d > dist[v]) continue;
    for (const auto &e : g[v]) {
      if (dist[v] + e.w < dist[e.to]) {
        dist[e.to] = dist[v] + e.w;
        pque.emplace(std::make_pair(dist[e.to], e.to));
      }
    }
  }

  return dist;
}

int main() {
  int n;
  int64_t a, b, c;
  std::cin >> n >> a >> b >> c;

  std::vector<std::vector<Edge>> g(n * 2);
  for (int i = 0; i < n; ++i) {
    g[i].emplace_back(i + n, 0);
    for (int j = 0; j < n; ++j) {
      int64_t d;
      std::cin >> d;
      if (i == j) continue;
      g[i].emplace_back(j, d * a);
      g[i + n].emplace_back(j + n, d * b + c);
    }
  }

  std::cout << Dijcstra(g, 0).back() << "\n";
  return 0;
}
