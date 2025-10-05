#include <bits/stdc++.h>
using namespace std;
int n, m;
int c[10];
string s[10];
int ind[5];
int res;
void solve(int cur, int st) {
  if (cur == c[0]) {
    string cs = s[0];
    for (int i = 0; i < n; i++) cs[i] = cs[i] == '1' ? '0' : '1';
    for (int i = 0; i < c[0]; i++) cs[ind[i]] = cs[ind[i]] == '1' ? '0' : '1';
    int num = 0;
    bool ok = true;
    for (int i = 1; i < m; i++) {
      int num = 0;
      for (int j = 0; j < n; j++)
        if (cs[j] == s[i][j]) num++;
      if (num != c[i]) {
        ok = false;
        break;
      }
    }
    if (ok) res++;
    return;
  }
  for (int i = st; i < n; i++) {
    ind[cur] = i;
    solve(cur + 1, i + 1);
  }
}
int main() {
  cin >> n >> m;
  int i, j;
  for (i = 0; i < m; i++) cin >> s[i] >> c[i];
  solve(0, 0);
  cout << res;
  return 0;
}
