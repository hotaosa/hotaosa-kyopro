#ifndef HOTAOSA_COMPRESSION_H_
#define HOTAOSA_COMPRESSION_H_

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace hotaosa {

template <typename T>
int Compression(std::vector<T> *v) {
  auto tmp = *v;
  std::sort(std::begin(tmp), std::end(tmp));
  tmp.erase(std::unique(std::begin(tmp), std::end(tmp)), std::end(tmp));

  int size = static_cast<int>(std::size(tmp));
  std::unordered_map<T, int> id;
  for (int i = 0; i < size; ++i) {
    id[tmp[i]] = i;
  }
  for (auto &e : *v) {
    e = id[e];
  }
  return size;
}

}  // namespace hotaosa

#endif  // HOTAOSA_COMPRESSION_H_