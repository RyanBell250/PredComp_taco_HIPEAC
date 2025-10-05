#include <bits/stdc++.h>
using namespace std;
namespace Fread {
const int MAXN = 1 << 20;
char buf[MAXN], *S, *T;
inline char getchar() {
  if (S == T) {
    T = (S = buf) + fread(buf, 1, MAXN, stdin);
    if (S == T) return EOF;
  }
  return *S++;
}
}  // namespace Fread
inline int read() {
  int f = 1, x = 0;
  char ch = Fread::getchar();
  while (!isdigit(ch)) {
    if (ch == '-') f = -1;
    ch = Fread::getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = Fread::getchar();
  }
  return x * f;
}
inline long long readll() {
  long long f = 1, x = 0;
  char ch = Fread::getchar();
  while (!isdigit(ch)) {
    if (ch == '-') f = -1;
    ch = Fread::getchar();
  }
  while (isdigit(ch)) {
    x = x * 10 + ch - '0';
    ch = Fread::getchar();
  }
  return x * f;
}
const int MAXN = 1e5;
map<pair<int, int>, int> mp;
vector<int> G[MAXN + 5];
pair<pair<int, int>, pair<int, int> > c[MAXN + 5];
set<pair<pair<int, int>, pair<int, int> > > s[MAXN + 5];
set<pair<int, int> > S;
int n, ansp[MAXN + 5], ansq[MAXN + 5], cnt;
pair<int, int> ck(pair<int, int> a) {
  if (a.first > a.second) swap(a.first, a.second);
  return a;
}
pair<int, int> ck(int a, int b) { return ck(make_pair(a, b)); }
bool vis[MAXN + 5];
void dfs(int u) {
  if (vis[u]) return;
  vis[u] = 1;
  ansp[++cnt] = u;
  for (int i = 0; i < (int)G[u].size(); ++i) dfs(G[u][i]);
}
int main() {
  int Testcases = read();
  while (Testcases--) {
    n = read();
    for (int i = 1; i <= n; ++i) s[i].clear(), G[i].clear(), vis[i] = 0;
    mp.clear();
    for (int i = 1; i <= n - 2; ++i) {
      c[i].first.first = read();
      c[i].first.second = read();
      c[i].second.first = read();
      c[i].second.second = i;
      mp[ck(c[i].first.first, c[i].first.second)]++;
      mp[ck(c[i].first.second, c[i].second.first)]++;
      mp[ck(c[i].second.first, c[i].first.first)]++;
      s[c[i].first.first].insert(c[i]);
      s[c[i].first.second].insert(c[i]);
      s[c[i].second.first].insert(c[i]);
    }
    for (map<pair<int, int>, int>::iterator it = mp.begin(); it != mp.end();
         ++it)
      if (it->second == 1) {
        G[it->first.first].push_back(it->first.second);
        G[it->first.second].push_back(it->first.first);
      }
    cnt = 0;
    dfs(1);
    for (int i = 1; i <= n; ++i) printf("%d%c", ansp[i], (i == n ? '\n' : ' '));
    S.clear();
    for (int i = 1; i <= n; ++i) S.insert(make_pair((int)s[i].size(), i));
    for (int i = 1; i <= n - 2; ++i) {
      pair<int, int> x = (*S.begin());
      assert(s[x.second].size() == 1);
      pair<pair<int, int>, pair<int, int> > cur = (*s[x.second].begin());
      ansq[i] = cur.second.second;
      S.erase(make_pair((int)s[cur.first.first].size(), cur.first.first));
      S.erase(make_pair((int)s[cur.first.second].size(), cur.first.second));
      S.erase(make_pair((int)s[cur.second.first].size(), cur.second.first));
      s[cur.first.first].erase(cur);
      s[cur.first.second].erase(cur);
      s[cur.second.first].erase(cur);
      if (s[cur.first.first].size())
        S.insert(make_pair((int)s[cur.first.first].size(), cur.first.first));
      if (s[cur.first.second].size())
        S.insert(make_pair((int)s[cur.first.second].size(), cur.first.second));
      if (s[cur.second.first].size())
        S.insert(make_pair((int)s[cur.second.first].size(), cur.second.first));
    }
    for (int i = 1; i <= n - 2; ++i)
      printf("%d%c", ansq[i], (i == n - 2 ? '\n' : ' '));
  }
  return 0;
}
