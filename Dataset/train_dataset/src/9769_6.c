#include <bits/stdc++.h>
using namespace std;
int main() {
  int mat[220][220] = {{0}};
  cin >> mat[110][110];
  bool change = true;
  while (change) {
    change = false;
    for (int i = 1; i < 218; i++) {
      for (int j = 1; j < 218; j++) {
        if (mat[i][j] >= 4) {
          change = true;
          int add = mat[i][j] / 4;
          mat[i][j] %= 4;
          mat[i + 1][j] += add;
          mat[i - 1][j] += add;
          mat[i][j + 1] += add;
          mat[i][j - 1] += add;
        }
      }
    }
  }
  int Q;
  cin >> Q;
  while (Q--) {
    int i, j;
    cin >> i >> j;
    if (abs(i) > 100 || abs(j) > 100)
      cout << 0 << '\n';
    else
      cout << mat[i + 110][j + 110] << '\n';
  }
  return 0;
}
