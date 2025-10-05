#include <bits/stdc++.h>
using namespace std;
const long long MAX = 250010;
vector<int> conn[MAX];
vector<int> route;
int n, m, k, lim_a, lim_b;
int chk[MAX], cnt_b;
vector<int> ans_b[MAX];
int f(int first) {
  int cnt = 0;
  chk[first] = route.size();
  route.push_back(first);
  for (auto second : conn[first]) {
    if (chk[second] == -1) {
      if (f(second)) return 1;
      cnt++;
    }
  }
  if (cnt == 0) {
    if (route.size() >= lim_a) {
      printf("PATH\n%d\n", route.size());
      for (auto second : route) printf("%d ", second);
      return 1;
    }
    int y1 = -1, y2 = -1;
    for (auto second : conn[first]) {
      if (chk[first] - chk[second] > 1) {
        if (y1 == -1)
          y1 = second;
        else
          y2 = second;
      }
      if (y2 != -1) break;
    }
    if ((chk[first] - chk[y1]) % 3 != 2) {
      for (int i = chk[y1]; i <= chk[first]; i++)
        ans_b[cnt_b].push_back(route[i]);
    } else if ((chk[first] - chk[y2]) % 3 != 2) {
      for (int i = chk[y2]; i <= chk[first]; i++)
        ans_b[cnt_b].push_back(route[i]);
    } else {
      if (chk[y1] > chk[y2]) swap(y1, y2);
      for (int i = chk[y1]; i <= chk[y2]; i++) ans_b[cnt_b].push_back(route[i]);
      ans_b[cnt_b].push_back(route[chk[first]]);
    }
    cnt_b++;
    if (lim_b == cnt_b) {
      printf("CYCLES\n");
      for (int i = 0; i < cnt_b; i++) {
        printf("%d\n", ans_b[i].size());
        for (int j = ans_b[i].size() - 1; j >= 0; j--)
          printf("%d ", ans_b[i][j]);
        printf("\n");
      }
      return 1;
    }
  }
  route.pop_back();
  return 0;
}
int main() {
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < m; i++) {
    int t1, t2;
    scanf("%d%d", &t1, &t2);
    conn[t1].push_back(t2);
    conn[t2].push_back(t1);
  }
  for (int i = 1; i <= n; i++) chk[i] = -1;
  lim_a = (n - 1) / k + 1;
  lim_b = k;
  f(1);
  return 0;
}
