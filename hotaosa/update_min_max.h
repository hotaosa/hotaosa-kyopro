#ifndef HOTAOSA_UPDATE_MIN_MAX_H_
#define HOTAOSA_UPDATE_MIN_MAX_H_

#include <concepts>

namespace hotaosa {

template <std::totally_ordered T>
bool UpdateMin(T a, T *b) {
  if (a < *b) {
    *b = a;
    return true;
  }
  return false;
}

template <std::totally_ordered T>
bool UpdateMax(T a, T *b) {
  if (a > *b) {
    *b = a;
    return true;
  }
  return false;
}

}  // namespace hotaosa

#endif  // HOTAOSA_UPDATE_MIN_MAX_H_