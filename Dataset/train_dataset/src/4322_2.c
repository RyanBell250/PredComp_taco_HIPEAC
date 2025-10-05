#include <bits/stdc++.h>
using namespace std;
int n, a[210], m;
priority_queue<int> q;
priority_queue<int, deque<int>, greater<int> > q2;
int main() {
  while (scanf("%d%d", &n, &m) != EOF) {
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    int ans = a[0];
    for (int i = 0; i < n; ++i) {
      for (int j = i; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
          if (k >= i && k <= j)
            q2.push(a[k]);
          else
            q.push(a[k]);
        }
        for (int k = 0; k < m; ++k) {
          if (q.empty() || q2.empty()) break;
          int s = q2.top();
          int l = q.top();
          if (s >= l) break;
          q2.pop();
          q.pop();
          q2.push(l);
          q.push(s);
        }
        int sum = 0;
        while (!q2.empty()) {
          sum += q2.top();
          q2.pop();
        }
        ans = max(ans, sum);
        while (!q.empty()) {
          q.pop();
        }
      }
    }
    printf("%d\n", ans);
  }
  return 0;
}
