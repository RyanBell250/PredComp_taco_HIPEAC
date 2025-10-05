#include <bits/stdc++.h>
using namespace std;
char c[100000] = {0};
bool bl[100000] = {0};
int num[100000] = {0};
int nm[1000] = {0};
vector<int> a[1000];
int cnt = -2;
void dfs(int x, int col) {
  num[nm[x]] = col;
  bl[nm[x]] = 1;
  cnt = max(cnt, col);
  int tmp = col + 1;
  for (int i = 0; i < a[x].size(); ++i) {
    int j = a[x][i];
    if (!bl[nm[j]]) {
      dfs(j, col + 1);
    }
  }
}
bool q[1000][1000] = {0};
int main() {
  int n, m, x, y;
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    cin >> x >> y;
    q[x][y] = q[y][x] = 1;
    q[x][x] = q[y][y] = 1;
    a[x].push_back(y);
    a[y].push_back(x);
  }
  memset(nm, -1, sizeof nm);
  int res = 0;
  for (int i = 1; i <= n; ++i) {
    if (nm[i] != -1) continue;
    nm[i] = i;
    ++res;
    for (int k = 0; k < a[i].size(); ++k) {
      int j = a[i][k];
      if (a[i].size() == a[j].size()) {
        bool l = 1;
        for (int z = 0; z < a[i].size(); ++z) {
          if (!q[j][a[i][z]]) {
            l = 0;
            break;
          }
        }
        for (int z = 0; z < a[j].size(); ++z) {
          if (!q[i][a[j][z]]) {
            l = 0;
            break;
          }
        }
        if (l) {
          nm[j] = i;
        }
      }
    }
  }
  bool f_ans = 1;
  int zen[1000] = {0};
  for (int i = 1; i <= n; ++i) {
    bool l[1000] = {0};
    int tmp = 0;
    for (int j = 0; j < a[i].size(); ++j) {
      if (!l[nm[a[i][j]]] && nm[a[i][j]] != nm[i]) {
        ++tmp;
        l[nm[a[i][j]]] = 1;
      }
    }
    zen[i] = tmp;
    if (tmp > 2) {
      f_ans = 0;
      break;
    }
  }
  if (!f_ans || res > 3) {
    cout << "NO" << endl;
  } else {
    for (int i = 1; i <= n; ++i) {
      if (zen[i] <= 1 && bl[nm[i]] == 0) {
        dfs(i, cnt + 2);
      }
    }
    if (cnt > 2) {
      cout << "NO" << endl;
    } else {
      cout << "YES" << endl;
      for (int i = 1; i <= n; ++i) {
        cout << (char(num[nm[i]] + 'a'));
      }
    }
  }
  return 0;
}
