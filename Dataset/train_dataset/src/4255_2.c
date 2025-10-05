#include <bits/stdc++.h>
using namespace std;
int main() {
  int x, y, color[1000], ptos[1000], n, m;
  int ptosn[1000];
  vector<pair<int, int> > seg;
  map<int, int> mapa;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    cin >> ptos[i];
    ptosn[i] = ptos[i];
  }
  sort(ptos, ptos + n);
  for (int i = 0; i < m; ++i) cin >> x >> y;
  bool alter = false;
  for (int i = 0; i < n; ++i) {
    mapa[ptos[i]] = alter;
    alter = !alter;
  }
  for (int i = 0; i < n; ++i) cout << mapa[ptosn[i]] << ' ';
  cout << endl;
}
