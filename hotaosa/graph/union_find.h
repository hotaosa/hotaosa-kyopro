#ifndef HOTAOSA_GRAPH_UNION_FIND_H_
#define HOTAOSA_GRAPH_UNION_FIND_H_

#include <cassert>
#include <utility>
#include <vector>

#include "hotaosa/util/arighmetic.h"

namespace hotaosa {

class UnionFind {
 public:
  UnionFind(const UnionFind&) = delete;
  UnionFind& operator=(const UnionFind&) = delete;
  UnionFind(UnionFind&&) = delete;
  UnionFind& operator=(UnionFind&&) = delete;

  explicit UnionFind(int n) : n_(n) { assert(n_ > 0); }

  int Root(int v) {
    assert(v >= 0 && v < n_);
    if (par_[v] == -1) {
      return v;
    }
    return par_[v] = Root(par_[v]);
  }

  bool Same(int u, int v) {
    assert(u >= 0 && u < n_);
    assert(v >= 0 && v < n_);
    return Root(u) == Root(v);
  }

  bool Merge(int u, int v) {
    assert(u >= 0 && u < n_);
    assert(v >= 0 && v < n_);
    u = Root(u);
    v = Root(v);
    if (u == v) return false;
    if (size_[u] < size_[v]) {
      std::swap(u, v);
    }
    par_[v] = u;
    size_[u] += size_[v];
    return true;
  }

  int Size(int v) {
    assert(v >= 0 && v < n_);
    return size_[Root(v)];
  }

 private:
  int n_;
  std::vector<int> par_;
  std::vector<int> size_;
};

template <arithmetic T>
class PotentialUnionFind {
 public:
  PotentialUnionFind(const PotentialUnionFind&) = delete;
  PotentialUnionFind& operator=(const PotentialUnionFind&) = delete;
  PotentialUnionFind(PotentialUnionFind&&) = delete;
  PotentialUnionFind& operator=(PotentialUnionFind&&) = delete;

  explicit PotentialUnionFind(int n) : n_(n) {
    assert(n_ > 0);
    par_.assign(n_, -1);
    rank_.assign(n_, 0);
    diff_.assign(n_, T{0});
  }

  int Root(int v) {
    assert(v >= 0 && v < n_);
    if (par_[v] == -1) {
      return v;
    } else {
      int r = Root(par_[v]);
      diff_[v] += diff_[par_[v]];
      return par_[v] = r;
    }
  }

  T Weight(int v) {
    assert(v >= 0 && v < n_);
    (void)Root(v);
    return diff_[v];
  }

  bool Same(int u, int v) {
    assert(u >= 0 && u < n_);
    assert(v >= 0 && v < n_);
    return Root(u) == Root(v);
  }

  bool Merge(int u, int v, T w) {
    assert(u >= 0 && u < n_);
    assert(v >= 0 && v < n_);
    w += Weight(u) - Weight(v);
    u = Root(u);
    v = Root(v);
    if (u == v) {
      return false;
    }
    if (rank_[u] < rank_[v]) {
      std::swap(u, v);
      w = -w;
    }
    if (rank_[u] == rank_[v]) ++rank_[u];
    par_[v] = u;
    diff_[v] = w;
    return true;
  }

  T Dist(int u, int v) {
    assert(u >= 0 && u < n_);
    assert(v >= 0 && v < n_);
    return Weight(u) - Weight(v);
  }

 private:
  int n_;
  std::vector<int> par_;
  std::vector<int> rank_;
  std::vector<T> diff_;
};

}  // namespace hotaosa

#endif  // HOTAOSA_GRAPH_UNION_FIND_H_