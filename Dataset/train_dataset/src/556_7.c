#include <bits/stdc++.h>
using namespace std;
template <class T>
T __sqr(const T x) {
  return x * x;
}
template <class T, class X>
inline T __pow(T a, X y) {
  T z = 1;
  for (int i = 1; i <= y; i++) {
    z *= a;
  }
  return z;
}
template <class T>
inline T gcd(T a, T b) {
  a = abs(a);
  b = abs(b);
  if (!b) return a;
  return __gcd(b, a % b);
}
template <class T>
inline T lcm(T a, T b) {
  a = abs(a);
  b = abs(b);
  return (a / __gcd(a, b)) * b;
}
inline bool ispow2(int x) { return (x != 0 && (x & (x - 1)) == 0); }
template <class T>
void UpdateMin(T &x, T y) {
  if (y < x) {
    x = y;
  }
}
template <class T>
void UpdateMax(T &x, T y) {
  if (x < y) {
    x = y;
  }
}
template <class T, class X, class Y>
inline T bigmod(T n, X m, Y mod) {
  unsigned long long ret = 1, a = n % mod;
  while (m) {
    if (m & 1) ret = (ret * a) % mod;
    m >>= 1;
    a = (a * a) % mod;
  }
  ret %= mod;
  return (T)ret;
}
template <class T, class Y>
inline T modinv(T n, Y mod) {
  return bigmod(n, mod - 2, mod);
}
template <class T, class X>
int getbit(T s, X i) {
  return (s >> i) & 1;
}
template <class T, class X>
T onbit(T s, X i) {
  return s | (T(1) << i);
}
template <class T, class X>
T offbit(T s, X i) {
  return s & (~(T(1) << i));
}
template <class T>
inline void read(T &n) {
  char c;
  for (c = getchar(); !(c >= '0' && c <= '9'); c = getchar())
    ;
  n = c - '0';
  for (c = getchar(); c >= '0' && c <= '9'; c = getchar()) n = n * 10 + c - '0';
}
void extended_euclid(long long a, long long b, long long &x, long long &y) {
  if (!b) {
    x = 1, y = 0;
    return;
  }
  long long first, second;
  extended_euclid(b, a % b, first, second);
  x = second;
  y = first - (a / b) * second;
}
pair<long long, pair<long long, long long> > extendedEuclid(long long a,
                                                            long long b) {
  long long x = 1, y = 0;
  long long xLast = 0, yLast = 1;
  long long q, r, m, n;
  while (a != 0) {
    q = b / a;
    r = b % a;
    m = xLast - q * x;
    n = yLast - q * y;
    xLast = x, yLast = y;
    x = m, y = n;
    b = a, a = r;
  }
  return make_pair(b, make_pair(xLast, yLast));
}
const long long mod[] = {0,          1000000007, 1000000009,
                         1000000021, 1000000033, 1000000097,
                         1000000093, 1000000097, 1000000103};
const long long base[] = {0,       1000003, 1000033, 1000037, 1000039,
                          1000081, 1000099, 1000117, 1000121};
map<int, int> MR, MC;
int mr = 0, mc = 0;
vector<pair<int, int> > row[(100000 + 20)], col[(100000 + 20)];
set<int> sr, sc;
int r[(100000 + 20)], c[(100000 + 20)];
int main() {
  int x[4], y[4];
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= k; i++) {
    scanf("%d%d%d%d", &x[1], &y[1], &x[2], &y[2]);
    if (x[1] == x[2]) {
      if (MR.find(x[1]) == MR.end()) MR[x[1]] = ++mr;
      int rn = MR[x[1]];
      row[rn].push_back(make_pair(min(y[1], y[2]), max(y[1], y[2])));
      sr.insert(x[1]);
    }
    if (y[1] == y[2]) {
      if (MC.find(y[1]) == MC.end()) MC[y[1]] = ++mc;
      int cn = MC[y[1]];
      col[cn].push_back(make_pair(min(x[1], x[2]), max(x[1], x[2])));
      sc.insert(y[1]);
    }
  }
  int ans = 0, mx = 0, tp = -1, no;
  for (map<int, int>::iterator it = MR.begin(); it != MR.end(); it++) {
    int i = (*it).second;
    sort(row[i].begin(), row[i].end());
    int st = 0, tot = 0;
    for (int j = 0; j < ((int)row[i].size()); j++) {
      pair<int, int> ob = row[i][j];
      if (st < ob.first) {
        tot += ob.first - st;
      }
      st = max(st, ob.second);
    }
    tot += (m - st);
    ans ^= tot;
    r[i] = tot;
  }
  for (map<int, int>::iterator it = MC.begin(); it != MC.end(); it++) {
    int i = (*it).second;
    sort(col[i].begin(), col[i].end());
    int st = 0, tot = 0;
    for (int j = 0; j < ((int)col[i].size()); j++) {
      pair<int, int> ob = col[i][j];
      if (st < ob.first) {
        tot += ob.first - st;
      }
      st = max(st, ob.second);
    }
    tot += (n - st);
    ans ^= tot;
    c[i] = tot;
  }
  int baki_row = (n - 1) - sr.size();
  int baki_col = (m - 1) - sc.size();
  if (baki_row & 1) ans ^= m;
  if (baki_col & 1) ans ^= n;
  if (ans == 0)
    puts("SECOND");
  else {
    puts("FIRST");
    int one = 1, bit = ans;
    while (bit ^ one) {
      bit = (bit | one) ^ one;
      one <<= 1;
    }
    int f = -1, fnd = -1, r_n, c_n;
    for (map<int, int>::iterator it = MR.begin(); it != MR.end(); it++) {
      int i = (*it).second;
      if (r[i] & bit) {
        r_n = (*it).first;
        f = i;
        fnd = 1;
        break;
      }
    }
    if (f == -1) {
      for (map<int, int>::iterator it = MC.begin(); it != MC.end(); it++) {
        int i = (*it).second;
        if (c[i] & bit) {
          c_n = (*it).first;
          fnd = 2;
          f = i;
          break;
        }
      }
    }
    if (fnd == 1) {
      int prev = r[f];
      int next = prev ^ ans;
      int nd = (prev - next);
      int st = 0, tot = 0, pr = 0;
      for (int i = 0; i < ((int)row[f].size()); i++) {
        pair<int, int> ob = row[f][i];
        if (st < ob.first) {
          if ((tot + (ob.first - st)) >= nd) {
            printf("%d %d %d %d\n", r_n, 0, r_n, st + (nd - tot));
            pr = 1;
            break;
          }
          tot += (ob.first - st);
        }
        st = max(st, ob.second);
      }
      if (pr == 0) {
        printf("%d %d %d %d\n", r_n, 0, r_n, st + (nd - tot));
      }
    } else if (fnd == 2) {
      int prev = c[f];
      int next = prev ^ ans;
      int nd = (prev - next);
      int st = 0, tot = 0, pr = 0;
      for (int i = 0; i < ((int)col[f].size()); i++) {
        pair<int, int> ob = col[f][i];
        if (st < ob.first) {
          if ((tot + (ob.first - st)) >= nd) {
            printf("%d %d %d %d\n", 0, c_n, st + (nd - tot), c_n);
            pr = 1;
            break;
          }
          tot += (ob.first - st);
        }
        st = max(st, ob.second);
      }
      if (pr == 0) {
        printf("%d %d %d %d\n", 0, c_n, st + (nd - tot), c_n);
      }
    } else {
      if (baki_col % 2 != 0 && (n & one) != 0) {
        int prev = n;
        int next = n ^ ans;
        int nd = (prev - next);
        int cl;
        for (cl = 1; cl <= m - 1; cl++) {
          if (sc.find(cl) == sc.end()) break;
        }
        printf("%d %d %d %d\n", 0, cl, nd, cl);
      } else {
        int prev = m;
        int next = m ^ ans;
        int nd = (prev - next);
        int rw;
        for (rw = 1; rw <= n - 1; rw++) {
          if (sr.find(rw) == sr.end()) break;
        }
        printf("%d %d %d %d\n", rw, 0, rw, nd);
      }
    }
  }
  return 0;
}
