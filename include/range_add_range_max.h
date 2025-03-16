#ifndef HOTAOSA_RANGE_ADD_RANGE_MAX_H_
#define HOTAOSA_RANGE_ADD_RANGE_MAX_H_

#include <limits>
#include <vector>
//
#include <atcoder/lazysegtree>

namespace hotaosa {

namespace range_add_range_max {

template <typename T>
T Max(T a, T b) {
  return a > b ? a : b;
}

template <typename T>
constexpr T MinValue() {
  return std::numeric_limits<T>::lowest();
}

template <typename T>
T Add(T a, T b) {
  return a + b;
}

template <typename T>
constexpr T Zero() {
  return T{0};
}

}  // namespace range_add_range_max

template <typename T>
using RangeAddRangeMax =
    atcoder::lazy_segtree<T, range_add_range_max::Max,
                          range_add_range_max::MinValue, T,
                          range_add_range_max::Add, range_add_range_max::Add,
                          range_add_range_max::Zero>;

}  // namespace hotaosa

#endif  // HOTAOSA_RANGE_ADD_RANGE_MAX_H_
