#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>

struct Point {
  int x;
  int y;
  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }
  void Move(const Point &d) {
    x += d.x;
    y += d.y;
  }
};

struct PointHash {
  size_t operator()(const Point &p) const {
    auto h = std::hash<int>{};
    return h(p.x) * 10007 + h(p.y);
  }
};

int main() {
  int n, rt, ct;
  std::string s;
  std::cin >> n >> rt >> ct >> s;

  Point takahashi{rt, ct};
  Point fire{0, 0};

  std::unordered_map<char, Point> mp{
      {'N', Point{1, 0}},
      {'E', Point{0, -1}},
      {'W', Point{0, 1}},
      {'S', Point{-1, 0}},
  };

  std::unordered_set<Point, PointHash> smokes{fire};

  std::string res{};
  res.reserve(n);
  for (auto ch : s) {
    const auto d = mp[ch];
    takahashi.Move(d);
    fire.Move(d);
    res += smokes.contains(takahashi) ? '1' : '0';
    smokes.insert(fire);
  }

  std::cout << res << "\n";
  return 0;
}