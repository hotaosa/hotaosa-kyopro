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
  std::string s;
  int k;
  std::cin >> s >> k;

  const int n = s.size();
  std::vector dp(n + 1, std::vector<int>(n + 1));
  for (int i = 0; i < n; ++i) {
    for (int j = i; j <= n; ++j) {
      dp[i][j] = j - i;
    }
  }

  for (int r = 1; r <= n; ++r) {
    for (int l = r - 1; l >= 0; --l) {
      for (int m = l + 1; m < r; ++m) {
        UpdateMin(dp[l][m] + dp[m][r], &dp[l][r]);
        if (s[l] != 'o' || s[m] != 'f') continue;
        if (dp[l + 1][m] == 0 && dp[m + 1][r] <= k) {
          dp[l][r] = 0;
        }
      }
    }
  }

  std::cout << dp[0][n] << "\n";
  return 0;
}