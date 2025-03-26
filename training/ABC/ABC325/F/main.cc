#include <array>
#include <iostream>
#include <vector>

template <class T>
inline bool UpdateMin(T a, T *b) {
  if (a < *b) {
    *b = a;
    return true;
  }
  return false;
}

int main() {
  int n;
  std::cin >> n;

  std::vector<int> d(n);
  for (auto &e : d) std::cin >> e;
  std::array<int, 2> l, k;
  std::array<int64_t, 2> c;
  for (int i = 0; i < 2; ++i) {
    std::cin >> l[i] >> c[i] >> k[i];
  }

  constexpr int INF = 1 << 30;
  std::vector dp(n + 1, std::vector<int>(k[0] + 1, INF));
  dp[0][0] = 0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= k[0]; ++j) {
      if (dp[i][j] == INF) continue;
      for (int x = 0; j + x <= k[0]; ++x) {
        int y = std::max(0, (d[i] - l[0] * x + l[1] - 1) / l[1]);
        if (dp[i][j] + y <= k[1]) UpdateMin(dp[i][j] + y, &dp[i + 1][j + x]);
      }
    }
  }

  constexpr int64_t LINF{1LL << 60};
  int64_t res{LINF};
  for (int i = 0; i <= k[0]; ++i) {
    if (dp[n][i] < INF) {
      UpdateMin(c[0] * i + c[1] * dp[n][i], &res);
    }
  }

  std::cout << (res < LINF ? res : -1) << "\n";
  return 0;
}