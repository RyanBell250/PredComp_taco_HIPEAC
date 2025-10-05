#include <bits/stdc++.h>
using namespace std;
using ll = long long;
inline int read() {
  int x = 0, f = 1;
  char ch = getchar();
  while (!isdigit(ch)) {
    if (ch == '-') f = -1;
    ch = getchar();
  }
  while (isdigit(ch)) {
    x = (x << 1) + (x << 3) + ch - '0';
    ch = getchar();
  }
  return x * f;
}
inline void write(ll x) {
  if (x < 0) putchar('-'), x = -x;
  if (x > 9) write(x / 10);
  putchar(x % 10 + '0');
}
const int N = 1e7 + 5, M = 4005;
int n, tot, prime[N], phi[N], sum[N], f[N], pc[N], cnt[N];
ll ans, now;
bool bz[N];
int main() {
  n = read();
  for (int i = 2; i <= n; i++) {
    if (!bz[i]) {
      prime[tot++] = i;
      phi[i] = i - 1;
      f[i] = i;
      pc[i] = 1;
    }
    cnt[i] = cnt[i - 1] + (1 ^ bz[i]);
    sum[f[i]]++;
    for (int j = 0; j < tot && i * prime[j] <= n; j++) {
      bz[i * prime[j]] = 1;
      f[i * prime[j]] = prime[j];
      if (i % prime[j] == 0) {
        phi[i * prime[j]] = phi[i] * prime[j];
        pc[i * prime[j]] = pc[i];
        break;
      }
      phi[i * prime[j]] = phi[i] * (prime[j] - 1);
      pc[i * prime[j]] = pc[i] + 1;
    }
  }
  for (int i = 2; i <= n; i++) sum[i] += sum[i - 1];
  now = 1ll * sum[n / 2] * (sum[n / 2] - 1) / 2;
  for (int i = 2; i <= n; i++)
    if (bz[i]) {
      ans += i - phi[i] - 1;
      now -= i - phi[i] - 1;
      ans += 2 * (phi[i] - cnt[i] + pc[i] - 1);
      now -= phi[i] - cnt[i] + pc[i] - 1;
    }
  for (int i = 2; i <= n / 2; i++)
    if (!bz[i]) {
      ans += 2 * (sum[n / i] - n / i);
      now -= sum[n / i] - n / i;
      ans -= 2 * cnt[min(i - 1, n / i)];
      now += cnt[min(i - 1, n / i)];
      if (i > n / i) {
        ans += 2 * (sum[i] - sum[i - 1]);
        now -= sum[i] - sum[i - 1];
      }
    }
  ans += 3 * now;
  write(ans);
  return 0;
}
