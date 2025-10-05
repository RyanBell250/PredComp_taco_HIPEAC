#include <bits/stdc++.h>
using namespace std;
const int N = 200010;
int n, m, k;
int a[N], nxt[N];
int f[N], cnt[N], ans[N];
vector<int> ad[N];
void sfa(int x) {
  memset(f, 127, sizeof(f));
  priority_queue<pair<int, int>, vector<pair<int, int>>,
                 greater<pair<int, int>>>
      q;
  q.push({0, x});
  f[x] = 0;
  cnt[x] = 1;
  ans[x] = nxt[x] == x;
  while (q.size()) {
    int c, u;
    tie(c, u) = q.top();
    q.pop();
    if (c == f[u]) {
      for (auto& v : ad[u]) {
        if (f[v] > c + 1) {
          f[v] = c + 1;
          q.push({c + 1, v});
          if (ans[v]) ans[v] = 0;
        }
        if (f[v] == c + 1) {
          cnt[v]++;
          if (nxt[v] == u) ans[v] = 1;
        }
      }
    }
  }
}
int main() {
  n = ({
    int x = 0;
    int c = getchar(), n = 0;
    for (; !isdigit(c); c = getchar()) n = (c == '-');
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    n ? -x : x;
  }),
  m = ({
    int x = 0;
    int c = getchar(), n = 0;
    for (; !isdigit(c); c = getchar()) n = (c == '-');
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    n ? -x : x;
  });
  for (int i = 1, _c = m; i <= _c; ++i) {
    int u = ({
      int x = 0;
      int c = getchar(), n = 0;
      for (; !isdigit(c); c = getchar()) n = (c == '-');
      for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
      n ? -x : x;
    }),
        v = ({
          int x = 0;
          int c = getchar(), n = 0;
          for (; !isdigit(c); c = getchar()) n = (c == '-');
          for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
          n ? -x : x;
        });
    ad[v].push_back(u);
  }
  for (int i = 1, _c = k = ({
                    int x = 0;
                    int c = getchar(), n = 0;
                    for (; !isdigit(c); c = getchar()) n = (c == '-');
                    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
                    n ? -x : x;
                  });
       i <= _c; ++i)
    a[i] = ({
      int x = 0;
      int c = getchar(), n = 0;
      for (; !isdigit(c); c = getchar()) n = (c == '-');
      for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
      n ? -x : x;
    });
  for (int i = 1, _c = k - 1; i <= _c; ++i) nxt[a[i]] = a[i + 1];
  sfa(a[k]);
  int lf = 0, rt = 0;
  for (int i = 1, _c = k - 1; i <= _c; ++i) {
    if (!ans[a[i]])
      lf++, rt++;
    else if (cnt[a[i]] > 1)
      rt++;
  }
  cout << lf << " " << rt;
}
