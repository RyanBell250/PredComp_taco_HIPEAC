#include <bits/stdc++.h>
using namespace std;
int k[250005];
vector<int> a[250005], c[250005];
int height[10000005], L[10000005], R[10000005];
long long cost[10000005], dp[10000005];
int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &k[i]);
    a[i].resize(k[i] + 1);
    c[i].resize(k[i] + 1);
    for (int j = 1; j <= k[i]; j++) scanf("%d", &a[i][j]);
    for (int j = 1; j <= k[i]; j++) scanf("%d", &c[i][j]);
  }
  int q;
  scanf("%d", &q);
  int idx = 0;
  for (int i = 1; i <= q; i++) {
    int id, mul;
    scanf("%d%d", &id, &mul);
    for (int j = 1; j <= k[id]; j++) {
      idx++;
      height[idx] = a[id][j];
      cost[idx] = c[id][j] * 1ll * mul;
    }
  }
  stack<int> st;
  for (int i = 1; i <= m; i++) {
    L[i] = max(1, i - height[i] + 1);
    while (!st.empty()) {
      int u = st.top();
      if (height[i] - i > -u) {
        L[i] = min(L[i], L[u]);
        st.pop();
      } else
        break;
    }
    st.push(i);
  }
  while (!st.empty()) st.pop();
  for (int i = m; i >= 1; i--) {
    R[i] = min(m, i + height[i] - 1);
    while (!st.empty()) {
      int u = st.top();
      if (height[i] + i > u) {
        R[i] = max(R[i], R[u]);
        st.pop();
      } else
        break;
    }
    st.push(i);
  }
  while (!st.empty()) st.pop();
  for (int i = 1; i <= m; i++) dp[i] = 1e18;
  stack<pair<long long, int> > st2;
  for (int i = 1; i <= m; i++) {
    while (!st2.empty() && st2.top().second < i) st2.pop();
    while (!st2.empty() && st2.top().first > dp[i - 1] + cost[i] &&
           st2.top().second == R[i])
      st2.pop();
    while (st2.empty() || dp[i - 1] + cost[i] < st2.top().first)
      st2.push(make_pair(dp[i - 1] + cost[i], R[i]));
    dp[i] = min(dp[L[i] - 1] + cost[i], st2.top().first);
  }
  printf("%lld\n", dp[m]);
}
