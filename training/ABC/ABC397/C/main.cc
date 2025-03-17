#include <iostream>
#include <vector>

int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (auto &e : a) {
    std::cin >> e;
    --e;
  }

  std::vector<int> c(n - 1), cnt(n, 0);
  {
    int cur = 0;
    std::vector<int> cnt(n, 0);
    for (int i = 0; i < n - 1; ++i) {
      if (!cnt[a[i]]++) ++cur;
      c[i] = cur;
    }
  }
  {
    int cur = 0;
    std::vector<int> cnt(n, 0);
    for (int i = n - 1; i > 0; --i) {
      if (!cnt[a[i]]++) ++cur;
      c[i - 1] += cur;
    }
  }

  int res = 0;
  for (int i = 0; i < n - 1; ++i) {
    res = std::max(res, c[i]);
  }

  std::cout << res << "\n";
  return 0;
}