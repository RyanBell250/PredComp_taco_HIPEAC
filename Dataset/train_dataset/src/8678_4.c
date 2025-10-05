#include <bits/stdc++.h>
using namespace std;
const long long mod = 1e9 + 7;
const long long inf = 5e18;
long long h, w;
vector<string> maze(1e3 + 10);
vector<vector<long long> > ans(1e3 + 10, vector<long long>(1e3 + 10));
vector<long long> idx = {1, 0, -1, 0};
vector<long long> idy = {0, 1, 0, -1};
long long dfs(long long y, long long x, long long n) {
  if (ans[y][x] > -1) return ans[y][x];
  ans[y][x] = 0;
  for (long long i = 0; i < 4; i++) {
    long long nx = x + idx[i];
    long long ny = y + idy[i];
    if (nx > -1 && nx < w && ny > -1 && ny < h && maze[ny][nx] == '#') {
      dfs(ny, nx, n);
    }
  }
  return ans[y][x] = n;
}
int main() {
  cin >> h >> w;
  for (long long i = 0; i < h; i++) cin >> maze[i];
  set<long long> ch, cw;
  for (long long i = 0; i < h; i++) {
    for (long long j = 0; j < w; j++) {
      if (maze[i][j] == '#') {
        ch.insert(i);
        cw.insert(j);
      }
    }
  }
  set<long long> wh, ww;
  for (long long i = 0; i < h; i++) {
    long long tmp = 1;
    for (long long j = 0; j < w; j++) {
      if (maze[i][j] == '#') tmp = 0;
    }
    if (tmp) wh.insert(i);
  }
  for (long long i = 0; i < w; i++) {
    long long tmp = 1;
    for (long long j = 0; j < h; j++) {
      if (maze[j][i] == '#') tmp = 0;
    }
    if (tmp) ww.insert(i);
  }
  if (wh.size() && ww.size()) {
    for (long long p : wh) {
      ch.insert(p);
    }
    for (long long p : ww) {
      cw.insert(p);
    }
  }
  long long f = 0;
  if (ch.size() < h || cw.size() < w) {
    f = 1;
  }
  for (long long i = 0; i < h; i++) {
    long long tmp = 0;
    for (long long j = 0; j < w; j++) {
      if (maze[i][j] == '#') {
        if (tmp != 2)
          tmp = 1;
        else
          f = 1;
      } else {
        if (tmp) tmp = 2;
      }
    }
  }
  for (long long i = 0; i < w; i++) {
    long long tmp = 0;
    for (long long j = 0; j < h; j++) {
      if (maze[j][i] == '#') {
        if (tmp != 2)
          tmp = 1;
        else
          f = 1;
      } else {
        if (tmp) tmp = 2;
      }
    }
  }
  for (long long i = 0; i < h; i++) {
    for (long long j = 0; j < w; j++) {
      ans[i][j] = -1;
    }
  }
  long long cnt = 1;
  set<long long> check;
  for (long long i = 0; i < h; i++) {
    for (long long j = 0; j < w; j++) {
      if (maze[i][j] == '#') {
        if (!check.count(dfs(i, j, cnt))) {
          check.insert(cnt);
          cnt++;
        }
      }
    }
  }
  if (f) {
    cout << -1 << endl;
    return 0;
  }
  cout << cnt - 1 << endl;
}
