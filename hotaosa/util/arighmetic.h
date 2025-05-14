#ifndef HOTAOSA_UTIL_ARITHMETIC_H_
#define HOTAOSA_UTIL_ARITHMETIC_H_

#include <concepts>

namespace hotaosa {

template <typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;

template <arithmetic T>
constexpr T SafeInf() {
  // No overflow by (Inf + Inf)
  if constexpr (std::integral<T>) {
    return std::numeric_limits<T>::max() >> 1;
  } else {
    return std::numeric_limits<T>::max() / 10.0;
  }
}

}  // namespace hotaosa

#endif  // HOTAOSA_UTIL_ARITHMETIC_H_