#ifndef HOTAOSA_BINOMIAL_COEFFICIENT_H_
#define HOTAOSA_BINOMIAL_COEFFICIENT_H_

#include <cassert>
#include <vector>
//
#include <atcoder/modint>

namespace hotaosa {

template <typename T>
concept ModInt = requires { std::is_same_v<T, atcoder::modint>; };

template <ModInt T>
class BinomialCoefficient {
 public:
  explicit BinomialCoefficient(int size)
      : size_(size), fact_(size), fact_inv_(size) {
    assert(size_ > 1);
    fact_[0] = fact_[1] = fact_inv_[0] = fact_inv_[1] = 1;
    for (int i = 1; i < size_; ++i) {
      fact_[i] = fact_[i - 1] * i;
    }
    fact_inv_[size_ - 1] = fact_[size_ - 1].inv();
    for (int i = size_ - 1; i > 2; --i) {
      fact_inv_[i - 1] = fact_inv_[i] * i;
    }
  }

  BinomialCoefficient(const BinomialCoefficient&) = delete;
  BinomialCoefficient& operator=(const BinomialCoefficient&) = delete;
  BinomialCoefficient(BinomialCoefficient&&) = delete;
  BinomialCoefficient& operator=(BinomialCoefficient&&) = delete;

  T Factorial(int n) const {
    assert(n < size_);
    return fact_[n];
  }

  T Permutation(int n, int r) const {
    assert(n < size_ && r < size_);
    if (n < 0 || r < 0 || n < r) return T{0};
    return fact_[n] * fact_inv_[n - r];
  }

  T Combination(int n, int r) const { return Permutation(n, r) * fact_inv_[r]; }

  T Homogeneous(int n, int r) const { return Combination(n + r - 1, r); }

 private:
  const int size_;
  std::vector<T> fact_;
  std::vector<T> fact_inv_;
};

}  // namespace hotaosa

#endif  // HOTAOSA_BINOMIAL_COEFFICIENT_H_
