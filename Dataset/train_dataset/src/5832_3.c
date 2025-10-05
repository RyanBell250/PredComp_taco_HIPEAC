#include <bits/stdc++.h>
using namespace std;
template <class T>
void read(T& x) {
  T res = 0, f = 1;
  char c = getchar();
  while (!isdigit(c)) {
    if (c == '-') f = -1;
    c = getchar();
  }
  while (isdigit(c)) {
    res = (res << 3) + (res << 1) + c - '0';
    c = getchar();
  }
  x = res * f;
}
const long long N = 400000 + 10;
const int mod = 1e9 + 7;
int n, a[N], mx, num[N], sum[N], pre[N], tot[N];
vector<int> p[N];
int calc(int x) {
  int ans = 0;
  for (int i = 0; i <= 2 * n; i++) pre[i] = 0;
  for (int i = 1; i <= n; i++) {
    sum[i] = sum[i - 1];
    if (a[i] == mx)
      sum[i]++;
    else if (a[i] == x)
      sum[i]--;
    if (sum[i] == 0)
      ans = max(i, ans);
    else {
      if (!pre[sum[i] + n])
        pre[sum[i] + n] = i;
      else
        ans = max(ans, i - pre[sum[i] + n]);
    }
  }
  return ans;
}
int CNT[N], cnt[N];
void add(int x) {
  --CNT[cnt[x]];
  ++CNT[++cnt[x]];
}
void del(int x) {
  --CNT[cnt[x]];
  ++CNT[--cnt[x]];
}
int calc2(int x) {
  for (int i = 1; i <= n; i++) CNT[i] = cnt[i] = 0;
  CNT[0] = n;
  int l = 1, tot = 0, ans = 0;
  for (int r = 1; r <= n; r++) {
    add(a[r]);
    if (a[r] == mx) tot++;
    if (tot < x)
      continue;
    else if (tot == x) {
      if (CNT[x] > 1) ans = max(ans, r - l + 1);
    } else {
      while (tot > x) {
        if (a[l] == mx) tot--;
        del(a[l++]);
      }
    }
  }
  return ans;
}
int main() {
  read(n);
  for (int i = 1; i <= n; i++) {
    read(a[i]);
    num[a[i]]++;
    num[a[i]] > num[mx] ? mx = a[i] : 0;
    p[a[i]].push_back(i);
  }
  for (int i = 1; i <= n; i++) tot[i] = tot[i - 1] + a[i] == mx;
  int ans = 0;
  int block = 400;
  for (int i = 1; i < block; i++) {
    ans = max(ans, calc2(i));
  }
  for (int i = 1; i <= n; i++) {
    if (i == mx) continue;
    if (num[i] >= block) ans = max(ans, calc(i));
  }
  printf("%d\n", ans);
  return 0;
}
