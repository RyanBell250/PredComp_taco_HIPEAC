#include <bits/stdc++.h>
using namespace std;
const int imax = INT32_MAX;
const int imin = INT32_MIN;
const int mx = 3e5;
const long long int inf = 1e18;
template <class T>
void print(vector<T> vec) {
  for (T i : vec) cout << i << " ";
  cout << "\n";
}
template <class T>
void alloc(vector<vector<T>*> vec, T n) {
  for (auto v : vec) v->resize(n + 1);
}
string a, b;
int m, n;
bool isValid(int x, int y, vector<vector<bool>>& vis) {
  return x >= 0 && x < m && y >= 0 && y < n && !vis[x][y];
}
void dfs(int x, int y, vector<vector<bool>>& vis) {
  vis[x][y] = true;
  if (a[x] == '>') {
    if (isValid(x, y + 1, vis)) dfs(x, y + 1, vis);
  } else {
    if (isValid(x, y - 1, vis)) dfs(x, y - 1, vis);
  }
  if (b[y] == 'v') {
    if (isValid(x + 1, y, vis)) dfs(x + 1, y, vis);
  } else {
    if (isValid(x - 1, y, vis)) dfs(x - 1, y, vis);
  }
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  long long int t = 1;
  while (t--) {
    cin >> m >> n;
    cin >> a >> b;
    bool flag = true;
    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        vector<vector<bool>> vis(m, vector<bool>(n, false));
        dfs(i, j, vis);
        for (int p = 0; p < m; ++p) {
          for (int q = 0; q < n; ++q) {
            if (!vis[p][q]) {
              flag = false;
              break;
            }
          }
        }
      }
    }
    cout << (flag ? "YES" : "NO") << "\n";
  }
  return 0;
}
