#include <bits/stdc++.h>
using namespace std;
template <typename T>
using minpq = priority_queue<T, vector<T>, greater<T>>;
const int N = 1e6 + 5;
int dsu[N];
int trace(int x) { return dsu[x] < 0 ? x : dsu[x] = trace(dsu[x]); }
void join(int x, int y) {
  if ((x = trace(x)) == (y = trace(y))) return;
  if (dsu[x] > dsu[y]) swap(x, y);
  dsu[x] += dsu[y];
  dsu[y] = x;
}
int solve(int n, int m) {
  fill(dsu, dsu + m, -1);
  for (int i = (0); i < (m); i++) {
    int x = (i + 2 * (n - 1)) % (2 * (m - 1));
    if (x >= m) x = 2 * (m - 1) - x;
    join(i, x);
    x = (i - 2 * (n - 1)) % (2 * (m - 1));
    if (x < 0) x += 2 * (m - 1);
    if (x >= m) x = 2 * (m - 1) - x;
    join(i, x);
  }
  int ans = 0;
  for (int i = (0); i < (m); i++) {
    ans += (dsu[i] < 0);
  }
  return ans;
}
int n, m;
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> m;
  cout << solve(min(n, m), max(m, n)) << '\n';
}
