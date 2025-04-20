#ifndef HOTAOSA_STRINGS_STR_JOIN_H_
#define HOTAOSA_STRINGS_STR_JOIN_H_

#include <concepts>
#include <ranges>
#include <sstream>

namespace hotaosa {

template <std::input_iterator It, std::sentinel_for<It> Sent>
std::string StrJoin(It begin, Sent end, const std::string& separator) {
  std::ostringstream oss;
  if constexpr (std::floating_point<std::iter_reference_t<It>>) {
    oss.setf(std::ios::fixed);
    oss.precision(15);
  }

  if (begin != end) {
    oss << *(begin++);
  }
  while (begin != end) {
    oss << separator << *(begin++);
  }
  return oss.str();
}

template <std::ranges::input_range Range>
std::string StrJoin(const Range& range, const std::string& separator) {
  return StrJoin(std::ranges::begin(range), std::ranges::end(range), separator);
}

}  // namespace hotaosa

#endif  // HOTAOSA_STRINGS_STR_JOIN_H_
