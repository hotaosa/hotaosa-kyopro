#include <iostream>
#include <vector>

#include "range_add_range_max.h"

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (auto &e : a) {
    std::cin >> e;
    --e;
  }

  std::vector<int> cl(n), cr(n);
  {
    int cur = 0;
    std::vector<int> cnt(n, 0);
    for (int i = 0; i < n; ++i) {
      if (!cnt[a[i]]++) ++cur;
      cl[i] = cur;
    }
  }
  {
    int cur = 0;
    std::vector<int> cnt(n, 0);
    for (int i = n - 1; i >= 0; --i) {
      if (!cnt[a[i]]++) ++cur;
      cr[i] = cur;
    }
  }

  hotaosa::RangeAddRangeMax<int> seg(cl);
  std::vector<int> pos(n, 0);
  int res = 0;

  for (int i = 0; i < n - 1; ++i) {
    seg.Add(pos[a[i]], i, 1);
    res = std::max(res, seg.Max(0, i) + cr[i + 1]);
    pos[a[i]] = i;
  }

  std::cout << res << "\n";
  return 0;
}