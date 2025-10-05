#include <bits/stdc++.h>
using namespace std;
vector<int> tmp;
vector<int> adj[100001];
int c[100001], x;
map<int, int> cnt;
long long t2 = 0;
int dfs(int node, int pa) {
  if (adj[node].size() == 1 && node != 1) {
    x ^= c[node];
    tmp.push_back(c[node]);
    return 1;
  }
  int curr = 0;
  for (int i = 0; i < adj[node].size(); ++i) {
    if (adj[node][i] == pa) continue;
    curr = max(curr, dfs(adj[node][i], node));
  }
  curr++;
  if (curr % 2) {
    x ^= c[node];
    tmp.push_back(c[node]);
    return curr;
  }
  cnt[c[node]]++;
  t2++;
  return curr;
}
int main() {
  int n, p;
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> c[i];
  for (int i = 2; i <= n; ++i) {
    cin >> p;
    adj[i].push_back(p);
    adj[p].push_back(i);
  }
  dfs(1, -1);
  long long ans = 0;
  if (x == 0) {
    ans = tmp.size();
    ans *= (ans - 1);
    ans /= 2;
    t2 *= (t2 - 1);
    t2 /= 2;
    ans += t2;
  }
  for (auto it : tmp) {
    ans += cnt[x ^ it];
  }
  cout << ans;
}
