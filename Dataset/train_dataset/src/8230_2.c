#include <bits/stdc++.h>
using namespace std;
int dig[505][5005];
int dist[505][5005];
pair<int, int> par[505][5005];
int main() {
  int d, s;
  scanf("%d %d", &d, &s);
  queue<pair<int, int> > Q;
  Q.push({0, s});
  memset(dist, -1, sizeof dist);
  dist[0][s] = 0;
  while (!Q.empty()) {
    auto top = Q.front();
    Q.pop();
    for (int i = 0; i <= 9; i++) {
      int mod = (top.first * 10 + i) % d;
      int sd = top.second - i;
      if (sd >= 0 && dist[mod][sd] == -1) {
        dist[mod][sd] = dist[top.first][top.second] + 1;
        par[mod][sd] = top;
        dig[mod][sd] = i;
        Q.push({mod, sd});
      }
    }
  }
  if (dist[0][0] == -1) {
    printf("-1\n");
    return 0;
  }
  int x = 0, y = 0;
  string st;
  while (1) {
    st += char(dig[x][y] + '0');
    auto nw = par[x][y];
    x = nw.first;
    y = nw.second;
    if (x == 0 && y == s) break;
  }
  reverse(st.begin(), st.end());
  printf("%s\n", st.c_str());
  return 0;
}
