#include <bits/stdc++.h>
using namespace std;
namespace IO {
char buf[1 << 21], *p1 = buf, *p2 = buf, obuf[1 << 23], *O = obuf;
inline int read() {
  int x = 0, sign = 0;
  char s =
      (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)
           ? EOF
           : *p1++);
  while (!isdigit(s))
    sign |= s == '-',
        s = (p1 == p2 &&
                     (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)
                 ? EOF
                 : *p1++);
  while (isdigit(s))
    x = (x << 1) + (x << 3) + (s - '0'),
    s = (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 20, stdin), p1 == p2)
             ? EOF
             : *p1++);
  return sign ? -x : x;
}
void print(long long x) {
  if (x > 9) print(x / 10);
  (*O++ = x % 10 + '0');
}
}  
namespace math {
const int mod = 99824353;
const int maxn = 1e6 + 5;
long long ksm(long long a, long long b) {
  long long s = 1, m = a;
  while (b) {
    if (b & 1) s = s * m % mod;
    m = m * m % mod, b >>= 1;
  }
  return s;
}
long long inv(long long x) { return ksm(x, mod - 2); }
long long fc[maxn], ifc[maxn];
void init_m(int n) {
  fc[0] = 1;
  for (int i = 1; i <= n; i++) fc[i] = fc[i - 1] * i % mod;
  ifc[n] = inv(fc[n]);
  for (int i = n - 1; i >= 0; i--) ifc[i] = ifc[i + 1] * (i + 1) % mod;
}
long long C(long long n, long long m) {
  return fc[n] * ifc[m] % mod * ifc[n - m] % mod;
}
}  
using namespace IO;
const int N = 2e5 + 5;
int n, m, cnt, son[N][26], f[N], edp[N];
string s[N];
vector<int> e[N];
void ins(int id) {
  int p = 0;
  for (char it : s[id]) {
    if (!son[p][it - 'a']) son[p][it - 'a'] = ++cnt;
    p = son[p][it - 'a'];
  }
  edp[id] = p;
}
void build() {
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (son[0][i]) q.push(son[0][i]);
  while (!q.empty()) {
    int t = q.front();
    q.pop();
    for (int i = 0; i < 26; i++)
      if (son[t][i])
        f[son[t][i]] = son[f[t]][i], q.push(son[t][i]);
      else
        son[t][i] = son[f[t]][i];
    e[f[t]].emplace_back(t);
  }
}
int dn, sz[N], dfn[N];
long long c[N];
void add(int x, int v) {
  while (x <= cnt + 1) c[x] += v, x += x & -x;
}
long long query(int x) {
  long long ans = 0;
  while (x) ans += c[x], x -= x & -x;
  return ans;
}
void dfs(int id) {
  sz[id] = 1, dfn[id] = ++dn;
  for (int it : e[id]) dfs(it), sz[id] += sz[it];
}
struct qq {
  int id, qid, ans;
};
vector<qq> q[N];
long long ans[N << 2];
int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> s[i], ins(i);
  build(), dfs(0);
  for (int i = 1; i <= m; i++) {
    int l = read(), r = read(), k = read();
    q[l - 1].emplace_back((qq){k, i, -1});
    q[r].emplace_back((qq){k, i, 1});
  }
  for (int i = 1; i <= n; i++) {
    int p = 0;
    for (char it : s[i]) {
      p = son[p][it - 'a'];
      add(dfn[p], 1);
    }
    for (qq it : q[i]) {
      p = edp[it.id];
      ans[it.qid] += it.ans * (query(dfn[p] + sz[p] - 1) - query(dfn[p] - 1));
    }
  }
  for (int i = 1; i <= m; i++) print(ans[i]), (*O++ = '\n');
  return fwrite(obuf, O - obuf, 1, stdout), 0;
}
