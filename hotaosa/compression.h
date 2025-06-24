#ifndef HOTAOSA_COMPRESSION_H_
#define HOTAOSA_COMPRESSION_H_

#include <algorithm>
#include <concepts>
#include <ranges>
#include <unordered_map>
#include <vector>

namespace hotaosa {

template <typename T>
concept CompressionCompatible =
    std::movable<T> && std::totally_ordered<T> && requires(T x) {
      { std::hash<T>{}(x) } -> std::convertible_to<std::size_t>;
    };

template <std::ranges::random_access_range Range>
  requires std::ranges::sized_range<Range> &&
           CompressionCompatible<std::ranges::range_value_t<Range>>
int Compression(Range* v) {
  using T = std::ranges::range_value_t<Range>;
  std::vector<T> tmp(v->begin(), v->end());
  std::sort(tmp.begin(), tmp.end());
  tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());

  int size = static_cast<int>(tmp.size());
  std::unordered_map<T, int> id;
  for (int i = 0; i < size; ++i) {
    id[tmp[i]] = i;
  }
  for (auto& e : *v) {
    e = id[e];
  }
  return size;
}

template <std::ranges::random_access_range Outer>
  requires std::ranges::random_access_range<
               std::ranges::range_value_t<Outer>> &&
           std::ranges::sized_range<std::ranges::range_value_t<Outer>> &&
           CompressionCompatible<
               std::ranges::range_value_t<std::ranges::range_value_t<Outer>>>
int Compression(Outer* v) {
  using T = std::ranges::range_value_t<std::ranges::range_value_t<Outer>>;
  auto joined = std::views::join(*v);
  std::vector<T> flat(joined.begin(), joined.end());

  int size = Compression(&flat);
  auto it = flat.begin();
  for (auto& row : *v) {
    for (auto& e : row) {
      e = *it++;
    }
  }
  return size;
}

}  // namespace hotaosa

#endif  // HOTAOSA_COMPRESSION_H_