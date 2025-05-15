#ifndef HOTAOSA_REROOTING_TREE_H_
#define HOTAOSA_REROOTING_TREE_H_

#include <functional>
#include <ranges>
#include <vector>

namespace hotaosa {

template <typename T, typename U>
class RerootingTree {
 public:
  RerootingTree(const RerootingTree&) = delete;
  RerootingTree& operator=(const RerootingTree&) = delete;
  RerootingTree(RerootingTree&&) = delete;
  RerootingTree& operator=(RerootingTree&&) = delete;

  RerootingTree(int size, std::function<T(T, T)> merge_func,
                std::function<T(T, U)> edge_func, T identity)
      : size_(size),
        identity_(identity),
        tree_(size),
        dp_(size, identity),
        dp_sub_(size, identity),
        merge_func_(std::move(merge_func)),
        edge_func_(std::move(edge_func)) {}

  void AddEdge(int u, int v, U d) {
    tree_[u].emplace_back(v, d, identity_, identity_);
    tree_[v].emplace_back(u, d, identity_, identity_);
  }

  std::vector<T> Solve() {
    PreWalk(0, -1);
    Walk(0, -1, identity_);
    return dp_;
  }

 private:
  struct Edge {
    int to;
    U data;
    T dp;
    T ndp;
  };

  void PreWalk(int v, int par) {
    for (const auto& e : tree_[v]) {
      if (e.to == par) continue;
      PreWalk(e.to, v);
      dp_sub_[v] = merge_func_(dp_sub_[v], edge_func_(dp_sub_[e.to], e.data));
    }
  }

  void Walk(int v, int par, T top) {
    T buff = identity_;
    for (auto& e : tree_[v]) {
      e.ndp = buff;
      e.dp = edge_func_(par == e.to ? top : dp_sub_[e.to], e.data);
      buff = merge_func_(buff, e.dp);
    }
    dp_[v] = buff;

    buff = identity_;
    for (auto& e : tree_[v] | std::views::reverse) {
      if (e.to != par) Walk(e.to, v, merge_func_(e.ndp, buff));
      e.ndp = merge_func_(e.ndp, buff);
      buff = merge_func_(buff, e.dp);
    }
  }

  int size_;
  T identity_;
  std::vector<std::vector<Edge>> tree_;
  std::vector<T> dp_;
  std::vector<T> dp_sub_;
  std::function<T(T, T)> merge_func_;
  std::function<T(T, U)> edge_func_;
};

}  // namespace hotaosa

#endif  // HOTAOSA_REROOTING_TREE_H_