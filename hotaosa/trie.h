#ifndef HOTAOSA_TRIE_H_
#define HOTAOSA_TRIE_H_

#include <array>
#include <memory>
#include <string_view>
#include <vector>

namespace hotaosa {

template <int kNumChar, char kBase>
class Trie {
 public:
  Trie(const Trie&) = delete;
  Trie& operator=(const Trie&) = delete;
  Trie(Trie&&) = delete;
  Trie& operator=(Trie&&) = delete;

  Trie() : root_(std::make_unique<Node>(nullptr)) {}

  void Insert(std::string_view word) {
    Node* p = root_.get();
    p->prefix_count++;
    for (char c : word) {
      const int idx = c - kBase;
      if (!p->children[idx]) {
        p->children[idx] = std::make_unique<Node>(p);
      }
      p = p->children[idx].get();
      p->prefix_count++;
    }
    p->is_end = true;
  }

  bool Contains(std::string_view word) {
    Node* p = root_.get();
    for (char c : word) {
      const int idx = c - kBase;
      if (!p->children[idx]) return false;
      p = p->children[idx].get();
    }
    return p->is_end;
  }

  bool ContainsPrefix(std::string_view word) {
    Node* p = root_.get();
    for (char c : word) {
      const int idx = c - kBase;
      if (!p->children[idx]) return false;
      p = p->children[idx].get();
    }
    return true;
  }

  int LongestCommonPrefixWith(std::string_view word) {
    std::shared_ptr<Node> p = root_;
    const int len = static_cast<int>(word.size());
    for (int i = 0; i < len; ++i) {
      const int idx = word[i] - kBase;
      if (!p->children[idx]) return i;
      p = p->children[idx];
    }
    return static_cast<int>(word.size());
  }

 private:
  struct Node {
    int prefix_count;
    bool is_end;
    Node* parent;
    std::array<std::unique_ptr<Node>, kNumChar> children;

    Node(Node* p) : prefix_count(0), is_end(false), parent(p), children() {}
  };

  std::unique_ptr<Node> root_;
};

}  // namespace hotaosa

#endif  // HOTAOSA_TRIE_H_