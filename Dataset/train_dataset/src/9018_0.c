#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  int n, m;
  cin >> n >> m;
  char mat[n][m];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) cin >> mat[i][j];
  int peri = 0;
  for (int i = 0; i < n; i++)
    for (int j = i; j < n; j++)
      for (int k = 0; k < m; k++)
        for (int l = k; l < m; l++) {
          bool c = true;
          for (int x = i; x <= j; x++)
            for (int y = k; y <= l; y++)
              if (mat[x][y] == '1') c = false;
          if (c) peri = max(peri, 2 * (j - i + l - k + 2));
        }
  cout << peri;
}
