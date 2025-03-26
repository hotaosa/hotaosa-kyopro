#include <iostream>
#include <map>
#include <ranges>

int main() {
  int n;
  std::cin >> n;
  std::map<int, int> mp{{-1, -1}};
  for (int i = 0; i < n; ++i) {
    int a;
    std::cin >> a;
    if (mp.contains(a)) {
      mp[a] = 0;
    } else {
      mp[a] = i + 1;
    }
  }

  for (auto [k, v] : mp | std::views::reverse) {
    if (v != 0) {
      std::cout << v << "\n";
      return 0;
    }
  }

  return 0;
}