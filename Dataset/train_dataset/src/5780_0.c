#include <bits/stdc++.h>
using namespace std;
const int bfsz = 1 << 16;
char bf[bfsz + 5];
int rsz = 0;
int ptr = 0;
char gc() {
  if (rsz <= 0) {
    ptr = 0;
    rsz = fread(bf, 1, bfsz, stdin);
    if (rsz <= 0) return EOF;
  }
  --rsz;
  return bf[ptr++];
}
void ga(char &c) {
  c = EOF;
  while (!isalpha(c)) c = gc();
}
int gs(char s[]) {
  int l = 0;
  char c = gc();
  while (isspace(c)) c = gc();
  while (c != EOF && !isspace(c)) {
    s[l++] = c;
    c = gc();
  }
  s[l] = '\0';
  return l;
}
template <class first>
bool gi(first &v) {
  v = 0;
  char c = gc();
  while (c != EOF && c != '-' && !isdigit(c)) c = gc();
  if (c == EOF) return false;
  bool neg = c == '-';
  if (neg) c = gc();
  while (isdigit(c)) {
    v = v * 10 + c - '0';
    c = gc();
  }
  if (neg) v = -v;
  return true;
}
long long gcd(long long x, long long y) { return y == 0 ? x : gcd(y, x % y); }
int toInt(char xx) { return xx - '0'; }
char toChar(int xx) { return xx + '0'; }
int isDigit(char xx) { return ('0' <= xx && xx <= '9'); }
void swapInt(int &x, int &y) {
  x = x ^ y;
  y = x ^ y;
  x = x ^ y;
}
const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};
const long long Mod = 1e9 + 7;
const int maxn = 52 + 2;
int exitInput = 0;
int ntest = 1, itest = 1;
const int K = 52;
struct matrix {
  long long a[K + 1][K + 1];
  matrix() {
    for (int i = 0; i <= K; ++i) {
      for (int j = 0; j <= K; ++j) {
        a[i][j] = 0;
      }
    }
  }
};
long long n, m, k;
matrix first;
vector<long long> F1(K + 1, 1);
matrix mul(matrix A, matrix B) {
  matrix res;
  int i, j, p;
  for (i = 1; i <= m; ++i) {
    for (j = 1; j <= m; ++j) {
      for (k = 1; k <= m; ++k) {
        res.a[i][j] = (res.a[i][j] + A.a[i][k] * B.a[k][j]) % Mod;
      }
    }
  }
  return res;
}
matrix Pow(matrix A, long long p) {
  if (p == 1) {
    return A;
  }
  matrix C = Pow(A, p / 2);
  C = mul(C, C);
  if (p & 1) {
    return mul(C, A);
  } else {
    return C;
  }
}
int getid(char x) { return (isupper(x) ? 26 : 0) + (tolower(x) - 'a' + 1); }
void read() {
  gi(n);
  gi(m);
  gi(k);
}
void init() {
  int i, j;
  for (i = 1; i <= m; ++i) {
    for (j = 1; j <= m; ++j) {
      first.a[i][j] = 1;
    }
  }
  char s[3];
  while (k--) {
    gs(s);
    first.a[getid(s[0])][getid(s[1])] = 0;
  }
  if (n == 1) {
    cout << m;
    return;
  }
  first = Pow(first, n - 1);
  long long res = 0;
  for (i = 1; i <= m; ++i) {
    for (j = 1; j <= m; ++j) {
      res = (res + first.a[i][j] * F1[j]) % Mod;
    }
  }
  cout << res;
}
void solve() {}
int main() {
  clock_t t1, t2;
  t1 = clock();
  ios_base::sync_with_stdio(0);
  for (itest = 1; itest <= ntest; ++itest) {
    read();
    if (exitInput) {
      break;
    }
    if (itest > 1) {
    }
    init();
    solve();
  }
  t2 = clock();
  return 0;
}
