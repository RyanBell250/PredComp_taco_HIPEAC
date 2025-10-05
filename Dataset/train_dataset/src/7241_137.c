#include <bits/stdc++.h>
template <typename T>
inline T max(T a, T b) {
  return a > b ? a : b;
}
template <typename T>
inline T min(T a, T b) {
  return a < b ? a : b;
}
template <typename T>
inline T abs(T a) {
  return a > 0 ? a : -a;
}
template <typename T>
inline bool repr(T &a, T b) {
  return a < b ? a = b, 1 : 0;
}
template <typename T>
inline bool repl(T &a, T b) {
  return a > b ? a = b, 1 : 0;
}
template <typename T>
inline T gcd(T a, T b) {
  T t;
  if (a < b) {
    while (a) {
      t = a;
      a = b % a;
      b = t;
    }
    return b;
  } else {
    while (b) {
      t = b;
      b = a % b;
      a = t;
    }
    return a;
  }
}
template <typename T>
inline T sqr(T x) {
  return x * x;
}
struct Cg {
  inline char operator()() { return getchar(); }
};
struct Cp {
  inline void operator()(char x) { putchar(x); }
};
inline bool IS(char x) { return x == 10 || x == 13 || x == ' '; }
template <typename T>
struct Fr {
  T P;
  inline Fr &operator,(int &x) {
    x = 0;
    char t = P();
    while ((t < '0' || t > '9') && t != '-') t = P();
    bool f = 0;
    if (t == '-') t = P(), f = 1;
    x = t - '0';
    for (t = P(); t >= '0' && t <= '9'; t = P()) x = x * 10 + t - '0';
    if (f) x = -x;
    return *this;
  }
  inline operator int() {
    int x;
    *this, x;
    return x;
  }
  inline Fr &operator,(long long &x) {
    x = 0;
    char t = P();
    while ((t < '0' || t > '9') && t != '-') t = P();
    bool f = 0;
    if (t == '-') t = P(), f = 1;
    x = t - '0';
    for (t = P(); t >= '0' && t <= '9'; t = P()) x = x * 10 + t - '0';
    if (f) x = -x;
    return *this;
  }
  inline operator long long() {
    long long x;
    *this, x;
    return x;
  }
  inline Fr &operator,(char &x) {
    for (x = P(); IS(x); x = P())
      ;
    return *this;
  }
  inline operator char() {
    char x;
    *this, x;
    return x;
  }
  inline Fr &operator,(char *x) {
    char t = P();
    for (; IS(t); t = P())
      ;
    if (~t) {
      for (; !IS(t) && ~t; t = P()) *x++ = t;
    }
    *x++ = 0;
    return *this;
  }
  inline Fr &operator,(double &x) {
    x = 0;
    char t = P();
    while ((t < '0' || t > '9') && t != '-') t = P();
    bool f = 0;
    if (t == '-') t = P(), f = 1;
    x = t - '0';
    for (t = P(); t >= '0' && t <= '9'; t = P()) x = x * 10 + t - '0';
    if (t == '.') {
      double u = 0.1;
      for (t = P(); t >= '0' && t <= '9'; t = P(), u *= 0.1) x += u * (t - '0');
    }
    if (f) x = -x;
    return *this;
  }
  inline operator double() {
    double x;
    *this, x;
    return x;
  }
  inline Fr &operator,(long double &x) {
    x = 0;
    char t = P();
    while ((t < '0' || t > '9') && t != '-') t = P();
    bool f = 0;
    if (t == '-') t = P(), f = 1;
    x = t - '0';
    for (t = P(); t >= '0' && t <= '9'; t = P()) x = x * 10 + t - '0';
    if (t == '.') {
      double u = 0.1;
      for (t = P(); t >= '0' && t <= '9'; t = P(), u *= 0.1) x += u * (t - '0');
    }
    if (f) x = -x;
    return *this;
  }
  inline operator long double() {
    long double x;
    *this, x;
    return x;
  }
  inline Fr &operator,(unsigned int &x) {
    x = 0;
    char t = P();
    while (t < '0' || t > '9') t = P();
    x = t - '0';
    for (t = P(); t >= '0' && t <= '9'; t = P()) x = x * 10 + t - '0';
    return *this;
  }
  inline operator unsigned int() {
    unsigned int x;
    *this, x;
    return x;
  }
  inline Fr &operator,(unsigned long long &x) {
    x = 0;
    char t = P();
    while (t < '0' || t > '9') t = P();
    x = t - '0';
    for (t = P(); t >= '0' && t <= '9'; t = P()) x = x * 10 + t - '0';
    return *this;
  }
  inline operator unsigned long long() {
    unsigned long long x;
    *this, x;
    return x;
  }
};
Fr<Cg> in;
template <typename T>
struct Fw {
  T P;
  inline Fw &operator,(int x) {
    if (x) {
      if (x < 0) P('-'), x = -x;
      char s[10], c = 0;
      while (x) s[c++] = x % 10 + '0', x /= 10;
      while (c--) P(s[c]);
    } else
      P('0');
    return *this;
  }
  inline Fw &operator()(int x) {
    if (x) {
      if (x < 0) P('-'), x = -x;
      char s[10], c = 0;
      while (x) s[c++] = x % 10 + '0', x /= 10;
      while (c--) P(s[c]);
    } else
      P('0');
    return *this;
  }
  inline Fw &operator,(unsigned int x) {
    if (x) {
      char s[10], c = 0;
      while (x) s[c++] = x % 10 + '0', x /= 10;
      while (c--) P(s[c]);
    } else
      P('0');
    return *this;
  }
  inline Fw &operator()(unsigned int x) {
    if (x) {
      char s[10], c = 0;
      while (x) s[c++] = x % 10 + '0', x /= 10;
      while (c--) P(s[c]);
    } else
      P('0');
    return *this;
  }
  inline Fw &operator,(long long x) {
    if (x) {
      if (x < 0) P('-'), x = -x;
      char s[19], c = 0;
      while (x) s[c++] = x % 10 + '0', x /= 10;
      while (c--) P(s[c]);
    } else
      P('0');
    return *this;
  }
  inline Fw &operator()(long long x) {
    if (x) {
      if (x < 0) P('-'), x = -x;
      char s[19], c = 0;
      while (x) s[c++] = x % 10 + '0', x /= 10;
      while (c--) P(s[c]);
    } else
      P('0');
    return *this;
  }
  inline Fw &operator,(unsigned long long x) {
    if (x) {
      char s[20], c = 0;
      while (x) s[c++] = x % 10 + '0', x /= 10;
      while (c--) P(s[c]);
    } else
      P('0');
    return *this;
  }
  inline Fw &operator()(unsigned long long x) {
    if (x) {
      char s[20], c = 0;
      while (x) s[c++] = x % 10 + '0', x /= 10;
      while (c--) P(s[c]);
    } else
      P('0');
    return *this;
  }
  inline Fw &operator,(char x) {
    P(x);
    return *this;
  }
  inline Fw &operator()(char x) {
    P(x);
    return *this;
  }
  inline Fw &operator,(const char *x) {
    while (*x) P(*x++);
    return *this;
  }
  inline Fw &operator()(const char *x) {
    while (*x) P(*x++);
    return *this;
  }
  inline Fw &operator()(double x, int y) {
    if (y) {
      double t = 0.5;
      for (int i = y; i--;) t *= 0.1;
      if (x >= 0)
        x += t;
      else
        x -= t, P('-');
      *this, (long long)(abs(x));
      P('.');
      if (x < 0) x = -x;
      while (y--) {
        x *= 10;
        x -= floor(x * 0.1) * 10;
        P(((int)x) % 10 + '0');
      }
    } else if (x >= 0)
      *this, (long long)(x + 0.5);
    else
      *this, (long long)(x - 0.5);
    ;
    return *this;
  }
  inline Fw &operator()(long double x, int y) {
    if (y) {
      double t = 0.5;
      for (int i = y; i--;) t *= 0.1;
      if (x >= 0)
        x += t;
      else
        x -= t, P('-');
      *this, (long long)(abs(x));
      P('.');
      if (x < 0) x = -x;
      while (y--) {
        x *= 10;
        x -= floor(x * 0.1) * 10;
        P(((int)x) % 10 + '0');
      }
    } else if (x >= 0)
      *this, (long long)(x + 0.5);
    else
      *this, (long long)(x - 0.5);
    ;
    return *this;
  }
};
Fw<Cp> out;
const int N = 300007;
struct _e {
  int o, x, y;
} e[N];
std::vector<std::pair<int, int> > p[N];
int n, m, s, c, a1[N], a2[N];
bool vis[N];
inline void dfs1(int x) {
  if (vis[x]) return;
  vis[x] = 1;
  for (__typeof(p[x].end()) i = p[x].begin(); i != p[x].end(); ++i) {
    if (!i->second)
      dfs1(i->first);
    else {
      if (a1[abs(i->second)]) continue;
      a1[abs(i->second)] = i->second > 0 ? 1 : 2;
      dfs1(i->first);
    }
  }
}
inline void dfs2(int x) {
  if (vis[x]) return;
  vis[x] = 1;
  for (__typeof(p[x].end()) i = p[x].begin(); i != p[x].end(); ++i) {
    if (!i->second) dfs2(i->first);
  }
}
inline void dfs3(int x, int *a) {
  if (vis[x]) return;
  vis[x] = 1;
  for (__typeof(p[x].end()) i = p[x].begin(); i != p[x].end(); ++i) {
    if (!i->second)
      dfs3(i->first, a);
    else {
      if (a[abs(i->second)] == (i->second > 0 ? 1 : 2)) dfs3(i->first, a);
    }
  }
}
int main() {
  in, n, m, s;
  for (int i = 1, iend = m; i <= iend; i++) {
    in, e[i].o, e[i].x, e[i].y;
    if (e[i].o == 1) {
      p[e[i].x].push_back(std::make_pair(e[i].y, 0));
    } else {
      ++c;
      p[e[i].x].push_back(std::make_pair(e[i].y, c));
      p[e[i].y].push_back(std::make_pair(e[i].x, -c));
    }
  }
  dfs1(s);
  memset(vis, 0, sizeof(vis));
  dfs2(s);
  c = 0;
  for (int i = 1, iend = m; i <= iend; i++)
    if (e[i].o == 2) {
      ++c;
      if (vis[e[i].x] && !vis[e[i].y])
        a2[c] = 2;
      else
        a2[c] = 1;
    }
  int t = 0;
  memset(vis, 0, sizeof(vis));
  dfs3(s, a1);
  for (int i = 1, iend = n; i <= iend; i++) t += vis[i];
  out, t, '\n';
  for (int i = 1, iend = c; i <= iend; i++) out, a1[i] == 1 ? '+' : '-';
  out, '\n';
  t = 0;
  memset(vis, 0, sizeof(vis));
  dfs3(s, a2);
  for (int i = 1, iend = n; i <= iend; i++) t += vis[i];
  out, t, '\n';
  for (int i = 1, iend = c; i <= iend; i++) out, a2[i] == 1 ? '+' : '-';
  out, '\n';
}
