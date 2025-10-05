#include <bits/stdc++.h>
using namespace std;
int n;
int code[300];
vector<int> ft[11][11][4];
void update(int mul, int rem, char c, int idx, int val) {
  while (idx < ft[mul][rem][code[c]].size()) {
    ft[mul][rem][code[c]][idx] += val;
    idx += idx & (-idx);
  }
}
void update(int idx, char c, int val) {
  for (int i = 1; i <= 10; i++) {
    update(i, idx % i, c, (idx + i) / i, val);
  }
}
int query(int mul, int rem, char c, int idx) {
  int res = 0;
  while (idx) {
    res += ft[mul][rem][code[c]][idx];
    idx -= idx & (-idx);
  }
  return res;
}
int query(int mul, int rem, char c, int kir, int kan) {
  if (kan < kir)
    return 0;
  else
    return query(mul, rem, c, kan) - query(mul, rem, c, kir - 1);
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  string s;
  cin >> s;
  n = s.length();
  s = " " + s;
  code['A'] = 0;
  code['G'] = 1;
  code['C'] = 2;
  code['T'] = 3;
  for (int i = 1; i <= 10; i++) {
    for (int j = 0; j < i; j++) {
      for (int k = 0; k < 4; k++) ft[i][j][k].assign(150000 / i, 0);
    }
  }
  for (int i = 1; i <= n; i++) update(i, s[i], 1);
  int q;
  cin >> q;
  while (q--) {
    int tipe;
    cin >> tipe;
    if (tipe == 1) {
      int idx;
      char c;
      cin >> idx >> c;
      update(idx, s[idx], -1);
      s[idx] = c;
      update(idx, s[idx], 1);
    } else {
      int l, r;
      cin >> l >> r;
      string t;
      cin >> t;
      int mul = t.size();
      int res = 0;
      for (int i = 0; i < t.size(); i++) {
        res += query(mul, (l + i) % mul, t[i], (l + i + mul) / mul,
                     (r - ((l + i) % mul) + mul) / mul);
      }
      cout << res << "\n";
    }
  }
}
