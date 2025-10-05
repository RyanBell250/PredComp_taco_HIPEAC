#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
int n, m, d, ans[N], st[N], st1[10];
int a[N];
int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    st[a[i]]++;
  }
  int ans = 0;
  for (int i = 1; i <= 150001; i++) {
    if (st[i - 1] >= 1) {
      st[i - 1]--;
      ans++;
    } else if (st[i] >= 1) {
      st[i]--;
      ans++;
    } else if (st[i + 1] >= 1) {
      ans++;
      st[i + 1]--;
    }
  }
  cout << ans << endl;
  return 0;
}
