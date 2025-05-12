#ifndef HOTAOSA_DATASTRUCTURE_BINARY_TRIE_H_
#define HOTAOSA_DATASTRUCTURE_BINARY_TRIE_H_

#include <array>
#include <cassert>
#include <limits>
#include <memory>

namespace hotaosa {

template <std::integral T>
class BinaryTrie {
 public:
  BinaryTrie(const BinaryTrie&) = delete;
  BinaryTrie& operator=(const BinaryTrie&) = delete;
  BinaryTrie(BinaryTrie&&) = delete;
  BinaryTrie& operator=(BinaryTrie&&) = delete;

  BinaryTrie() : root_(std::make_unique<Node>(nullptr)) {}

  int Count() const { return root_->prefix_count; }

  void Insert(T value) { Insert(value, 1); }

  void Insert(T value, int count) {
    Node* p = root_.get();
    p->prefix_count += count;
    for (size_t i = 0; i < kMaxBit; ++i) {
      const int b = value >> (kMaxBit - 1 - i) & 1;
      if (!p->children[b]) {
        p->children[b] = std::make_unique<Node>(p);
      }
      p = p->children[b].get();
      p->prefix_count += count;
    }
  }

  void Erase(T value) { Erase(value, 1); }

  void Erase(T value, int count) {
    Node* p = Find(value);
    if (!p || p->prefix_count == 0) return;
    int count_sub = std::min(p->prefix_count, count);
    while (p) {
      p->prefix_count -= count_sub;
      p = p->parent;
    }
  }

  void EraseAll(T value) {
    Node* p = Find(value);
    if (!p || p->prefix_count == 0) return;
    int count_sub = p->prefix_count;
    while (p) {
      p->prefix_count -= count_sub;
      p = p->parent;
    }
  }

  bool Contains(T value) const {
    Node* p = Find(value);
    return p && p->prefix_count > 0;
  }

  int Count(T value) const {
    Node* p = Find(value);
    if (!p) return 0;
    return p->prefix_count;
  }

  T MinValue() const { return KthValue(1); }

  T MaxValue() const { return KthValue(root_->prefix_count); };

  T KthValue(int k) const { return XorKthValue(k, 0); }

  int CountLessThan(T value) const { return XorCountLessThan(value, 0); }

  T XorMinValue(T x) const { return XorKthValue(1, x); }

  T XorMaxValue(T x) const { return XorKthValue(root_->prefix_count, x); }

  T XorKthValue(int k, T x) const {
    assert(k >= 1 && k <= root_->prefix_count);
    Node* p = root_.get();
    T value{0};
    for (size_t i = 0; i < kMaxBit; ++i) {
      const int xb = x >> (kMaxBit - 1 - i) & 1;
      Node* lch = p->children[xb].get();
      Node* rch = p->children[xb ^ 1].get();
      if (lch && lch->prefix_count >= k) {
        p = lch;
      } else {
        assert(rch);
        if (lch) {
          k -= lch->prefix_count;
        }
        p = rch;
        value |= T{1} << (kMaxBit - 1 - i);
      }
    }
    return value;
  }

  int XorCountLessThan(T value, T x) const {
    Node* p = root_.get();
    int count = 0;
    for (size_t i = 0; i < kMaxBit; ++i) {
      const int b = value >> (kMaxBit - 1 - i) & 1;
      const int xb = x >> (kMaxBit - 1 - i) & 1;
      Node* next_child = p->children[b ^ xb].get();
      Node* opposite_child = p->children[b ^ xb ^ 1].get();
      if (b ^ xb && opposite_child) {
        count += opposite_child->prefix_count;
      }
      if (!next_child) break;
      p = next_child;
    }
    return count;
  }

 private:
  static constexpr size_t kMaxBit = std::numeric_limits<T>::digits;

  struct Node {
    int prefix_count;
    Node* parent;
    std::array<std::unique_ptr<Node>, 2> children;

    Node(Node* p) : prefix_count(0), parent(p), children() {}
  };

  Node* Find(T x) const {
    Node* p = root_.get();
    for (size_t i = 0; i < kMaxBit; ++i) {
      const int b = x >> (kMaxBit - 1 - i) & 1;
      if (!p->children[b]) return nullptr;
      p = p->children[b].get();
    }
    return p;
  }

  std::unique_ptr<Node> root_;
};

}  // namespace hotaosa

#endif  // HOTAOSA_DATASTRUCTURE_BINARY_TRIE_H_