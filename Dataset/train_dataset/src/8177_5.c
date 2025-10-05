#include <bits/stdc++.h>
using namespace std;
int n, h, q;
int l[55], r[55], c[55], t[55], ans, custo[55][55][55][55];
int dp[55][55][55];
int solve(int ini, int fim, int vmax) {
  int ans = 0;
  if (fim < ini) return 0;
  if (dp[ini][fim][vmax] != -1) return dp[ini][fim][vmax];
  for (int x = 0; x <= vmax; x++)
    for (int mid = ini; mid <= fim; mid++)
      ans = max(ans, solve(ini, mid - 1, x) + solve(mid + 1, fim, x) + x * x -
                         custo[ini][fim][mid][x]);
  return dp[ini][fim][vmax] = ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n >> h >> q;
  for (int i = 1; i <= q; i++) cin >> l[i] >> r[i] >> c[i] >> t[i];
  memset(dp, -1, sizeof dp);
  for (int ini = 1; ini <= n; ini++)
    for (int fim = ini; fim <= n; fim++)
      for (int mid = ini; mid <= fim; mid++)
        for (int x = 0; x <= h; x++)
          for (int i = 1; i <= q; i++)
            if (ini <= l[i] and l[i] <= mid and mid <= r[i] and r[i] <= fim and
                x > c[i])
              custo[ini][fim][mid][x] += t[i];
  cout << solve(1, n, h) << "\n";
}
