#include <bits/stdc++.h>
using namespace std;
int const mod = 1e9 + 7;
inline void SAFE_ADD(int& a, int b) {
  a += b;
  if (a >= mod) a -= mod;
}
struct Matr {
  vector<vector<int> > _data;
  Matr(int sz) : _data(sz, vector<int>(sz, 0)) {}
  void ones() {
    for (int i = 0; i < _data.size(); ++i) _data[i][i] = 1;
  }
};
Matr operator*(Matr const& a, Matr const& b) {
  int n = a._data.size();
  Matr ans(n);
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      for (int k = 0; k < n; ++k) {
        SAFE_ADD(ans._data[i][k], a._data[i][j] * 1LL * b._data[j][k] % mod);
      }
  return ans;
}
inline int getnum(char c) {
  if (c >= 'a' && c <= 'z')
    return c - 'a';
  else
    return 26 + c - 'A';
}
Matr pow(Matr const& a, long long b) {
  Matr ans(a._data.size());
  ans.ones();
  Matr tmp(a);
  while (b) {
    if (b & 1) ans = ans * tmp;
    tmp = tmp * tmp;
    b >>= 1;
  }
  return ans;
}
int main() {
  ios_base::sync_with_stdio(false);
  long long n;
  int m, k;
  cin >> n >> m >> k;
  if (n == 1) {
    cout << m << '\n';
    return 0;
  };
  Matr a(m);
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j) a._data[i][j] = 1;
  for (int i = 0; i < k; ++i) {
    string tmp;
    cin >> tmp;
    a._data[getnum(tmp[0])][getnum(tmp[1])] = 0;
  }
  a = pow(a, n - 1);
  int ans = 0;
  for (int i = 0; i < m; ++i)
    for (int j = 0; j < m; ++j) SAFE_ADD(ans, a._data[i][j]);
  cout << ans << endl;
  return 0;
}
