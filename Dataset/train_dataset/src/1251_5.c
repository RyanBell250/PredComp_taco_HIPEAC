#include <bits/stdc++.h>
using namespace std;
int n, k, t, x, y, w;
int a[25][25];
bool u[25];
vector<int> ans;
void calc(int ph, int sum) {
  if (ph == n)
    ans.push_back(sum);
  else {
    for (int i = 0; i < n; i++)
      if (!u[i] && a[ph][i]) {
        u[i] = true;
        calc(ph + 1, sum + a[ph][i]);
        u[i] = false;
      }
    calc(ph + 1, sum);
  }
}
int main() {
  cin >> n >> k >> t;
  for (int i = 0; i < k; i++) {
    scanf("%d%d%d", &x, &y, &w);
    a[x - 1][y - 1] = w;
  }
  calc(0, 0);
  sort(ans.begin(), ans.end());
  cout << ans[t - 1];
  return 0;
}
