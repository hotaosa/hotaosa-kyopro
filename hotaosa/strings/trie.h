#ifndef HOTAOSA_STRINGS_TRIE_H_
#define HOTAOSA_STRINGS_TRIE_H_

#include <array>
#include <memory>
#include <ranges>
#include <string_view>
#include <vector>

namespace hotaosa {

template <int kNumChar, char kBase>
class TrieTree {
 public:
  TrieTree(const TrieTree&) = delete;
  TrieTree& operator=(const TrieTree&) = delete;
  TrieTree(TrieTree&&) = delete;
  TrieTree& operator=(TrieTree&&) = delete;

  TrieTree() : root_(std::make_unique<Node>()) {}

  void Insert(std::string_view word) {
    Node* p = root_.get();
    p->count++;
    for (char c : word) {
      const int idx = c - kBase;
      if (!p->children[idx]) {
        p->children[idx] = std::make_unique<Node>();
      }
      p = p->children[idx].get();
      p->count++;
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

  int LongestCommonPrefixWith(std::string_view word) {
    Node* p = root_.get();
    // for (auto [i, c] : std::views::enumerate(word)) {
    //   const int idx = c - kBase;
    //   if (!p->children[idx]) return i;
    //   p = p->children[idx].get();
    // }
    const int len = static_cast<int>(word.size());
    for (int i = 0; i < len; ++i) {
      const int idx = word[i] - kBase;
      if (!p->children[idx]) return i;
      p = p->children[idx].get();
    }
    return static_cast<int>(word.size());
  }

  std::vector<int> CountCommonWords(std::string_view word) {
    Node* p = root_.get();
    std::vector<int> count(word.size(), 0);
    // for (auto [i, c] : std::views::enumerate(word)) {
    //   const int idx = c - kBase;
    //   if (!p->children[idx]) return count;
    //   p = p->children[idx].get();
    //   count[i] = p->count;
    // }
    const int len = static_cast<int>(word.size());
    for (int i = 0; i < len; ++i) {
      const int idx = word[i] - kBase;
      if (!p->children[idx]) return count;
      p = p->children[idx].get();
      count[i] = p->count;
    }
    return count;
  }

 private:
  struct Node {
    int count;
    bool is_end;
    std::array<std::unique_ptr<Node>, kNumChar> children;

    Node() : count(0), is_end(false), children() {}
  };

  std::unique_ptr<Node> root_;
};

template <int kNumChar, char kBase>
class ParentLinkedTrieTree {
 public:
  ParentLinkedTrieTree(const ParentLinkedTrieTree&) = delete;
  ParentLinkedTrieTree& operator=(const ParentLinkedTrieTree&) = delete;
  ParentLinkedTrieTree(ParentLinkedTrieTree&&) = delete;
  ParentLinkedTrieTree& operator=(ParentLinkedTrieTree&&) = delete;

  ParentLinkedTrieTree() : root_(std::make_shared<Node>(nullptr)) {}

  void Insert(std::string_view word) {
    std::shared_ptr<Node> p = root_;
    p->count++;
    for (char c : word) {
      const int idx = c - kBase;
      if (!p->children[idx]) {
        p->children[idx] = std::make_shared<Node>(p);
      }
      p = p->children[idx];
      p->count++;
    }
    p->is_end = true;
  }

  bool Contains(std::string_view word) {
    std::shared_ptr<Node> p = root_;
    for (char c : word) {
      const int idx = c - kBase;
      if (!p->children[idx]) return false;
      p = p->children[idx];
    }
    return p->is_end;
  }

 private:
  struct Node {
    int count;
    bool is_end;
    std::shared_ptr<Node> parent;
    std::array<std::shared_ptr<Node>, kNumChar> children;

    Node(std::shared_ptr<Node> p)
        : parent(p), count(0), is_end(false), children() {}
  };

  std::shared_ptr<Node> root_;
};

}  // namespace hotaosa

#endif  // HOTAOSA_STRINGS_TRIE_H_