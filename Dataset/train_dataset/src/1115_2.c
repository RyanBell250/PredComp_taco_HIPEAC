#include <bits/stdc++.h>
using namespace std;
inline int read() {
  int s = 0, t = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') t = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
    s = (s << 3) + (s << 1) + (ch ^ 48), ch = getchar();
  return s * t;
}
const int N = 1e7 + 5;
int n, T, tot, m, rm, S, rS;
long long Sum, Ans;
int p[N / 10], mu[N], s[N];
bool vis[N];
void Pre(int n) {
  mu[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!vis[i]) mu[i] = -1, p[++tot] = i, s[i]++;
    for (int j = 1; j <= tot && i * p[j] <= n; j++) {
      s[p[j]]++, vis[i * p[j]] = 1;
      if (i % p[j] == 0) break;
      mu[i * p[j]] = -mu[i];
    }
  }
  for (int i = 1; i <= n; i++) mu[i] += mu[i - 1], s[i] += s[i - 1];
}
long long Calc(int n) {
  long long res = 0;
  for (int i = 1, j = 0; i <= n; i = j + 1) {
    j = n / (n / i);
    res += 1ll * (mu[j] - mu[i - 1]) * (n / i) * (n / i - 1) / 2;
  }
  return res;
}
int main() {
  n = read(), T = sqrt(n), Pre(n), Ans = 1ll * n * (n - 1) / 2;
  Sum = Calc(n), Ans -= Sum, Sum -= n - 1;
  for (int i = 1; i <= tot; i++)
    if (p[i] > T) m++, Sum += n / p[i] - 1;
  Sum -= 1ll * (n - m - 1) * m;
  for (int i = 1; i <= tot; i++)
    if (p[i] > T && p[i] * 2 <= n) {
      rm++;
      int t = s[n / p[i]] - (n / p[i] - 1);
      Ans += 2ll * t + 3ll * (n - m - 1 - s[n / p[i]]);
    }
  Ans += 2ll * (Sum - 1ll * m * (m - 1) / 2);
  Ans += 3ll * rm * (rm - 1) / 2;
  cout << Ans;
  return 0;
}
