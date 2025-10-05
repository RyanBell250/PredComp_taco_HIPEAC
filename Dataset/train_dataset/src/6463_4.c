#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
const int M = 2e6 + 5;
const int mod = 1e9 + 7;
inline int add(int x, int y) { return x + y >= mod ? x + y - mod : x + y; }
inline int mul(int x, int y) { return (long long)x * y % mod; }
int n;
int a[N];
int lp[M];
vector<int> pr;
int cnt[M], many[M];
int main() {
  for (int i = 2; i < M; i++) {
    if (!lp[i]) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (auto x : pr) {
      if (x > lp[i] or x * i >= M) break;
      lp[x * i] = x;
    }
  }
  scanf("%d", &n);
  bool add_one = 0;
  for (int i = 1; i <= n; i++) {
    scanf("%d", a + i);
  }
  sort(a + 1, a + n + 1);
  reverse(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) {
    int x = a[i];
    bool flag = 0;
    while (x > 1) {
      int y = lp[x], c = 0;
      while (x % y == 0) {
        x /= y;
        c++;
      }
      if (c > cnt[y]) {
        cnt[y] = c;
        flag = 1;
        many[y] = 1;
      } else if (c == cnt[y])
        many[y]++;
    }
    if (!flag) {
      x = a[i];
      int y = lp[x], c = 0;
      while (x % y == 0) {
        x /= y;
        c++;
      }
      if (c == cnt[y]) many[y]--;
      x = --a[i];
      while (x > 1) {
        int y = lp[x], c = 0;
        while (x % y == 0) {
          x /= y;
          c++;
        }
        if (c > cnt[y]) {
          cnt[y] = c;
          flag = 1;
          many[y] = 1;
        } else if (c == cnt[y])
          many[y]++;
      }
      if (!flag) add_one = 1;
    }
  }
  int ans = 1;
  for (int i = 2; i < M; i++) {
    for (int it = 0; it < cnt[i]; it++) {
      ans = mul(ans, i);
    }
  }
  for (int i = 1; i <= n; i++) {
    int x = a[i];
    bool flag = 0;
    while (x > 1) {
      int y = lp[x], c = 0;
      while (x % y == 0) {
        x /= y;
        c++;
      }
      if (c == cnt[y] and many[y] == 1) {
        flag = 1;
      }
    }
    if (!flag) add_one = 1;
  }
  ans = add(ans, add_one);
  printf("%d\n", ans);
  return 0;
}
