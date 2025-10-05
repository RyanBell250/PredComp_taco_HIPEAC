#include <bits/stdc++.h>
using namespace std;
bool g[200][200];
int w[200];
bool flag[200];
bool isLeaf[200];
int n;
vector<pair<int, int> > v;
vector<int> firstPart;
vector<int> secondPart;
void printW(void) {
  for (int i = 0; i < n; i++) printf("%d ", w[i]);
  printf("\n");
  return;
}
void dfs(int x, int level) {
  w[x] = level;
  flag[x] = true;
  isLeaf[x] = true;
  for (int i = 0; i < n; i++)
    if (g[x][i] && !flag[i]) {
      isLeaf[x] = false;
      dfs(i, level + 1);
    }
  return;
}
bool judgeLeaf(int x) {
  int outd = 0;
  for (int i = 0; i < n; i++)
    if (g[x][i]) outd++;
  return outd == 1;
}
int getMaxPath(int x) {
  if (judgeLeaf(x)) {
    memset(w, 0, sizeof(w));
    memset(flag, false, sizeof(flag));
    memset(isLeaf, false, sizeof(isLeaf));
    dfs(x, 0);
    int res = 0;
    for (int i = 0; i < n; i++)
      if (isLeaf[i]) res = max(res, w[i]);
    return res;
  }
  return 0;
}
void floodfill(int x, vector<int> &partv) {
  flag[x] = true;
  partv.push_back(x);
  for (int i = 0; i < n; i++)
    if (g[x][i] && !flag[i]) floodfill(i, partv);
  return;
}
int solve(void) {
  int res = 0;
  for (int i = 0; i < v.size(); i++) {
    g[v[i].first][v[i].second] = g[v[i].second][v[i].first] = false;
    firstPart.clear();
    secondPart.clear();
    memset(flag, false, sizeof(flag));
    floodfill(v[i].first, firstPart);
    floodfill(v[i].second, secondPart);
    if (firstPart.size() != 1 && secondPart.size() != 1) {
      int max_first = 0;
      int max_second = 0;
      for (int j = 0; j < firstPart.size(); j++)
        max_first = max(max_first, getMaxPath(firstPart[j]));
      for (int k = 0; k < secondPart.size(); k++)
        max_second = max(max_second, getMaxPath(secondPart[k]));
      if (max_first * max_second > res) {
        res = max_first * max_second;
      }
    }
    g[v[i].first][v[i].second] = g[v[i].second][v[i].first] = true;
  }
  return res;
}
int main(void) {
  int a, b;
  while (scanf("%d", &n) != EOF) {
    v.clear();
    memset(g, false, sizeof(g));
    for (int i = 1; i < n; i++) {
      scanf("%d%d", &a, &b);
      a--;
      b--;
      v.push_back(make_pair(a, b));
      g[a][b] = g[b][a] = true;
    }
    printf("%d\n", solve());
  }
  return 0;
}
