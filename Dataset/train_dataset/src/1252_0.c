#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;
const double PI = acos(-1.0);
const double E = exp(1.0);
const int M = 2e6 + 5;
int prime[M];
int huiwen[M];
int sum[M];
void getprime() {
  for (int i = 2; i < M; ++i) {
    sum[i] = sum[i - 1];
    if (!prime[i]) {
      prime[++prime[0]] = i;
      sum[i]++;
    }
    for (int j = 1; j <= prime[0] && prime[j] * i < M; ++j) {
      prime[prime[j] * i] = 1;
      if (i % prime[j] == 0) break;
    }
  }
}
bool judge(int x) {
  int p[11];
  int len = 0;
  while (x) {
    p[len++] = x % 10;
    x /= 10;
  }
  for (int i = 0; i <= len / 2; ++i)
    if (p[i] != p[len - i - 1]) return 0;
  return 1;
}
void gethuiwen() {
  int cnt = 1;
  for (int i = 1; i < M; ++i) {
    huiwen[i] = huiwen[i - 1];
    if (judge(i)) huiwen[i]++;
  }
}
int main() {
  gethuiwen();
  getprime();
  int p, q;
  cin >> p >> q;
  for (int i = M - 2; i >= 0; --i) {
    if (q * sum[i] <= p * huiwen[i]) {
      cout << i << endl;
      return 0;
    }
  }
  return 0;
}
