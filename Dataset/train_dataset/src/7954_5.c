#include <bits/stdc++.h>
using namespace std;
inline long long read() {
  char c = getchar();
  long long first = 0;
  bool f = 0;
  for (; !isdigit(c); c = getchar()) f ^= !(c ^ 45);
  for (; isdigit(c); c = getchar())
    first = (first << 1) + (first << 3) + (c ^ 48);
  if (f) first = -first;
  return first;
}
const long long M = 3e5 + 10;
long long n, a[M];
struct BIT {
  long long c[M];
  long long lowbit(long long first) { return first & (-first); }
  void add(long long k, long long first) {
    for (long long i = k; i < M; i += lowbit(i)) c[i] += first;
  }
  long long ask(long long first) {
    long long res = 0;
    for (long long i = first; i >= 1; i -= lowbit(i)) res += c[i];
    return res;
  }
  long long query(long long l, long long r) {
    return ask(min(r, M - 1)) - ask(l - 1);
  }
} T1, T2;
signed main() {
  n = read();
  long long res = 0, sum = 0;
  for (long long i = 1; i <= n; i++) a[i] = read();
  for (long long i = 1; i <= n; i++) {
    res += a[i] * (i - 1) - T2.ask(a[i]);
    long long s1 = 0;
    for (long long j = 1; j <= M / a[i] + 1; j++)
      s1 += (T1.query((j - 1) * a[i], a[i] * j - 1)) * (j - 1);
    res += sum - s1 * a[i];
    cout << res << ' ';
    sum += a[i];
    T1.add(a[i], 1);
    for (long long j = 2; j <= M / a[i] + 1; j++) T2.add((j - 1) * a[i], a[i]);
  }
  return 0;
}
