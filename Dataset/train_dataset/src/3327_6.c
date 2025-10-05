#include <bits/stdc++.h>
using namespace std;
int ans = 1 << 30;
long long conf[18];
int dfs(long long n, int num) {
  int k = int(n / conf[num]) * num;
  long long _n = n % conf[num];
  if (_n == 0) return k;
  return k + min(dfs(conf[num] - _n, num - 1) + num, dfs(_n, num - 1));
}
int main() {
  long long n;
  scanf("%I64d", &n);
  conf[0] = 0;
  for (int i = 1; i < 18; ++i) conf[i] = conf[i - 1] * 10 + 1;
  printf("%d\n", dfs(n, 17));
  return 0;
}
