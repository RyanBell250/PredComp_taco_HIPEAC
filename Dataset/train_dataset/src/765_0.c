#include <bits/stdc++.h>
using namespace std;
using namespace std;
const int N = 300500;
int n, m, k;
int sz;
int p[N];
int cnt[N];
bool used[N];
int todel[N];
vector<int> g[N];
bool cmp(int x, int y) { return cnt[x] < cnt[y]; }
void solve() {
  queue<int> q;
  for (int i = 1; i <= n; i++) {
    used[i] = false;
  }
  used[1] = true;
  for (int i = 1; i <= k; i++) {
    q.push(p[i]);
    used[p[i]] = true;
  }
  set<int> now;
  for (int i = 1; i <= n; i++) {
    if (!used[i]) {
      now.insert(i);
    }
  }
  set<int>::iterator it;
  while (!q.empty()) {
    int ver = q.front();
    q.pop();
    int t = 0;
    it = now.begin();
    int ptr = 0;
    while (true) {
      if (it == now.end()) {
        break;
      }
      if (ptr == (int)g[ver].size()) {
        break;
      }
      if (g[ver][ptr] < *it) {
        ++ptr;
        continue;
      }
      if (g[ver][ptr] == *it) {
        ++it;
        ++ptr;
        continue;
      }
      used[*it] = true;
      todel[++t] = *it;
      q.push(*it);
      ++it;
    }
    while (true) {
      if (it == now.end()) {
        break;
      }
      used[*it] = true;
      todel[++t] = *it;
      q.push(*it);
      ++it;
    }
    for (int i = 1; i <= t; i++) {
      now.erase(now.find(todel[i]));
    }
  }
  bool ans = true;
  for (int i = 1; i <= n; i++) {
    ans &= used[i];
  }
  if (ans) {
    puts("possible");
    exit(0);
  }
}
int main() {
  srand(time(NULL));
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    if (u > v) swap(u, v);
    g[u].push_back(v);
    g[v].push_back(u);
    if (u == 1) {
      used[v] = true;
    }
  }
  sz = 0;
  cnt[1] = (int)g[1].size();
  for (int i = 2; i <= n; i++) {
    sort(g[i].begin(), g[i].end());
    cnt[i] = (int)g[i].size();
    if (!used[i]) {
      p[++sz] = i;
    }
  }
  if (sz < k) {
    puts("impossible");
    return 0;
  }
  sort(p + 1, p + 1 + sz, cmp);
  solve();
  reverse(p + 1, p + 1 + sz);
  solve();
  int iter = 30;
  while (iter--) {
    random_shuffle(p + 1, p + 1 + sz);
    solve();
  }
  puts("impossible");
  return 0;
}
