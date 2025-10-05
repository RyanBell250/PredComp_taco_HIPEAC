#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int N = 3e5 + 5;
const int N2 = 1.5e7 + 5;
int n;
int cnt = 0;
int check[5005];
int a[N];
int num[N2];
int prime[N];
int gcd(int x, int y) { return y == 0 ? x : gcd(y, x % y); }
void _prime() {
  int m = 5000;
  for (int i = 2; i <= m; i++) {
    if (!check[i]) {
      prime[++cnt] = i;
      for (int j = i; j <= m; j += i) {
        check[j] = 1;
      }
    }
  }
}
void factor(int m) {
  for (int i = 1; i <= cnt; i++) {
    if (m % prime[i] == 0) num[prime[i]]++;
    while (m % prime[i] == 0) {
      m /= prime[i];
    }
  }
  if (m != 1) num[m]++;
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
  int g = a[1];
  for (int i = 2; i <= n; i++) g = gcd(g, a[i]);
  _prime();
  for (int i = 1; i <= n; i++) {
    a[i] /= g;
    factor(a[i]);
  }
  int ans = INF;
  for (int i = 1; i <= N2; i++) {
    if (num[i]) ans = min(ans, n - num[i]);
  }
  cout << (ans < n ? ans : -1) << endl;
}
