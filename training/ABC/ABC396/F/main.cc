#include <iostream>
#include <ranges>
#include <vector>

#include "inversion_number.h"

int main() {
  int n, m;
  std::cin >> n >> m;
  std::vector<int> a(n);
  for (auto &e : a) {
    std::cin >> e;
  }

  std::vector<int> cl(m, 0), cr(m, 0);
  for (int x : a) ++cr[x];

  std::vector<int> diff(m, 0);
  for (int i = 0; i < n; ++i) {
    --cr[a[i]];
    if (a[i] > 0) {
      diff[m - a[i]] += (i - cl[a[i]]) - (n - 1 - i - cr[a[i]]);
    }
    ++cl[a[i]];
  }

  int64_t res = hotaosa::InversionNumber(a);
  for (int d : diff) {
    res += d;
    std::cout << res << "\n";
  }

  return 0;
}