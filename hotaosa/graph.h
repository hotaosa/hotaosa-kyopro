#ifndef HOTAOSA_GRAPH_H_
#define HOTAOSA_GRAPH_H_

#include <algorithm>
#include <cassert>
#include <concepts>
#include <deque>
#include <numeric>
#include <queue>
#include <vector>

#include "hotaosa/arighmetic.h"
#include "hotaosa/union_find.h"
#include "hotaosa/update_min_max.h"

namespace hotaosa {

template <arithmetic T>
struct Edge {
  int from;
  int to;
  T weight;

  Edge(int from, int to, T weight) : from(from), to(to), weight(weight) {}
  Edge(int to, T weight) : from(-1), to(to), weight(weight) {}
};

template <arithmetic T>
class Graph {
 public:
  Graph(const Graph &) = delete;
  Graph &operator=(const Graph &) = delete;
  Graph(Graph &&) = delete;
  Graph &operator=(Graph &&) = delete;

  explicit Graph(int n) : n_(n) {
    assert(n_ > 0);
    g_.resize(n);
  }
  explicit Graph(const std::vector<std::vector<Edge<T>>> &g)
      : n_(std::size(g)), g_(g) {
    assert(n_ > 0);
  }

  // lowercase to use std::size(graph);
  size_t size() const { return static_cast<size_t>(n_); }

  size_t Size() const { return size(); }

  void AddEdge(Edge<T> e) {
    assert(e.from >= 0 && e.from < n_);
    assert(e.to >= 0 && e.to < n_);
    g_[e.from].emplace_back(e);
  }

  void AddEdge(int u, int v, T w) {
    assert(u >= 0 && u < n_);
    assert(v >= 0 && v < n_);
    g_[u].emplace_back(u, v, w);
  }

  bool BellmanFord(int s, std::vector<T> *dist) const {
    assert(s >= 0 && s < n_);
    dist->assign(n_, kInf);
    (*dist)[s] = T{0};

    bool updated = false;
    for (int i = 0; i < n_; ++i) {
      updated = false;
      for (int v = 0; v < n_; ++v) {
        if ((*dist)[v] == kInf) continue;
        for (const auto &e : g_[v]) {
          updated |= UpdateMin((*dist)[v] + e.weight, &(*dist)[e.to]);
        }
      }
      if (!updated) return true;
    }
    return !updated;
  }

  std::vector<T> Dijkstra(int s) const {
    // requires negative-edge does not exist
    assert(s >= 0 && s < n_);
    using Pair = std::pair<T, int>;
    std::vector<T> dist(n_, kInf);
    dist[s] = T{0};

    std::priority_queue<Pair, std::vector<Pair>, std::greater<>> pque{
        {dist[s], s}};

    while (!pque.empty()) {
      const auto [d, v] = pque.top();
      pque.pop();
      if (d > dist[v]) continue;
      for (const auto &e : g_[v]) {
        if (UpdateMin(dist[v] + e.weight, &dist[e.to])) {
          pque.emplace(dist[e.to], e.to);
        }
      }
    }
    return dist;
  }

  std::vector<T> BreadthFirstSearch(int s) const
    requires std::integral<T>
  {
    // requires all edge weights are 1 (ignore Edge::weight)
    assert(s >= 0 && s < n_);
    std::vector<T> dist(n_, kInf);
    dist[s] = 0;

    std::queue<int> que{s};

    while (!que.empty()) {
      const int v = que.front();
      que.pop();
      for (const auto &e : g_[v]) {
        if (dist[e.to] == kInf) {
          dist[e.to] = dist[v] + 1;
          que.emplace(e.to);
        }
      }
    }
    return dist;
  }

  std::vector<int> ZeroOneBreadthFirstSearch(int s) const
    requires std::integral<T>
  {
    // requires all edge weights are 0 or 1
    assert(s >= 0 && s < n_);
    std::vector<T> dist(n_, kInf);

    std::deque<int> dq{s};

    while (!dq.empty()) {
      const int v = dq.front();
      dq.pop_front();
      for (const auto &e : g_[v]) {
        assert(e.weight == T{0} || e.weight == T{1});
        if (e.weight == T{0} && UpdateMin(dist[v], &dist[e.to])) {
          dq.emplace_front(e.to);
        } else if (e.weight == T{1} && UpdateMin(dist[v] + 1, &dist[e.to])) {
          dq.emplace_back(e.to);
        }
      }
    }
    return dist;
  }

  T Kruskal(Graph<T> *g) const {
    std::vector<Edge<T>> edges;
    edges.reserve(std::accumulate(
        std::begin(g_), std::end(g_),
        [](size_t acc, const auto &v) { return acc + v.size(); }));

    for (const auto &v : g_) {
      edges.insert(std::end(edges), std::begin(v), std::end(v));
    }

    T total_weight = T{0};
    UnionFind uf(n_);
    for (const auto &e : edges) {
      if (uf.Merge(e.from, e.to)) {
        total_weight += e.w;
        g[e.from].emplace_back(e.to);
        g[e.to].emplace_back(e.from);
      }
    }
    return total_weight;
  }

 private:
  static constexpr T kInf = SafeInf<T>();
  int n_;
  std::vector<std::vector<Edge<T>>> g_;
};

}  // namespace hotaosa

#endif  // HOTAOSA_GRAPH_H_
