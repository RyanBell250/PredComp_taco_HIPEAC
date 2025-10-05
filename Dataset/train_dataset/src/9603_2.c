#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;
const int MAX = 1e6 + 7;
char ans[1005][1005];
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, a, b;
  cin >> n >> a >> b;
  if (n == 1) {
    cout << "YES\n0\n";
    return 0;
  }
  if (a != 1 && b != 1) {
    cout << "NO\n";
    return 0;
  }
  if (a == 1 && b == 1 && n <= 3) {
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";
  if (a == 1 && b == 1) {
    for (int i = 1; i < n; i++) ans[i][i + 1] = '1', ans[i + 1][i] = '1';
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
        if (ans[i][j] == '1')
          cout << ans[i][j];
        else
          cout << '0';
      cout << "\n";
    }
    return 0;
  }
  if (a == 1) {
    for (int i = 1; i <= b - 1; i++)
      for (int j = i + 1; j <= n; j++) ans[i][j] = '1', ans[j][i] = '1';
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
        if (ans[i][j] == '1')
          cout << ans[i][j];
        else
          cout << '0';
      cout << "\n";
    }
    return 0;
  }
  if (b == 1) {
    for (int i = 1; i <= a - 1; i++)
      for (int j = i + 1; j <= n; j++) ans[i][j] = '0', ans[j][i] = '0';
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++)
        if (ans[i][j] == '0')
          cout << ans[i][j];
        else if (i == j)
          cout << '0';
        else
          cout << '1';
      cout << "\n";
    }
  }
}
