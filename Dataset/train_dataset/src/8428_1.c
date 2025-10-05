#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;
inline char gc(void) {
  static char buf[100000], *p1 = buf, *p2 = buf;
  return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2)
             ? EOF
             : *p1++;
}
template <class T>
inline void read(T &x) {
  T f = 1;
  x = 0;
  static char c = gc();
  for (; !isdigit(c); c = gc())
    if (c == '-') f = -f;
  for (; isdigit(c); c = gc()) x = (x << 1) + (x << 3) + (c & 15);
  x *= f;
}
inline void readstr(char *s) {
  do *s = gc();
  while ((*s == ' ') || (*s == '\n') || (*s == '\r'));
  do *(++s) = gc();
  while ((~*s) && (*s != ' ') && (*s != '\n') && (*s != '\r'));
  *s = 0;
  return;
}
inline void readch(char &x) {
  while (isspace(x = gc()))
    ;
}
char pf[100000], *o1 = pf, *o2 = pf + 100000;
template <class T>
inline void writeln(T x, char c = '\n') {
  if (x < 0)
    (o1 == o2 ? fwrite(pf, 1, 100000, stdout), *(o1 = pf)++ = 45 : *o1++ = 45),
        x = -x;
  static char s[15], *b;
  b = s;
  if (!x) *b++ = 48;
  for (; x; *b++ = x % 10 + 48, x /= 10)
    ;
  for (; b-- != s; (o1 == o2          ? fwrite(pf, 1, 100000, stdout),
                    *(o1 = pf)++ = *b : *o1++ = *b))
    ;
  (o1 == o2 ? fwrite(pf, 1, 100000, stdout), *(o1 = pf)++ = c : *o1++ = c);
}
template <class T>
inline void chkmax(T &x, const T y) {
  x > y ? x = x : x = y;
}
template <class T>
inline void chkmin(T &x, const T y) {
  x < y ? x = x : x = y;
}
const int N = 1e6 + 5;
int x[N], y[N], w[N], s[N], v[N];
bool in[N << 1];
vector<pair<int, int> > e[N];
vector<int> res;
int n, m;
int main() {
  read(n), read(m);
  for ( int i = (1); i <= (m); i++) {
    read(x[i]), read(y[i]);
    w[i] = 1;
    s[x[i]]++;
    s[y[i]]++;
    e[max(x[i], y[i])].push_back(make_pair(min(x[i], y[i]), i));
  }
  for ( int i = (1); i <= (n); i++) {
    for (auto it : e[i]) {
      if (!v[it.first]) {
        v[it.first] = 1;
        w[it.second] = 0;
        s[i]--;
      }
      in[s[it.first]] = 1;
    }
    for (auto it : e[i]) {
      if (!in[s[i]]) break;
      s[i]++;
      v[it.first] = 0;
      w[it.second]++;
    }
    for (auto it : e[i]) in[s[it.first]] = 0;
  }
  for ( int i = (1); i <= (n); i++)
    if (v[i]) res.push_back(i);
  writeln(int(res.size()));
  for (auto it : res) writeln(it, ' ');
  puts("");
  for ( int i = (1); i <= (m); i++)
    writeln(x[i], ' '), writeln(y[i], ' '), writeln(w[i]);
  fwrite(pf, 1, o1 - pf, stdout);
  return 0;
}
