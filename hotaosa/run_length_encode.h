#ifndef HOTAOSA_RUN_LENGTH_ENCODE_H_
#define HOTAOSA_RUN_LENGTH_ENCODE_H_

#include <ranges>
#include <utility>
#include <vector>

namespace hotaosa {

template <std::input_iterator It, std::sentinel_for<It> Sent>
std::vector<std::pair<std::iter_value_t<It>, int>> RunLengthEncode(It start,
                                                                   Sent end) {
  using T = std::iter_value_t<It>;
  std::vector<std::pair<T, int>> res;

  if (start == end) return res;

  T current = *start;
  int count = 1;

  for (++start; start != end; ++start) {
    if (*start == current) {
      ++count;
    } else {
      res.emplace_back(current, count);
      current = *start;
      count = 1;
    }
  }

  res.emplace_back(current, count);
  return res;
}

template <std::ranges::input_range Range>
auto RunLengthEncode(const Range &r) {
  return RunLengthEncode(std::ranges::begin(r), std::ranges::end(r));
}

}  // namespace hotaosa

#endif  // HOTAOSA_RUN_LENGTH_ENCODE_H_