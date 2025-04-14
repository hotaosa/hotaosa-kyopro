#ifndef HOTAOSA_DATASTRUCTURE_RANGE_ADD_RANGE_MAX_H_
#define HOTAOSA_DATASTRUCTURE_RANGE_ADD_RANGE_MAX_H_

#include <limits>
#include <vector>
//
#include <atcoder/lazysegtree>

namespace hotaosa {

template <typename T>
class RangeAddRangeMax {
 public:
  explicit RangeAddRangeMax(int n) : seg_(n) {}
  explicit RangeAddRangeMax(const std::vector<T> &v) : seg_(v) {}
  explicit RangeAddRangeMax(std::vector<T> &&v) : seg_(std::move(v)) {}

  RangeAddRangeMax(const RangeAddRangeMax &) = delete;
  RangeAddRangeMax &operator=(const RangeAddRangeMax &) = delete;
  RangeAddRangeMax(RangeAddRangeMax &&) = delete;
  RangeAddRangeMax &operator=(RangeAddRangeMax &&) = delete;

  void Set(int p, T x) { seg_.set(p, x); }

  T Get(int p) { return seg_.get(p); }

  T Max() { return seg_.all_prod(); }

  T Max(int l, int r) { return seg_.prod(l, r); }

  void Add(int p, T f) { seg_.apply(p, f); };

  void Add(int l, int r, T f) { seg_.apply(l, r, f); }

  template <bool (*g)(T)>
  int MaxRight(int l) {
    return seg_.max_right(l, [](T x) { return g(x); });
  }

  template <class G>
  int MaxRight(int l, G g) {
    return seg_.max_right(l, g);
  }

  template <bool (*g)(T)>
  int MinLeft(int r) {
    return seg_.min_left(r, [](T x) { return g(x); });
  }

  template <class G>
  int MinLeft(int r, G g) {
    return seg_.min_left(r, g);
  }

 private:
  static T Op(T l, T r) { return l > r ? l : r; }
  static constexpr T E() { return std::numeric_limits<T>::lowest(); }
  static T Map(T f, T x) { return f + x; }
  static T Composite(T f, T g) { return f + g; }
  static constexpr T Id() { return T{0}; }
  using LazySegtree = atcoder::lazy_segtree<T, Op, E, T, Map, Composite, Id>;

  LazySegtree seg_;
};

}  // namespace hotaosa

#endif  // HOTAOSA_DATASTRUCTURE_RANGE_ADD_RANGE_MAX_H_
