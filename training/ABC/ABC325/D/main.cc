#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

int main() {
  std::cin.tie(nullptr);
  std::ios::sync_with_stdio(false);

  int n;
  std::cin >> n;

  std::vector<std::pair<int64_t, int64_t>> items;
  items.reserve(n);

  for (int i = 0; i < n; ++i) {
    int64_t t, d;
    std::cin >> t >> d;
    items.emplace_back(t, t + d);
  }
  std::sort(std::rbegin(items), std::rend(items));

  std::priority_queue<int64_t, std::vector<int64_t>, std::greater<>> waits;
  int64_t now{0};

  int res = 0;
  while (!items.empty() || !waits.empty()) {
    while (!waits.empty() && waits.top() < now) waits.pop();
    while (!items.empty() && items.back().first == now) {
      waits.emplace(items.back().second);
      items.pop_back();
    }
    if (waits.empty()) {
      if (!items.empty()) now = items.back().first;
    } else {
      ++res;
      waits.pop();
      ++now;
    }
  }

  std::cout << res << "\n";
  return 0;
}