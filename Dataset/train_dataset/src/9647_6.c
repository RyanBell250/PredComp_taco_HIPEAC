#include <bits/stdc++.h>
using namespace std;
long long modpow(long long b, long long e, long long mod) {
  long long ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
int32_t main() {
  string r;
  cin >> r;
  vector<array<char, 3> > v;
  for (char i = 'a'; i <= 'z'; i++) {
    for (char j = 'a'; j <= 'z'; j++) {
      for (char k = 'a'; k <= 'z'; k++) {
        if (i != j && j != k && i != k) v.push_back({i, j, k});
      }
    }
  }
  string s[3];
  for (int i = 0; i < ((int)(r).size()); ++i) {
    for (int j = 0; j < (3); ++j) {
      s[j].push_back(v[i][j]);
    }
  }
  cout << "? " << s[0] << endl;
  string t[3];
  cin >> t[0];
  cout << "? " << s[1] << endl;
  cin >> t[1];
  cout << "? " << s[2] << endl;
  cin >> t[2];
  vector<int> perm((int)(r).size());
  for (int i = 0; i < ((int)(r).size()); ++i) {
    for (int j = 0; j < ((int)(r).size()); ++j) {
      bool can = true;
      for (int k = 0; k < (3); ++k) {
        if (s[k][i] != t[k][j]) can = false;
      }
      if (can) perm[i] = j;
    }
  }
  vector<int> pprm((int)(r).size());
  for (int i = 0; i < ((int)(r).size()); ++i) pprm[perm[i]] = i;
  string l = r;
  for (int i = 0; i < ((int)(r).size()); ++i) {
    l[pprm[i]] = r[i];
  }
  cout << "! " << l << endl;
}
