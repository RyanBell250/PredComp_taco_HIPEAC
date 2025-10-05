#include <bits/stdc++.h>
using namespace std;
int n, m, k, j;
int d[100001];
vector<int> ans;
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n + m; i++) {
    while (d[i] < k || ans[ans.size() - 1] + n - 1 == i) {
      ans.push_back(i);
      for (j = i; j <= i + n - 1; j++) d[j]++;
    }
  }
  int si = ans.size();
  printf("%d\n", si);
  for (int i = 0; i < si; i++) printf("%d ", ans[i]);
  return 0;
}
