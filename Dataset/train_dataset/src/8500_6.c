#include <bits/stdc++.h>
int n;
std::vector<std::pair<int, int> > B[3], A[8][3];
inline bool chk(int x) {
  int p[3] = {0, 1, 2};
  do {
    for (int o = 0; o < 4; o++) {
      int u = A[o << 1][p[0]][x - 1].first + 1;
      int y = x, v = ((int)1e9 + 1);
      for (auto [i, j] : A[o << 1][p[1]])
        if (i >= u && !--y) {
          v = i + 1;
          break;
        }
      y = x;
      for (auto [i, j] : A[o << 1][p[2]])
        if (i >= v && !--y) return 1;
      y = x, v = ((int)1e9 + 1);
      for (auto [i, j] : A[o << 1 | 1][p[1]])
        if (i >= u && !--y) {
          v = j + 1;
          break;
        }
      y = x;
      for (auto [i, j] : A[o << 1 | 1][p[2]])
        if (i >= u && j >= v && !--y) return 1;
    }
  } while (std::next_permutation(p, p + 3));
  return 0;
}
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    int x, y, c;
    scanf("%d%d%d", &x, &y, &c);
    B[c - 1].emplace_back(x, y);
  }
  for (int oo = 0; oo < 2; oo++) {
    for (int o = 0; o < 2; o++) {
      for (int i = 0; i < 3; i++) {
        A[(oo << 2) | (o << 1)][i] = B[i];
        std::sort(A[(oo << 2) | (o << 1)][i].begin(),
                  A[(oo << 2) | (o << 1)][i].end());
        A[(oo << 2) | (o << 1) | 1][i] = B[i];
        std::sort(A[(oo << 2) | (o << 1) | 1][i].begin(),
                  A[(oo << 2) | (o << 1) | 1][i].end(),
                  [](std::pair<int, int> u, std::pair<int, int> v) {
                    return u.second == v.second ? u.first < v.first
                                                : u.second < v.second;
                  });
      }
      for (int i = 0; i < 3; i++)
        for (int j = 0; j < n / 3; j++) B[i][j].first *= -1;
    }
    for (int i = 0; i < 3; i++)
      for (int j = 0; j < n / 3; j++) std::swap(B[i][j].first, B[i][j].second);
  }
  int L = 1, R = n / 3, res = L;
  while (L <= R) {
    int mid = (L + R) >> 1;
    if (chk(mid))
      res = mid, L = mid + 1;
    else
      R = mid - 1;
  }
  printf("%d\n", 3 * res);
}
