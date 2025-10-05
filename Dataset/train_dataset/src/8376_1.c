#include <bits/stdc++.h>
using namespace std;
template <typename t>
using V = vector<t>;
int n, m;
V<int> tab[2];
V<int> val[2];
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    int p;
    cin >> p;
    tab[i % 2].push_back(p);
  }
  for (int i = 0; i < 2; ++i) {
    for (int k = 0; k < (1 << tab[i].size()); ++k) {
      long long sum = 0;
      for (int j = 0; j < tab[i].size(); ++j)
        if ((1 << j) & k) sum += tab[i][j];
      sum %= m;
      val[i].push_back(sum);
    }
  }
  int res = 0;
  sort((val[1]).begin(), (val[1]).end());
  for (int i = 0; i < val[0].size(); ++i) {
    int szuk = m - val[0][i];
    int lo = -1;
    for (int b = val[1].size(); b >= 1; b /= 2)
      while (lo + b < val[1].size() and val[1][lo + b] < szuk) lo += b;
    res = max(res, val[1][lo] + val[0][i]);
  }
  cout << res << '\n';
}
