#include <bits/stdc++.h>
using namespace std;
int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
int dy[] = {1, 0, -1, 0, 1, -1, 1, -1};
long long fix_mod(long long x, long long y) { return (y + x % y) % y; }
void fast() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
}
int idx[(int)1e5 + 10];
vector<vector<int>> edg;
int mem[(int)1e5 + 10];
int solve(int i) {
  int& ret = mem[i];
  if (~ret) return ret;
  ret = 0;
  for (auto v : edg[i]) {
    ret = max(ret, solve(v) + 1);
  }
  return ret;
}
int main() {
  fast();
  int n;
  cin >> n;
  vector<int> v(n);
  edg = vector<vector<int>>(n);
  memset(idx, -1, sizeof idx);
  memset(mem, -1, sizeof mem);
  for (int i = 0; i < n; i++) cin >> v[i], idx[v[i]] = i;
  for (int i = 2; i <= 1e5; i++) {
    int p = -1;
    for (int j = i; j <= 1e5; j += i) {
      if (idx[j] != -1) {
        if (p != -1) edg[p].push_back(idx[j]);
        p = idx[j];
      }
    }
  }
  int mx = 0;
  for (int i = 0; i < n; i++) mx = max(mx, solve(i) + 1);
  return cout << mx << "\n", 0;
  ;
}
