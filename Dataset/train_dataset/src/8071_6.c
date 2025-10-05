#include <bits/stdc++.h>
using namespace std;
void deb(vector<vector<int>> &matr) {
  int n = matr.size() - 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << matr[i][j] << ' ';
    }
    cout << endl;
  }
}
int main() {
  int n;
  cin >> n;
  vector<vector<int>> matr(n + 1, vector<int>(n + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      char c;
      cin >> c;
      if (c == '#') {
        matr[i][j] = 1;
      } else {
        matr[i][j] = 0;
      }
    }
  }
  bool ans = false;
  vector<vector<int>> m = matr;
  for (int k = 0; k <= n * n; k++) {
    int cp = k;
    matr = m;
    for (int i = 1; i <= n && cp; i++) {
      for (int j = 1; j <= n && cp; j++) {
        if (i - 1 < 1 || i + 1 > n || j - 1 < 1 || j + 1 > n ||
            matr[i][j] != 0 || matr[i - 1][j] != 0 || matr[i + 1][j] != 0 ||
            matr[i][j - 1] != 0 || matr[i][j + 1] != 0)
          continue;
        matr[i][j]++;
        matr[i - 1][j]++;
        matr[i + 1][j]++;
        matr[i][j - 1]++;
        matr[i][j + 1]++;
        cp--;
      }
    }
    bool ans1 = true;
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (matr[i][j] > 1) ans1 = false;
        if (m[i][j] == 0 && matr[i][j] == 0) ans1 = false;
      }
    }
    if (ans1) {
      ans = true;
      break;
    }
  }
  if (ans) {
    cout << "YES\n";
  } else {
    cout << "NO\n";
  }
  return 0;
}
