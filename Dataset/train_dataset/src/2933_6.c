#include <bits/stdc++.h>
using namespace std;
const long long MOD = 998244353;
const long long MAXN = (1ll << 21) + 10;
long long h, g, sum;
long long input[MAXN], ans[MAXN], levelOf[MAXN];
inline long long fastPow(long long a, long long b) {
  long long res = 1;
  while (b) {
    if (b & 1) res = (res * a) % MOD;
    a = (a * a) % MOD;
    b >>= 1;
  }
  return res;
}
inline long long mul(const long long& a, const long long& b) {
  return (a * b) % MOD;
}
inline long long add(const long long& a, const long long& b) {
  return (a + b + MOD) % MOD;
}
inline long long sub(const long long& a, const long long& b) {
  return (a - b + MOD) % MOD;
}
bool chainPossibleBeyondLevelGInitiatingAt(long long x) {
  if (input[x] == 0) return false;
  while (input[x << 1] || input[x << 1 | 1]) {
    x = input[x << 1] > input[x << 1 | 1] ? x << 1 : x << 1 | 1;
  }
  if (levelOf[x] <= g) return false;
  return true;
}
void work(long long x) {
  while (input[x << 1] || input[x << 1 | 1]) {
    input[x] =
        input[x << 1] > input[x << 1 | 1] ? input[x << 1] : input[x << 1 | 1];
    x = input[x << 1] > input[x << 1 | 1] ? x << 1 : x << 1 | 1;
  }
  input[x] = 0;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  for (long long i = 1; i < (1 << 20); ++i) {
    levelOf[i] = levelOf[i >> 1] + 1;
  }
  long long T;
  scanf("%lld", &T);
  while (T--) {
    ans[0] = 0;
    sum = 0;
    scanf("%lld %lld", &h, &g);
    for (long long i = 1; i < (1 << h); ++i) {
      scanf("%lld", input + i);
    }
    for (long long i = 1; i < (1 << h); ++i) {
      while (chainPossibleBeyondLevelGInitiatingAt(i))
        work(i), ans[++ans[0]] = i;
    }
    for (long long i = 1; i < (1 << g); ++i) {
      sum += input[i];
    }
    printf("%lld\n", sum);
    for (long long i = 1; i <= ans[0]; ++i) {
      printf("%lld ", ans[i]);
    }
    for (long long i = 1; i < (1 << h); ++i) input[i] = 0;
    printf("\n");
  }
  return 0;
}
