#include <bits/stdc++.h>
using namespace std;
const int MAXNODES = 3e6;
int n, m, q, x, mx = 0;
string s, ans;
vector<pair<int, string>> v;
int par[MAXNODES];
void Init() {
  for (int i = 0; i < MAXNODES; ++i) par[i] = i;
}
int findleader(int i) { return par[i] == i ? i : par[i] = findleader(par[i]); }
void joinset(int i, int j) {
  int l1 = findleader(i), l2 = findleader(j);
  par[l1] = l2;
}
signed main() {
  ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  Init();
  ans = string(MAXNODES, 'a');
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> s >> q;
    m = s.size();
    while (q--) {
      cin >> x;
      x--;
      mx = max(mx, x + m);
      int st = findleader(x);
      int sz = s.size();
      int en = x + sz;
      while (st < en) {
        ans[st] = s[st - x];
        joinset(st, st + 1);
        st = findleader(st);
      }
    }
  }
  cout << ans.substr(0, mx) << '\n';
}
