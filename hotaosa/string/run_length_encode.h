#ifndef HOTAOSA_STRING_RUN_LENGTH_ENCODE_H_
#define HOTAOSA_STRING_RUN_LENGTH_ENCODE_H_

#include <ranges>
#include <utility>
#include <vector>

namespace hotaosa {

template <std::input_iterator It, std::sentinel_for<It> Sent>
std::vector<std::pair<std::iter_value_t<It>, int>> RunLengthEncode(It begin,
                                                                   Sent end) {
  using T = std::iter_value_t<It>;
  std::vector<std::pair<T, int>> res;

  if (begin == end) return res;

  T current = *begin;
  int count = 1;

  for (++begin; begin != end; ++begin) {
    if (*begin == current) {
      ++count;
    } else {
      res.emplace_back(current, count);
      current = *begin;
      count = 1;
    }
  }

  res.emplace_back(current, count);
  return res;
}

template <std::ranges::input_range Range>
auto RunLengthEncode(const Range &range) {
  return RunLengthEncode(std::ranges::begin(range), std::ranges::end(range));
}

}  // namespace hotaosa

#endif  // HOTAOSA_STRING_RUN_LENGTH_ENCODE_H_