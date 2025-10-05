#include <bits/stdc++.h>
using namespace std;
vector<int> vv[101];
bitset<5100> dp[101];
vector<int> getPerm(int n, int k) {
  if (n == 1) return vector<int>(1, 0);
  int i, j;
  for (i = 1; i < n; i++) {
    if ((i >= 3) && dp[n - i][k - i - 1]) {
      vector<int> v = getPerm(n - i, k - i - 1);
      for (j = 0; j < v.size(); j++) v[j] += vv[i + 1][0];
      for (j = 1; j < i + 1; j++) {
        if (vv[i + 1][j] > vv[i + 1][0])
          v.push_back(vv[i + 1][j] + n - i - 1);
        else
          v.push_back(vv[i + 1][j]);
      }
      return v;
    } else if ((k >= (i + 1) * (i + 2) / 2 - 1) &&
               dp[n - i][k - (i + 1) * (i + 2) / 2 + 1]) {
      vector<int> v = getPerm(n - i, k - (i + 1) * (i + 2) / 2 + 1);
      if (max_element(v.begin(), v.end()) - v.begin() >
          min_element(v.begin(), v.end()) - v.begin())
        reverse(v.begin(), v.end());
      for (j = 0; j < i; j++) v.push_back(n - i + j);
      return v;
    }
  }
  return vector<int>();
}
int main() {
  int i, j, k;
  dp[1][1] = 1;
  for (i = 2; i <= 100; i++) {
    for (j = 1; j < i; j++) {
      if (j >= 3) dp[i] |= dp[i - j] << (j + 1);
      dp[i] |= dp[i - j] << ((j + 1) * (j + 2) / 2 - 1);
    }
    if (i >= 4) {
      for (j = 0; j < i; j++) vv[i].push_back(j);
      while (1) {
        int c = 0;
        random_shuffle(vv[i].begin(), vv[i].end());
        for (j = 0; j < vv[i].size(); j++) {
          int s = vv[i][j], b = vv[i][j];
          for (k = j; k < vv[i].size(); k++) {
            s = min(s, vv[i][k]), b = max(b, vv[i][k]);
            if (b - s == k - j) c++;
          }
        }
        if (c == i + 1) break;
      }
    }
  }
  int q, n;
  scanf("%d", &q);
  for (i = 0; i < q; i++) {
    scanf("%d %d", &n, &k);
    if (!dp[n][k])
      printf("NO\n");
    else {
      printf("YES\n");
      vector<int> v = getPerm(n, k);
      for (j = 0; j < n; j++) printf("%d ", v[j] + 1);
      printf("\n");
    }
  }
  return 0;
}
