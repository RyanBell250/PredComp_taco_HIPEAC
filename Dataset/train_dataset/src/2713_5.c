#include <bits/stdc++.h>
#pragma optimize("Ofast")
using namespace std;
const int N = 100001;
const int M = 31;
const int BLOCK = 100000;
int n, q, cnt = 0;
long long mod;
long long a[N];
long long exgcd(long long a, long long b, long long &x, long long &y) {
  if (!b)
    x = 1, y = 0;
  else
    exgcd(b, a % b, y, x), y -= a / b * x;
}
long long sgt[N << 2], prime_t[N << 2][M], sgt_sum[N << 2];
long long prime_list[M], prime_pow1[M][N], prime_pow2[M][N];
long long my_pow(int p, long long q) {
  return prime_pow1[p][q % BLOCK] * prime_pow2[p][q / BLOCK] % mod;
}
void init() {
  long long x = mod;
  for (long long i = 2; i * i <= x; i++) {
    if (x % i == 0) {
      prime_list[cnt++] = i;
      while (x % i == 0) x /= i;
    }
  }
  if (x > 1) prime_list[cnt++] = x;
  for (int i = 0; i < cnt; i++) {
    prime_pow1[i][0] = 1ll;
    for (int j = 1; j <= BLOCK; j++)
      prime_pow1[i][j] = prime_pow1[i][j - 1] * prime_list[i] % mod;
    prime_pow2[i][0] = 1ll;
    for (int j = 1; j <= BLOCK; j++)
      prime_pow2[i][j] = prime_pow2[i][j - 1] * prime_pow1[i][BLOCK] % mod;
  }
}
long long x, x_prime_t[M];
void calc(long long num) {
  for (int i = 0; i < cnt; i++) {
    x_prime_t[i] = 0;
    while (num % prime_list[i] == 0) x_prime_t[i]++, num /= prime_list[i];
  }
  x = num;
}
void pushdown(int now) {
  for (int i = 0; i <= 1; i++) {
    int ch = now << 1 | i;
    sgt[ch] = sgt[ch] * sgt[now] % mod;
    sgt_sum[ch] = sgt_sum[ch] * sgt[now] % mod;
    for (int j = 0; j < cnt; j++) {
      sgt_sum[ch] = sgt_sum[ch] * my_pow(j, prime_t[now][j]) % mod;
      prime_t[ch][j] += prime_t[now][j];
    }
  }
  sgt[now] = 1ll;
  for (int i = 0; i < cnt; i++) prime_t[now][i] = 0;
}
void pushup(int now) {
  sgt_sum[now] = (sgt_sum[now << 1] + sgt_sum[now << 1 | 1]) % mod;
}
void build(int l, int r, int now) {
  int mid = (l + r) >> 1;
  sgt[now] = 1ll;
  for (int i = 0; i < cnt; i++) prime_t[now][i] = 0;
  if (l == r) {
    calc(a[mid]);
    sgt[now] = sgt_sum[now] = x;
    for (int i = 0; i < cnt; i++) {
      sgt_sum[now] = sgt_sum[now] * my_pow(i, x_prime_t[i]) % mod;
      prime_t[now][i] = x_prime_t[i];
    }
  }
  if (l < r) {
    build(l, mid, now << 1), build(mid + 1, r, now << 1 | 1);
    pushup(now);
  }
}
void change(int left, int right, int l, int r, int now) {
  int mid = (l + r) >> 1;
  if (l == left && r == right) {
    sgt[now] = sgt[now] * x % mod, sgt_sum[now] = sgt_sum[now] * x % mod;
    for (int i = 0; i < cnt; i++) {
      sgt_sum[now] = sgt_sum[now] * my_pow(i, x_prime_t[i]) % mod;
      prime_t[now][i] += x_prime_t[i];
    }
  } else {
    pushdown(now);
    if (right <= mid)
      change(left, right, l, mid, now << 1);
    else if (left > mid)
      change(left, right, mid + 1, r, now << 1 | 1);
    else
      change(left, mid, l, mid, now << 1),
          change(mid + 1, right, mid + 1, r, now << 1 | 1);
    pushup(now);
  }
}
void divide(int pos, int l, int r, int now) {
  int mid = (l + r) >> 1;
  if (l == r) {
    long long num = sgt[now];
    long long num1, num2;
    exgcd(mod, x % mod, num1, num2);
    num2 %= mod;
    if (num2 < 0) num2 += mod;
    sgt[now] = sgt_sum[now] = num * num2 % mod;
    for (int i = 0; i < cnt; i++) {
      prime_t[now][i] -= x_prime_t[i];
      sgt_sum[now] = sgt_sum[now] * my_pow(i, prime_t[now][i]) % mod;
    }
  } else {
    pushdown(now);
    if (pos <= mid)
      divide(pos, l, mid, now << 1);
    else
      divide(pos, mid + 1, r, now << 1 | 1);
    pushup(now);
  }
}
long long query(int left, int right, int l, int r, int now) {
  int mid = (l + r) >> 1;
  if (l == left && r == right)
    return sgt_sum[now];
  else {
    pushdown(now);
    if (right <= mid)
      return query(left, right, l, mid, now << 1);
    else if (left > mid)
      return query(left, right, mid + 1, r, now << 1 | 1);
    else
      return (query(left, mid, l, mid, now << 1) +
              query(mid + 1, right, mid + 1, r, now << 1 | 1)) %
             mod;
  }
}
int main() {
  scanf("%d%lld", &n, &mod);
  init();
  for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
  scanf("%d", &q);
  build(1, n, 1);
  for (int i = 1; i <= q; i++) {
    int type;
    scanf("%d", &type);
    if (type == 1) {
      int left, right;
      long long num;
      scanf("%d%d%lld", &left, &right, &num);
      calc(num);
      change(left, right, 1, n, 1);
    } else if (type == 2) {
      int pos;
      long long num;
      scanf("%d%lld", &pos, &num);
      calc(num);
      divide(pos, 1, n, 1);
    } else {
      int left, right;
      scanf("%d%d", &left, &right);
      printf("%lld\n", query(left, right, 1, n, 1));
    }
  }
  return 0;
}
