#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:64000000")
using namespace std;
const int INF = (int)1E9;
const long long INF64 = (long long)1E18;
const long double EPS = 1E-9;
const long double PI = 3.1415926535897932384626433832795;
const int MAXN = 100100;
const int MAGIC = 10;
int n, m, col[MAXN], ans[MAXN];
vector<int> g[MAXN], c[2];
bool used[MAXN];
int DFS(int v, int color) {
  if (used[v]) return 0;
  col[v] = color;
  c[color].push_back(v);
  used[v] = true;
  int ans = 0;
  for (int i = 0; i < (int)(g[v].size()); i++) ans += DFS(g[v][i], color ^ 1);
  return ans;
}
pair<int, int> diff(vector<int> a, vector<int> b) {
  set<int> st((a).begin(), (a).end());
  for (int i = 0; i < (int)(b.size()); i++) st.erase(b[i]);
  return make_pair(*st.begin(), *(++st.begin()));
}
void erase(int v) {
  for (int i = 0; i < (int)(g[v].size()); i++) {
    int u = g[v][i];
    g[u].erase(find((g[u]).begin(), (g[u]).end(), v));
  }
}
void solve() {
  int one = -1;
  for (int i = 0; i < (int)(n); i++)
    if (!used[i]) {
      int cur = DFS(i, 0);
      if (cur == 1) one = i;
    }
  if (c[0].size() % 3 == 0) {
    int start = 0;
    for (int color = 0; color < (int)(2); color++) {
      for (int i = 0; i < (int)(c[color].size()); i++)
        ans[c[color][i]] = start + i / 3;
      start += (int)c[color].size() / 3;
    }
    cout << "YES" << endl;
    for (int i = 0; i < (int)(n); i++) printf("%d ", ans[i] + 1);
    exit(0);
  }
  if (one != -1) {
    c[col[one]].erase(find((c[col[one]]).begin(), (c[col[one]]).end(), one));
    ans[one] = n / 3 - 1;
    if (c[0].size() == 1) {
      ans[c[0].back()] = ans[one];
      c[0].pop_back();
      ans[c[1].back()] = ans[one];
      c[1].pop_back();
    } else if (c[0].size() == 2) {
      ans[c[0].back()] = ans[one];
      c[0].pop_back();
      ans[c[0].back()] = ans[one];
      c[0].pop_back();
    } else {
      ans[c[1].back()] = ans[one];
      c[1].pop_back();
      ans[c[1].back()] = ans[one];
      c[1].pop_back();
    }
    int start = 0;
    for (int color = 0; color < (int)(2); color++) {
      for (int i = 0; i < (int)(c[color].size()); i++)
        ans[c[color][i]] = start + i / 3;
      start += (int)c[color].size() / 3;
    }
    cout << "YES" << endl;
    for (int i = 0; i < (int)(n); i++) printf("%d ", ans[i] + 1);
    exit(0);
  }
  if (c[0].size() % 3 == 2) {
    swap(c[0], c[1]);
    for (int i = 0; i < (int)(n); i++) col[i] ^= 1;
  }
  for (int i = 0; i < (int)(c[0].size()); i++) {
    int v = c[0][i];
    if (int(g[v].size()) <= int(c[1].size()) - 2) {
      pair<int, int> dd = diff(c[1], g[v]);
      ans[v] = n / 3 - 1;
      ans[dd.first] = ans[v];
      ans[dd.second] = ans[v];
      c[0].erase(find((c[0]).begin(), (c[0]).end(), v));
      c[1].erase(find((c[1]).begin(), (c[1]).end(), dd.first));
      c[1].erase(find((c[1]).begin(), (c[1]).end(), dd.second));
      int start = 0;
      for (int color = 0; color < (int)(2); color++) {
        for (int i = 0; i < (int)(c[color].size()); i++)
          ans[c[color][i]] = start + i / 3;
        start += (int)c[color].size() / 3;
      }
      cout << "YES" << endl;
      for (int i = 0; i < (int)(n); i++) printf("%d ", ans[i] + 1);
      exit(0);
    }
  }
  swap(c[0], c[1]);
  for (int i = 0; i < (int)(n); i++) col[i] ^= 1;
  int cur = n / 3 - 1;
  for (int step = 0; step < (int)(2); step++) {
    bool ok = false;
    for (int i = 0; i < (int)(c[0].size()); i++) {
      int v = c[0][i];
      if (int(g[v].size()) <= int(c[1].size()) - 2) {
        pair<int, int> dd = diff(c[1], g[v]);
        ans[v] = cur;
        ans[dd.first] = cur;
        ans[dd.second] = cur;
        erase(v);
        erase(dd.first);
        erase(dd.second);
        c[0].erase(find((c[0]).begin(), (c[0]).end(), v));
        c[1].erase(find((c[1]).begin(), (c[1]).end(), dd.second));
        c[1].erase(find((c[1]).begin(), (c[1]).end(), dd.first));
        ok = true;
        if (step == 1) {
          int start = 0;
          for (int color = 0; color < (int)(2); color++) {
            for (int i = 0; i < (int)(c[color].size()); i++)
              ans[c[color][i]] = start + i / 3;
            start += (int)c[color].size() / 3;
          }
          cout << "YES" << endl;
          for (int i = 0; i < (int)(n); i++) printf("%d ", ans[i] + 1);
          exit(0);
        }
        break;
      }
    }
    cur--;
  }
}
int main() {
  cin >> n >> m;
  for (int i = 0; i < (int)(m); i++) {
    int v, u;
    scanf("%d%d", &v, &u);
    v--;
    u--;
    g[v].push_back(u);
    g[u].push_back(v);
  }
  solve();
  cout << "NO" << endl;
  return 0;
}
