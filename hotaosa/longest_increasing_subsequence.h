#ifndef HOTAOSA_LONGEST_INCREASING_SUBSEQUENCE_H_
#define HOTAOSA_LONGEST_INCREASING_SUBSEQUENCE_H_

#include <algorithm>
#include <iterator>
#include <ranges>
#include <vector>

namespace hotaosa {

template <std::random_access_iterator It, std::sentinel_for<It> Sent>
std::vector<std::iter_value_t<It>> LongestIncreasingSubsequence(It start,
                                                                Sent end) {
  using T = std::iter_value_t<It>;
  const int n = std::distance(start, end);

  std::vector<int> tails;
  tails.reserve(n);

  std::vector<int> prev(n, -1);
  int i = 0;
  for (It it = start; it != end; ++it, ++i) {
    const T& x = *it;

    auto cmp = [start](int idx, const T& val) { return *(start + idx) < val; };

    auto pos_it = std::lower_bound(tails.begin(), tails.end(), x, cmp);
    if (pos_it == tails.end()) {
      tails.emplace_back(i);
    } else {
      *pos_it = i;
    }
    const int k = std::distance(tails.begin(), pos_it);
    if (k > 0) {
      prev[i] = tails[k - 1];
    }
  }

  std::vector<T> lis;
  lis.reserve(tails.size());
  if (!tails.empty()) {
    for (int cur = tails.back(); cur != -1; cur = prev[cur]) {
      lis.emplace_back(*(start + cur));
    }
    std::reverse(lis.begin(), lis.end());
  }
  return lis;
}

template <std::ranges::input_range Range>
auto LongestIncreasingSubsequence(const Range& r) {
  return LongestIncreasingSubsequence(std::ranges::begin(r),
                                      std::ranges::end(r));
}

}  // namespace hotaosa

#endif  // HOTAOSA_LONGEST_INCREASING_SUBSEQUENCE_H_
