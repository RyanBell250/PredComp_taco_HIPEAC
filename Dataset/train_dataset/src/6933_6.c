#include <bits/stdc++.h>
using namespace std;
template <class T>
T smin(T &a, T b) {
  if (a > b) a = b;
  return a;
}
template <class T>
T smax(T &a, T b) {
  if (a < b) a = b;
  return a;
}
char str[1 << 20];
int Rand(int l, int r) { return rand() % (r - l + 1) + l; }
int prim(int n) {
  for (int i = 2; 1ll * i * i <= n; ++i)
    if (!(n % i)) return 0;
  return 1;
}
int pow(int a, int b, int mod) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = (1ll * ans * a) % mod;
    a = (1ll * a * a) % mod;
    b /= 2;
  }
  return ans;
}
int n;
int root(int mod) {
  set<int> dv;
  for (int i = 1; 1ll * i * i <= (mod - 1); ++i)
    if (!((mod - 1) % i)) dv.insert((mod - 1) / i), dv.insert(i);
  dv.erase(mod - 1);
  for (int g = 1; g; ++g) {
    int okay = 1;
    for (auto d : dv) okay &= pow(g, d, mod) != 1;
    if (okay) return pow(g, (mod - 1) / n, mod);
  }
}
const int oo = 1e9 + 69;
int main(void) {
  srand(time(0));
  cin >> n;
  cin >> str;
  for (int cs = 0; cs < 5; ++cs) {
    int mod;
    while (!prim(mod = Rand(1, oo / n) * n + 1))
      ;
    int g = root(mod);
    int w = 1;
    int ans = 0;
    for (int i = 0; i < n; ++i)
      ans = (ans + 1ll * w * (str[i] - '0')) % mod, w = (1ll * w * g) % mod;
    if (ans) return puts("NO") * 0;
  }
  puts("YES");
  return 0;
}
