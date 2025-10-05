#include <bits/stdc++.h>
static struct FASTIO {
  char READ_CHARACTER;
  bool REMAINING_CHARACTER = false;
  inline void ignore();
  inline void flush();
  template <typename T>
  inline bool READ_INT(T &x);
  template <typename T>
  inline bool READ_STRING(T &x);
  template <size_t N>
  inline bool READ_CHAR_ARRAY(char (&x)[N]);
  template <size_t N>
  inline bool READ_VAR(char (&x)[N]);
  template <typename T>
  inline bool READ_CHAR(T &x);
  inline bool READ_CHAR_ARRAY(char *&x);
  inline bool READ_GETLINE(std::string &x);
  template <typename T>
  inline bool READ_FLOAT(T &x);
  template <typename T>
  inline bool READ_DOUBLE(T &x);
  template <std::size_t N>
  inline bool READ_BITSET(std::bitset<N> &bit);
  template <std::size_t N>
  inline bool READ_VAR(std::bitset<N> &bit);
  inline bool READ_VAR(bool &x);
  inline bool READ_VAR(short int &x);
  inline bool READ_VAR(int &x);
  inline bool READ_VAR(long int &x);
  inline bool READ_VAR(long long int &x);
  inline bool READ_VAR(unsigned short int &x);
  inline bool READ_VAR(unsigned int &x);
  inline bool READ_VAR(unsigned long &x);
  inline bool READ_VAR(unsigned long long &x);
  inline bool READ_VAR(std::string &x);
  inline bool READ_VAR(char &x);
  inline bool READ_VAR(char *&x);
  inline bool READ_VAR(float &x);
  inline bool READ_VAR(double &x);
  inline bool READ_VAR(long double &x);
  template <typename T>
  inline void WRITE_INT(T x);
  inline void WRITE_STRING(std::string &x);
  inline void WRITE_CHAR(char x);
  inline void WRITE_CHAR_ARRAY(const char *x);
  inline void WRITE_FLOAT(float x);
  template <typename T>
  inline void WRITE_DOUBLE(T x);
  inline void WRITE_VAR(bool x);
  inline void WRITE_VAR(short int x);
  inline void WRITE_VAR(int x);
  inline void WRITE_VAR(long int x);
  inline void WRITE_VAR(long long int x);
  inline void WRITE_VAR(unsigned short int x);
  inline void WRITE_VAR(unsigned int x);
  inline void WRITE_VAR(unsigned long x);
  inline void WRITE_VAR(unsigned long long x);
  inline void WRITE_VAR(char x);
  inline void WRITE_VAR(const char *x);
  inline void WRITE_VAR(std::string &x);
  inline void WRITE_VAR(float x);
  inline void WRITE_VAR(double x);
  inline void WRITE_VAR(long double x);
  template <std::size_t N>
  inline void WRITE_VAR(std::bitset<N> &bit);
  template <std::size_t N>
  inline void WRITE_BITSET(std::bitset<N> &bit);
} __FIO__;
using namespace std;
#pragma GCC optimize("O2,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
const int maxn = 1e5 + 10, maxm = 1e5 + 10, lg = 21, mod = 1e9 + 7, inf = 1e18;
struct node {
  long long s1, s2, laz;
  node(int s1 = 0, int s2 = 0, int laz = 0) : s1(s1), s2(s2), laz(laz) {}
} seg[maxn << 2];
int n, ans[maxn], st[maxn], ft[maxn], tt;
vector<pair<int, int> > g[maxn], pp[maxn];
void apply(int siz, int v, int x) {
  seg[v].s2 += ((long long)siz * ((long long)x * x % mod) % mod) +
               ((long long)2 * seg[v].s1 * x % mod);
  while (seg[v].s2 >= mod) seg[v].s2 -= mod;
  seg[v].s1 += (long long)siz * x % mod;
  while (seg[v].s1 >= mod) seg[v].s1 -= mod;
  seg[v].laz += x;
  while (seg[v].laz >= mod) seg[v].laz -= mod;
}
node mrg(node n1, node n2) {
  return node(n1.s1 + n2.s1 + (n1.s1 + n2.s1 >= mod ? -mod : 0),
              n1.s2 + n2.s2 + (n1.s2 + n2.s2 >= mod ? -mod : 0), 0);
}
void add(int l, int r, int x, int s = 0, int t = n, int v = 1) {
  if (l >= t || r <= s) return;
  if (l <= s && r >= t) return apply(t - s, v, x);
  apply(((s + t) >> 1) - s, (v << 1), seg[v].laz);
  apply(t - ((s + t) >> 1), ((v << 1) ^ 1), seg[v].laz);
  seg[v].laz = 0;
  add(l, r, x, s, ((s + t) >> 1), (v << 1));
  add(l, r, x, ((s + t) >> 1), t, ((v << 1) ^ 1));
  seg[v] = mrg(seg[(v << 1)], seg[((v << 1) ^ 1)]);
}
node get(int l, int r, int s = 0, int t = n, int v = 1) {
  if (l >= t || r <= s) return node(0, 0, 0);
  if (l <= s && r >= t) return seg[v];
  apply(((s + t) >> 1) - s, (v << 1), seg[v].laz);
  apply(t - ((s + t) >> 1), ((v << 1) ^ 1), seg[v].laz);
  seg[v].laz = 0;
  return mrg(get(l, r, s, ((s + t) >> 1), (v << 1)),
             get(l, r, ((s + t) >> 1), t, ((v << 1) ^ 1)));
}
void pfs(int v = 1, int p = 0, int h = 0) {
  st[v] = tt++;
  for (auto u : g[v])
    if (u.first != p)
      pfs(u.first, v, (h + u.second) + (h + u.second >= mod ? -mod : 0));
  ft[v] = tt;
  add(st[v], st[v] + 1, h);
}
void dfs(int v = 1, int p = 0) {
  for (auto x : pp[v]) {
    ans[x.second] += get(st[x.first], ft[x.first]).s2;
    if (ans[x.second] >= mod) ans[x.second] -= mod;
    ans[x.second] -= mrg(get(0, st[x.first]), get(ft[x.first], n)).s2,
        ans[x.second] += mod;
    if (ans[x.second] >= mod) ans[x.second] -= mod;
  }
  for (auto uw : g[v])
    if (uw.first != p) {
      int u = uw.first, w = uw.second;
      add(st[u], ft[u], mod - w);
      add(0, st[u], w);
      add(ft[u], n, w);
      dfs(u, v);
      add(st[u], ft[u], w);
      add(0, st[u], mod - w);
      add(ft[u], n, mod - w);
    }
}
int main() {
  0, 0, 0;
  __FIO__.READ_VAR(n);
  for (int i = 1; i < n; i++) {
    int v, u, w;
    __FIO__.READ_VAR(v), __FIO__.READ_VAR(u), __FIO__.READ_VAR(w);
    g[v].push_back({u, w}), g[u].push_back({v, w});
  }
  int q;
  __FIO__.READ_VAR(q);
  for (int i = 0; i < q; i++) {
    int v, u;
    __FIO__.READ_VAR(u), __FIO__.READ_VAR(v);
    pp[u].push_back({v, i});
  }
  pfs(), dfs();
  for (int i = 0; i < q; i++) __FIO__.WRITE_VAR(ans[i]), putchar('\n');
  return 0;
}
inline void FASTIO::ignore() {
  if (REMAINING_CHARACTER == true)
    REMAINING_CHARACTER = false;
  else
    READ_CHARACTER = getchar();
}
inline void FASTIO::flush() { fflush(stdout); }
template <typename T>
inline bool FASTIO::READ_INT(T &x) {
  x = 0;
  T sig = 1;
  if (!REMAINING_CHARACTER)
    READ_CHARACTER = getchar(), REMAINING_CHARACTER = true;
  else
    REMAINING_CHARACTER = false;
  while (!isdigit(READ_CHARACTER) && READ_CHARACTER != EOF)
    sig = (READ_CHARACTER == '-' ? -sig : sig), READ_CHARACTER = getchar();
  if (READ_CHARACTER == EOF) return REMAINING_CHARACTER = false, false;
  while (isdigit(READ_CHARACTER))
    x = x * 10 + READ_CHARACTER - '0', READ_CHARACTER = getchar();
  x *= sig;
  REMAINING_CHARACTER = true;
  return true;
}
template <typename T>
inline bool FASTIO::READ_STRING(T &x) {
  x = "";
  if (!REMAINING_CHARACTER)
    READ_CHARACTER = getchar(), REMAINING_CHARACTER = true;
  else
    REMAINING_CHARACTER = false;
  while ((READ_CHARACTER == '\n' || READ_CHARACTER == '\t' ||
          READ_CHARACTER == ' '))
    READ_CHARACTER = getchar();
  if (READ_CHARACTER == EOF) return REMAINING_CHARACTER = false, false;
  while ((READ_CHARACTER != '\n' && READ_CHARACTER != '\t' &&
          READ_CHARACTER != ' ' && READ_CHARACTER != EOF))
    x += READ_CHARACTER, READ_CHARACTER = getchar();
  REMAINING_CHARACTER = true;
  return true;
}
inline bool FASTIO::READ_GETLINE(std::string &x) {
  x = "";
  if (!REMAINING_CHARACTER)
    READ_CHARACTER = getchar(), REMAINING_CHARACTER = true;
  else
    REMAINING_CHARACTER = false;
  if (READ_CHARACTER == EOF) return REMAINING_CHARACTER = false, false;
  while ((READ_CHARACTER != '\n' && READ_CHARACTER != EOF))
    x += READ_CHARACTER, READ_CHARACTER = getchar();
  REMAINING_CHARACTER = false;
  return true;
}
template <typename T>
inline bool FASTIO::READ_CHAR(T &x) {
  if (!REMAINING_CHARACTER)
    READ_CHARACTER = getchar(), REMAINING_CHARACTER = true;
  else
    REMAINING_CHARACTER = false;
  if (READ_CHARACTER == EOF) return REMAINING_CHARACTER = false, false;
  while ((READ_CHARACTER == '\n' || READ_CHARACTER == '\t' ||
          READ_CHARACTER == ' '))
    READ_CHARACTER = getchar();
  x = READ_CHARACTER;
  REMAINING_CHARACTER = false;
  return true;
}
template <size_t N>
inline bool FASTIO::READ_CHAR_ARRAY(char (&x)[N]) {
  if (!REMAINING_CHARACTER)
    READ_CHARACTER = getchar(), REMAINING_CHARACTER = true;
  else
    REMAINING_CHARACTER = false;
  while ((READ_CHARACTER == '\n' || READ_CHARACTER == '\t' ||
          READ_CHARACTER == ' '))
    READ_CHARACTER = getchar();
  if (READ_CHARACTER == EOF) return REMAINING_CHARACTER = false, false;
  char *ptr = &x[0];
  while ((READ_CHARACTER != '\n' && READ_CHARACTER != '\t' &&
          READ_CHARACTER != ' ' && READ_CHARACTER != EOF))
    *ptr++ = READ_CHARACTER, READ_CHARACTER = getchar();
  *ptr = '\0', REMAINING_CHARACTER = true;
  return true;
}
inline bool FASTIO::READ_CHAR_ARRAY(char *&x) {
  std::string y;
  if (READ_STRING(y) == false) return false;
  x = new char[(int)y.size() + 1];
  strcpy(x, y.c_str());
  return true;
}
template <typename T>
inline bool FASTIO::READ_FLOAT(T &x) {
  return (scanf("%f", &x) != EOF);
}
template <typename T>
inline bool FASTIO::READ_DOUBLE(T &x) {
  double y;
  if (scanf("%lf", &y) == EOF) return false;
  x = y;
  return true;
}
template <std::size_t N>
inline bool FASTIO::READ_BITSET(std::bitset<N> &x) {
  if (!REMAINING_CHARACTER)
    READ_CHARACTER = getchar(), REMAINING_CHARACTER = true;
  else
    REMAINING_CHARACTER = false;
  while ((READ_CHARACTER == '\n' || READ_CHARACTER == '\t' ||
          READ_CHARACTER == ' '))
    READ_CHARACTER = getchar();
  if (READ_CHARACTER == EOF) return REMAINING_CHARACTER = false, false;
  int i = 0;
  REMAINING_CHARACTER = true;
  while (READ_CHARACTER == '0' || READ_CHARACTER == '1')
    x[i++] = READ_CHARACTER - '0', READ_CHARACTER = getchar();
  return true;
}
inline bool FASTIO::READ_VAR(short int &x) { return READ_INT(x); }
inline bool FASTIO::READ_VAR(int &x) { return READ_INT(x); }
inline bool FASTIO::READ_VAR(long int &x) { return READ_INT(x); }
inline bool FASTIO::READ_VAR(long long int &x) { return READ_INT(x); }
inline bool FASTIO::READ_VAR(unsigned short int &x) { return READ_INT(x); }
inline bool FASTIO::READ_VAR(unsigned int &x) { return READ_INT(x); }
inline bool FASTIO::READ_VAR(unsigned long &x) { return READ_INT(x); }
inline bool FASTIO::READ_VAR(unsigned long long &x) { return READ_INT(x); }
inline bool FASTIO::READ_VAR(std::string &x) { return READ_STRING(x); }
inline bool FASTIO::READ_VAR(char &x) { return READ_CHAR(x); }
template <size_t N>
inline bool FASTIO::READ_VAR(char (&x)[N]) {
  return READ_CHAR_ARRAY(x);
}
inline bool FASTIO::READ_VAR(char *&x) { return READ_CHAR_ARRAY(x); }
inline bool FASTIO::READ_VAR(float &x) { return READ_FLOAT(x); }
inline bool FASTIO::READ_VAR(double &x) { return READ_DOUBLE(x); }
inline bool FASTIO::READ_VAR(long double &x) { return READ_DOUBLE(x); }
template <std::size_t N>
inline bool FASTIO::READ_VAR(std::bitset<N> &x) {
  return READ_BITSET(x);
}
template <typename T>
inline void FASTIO::WRITE_INT(T x) {
  if (x < 0) {
    putchar('-');
    x = -x;
  }
  char writeBuffer[20], *writePtr = writeBuffer;
  do {
    *writePtr++ = '0' + x % 10;
    x /= 10;
  } while (x);
  do {
    putchar(*--writePtr);
  } while (writePtr > writeBuffer);
}
inline void FASTIO::WRITE_CHAR(char x) { putchar(x); }
inline void FASTIO::WRITE_CHAR_ARRAY(const char *x) {
  while (*x != '\0') putchar(*x++);
}
inline void FASTIO::WRITE_STRING(std::string &x) {
  for (char c : x) putchar(c);
}
inline void FASTIO::WRITE_FLOAT(float x) { printf("%f", x); }
template <typename T>
inline void FASTIO::WRITE_DOUBLE(T x) {
  printf("%lf", (double)x);
}
template <std::size_t N>
inline void FASTIO::WRITE_BITSET(std::bitset<N> &x) {
  for (int i = (int)x.size() - 1; i >= 0; i--) putchar(x[i] + 48);
}
inline void FASTIO::WRITE_VAR(bool x) { WRITE_INT(x); }
inline void FASTIO::WRITE_VAR(short int x) { WRITE_INT(x); }
inline void FASTIO::WRITE_VAR(int x) { WRITE_INT(x); }
inline void FASTIO::WRITE_VAR(long int x) { WRITE_INT(x); }
inline void FASTIO::WRITE_VAR(long long int x) { WRITE_INT(x); }
inline void FASTIO::WRITE_VAR(unsigned short int x) { WRITE_INT(x); }
inline void FASTIO::WRITE_VAR(unsigned int x) { WRITE_INT(x); }
inline void FASTIO::WRITE_VAR(unsigned long x) { WRITE_INT(x); }
inline void FASTIO::WRITE_VAR(unsigned long long x) { WRITE_INT(x); }
inline void FASTIO::WRITE_VAR(std::string &x) { WRITE_STRING(x); }
inline void FASTIO::WRITE_VAR(char x) { WRITE_CHAR(x); }
inline void FASTIO::WRITE_VAR(const char *x) { WRITE_CHAR_ARRAY(x); }
inline void FASTIO::WRITE_VAR(float x) { WRITE_FLOAT(x); }
inline void FASTIO::WRITE_VAR(double x) { WRITE_DOUBLE(x); }
inline void FASTIO::WRITE_VAR(long double x) { WRITE_DOUBLE(x); }
template <std::size_t N>
inline void FASTIO::WRITE_VAR(std::bitset<N> &x) {
  WRITE_BITSET(x);
}
