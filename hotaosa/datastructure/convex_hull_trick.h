#ifndef HOTAOSA_DATASTRUCTURE_CONVEX_HULL_TRICK_H_
#define HOTAOSA_DATASTRUCTURE_CONVEX_HULL_TRICK_H_

#include <cassert>
#include <concepts>
#include <deque>
#include <utility>

namespace hotaosa {

template <typename T>
class ConvexHullTrick {
 public:
  ConvexHullTrick() = default;

  ConvexHullTrick(const ConvexHullTrick&) = delete;
  ConvexHullTrick& operator=(const ConvexHullTrick&) = delete;

  ConvexHullTrick(ConvexHullTrick&&) = delete;
  ConvexHullTrick& operator=(ConvexHullTrick&&) = delete;

  bool empty() const noexcept { return std::empty(dq_); }

  void Clear() { dq_.clear(); }

  void Add(T a, T b) {
    Line line{a, b};
    if (this->empty()) {
      dq_.emplace_back(line);
      return;
    }
    if (dq_.front().a <= a) {
      if (dq_.front().a == a) {
        if (dq_.front().b <= b) return;
        dq_.pop_front();
      }
      while (dq_.size() >= 2 && L2IsNeeded(line, dq_[0], dq_[1])) {
        dq_.pop_front();
      }
      dq_.emplace_front(line);
    } else {
      assert(a <= dq_.back().a);
      if (dq_.back().a == a) {
        if (dq_.back().b <= b) return;
        dq_.pop_back();
      }
      while (dq_.size() >= 2 &&
             L2IsNeeded(dq_[dq_.size() - 2], dq_[dq_.size() - 1], line)) {
        dq_.pop_back();
      }
      dq_.emplace_back(line);
    }
  }

  T Query(T x) const {
    assert(!this->empty());
    int l = -1;
    int r = dq_.size() - 1;
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (dq_[m](x) >= dq_[m + 1](x)) {
        l = m;
      } else {
        r = m;
      }
    }
    return dq_[r](x);
  }

  T QueryInc(T x) {
    assert(!this->empty());
    while (dq_.size() >= 2 && dq_[0](x) >= dq_[1](x)) {
      dq_.pop_front();
    }
    return dq_.front().a * x + dq_.front().b;
  }

  T QueryDec(T x) {
    assert(!this->empty());
    while (dq_.size() >= 2 &&
           dq_[dq_.size() - 1](x) >= dq_[dq_.size() - 2](x)) {
      dq_.pop_back();
    }
    return dq_.back()(x);
  }

 private:
  struct Line {
    T a;
    T b;
    T operator()(T x) const { return a * x + b; }
  };

  int Sign(T x) const { return (x > T{0}) - (x < T{0}); }

  bool L2IsNeeded(const Line& l1, const Line& l2, const Line& l3) const {
    if constexpr (std::is_integral_v<T>) {
      if (l2.b == l1.b || l2.b == l3.b) {
        return Sign(l2.a - l1.a) * Sign(l3.b - l2.b) >=
               Sign(l3.a - l2.a) * Sign(l2.b - l1.b);
      }
      return static_cast<__int128_t>(l2.b - l1.b) * (l1.a - l3.a) >=
             static_cast<__int128_t>(l3.b - l1.b) * (l1.a - l2.a);
    } else {
      if (l2.b == l1.b || l2.b == l3.b) {
        return Sign(l2.a - l1.a) * Sign(l3.b - l2.b) >=
               Sign(l3.a - l2.a) * Sign(l2.b - l1.b);
      }
      return static_cast<long double>(l2.b - l1.b) * (l1.a - l3.a) >=
             static_cast<long double>(l3.b - l1.b) * (l1.a - l2.a);
    }
  }

  std::deque<Line> dq_;
};

}  // namespace hotaosa

#endif  // HOTAOSA_DATASTRUCTURE_CONVEX_HULL_TRICK_H_n