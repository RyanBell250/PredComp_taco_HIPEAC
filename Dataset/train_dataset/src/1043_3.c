#include <bits/stdc++.h>
using namespace std;
int a[4];
map<int, int> ma[4];
vector<int> ve[4];
vector<int> siz[4];
void fa(int p, int a, int s) {
  if (ma[p].count(a) > 0) return;
  ma[p][a] = s;
  if (a % 2 == 0) {
    fa(p, a / 2, s + 1);
  }
  if (a % 3 == 0) {
    fa(p, 2 * (a / 3), s + 1);
  }
}
void init() {
  for (int k = 0; k < 4; k++) {
    fa(k, a[k], 0);
  }
  for (int k = 0; k < 4; k++) {
    for (map<int, int>::iterator it = ma[k].begin(); it != ma[k].end(); it++) {
      ve[k].push_back(it->first);
      siz[k].push_back(it->second);
    }
  }
}
int res = 0;
long long bw;
map<long long, int> mf;
void solve() {
  res = 1e9;
  bw = -1;
  int sa1, sb1, sa2, sb2;
  long long w;
  for (int i = 0; i < ve[0].size(); i++) {
    for (int j = 0; j < ve[1].size(); j++) {
      w = (long long)ve[0][i] * ve[1][j];
      mf[w] = siz[0][i] + siz[1][j];
    }
  }
  int rp = 0;
  for (int i = 0; i < ve[2].size(); i++) {
    for (int j = 0; j < ve[3].size(); j++) {
      w = (long long)ve[2][i] * ve[3][j];
      if (mf.count(w) > 0) {
        rp = mf[w] + siz[2][i] + siz[3][j];
        if (res > rp) {
          bw = w;
          res = rp;
          sa2 = ve[2][i];
          sb2 = ve[3][j];
        }
      }
    }
  }
  if (res == 1e9) {
    cout << -1 << endl;
    return;
  }
  for (int i = 0; i < ve[0].size(); i++) {
    for (int j = 0; j < ve[1].size(); j++) {
      w = (long long)ve[0][i] * ve[1][j];
      if (w == bw) {
        sa1 = ve[0][i];
        sb1 = ve[1][j];
      }
    }
  }
  cout << res << endl;
  cout << sa1 << " " << sb1 << endl;
  cout << sa2 << " " << sb2 << endl;
}
int main() {
  for (int k = 0; k < 4; k++) {
    cin >> a[k];
  }
  init();
  solve();
  return 0;
}
