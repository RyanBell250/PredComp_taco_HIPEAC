#include <bits/stdc++.h>
using namespace std;
const int N = 210;
int n, m;
long long k, f[N], d[N], h[N], qy[2][2];
string p[2], s[2], str[17], suf[N * 10], ans;
inline bool cmp(string a, string b) {
  for (int i = 0; i < min(a.length(), b.length()); i++) {
    if (a[i] == b[i]) continue;
    if (a[i] < b[i])
      return 1;
    else
      return 0;
  }
  return a.length() < b.length();
}
int Try(string a) {
  int res = 0;
  for (int i = 0; i < a.length(); i++) {
    if (i + ans.length() - 1 >= a.length()) break;
    bool flag = 1;
    for (int j = 0; j < ans.length(); j++)
      if (a[i + j] != ans[j]) flag = 0;
    res += flag;
  }
  return res;
}
long long solve() {
  int len = ans.length();
  memset(d, 0, sizeof(d));
  memset(h, 0, sizeof(h));
  memset(qy, 0, sizeof(qy));
  p[0].clear();
  p[1].clear();
  s[0].clear();
  s[1].clear();
  d[14] = h[14] = 0;
  d[15] = h[15] = 1;
  for (int i = 0; i < len - 1; i++)
    p[0].push_back(str[14][i]), p[1].push_back(str[15][i]);
  for (int i = 1; i <= len - 1; i++)
    s[0].push_back(str[14][str[14].length() - len + i]);
  for (int i = 1; i <= len - 1; i++)
    s[1].push_back(str[15][str[15].length() - len + i]);
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) qy[i][j] = Try(p[i] + s[j]);
  f[14] = Try(str[14]);
  f[15] = Try(str[15]);
  for (int i = 16; i <= n; i++) {
    h[i] = h[i - 1];
    d[i] = d[i - 2];
    f[i] = f[i - 1] + f[i - 2];
    f[i] += qy[d[i]][h[i]];
    if (f[i] > 1e18) return f[i];
  }
  return f[n];
}
int main() {
  scanf("%d%lld%d", &n, &k, &m);
  str[0] = "0";
  str[1] = "1";
  for (int i = 2; i <= 15; i++) str[i] = str[i - 2] + str[i - 1];
  if (n <= 15) {
    for (int i = 0; i < str[n].length(); i++)
      for (int j = i; j < str[n].length(); j++) suf[i + 1].push_back(str[n][j]);
    sort(suf + 1, suf + str[n].length() + 1, cmp);
    for (int i = 0; i < min(m, (int)suf[k].length()); i++)
      printf("%c", suf[k][i]);
    return 0;
  }
  for (int i = 1; i <= m; i++) {
    ans.push_back('0');
    long long z = solve();
    if (z < k) {
      k -= z;
      ans.pop_back();
      ans.push_back('1');
    }
    int flag = 1;
    for (int i = suf[n].length() - ans.length(), j = 0; j < suf[n].length();
         i++) {
      if (ans[j] != suf[n][i]) flag = false;
      j++;
    }
    k -= flag;
    if (k == 0) {
      for (int i = 0; i < ans.length(); i++) printf("%c", ans[i]);
      return 0;
    }
  }
  for (int i = 0; i < ans.length(); i++) printf("%c", ans[i]);
  return 0;
}
