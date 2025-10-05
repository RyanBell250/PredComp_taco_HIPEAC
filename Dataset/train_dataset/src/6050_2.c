#include <bits/stdc++.h>
using namespace std;
template <class _T>
inline _T sqr(const _T& x) {
  return x * x;
}
template <class _T>
inline string tostr(const _T& a) {
  ostringstream os("");
  os << a;
  return os.str();
}
template <class _T>
inline istream& operator<<(istream& is, const _T& a) {
  is.putback(a);
  return is;
}
const long double PI = 3.1415926535897932384626433832795;
const long double EPS = 1e-11;
int ans = 0, n, a[12], w[120000], u[12], T[120000];
map<signed int, signed int> M;
vector<signed int> v;
vector<signed int> g[120000];
void rec(int x, int k) {
  if (x == n) {
    signed int z = 0;
    for (int i = 0; i < n; i++) {
      z *= 10;
      z += a[i];
    }
    M[z] = ans++;
    v.push_back(z);
    return;
  }
  for (int i = 0; i < k; i++) {
    a[x] = i;
    rec(x + 1, k);
  }
  a[x] = k;
  rec(x + 1, k + 1);
}
int b[12];
inline signed int popyachsa() {
  for (int i = 0; i < n; i++) u[i] = -1;
  int z = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (u[a[i]] == -1) {
      u[a[i]] = z++;
    }
    b[i] = u[a[i]];
  }
  int x = 0;
  for (int i = n - 1; i >= 0; i--) {
    x *= 10;
    x += b[i];
  }
  return x;
}
void wrt(int x) {
  for (int i = 0; i < 12; i++) {
    a[i] = x % 10;
    x /= 10;
  }
  a[n - 1] = 0;
  for (int i = 0; i <= 9; i++) {
    bool fst = true;
    for (int j = n - 1; j >= 0; j--)
      if (a[j] == i) {
        if (!fst)
          printf(",");
        else {
          if (i)
            printf(",{");
          else
            printf("{");
        }
        fst = false;
        printf("%d", n - j);
      }
    if (!fst)
      printf("}");
    else
      break;
  }
  puts("");
}
int main() {
  cout << setiosflags(ios::fixed) << setprecision(10);
  cin >> n;
  rec(1, 1);
  a[0] = 0;
  int k = ans;
  memset((T), 0, sizeof(T));
  for (int i = 0; i < k; i++) {
    signed int x = v[i];
    for (int j = 0; j < n; j++) {
      a[j] = x % 10;
      x /= 10;
    }
    for (int w = 0; w < n; w++) {
      int e = a[w];
      for (int j = 0; j <= 9; j++) {
        a[w] = j;
        int t = popyachsa();
        if (t != v[i] && M.find(t) != M.end()) {
          int mt = M[t];
          if (T[mt] <= i) {
            T[mt] = i + 1;
            g[i].push_back(mt);
          }
        }
      }
      a[w] = e;
    }
  }
  int x = 0;
  printf("%d\n", ans);
  memset((w), 0, sizeof(w));
  for (int i = 0; i < k; i++) {
    w[i] = g[i].size();
  }
  for (int i = 0; i < g[0].size(); i++) {
    w[g[0][i]]--;
  }
  w[v[0]] = 2000000000;
  int id, mn;
  wrt(v[0]);
  k--;
  while (k) {
    mn = 2000000001;
    for (int i = 0; i < g[x].size(); i++) {
      if (w[g[x][i]] < mn) {
        mn = w[g[x][i]];
        id = i;
      }
    }
    x = g[x][id];
    w[x] = 2000000000;
    wrt(v[x]);
    for (int i = 0; i < g[x].size(); i++)
      if (w[g[x][i]] != 2000000000) w[g[x][i]]--;
    if (mn == 2000000000) {
      return 0;
    }
    k--;
  }
  return 0;
}
