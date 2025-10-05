#include <bits/stdc++.h>
using namespace std;
char grid[1010][1010];
int main() {
  int n, fl, cnt = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    if (i % 2 == 0) {
      for (int j = 0; j < n; j++) {
        if (j % 2 == 0) {
          grid[i][j] = 'C';
          cnt++;
        } else
          grid[i][j] = '.';
      }
    } else {
      for (int j = 0; j < n; j++) {
        if (j % 2 == 0)
          grid[i][j] = '.';
        else {
          grid[i][j] = 'C';
          cnt++;
        }
      }
    }
  }
  cout << cnt << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << grid[i][j];
    cout << endl;
  }
  return 0;
}
