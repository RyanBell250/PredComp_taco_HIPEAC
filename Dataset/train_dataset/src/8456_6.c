#include <bits/stdc++.h>
using namespace std;
const int ms = 111111;
int n, x;
int v[ms];
long long cnt[ms];
int main() {
  scanf("%d%d", &n, &x);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
    cnt[v[i]]++;
  }
  long long ans = 0;
  for (int i = 0; i < ms; ++i) {
    int j = x ^ i;
    if (j < ms) {
      if (j == i) {
        if (cnt[j] > 1) ans += cnt[j] * (cnt[j] - 1);
      } else
        ans += cnt[j] * cnt[i];
    }
  }
  printf("%lld\n", ans / 2);
  return 0;
}
