#include <bits/stdc++.h>
using namespace std;
const int mod = (int)1e9 + 7, maxn = 200005, ln = 17;
const int shift = 30, etf = mod - 1;
const long long int inf = (long long int)1e18 + 1;
const double PI = (double)3.141592653589793238, EPSILON = 1e-10;
int col[maxn], mark[maxn];
set<int> s[maxn];
vector<int> graph[maxn], nodescol[maxn];
int main() {
  int n, m, mx = -1, c = 0;
  cin >> n >> m;
  for (int i = 1; i < n + 1; i++) {
    scanf("%d", &col[i]);
    nodescol[col[i]].push_back(i);
    mark[col[i]] = 1;
  }
  for (int i = 1; i < m + 1; i++) {
    int x, y;
    scanf("%d", &x);
    scanf("%d", &y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }
  for (int i = 1; i < maxn; i++) {
    if (mark[i]) {
      for (int j = 0; j < nodescol[i].size(); j++) {
        int node = nodescol[i][j];
        for (int k = 0; k < graph[node].size(); k++) {
          int p = graph[node][k];
          if (col[p] != i) {
            s[i].insert(col[p]);
          }
        }
      }
      if (mx < (int)s[i].size()) {
        mx = (int)s[i].size();
        c = i;
      }
    }
  }
  cout << c << endl;
  return 0;
}
