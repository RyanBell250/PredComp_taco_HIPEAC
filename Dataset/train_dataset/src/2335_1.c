#include <bits/stdc++.h>
using namespace std;
const int N = 200005;
bool vis[N * 5];
vector<int> p;
int n, ord[N];
long long ans = 0, a[N];
int main() {
  srand(time(NULL));
  for (int i = 2; i <= 1000000; i++)
    if (!vis[i]) {
      p.push_back(i);
      for (int j = i + i; j <= 1000000; j += i) vis[j] = true;
    }
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%lld", &a[i]), ord[i] = i, ans += a[i] % 2;
  random_shuffle(ord + 1, ord + n + 1);
  vector<long long> v;
  for (int i = 1; i <= min(100, n); i++) {
    for (int dlt = -1; dlt <= 1; dlt++) {
      long long tmp = a[ord[i]] + dlt;
      if (tmp <= 1) continue;
      for (int i = 0; 1LL * p[i] * p[i] <= tmp && i < p.size(); i++)
        if (tmp % p[i] == 0) {
          v.push_back(p[i]);
          while (tmp % p[i] == 0) tmp /= p[i];
        }
      if (tmp > 1) v.push_back(tmp);
    }
  }
  sort(v.begin(), v.end());
  v.resize(unique(v.begin(), v.end()) - v.begin());
  for (int i = 0; i < v.size(); i++) {
    long long res = 0;
    for (int j = 1; j <= n; j++)
      if (a[j] <= v[i])
        res += v[i] - a[j];
      else
        res += min(a[j] % v[i], v[i] - a[j] % v[i]);
    ans = min(ans, res);
  }
  printf("%lld\n", ans);
  return 0;
}
