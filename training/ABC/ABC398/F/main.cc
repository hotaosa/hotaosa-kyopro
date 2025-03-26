#include <algorithm>
#include <iostream>
#include <string>
//
#include <atcoder/string>

int main() {
  std::string s;
  std::cin >> s;
  const int n = s.size();

  std::string t{s};
  std::reverse(t.begin(), t.end());
  t += "$" + s;

  const auto z = atcoder::z_algorithm(t);
  int len = 0;
  for (int i = 1; i <= n; ++i) {
    if (z[n * 2 + 1 - i] == i) {
      len = i;
    }
  }

  std::cout << s << t.substr(len, n - len) << "\n";
  return 0;
}