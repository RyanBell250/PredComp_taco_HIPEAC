#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const double EPS = 1e-7;
const double PI = 3.1415926535897932384626433832795;
inline int get_int() {
  int res, t = 1;
  char c;
  while (!isdigit(c = getchar()))
    if (c == '-') t = -1;
  for (res = c - '0'; isdigit(c = getchar());) res = res * 10 + c - '0';
  return res * t;
}
const int MAXN = 200000;
int n;
vector<pair<int, int> > st;
vector<int> G[MAXN + 10];
int col[MAXN + 10];
bool dfs(int u, int c) {
  col[u] = c;
  for (int i = 0; i < (int)(G[u].size()); i++) {
    int v = G[u][i];
    if (col[v] == c)
      return 0;
    else if (col[v] == 0 && !dfs(v, 3 - c))
      return 0;
  }
  return 1;
}
int main() {
  n = get_int();
  for (int i = 0; i < (int)(n); i++) {
    int x = get_int(), y = get_int();
    st.push_back(pair<int, int>(x << 1, i << 1));
    st.push_back(pair<int, int>(y << 1 | 1, i << 1 | 1));
    G[i << 1].push_back(i << 1 | 1);
    G[i << 1 | 1].push_back(i << 1);
  }
  sort(st.begin(), st.end());
  for (int i = 0; i < (int)(n); i++) {
    int u = st[i << 1].second;
    int v = st[i << 1 | 1].second;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  for (int i = 0; i < (int)(n << 1); i++) {
    if (!col[i]) dfs(i, 1);
  }
  for (int i = 0; i < (int)(n); i++) {
    cout << col[i << 1] - 1 << ' ';
  }
  cout << endl;
  return 0;
}
