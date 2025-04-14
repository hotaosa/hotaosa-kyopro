#ifndef HOTAOSA_DATASTRUCTURE_RANGE_SET_RANGE_SUM_H_
#define HOTAOSA_DATASTRUCTURE_RANGE_SET_RANGE_SUM_H_

#include <limits>
#include <vector>
//
#include <atcoder/lazysegtree>

namespace hotaosa {

template <typename T>
class RangeSetRangeSum {
 public:
  explicit RangeSetRangeSum(int n) : seg_(n) {}
  explicit RangeSetRangeSum(const std::vector<T> &v) {
    std::vector<S> s;
    s.reserve(v.size());
    for (auto &x : v) {
      s.emplace_back(S{x, 1});
    }
    seg_ = LazySegtree(s);
  }
  explicit RangeSetRangeSum(std::vector<T> &&v) {
    std::vector<S> s;
    s.reserve(v.size());
    for (auto &&x : v) {
      s.emplace_back(S{x, 1});
    }
    seg_ = LazySegtree(s);
  }

  RangeSetRangeSum(const RangeSetRangeSum &) = delete;
  RangeSetRangeSum &operator=(const RangeSetRangeSum &) = delete;
  RangeSetRangeSum(RangeSetRangeSum &&) = delete;
  RangeSetRangeSum &operator=(RangeSetRangeSum &&) = delete;

  void set(int p, T x) { seg_.set(p, S{x, 1}); }

  T get(int p) { return seg_.get(p).val; }

  T prod(int l, int r) { return seg_.prod(l, r).val; }

  T all_prod(int l, int r) { return seg_.all_prod().val; }

  void apply(int p, T a, T b) { seg_.apply(p, F{a, b}); }

  void apply(int l, int r, T a, T b) { seg_.apply(l, r, F{a, b}); }

  template <bool (*g)(T)>
  int max_right(int l) {
    return seg_.max_right(l, [](S x) { return g(x.val); });
  }

  template <class G>
  int max_right(int l, G g) {
    return seg_.max_right(l, g);
  }

  template <bool (*g)(T)>
  int min_left(int r) {
    return seg_.min_left(r, [](S x) { return g(x.val); });
  }

  template <class G>
  int min_left(int r, G g) {
    return seg_.min_left(r, g);
  }

 private:
  struct S {
    T val;
    int size;
  };
  static S Op(S l, S r) { return S{l.val + r.val, l.size + r.size}; }
  static constexpr S E() { return S{T{0}, 0}; }
  static S Map(T f, S x) { return f == Id() ? x : S{f * x.size, x.size}; }
  static T Composite(T f, T g) { return f + g; }
  static constexpr T Id() { return std::numeric_limits<T>::lowest(); }
  using LazySegtree = atcoder::lazy_segtree<S, Op, E, F, Map, Composite, Id>;

  LazySegtree seg_;
};

}  // namespace hotaosa

#endif  // HOTAOSA_DATASTRUCTURE_RANGE_SET_RANGE_SUM_H_
