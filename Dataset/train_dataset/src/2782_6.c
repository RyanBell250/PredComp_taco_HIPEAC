#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
int n, k;
int cnt[N + 10];
pair<int, int> a[N + 10];
bool flag = false;
bool ok(int mid) {
  if (mid == 0) {
    return true;
  }
  long long temp = 0;
  for (int i = 1; i <= n; i++) {
    temp += a[i].first / mid;
  }
  if (temp >= k) return true;
  return false;
}
int main() {
  scanf("%d%d", &n, &k);
  for (int i = 1; i <= n; i++) {
    int x;
    scanf("%d", &x);
    cnt[x]++;
  }
  n = 0;
  for (int i = 1; i <= N; i++)
    if (cnt[i] > 0) {
      a[++n].first = cnt[i];
      a[n].second = i;
    }
  sort(a + 1, a + 1 + n);
  reverse(a + 1, a + 1 + n);
  if (a[1].first == 1 && n == N) {
    flag = true;
  }
  int l = 0, r = 2e5, temp = -1;
  while (l <= r) {
    int mid = (l + r) >> 1;
    if (ok(mid)) {
      l = mid + 1;
      temp = mid;
    } else {
      r = mid - 1;
    }
  }
  int cur = k;
  for (int i = 1; i <= n; i++) {
    int ma = a[i].first / temp;
    int needed = min(cur, ma);
    for (int j = 1; j <= needed; j++) {
      printf("%d ", a[i].second);
    }
    cur -= needed;
  }
  return 0;
}
