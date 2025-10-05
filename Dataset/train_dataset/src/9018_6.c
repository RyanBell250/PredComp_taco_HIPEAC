#include <bits/stdc++.h>
using namespace std;
char M[26][26];
int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      cin >> M[i][j];
    }
  int r = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      for (int w = 1; w < n + 1; ++w)
        for (int h = 1; h < m + 1; ++h) {
          bool g = true;
          for (int ii = i; ii < i + w; ++ii)
            for (int jj = j; jj < j + h; ++jj) {
              if (M[ii][jj] - '0' || ii >= n || jj >= m) g = false;
            }
          if (g && r < w + h) r = w + h;
        }
  cout << 2 * r;
  return 0;
}
