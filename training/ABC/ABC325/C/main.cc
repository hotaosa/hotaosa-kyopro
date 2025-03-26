#include <array>
#include <iostream>
#include <string>
#include <vector>
//
#include <atcoder/dsu>

int main() {
  int h, w;
  std::cin >> h >> w;

  int cnt = 0;
  std::vector sensor(h, std::vector<int>(w, -1));
  for (int i = 0; i < h; ++i) {
    std::string s;
    std::cin >> s;
    for (int j = 0; j < w; ++j) {
      if (s[j] == '#') {
        sensor[i][j] = cnt++;
      }
    }
  }

  std::array<int, 8> dr{-1, -1, -1, 0, 0, 1, 1, 1};
  std::array<int, 8> dc{-1, 0, 1, -1, 1, -1, 0, 1};

  atcoder::dsu uf(cnt);
  for (int r = 0; r < h; ++r) {
    for (int c = 0; c < w; ++c) {
      if (sensor[r][c] == -1) continue;
      for (int i = 0; i < 8; ++i) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < h && nc >= 0 && nc < w && sensor[nr][nc] != -1) {
          uf.merge(sensor[r][c], sensor[nr][nc]);
        }
      }
    }
  }

  std::cout << uf.groups().size() << "\n";
  return 0;
}