#include <bits/stdc++.h>
using namespace std;
char s[1000010];
vector<int> adj[1000010];
int par[1000010] = {0}, dp[1000010][2];
int T[1000010][26], sz = 2;
void init() {
  for (int i = 0; i < 1000010; ++i) {
    for (int j = 0; j < 26; ++j) T[i][j] = 0;
    par[i] = 0;
    dp[i][0] = dp[i][1] = 0;
  }
}
void insert(char *str) {
  int curr = 1, l = strlen(str);
  for (int i = 0; i < l; ++i) {
    int ch = str[i] - 'a';
    if (!T[curr][ch]) T[curr][ch] = sz++;
    curr = T[curr][ch];
  }
}
void construct_tree(vector<int> idx) {
  for (int i = 0; i < idx.size() - 1; ++i) {
    char *t = s + idx[i];
    int l = idx[i + 1] - idx[i];
    int curr0 = 1, curr1 = T[1][t[0] - 'a'];
    for (int j = 1; j < l; ++j) {
      curr1 = T[curr1][t[j] - 'a'];
      curr0 = T[curr0][t[j] - 'a'];
      if (!curr0) break;
      if (!par[curr1]) {
        par[curr1] = curr0;
        adj[curr0].push_back(curr1);
      }
    }
  }
}
void dfs(int v, int p) {
  dp[v][1] = 1;
  for (int i = 0; i < adj[v].size(); ++i) {
    int t = adj[v][i];
    dfs(t, v);
    dp[v][1] += dp[t][0];
    dp[v][0] += max(dp[t][1], dp[t][0]);
  }
  adj[v].clear();
}
void solve() {
  int n, st = 0;
  scanf("%d", &n);
  vector<int> idx;
  for (int i = 0; i < n; ++i) {
    idx.push_back(st);
    scanf("%s", s + st);
    insert(s + st);
    st += strlen(s + st);
  }
  idx.push_back(st);
  construct_tree(idx);
  int ans = 0;
  for (int i = 2; i < sz; ++i) {
    if (!par[i]) {
      dfs(i, i);
      ans += max(dp[i][0], dp[i][1]);
    }
  }
  printf("%d\n", ans);
}
int main() {
  init();
  int t;
  scanf("%d", &t);
  while (t--) {
    for (int i = 1; i < sz; ++i) {
      par[i] = 0;
      dp[i][0] = dp[i][1] = 0;
      for (int j = 0; j < 26; ++j) T[i][j] = 0;
    }
    sz = 2;
    solve();
  }
  return 0;
}
