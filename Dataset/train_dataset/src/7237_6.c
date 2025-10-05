#include <bits/stdc++.h>
using namespace std;
map<pair<int, int>, int> mp;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const int maxn = 100 + 100 + 10;
int a[maxn][maxn], t;
int main() {
  ios_base::sync_with_stdio(false);
  cin >> a[100][100] >> t;
  bool flag = true;
  while (flag) {
    flag = false;
    for (int i = 1; i <= 200; i++)
      for (int j = 1; j <= 200; j++) {
        if (a[i][j] >= 4) {
          flag = true;
          int x = a[i][j] / 4;
          a[i + 1][j] += x;
          a[i][j + 1] += x;
          a[i - 1][j] += x;
          a[i][j - 1] += x;
          a[i][j] -= x * 4;
        }
      }
  }
  for (int i = 1; i <= t; i++) {
    int x, y;
    cin >> x >> y;
    if (x > -100 && x < 100 && y > -100 && y < 100)
      cout << a[100 + x][100 + y] << endl;
    else
      cout << "0" << endl;
  }
  return 0;
}
