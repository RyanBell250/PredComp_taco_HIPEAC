#include <bits/stdc++.h>
using namespace std;
int d[2005];
queue<int> q;
int main() {
  int n, k, i, a;
  scanf("%d %d", &n, &k);
  for (i = 0; i <= 2000; i++) d[i] = 999999;
  for (i = 1; i <= k; i++) {
    scanf("%d", &a);
    d[a - n + 1000] = 1;
  }
  for (i = 0; i <= 2000; i++)
    if (d[i] == 1) q.push(i);
  while (q.size()) {
    a = q.front();
    q.pop();
    for (i = 0; i <= 2000; i++)
      if (d[i] == 1 && d[a + i - 1000] == 999999) {
        q.push(a + i - 1000);
        d[a + i - 1000] = d[a] + 1;
      }
  }
  if (d[1000] == 999999)
    cout << -1 << endl;
  else
    cout << d[1000] << endl;
  return 0;
}
