#include <bits/stdc++.h>
using namespace std;
int d, s;
bool vis[510][5010];
queue<pair<int, int> > q;
pair<pair<int, int>, int> p[510][5010];
void bfs() {
  vis[0][0] = true;
  q.push(make_pair(0, 0));
  while (!q.empty()) {
    int x = q.front().first, y = q.front().second;
    q.pop();
    for (int i = 0; i < 10; i++) {
      int x_ = (x * 10 + i) % d, y_ = y + i;
      if (y_ <= s && !vis[x_][y_]) {
        vis[x_][y_] = true;
        p[x_][y_] = make_pair(make_pair(x, y), i);
        q.push(make_pair(x_, y_));
      }
    }
  }
}
void output(int x, int y) {
  if (!x && !y) {
    return;
  }
  output(p[x][y].first.first, p[x][y].first.second);
  putchar('0' + p[x][y].second);
}
int main() {
  cin >> d >> s;
  bfs();
  if (!vis[0][s]) {
    puts("-1");
  } else {
    output(0, s);
  }
  return 0;
}
