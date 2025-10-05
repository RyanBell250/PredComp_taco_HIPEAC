#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<long double> > dp;
long double calc(long double x, long double y) {
  if (dp[x][y] != -1.0) return dp[x][y];
  if (x == 0) return dp[x][y] = n / y + calc(x, y - 1);
  if (y == 0) return dp[x][y] = n / x + calc(x - 1, y);
  return dp[x][y] = (n * n) / (n * n - (n - x) * (n - y)) +
                    (calc(x - 1, y - 1) * x * y + calc(x - 1, y) * x * (n - y) +
                     calc(x, y - 1) * y * (n - x)) /
                        (n * n - (n - x) * (n - y));
}
int main() {
  int m, r, c;
  cin >> n >> m;
  vector<bool> row(n, false);
  vector<bool> col(n, false);
  for (int i = 0; i < m; ++i) {
    cin >> r >> c;
    row[r - 1] = true;
    col[c - 1] = true;
  }
  r = 0;
  c = 0;
  for (int i = 0; i < n; ++i) {
    if (row[i]) ++r;
    if (col[i]) ++c;
  }
  dp = vector<vector<long double> >(n + 1, vector<long double>(n + 1, -1.0));
  dp[0][0] = 0;
  cout.setf(ios::fixed);
  cout.precision(16);
  cout << calc(n - r, n - c) << endl;
}
