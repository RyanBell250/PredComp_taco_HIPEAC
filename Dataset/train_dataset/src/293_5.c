#include <bits/stdc++.h>
#pragma comment(linker, "/STACK:102400000,102400000")
using namespace std;
template <class T, class U>
inline void Max(T &a, U b) {
  if (a < b) a = b;
}
template <class T, class U>
inline void Min(T &a, U b) {
  if (a > b) a = b;
}
inline void add(int &a, int b) {
  a += b;
  while (a >= 1000000007) a -= 1000000007;
}
int pow(int a, int b) {
  int ans = 1;
  while (b) {
    if (b & 1) ans = ans * (long long)a % 1000000007;
    a = (long long)a * a % 1000000007;
    b >>= 1;
  }
  return ans;
}
char s[300010];
int d[300010], b[300010], dp[300010], ndp[300010];
vector<int> v;
const int M = (int)1e8;
int divide(int first) {
  long long c = 0;
  for (int i = (int)(v.size()) - 1; i >= 0; i--) {
    c = (c * M + v[i]);
    v[i] = c / first;
    c %= first;
  }
  while ((int)(v.size()) && v.back() == 0) v.pop_back();
  return c;
}
int main() {
  int T, i, j, k, ca = 0, m = 0, K = 0, n;
  scanf("%d", &n);
  for (int i = 1; i < n; i++) scanf("%d", &d[i]);
  for (int i = 0; i < n; i++) scanf("%d", &b[i]);
  scanf("%s", s);
  m = strlen(s);
  for (int i = m - 1; i >= 0; i--) {
    k = 0;
    j = max(i - 8, -1);
    for (int l = j + 1; l < i + 1; l++) k = k * 10 + (s[l] - '0');
    v.push_back(k);
    i = j + 1;
  }
  int rem;
  dp[0] = 1;
  d[n] = 1 << 30;
  for (int i = 0; i < n; i++) {
    K += b[i];
    for (int j = 0; j < K + 1; j++) ndp[j] = dp[j];
    for (int j = 1; j < K + 1; j++) {
      add(ndp[j], ndp[j - 1]);
      if (j > b[i]) add(ndp[j], 1000000007 - dp[j - b[i] - 1]);
    }
    if (d[i + 1] > 1)
      rem = divide(d[i + 1]);
    else
      rem = 0;
    k = 0;
    for (j = rem; j <= K; j += d[i + 1]) {
      dp[k++] = ndp[j];
    }
    for (int j = k; j < K + 1; j++) dp[j] = 0;
    K /= d[i + 1];
  }
  printf("%d\n", dp[0]);
  return 0;
}
