#include <algorithm>
#include <iostream>
#include <vector>

#include "convex_hull_trick.h"

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<int64_t> b(n), c(m);
  for (auto &e : b) std::cin >> e;
  for (auto &e : c) std::cin >> e;
  std::sort(std::rbegin(b), std::rend(b));

  hotaosa::ConvexHullTrick<int64_t> cht;
  for (int i = 0; i < n; ++i) {
    cht.Add(-i - 1, -b[i] * (i + 1));
  }

  for (int i = 0; i < m; ++i) {
    std::cout << -cht.Query(c[i]) << " ";
  }
  std::cout << "\n";

  return 0;
}