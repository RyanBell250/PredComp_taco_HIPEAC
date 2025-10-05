#include <bits/stdc++.h>
using namespace std;
const int mod = 1000000007;
inline int add(int a, int b) {
  if ((a += b) >= mod) a -= mod;
  return a;
}
inline int dec(int a, int b) {
  if ((a -= b) < 0) a += mod;
  return a;
}
inline int mult(int a, int b) {
  long long t = 1ll * a * b;
  if (t >= mod) t %= mod;
  return t;
}
inline int power(int a, int b) {
  int out = 1;
  while (b) {
    if (b & 1) out = mult(out, a);
    a = mult(a, a);
    b >>= 1;
  }
  return out;
}
int f[2000010];
bool flag[2000010];
vector<int> prime;
void init() {
  memset(f, 0x3f, sizeof(f));
  for (int i = 2; i <= 2000000; i++) {
    if (!flag[i]) f[i] = i, prime.push_back(i);
    for (int j = 0; j < prime.size() && i * prime[j] <= 2000000; j++) {
      f[i * prime[j]] = min(f[i * prime[j]], prime[j]);
      flag[i * prime[j]] = 1;
      if (!(i % prime[j])) break;
    }
  }
}
int n, p[200010], cntmx[2000010], mx[2000010];
int main() {
  init();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) scanf("%d", &p[i]);
  sort(p + 1, p + n + 1);
  for (int i = n; i >= 1; i--) {
    if (!mx[p[i]]) {
      cntmx[p[i]] = 1;
      mx[p[i]] = 1;
    } else {
      p[i]--;
      int t = p[i];
      while (t != 1) {
        int p = f[t], cnt = 0;
        while (t % p == 0) t /= p, cnt++;
        if (mx[p] < cnt) {
          cntmx[p] = 1;
          mx[p] = cnt;
        } else if (mx[p] == cnt)
          cntmx[p]++;
      }
    }
  }
  int ad = 0;
  for (int i = 1; i <= n; i++) {
    int t = p[i];
    bool flag = 1;
    while (t != 1) {
      int c = f[t], cnt = 0;
      while (t % c == 0) t /= c, cnt++;
      if (cntmx[c] == 1 && cnt == mx[c]) {
        flag = 0;
        break;
      }
    }
    if (flag) {
      ad = 1;
      break;
    }
  }
  int ans = 1;
  for (auto &x : prime) ans = mult(ans, power(x, mx[x]));
  printf("%d\n", add(ans, ad));
  return 0;
}
