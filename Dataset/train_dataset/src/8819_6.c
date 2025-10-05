#include <bits/stdc++.h>
using namespace std;
const long long N = 1e6 + 7;
const long long inf = 2e18;
struct node {
  unsigned long long op;
  long long x, y, det, detx, dety;
} h, f[N], e[N];
long long n, rt, pt, tot, len, a[N], lf[N], rf[N], siz[N], ch[N][2];
inline long long read() {
  long long num = 0;
  char g = getchar();
  while (g < 48 || 57 < g) g = getchar();
  while (47 < g && g < 58)
    num = (num << 1) + (num << 3) + g - 48, g = getchar();
  return num;
}
inline long long newnode(long long x, long long y) {
  tot++, f[tot].op = rand() * rand() * rand() * rand(), f[tot].x = x,
         f[tot].y = y, siz[tot] = 1;
  return tot;
}
inline void update(long long u) {
  if (!u) return;
  siz[u] = siz[ch[u][0]] + siz[ch[u][1]] + 1;
  if (!f[u].det && !f[u].detx && !f[u].dety) return;
  f[u].y += f[u].x * f[u].det + f[u].dety, f[u].x += f[u].detx;
  f[ch[u][0]].det += f[u].det,
      f[ch[u][0]].dety += f[ch[u][0]].detx * f[u].det + f[u].dety,
      f[ch[u][0]].detx += f[u].detx;
  f[ch[u][1]].det += f[u].det,
      f[ch[u][1]].dety += f[ch[u][1]].detx * f[u].det + f[u].dety,
      f[ch[u][1]].detx += f[u].detx;
  f[u].det = 0, f[u].detx = 0, f[u].dety = 0;
}
inline long long merge(long long u, long long v) {
  update(u), update(v);
  if (!u || !v) return (u + v);
  if (f[u].op < f[v].op) {
    ch[u][1] = merge(ch[u][1], v);
    update(u);
    return u;
  } else {
    ch[v][0] = merge(u, ch[v][0]);
    update(v);
    return v;
  }
}
inline void spilt(long long u, long long &a, long long &b, long long k) {
  if (!u) {
    a = 0, b = 0;
    return;
  }
  update(u);
  if (f[u].x < k)
    a = u, spilt(ch[u][1], ch[u][1], b, k);
  else
    b = u, spilt(ch[u][0], a, ch[u][0], k);
  update(u);
}
inline long long getpos(long long u, long long k) {
  update(u);
  if (siz[ch[u][0]] + 1 == k) return u;
  if (siz[ch[u][0]] >= k) return getpos(ch[u][0], k);
  return getpos(ch[u][1], k - siz[ch[u][0]] - 1);
}
inline void build(long long u) {
  if (!u) return;
  update(u), build(ch[u][0]), e[++len] = f[u], build(ch[u][1]);
}
inline long long getsum(long long c, node x, node y) {
  long long k = (x.y - y.y) / (x.x - y.x), b = x.y - x.x * k;
  return c * k + b;
}
inline void print(long long u) {
  if (!u) return;
  update(u);
  print(ch[u][0]);
  cout << f[u].x << ' ' << f[u].y << endl;
  print(ch[u][1]);
}
inline long long getpre(long long u) {
  while (ch[u][0]) update(u), u = ch[u][0];
  update(u);
  return u;
}
inline long long getnxt(long long u) {
  while (ch[u][1]) update(u), u = ch[u][1];
  update(u);
  return u;
}
inline void init() {
  memset(ch, 0, sizeof(ch));
  for (long long i = 1; i <= tot; i++) f[i] = h;
  tot = 0, memset(siz, 0, sizeof(siz));
}
inline long long getans(long long u) {
  init();
  rt = newnode(u, abs(u)), pt = rt;
  for (long long i = 2; i <= n; i++) {
    long long l, r;
    long long w = f[pt].x;
    spilt(rt, l, r, w), spilt(r, pt, r, w + 1);
    long long fx = 0;
    while (l > 0) {
      long long cq = getnxt(l);
      if (f[cq].y != f[pt].y)
        break;
      else
        spilt(l, l, fx, f[cq].x);
    }
    if (!fx) fx = pt;
    while (r > 0) {
      long long cq = getpre(r);
      if (f[cq].y != f[pt].y)
        break;
      else
        spilt(r, pt, r, f[cq].x + 1);
    }
    w = f[pt].x;
    f[l].detx = f[l].detx - rf[i] + a[i];
    f[r].detx = f[r].detx - lf[i] + a[i];
    long long vas = inf;
    long long pq = pt;
    l = merge(l, newnode(f[fx].x - rf[i] + a[i], f[pt].y));
    long long cs = f[pt].y;
    if (cs + abs(f[fx].x - rf[i] + a[i]) <= vas)
      vas = cs + abs(f[fx].x - rf[i] + a[i]), pt = tot;
    if (lf[i] != rf[i] || fx != pq) {
      r = merge(newnode(w - lf[i] + a[i], cs), r);
      if (cs + abs(w - lf[i] + a[i]) <= vas)
        vas = cs + abs(w - lf[i] + a[i]), pt = tot;
    }
    rt = merge(l, r);
    spilt(rt, l, r, 0);
    long long c = getpre(r), d = getnxt(l);
    if (c > 0 && !f[c].x) {
      if (f[c].y <= vas) pt = c, vas = f[c].y;
    }
    if (f[c].x != 0 && d != 0) {
      r = merge(newnode(0, getsum(0, f[d], f[c])), r);
      if (getsum(0, f[d], f[c]) <= vas) vas = getsum(0, f[d], f[c]), pt = tot;
    }
    f[l].det--, f[r].det++;
    rt = merge(l, r);
  }
  len = 0, build(rt);
  long long l = lf[1] + u - a[1], r = rf[1] + u - a[1], ans = inf;
  if (l <= e[1].x && e[1].x <= r) ans = e[1].y;
  for (long long i = 2; i <= len; i++) {
    long long lq = max(l, e[i - 1].x), rq = min(r, e[i].x);
    if (lq > rq) continue;
    ans = min(min(ans, getsum(lq, e[i - 1], e[i])), getsum(rq, e[i - 1], e[i]));
  }
  return ans;
}
signed main() {
  n = read();
  long long l = 0, r = 0, pos;
  for (long long i = 1; i <= n; i++)
    a[i] = read(), lf[i] = read(), rf[i] = read(), l -= a[i], r += a[i];
  pos = l;
  while (l <= r) {
    long long d = (l + r) >> 1;
    if (getans(d) <= getans(d + 1))
      pos = d, r = d - 1;
    else
      l = d + 1;
  }
  cout << getans(pos) << endl;
}
