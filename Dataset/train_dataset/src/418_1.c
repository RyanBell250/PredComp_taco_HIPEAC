#include <bits/stdc++.h>
using namespace std;
int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
char grid[1010][1010];
bool mark[1010][1010];
struct cell {
  int x, y;
  char c;
} push, now;
int main() {
  int n, i, j;
  cin >> n;
  queue<cell> q;
  push.x = 0;
  push.y = 0;
  push.c = 'C';
  q.push(push);
  mark[0][0] = true;
  int total = 0;
  char c;
  while (!q.empty()) {
    now = q.front();
    q.pop();
    if (now.c == 'C') {
      total++;
      c = '.';
      grid[now.x][now.y] = 'C';
    } else {
      c = 'C';
      grid[now.x][now.y] = '.';
    }
    for (i = 0; i < 4; i++) {
      int x = now.x + dx[i];
      int y = now.y + dy[i];
      if (x >= 0 && x < n && y >= 0 && y < n && !mark[x][y]) {
        push.x = x;
        push.y = y;
        push.c = c;
        q.push(push);
        mark[x][y] = true;
      }
    }
  }
  cout << total << endl;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) cout << grid[i][j];
    cout << endl;
  }
  return 0;
}
