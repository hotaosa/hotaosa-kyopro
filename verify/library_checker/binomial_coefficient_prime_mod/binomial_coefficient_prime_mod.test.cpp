#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient_prime_mod"
#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>
//
#include <atcoder/modint>

#include "binomial_coefficient.h"

using mint = atcoder::modint;

int main() {
  std::cin.tie(nullptr);
  std::ios_base::sync_with_stdio(false);

  int t, m;
  std::cin >> t >> m;
  mint::set_mod(m);

  int size = 0;
  std::vector<int> n(t), k(t);
  for (int i = 0; i < t; ++i) {
    int64_t ni, ki;
    std::cin >> ni >> ki;
    n[i] = ni % m;
    k[i] = ki % m;
    size = std::max({size, n[i], k[i]});
  }

  hotaosa::BinomialCoefficient<mint> binom(size + 1);

  for (auto [ni, ki] : std::views::zip(n, k)) {
    std::cout << binom.Combination(ni, ki).val() << "\n";
  }

  return 0;
}