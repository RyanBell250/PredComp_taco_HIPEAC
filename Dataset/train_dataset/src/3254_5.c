#include <bits/stdc++.h>
using namespace std;
const int N = 1 << 20;
long long here[N + 100];
int n, m;
long double ter[N + 100];
int go(string &s1, string &s2) {
  int val = 0;
  for (int i = int(0); i < int(m); ++i)
    if (s1[i] == s2[i]) val |= (1 << i);
  return val;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout << fixed << setprecision(14);
  cin >> n;
  vector<string> vec(n);
  for (int i = int(0); i < int(n); ++i) cin >> vec[i];
  m = int((vec[0]).size());
  for (int i = int(0); i < int(n); ++i)
    for (int j = int(i + 1); j < int(n); ++j)
      if (i != j) {
        int mask = go(vec[i], vec[j]);
        here[mask] |= (1LL << i) | (1LL << j);
      }
  int lim = (1 << m) - 1;
  for (int mask = int(lim); mask >= int(0); mask--)
    for (int i = int(0); i < int(m); ++i) here[mask] |= here[mask | (1 << i)];
  ter[lim] = 0;
  for (int i = int(lim - 1); i >= int(0); i--) {
    ter[i] = __builtin_popcountll(here[i]);
    long double val = 0;
    for (int j = int(0); j < int(m); ++j)
      if (1 - ((i >> j) & 1)) val += ter[i | (1 << j)];
    ter[i] += val / (m - __builtin_popcount(i));
  }
  cout << ter[0] / n << endl;
  return 0;
}
