#include <bits/stdc++.h>
using namespace std;
int l, r;
int k;
int Q;
int ans[10][1000001];
int dfs(int x) {
  if (x < 10) return x;
  int temp = 1;
  while (x) {
    temp *= (x % 10 > 0 ? x % 10 : 1);
    x /= 10;
  }
  return dfs(temp);
}
void init() {
  for (int i = 1; i <= 1000000; i++) ans[dfs(i)][i]++;
  for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= 1000000; j++) {
      ans[i][j] += ans[i][j - 1];
    }
  }
}
int main() {
  init();
  cin >> Q;
  while (Q--) {
    cin >> l >> r >> k;
    cout << endl << ans[k][r] - ans[k][l - 1];
  }
  return 0;
}
