#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b) {
  int t;
  while (a > 0) t = b % a, b = a, a = t;
  return b;
}
long long floor_sum(long long n, long long m, long long a, long long b) {
  long long ans = 0;
  if (a >= m) {
    ans += (n - 1) * n * (a / m) / 2;
    a %= m;
  }
  if (b >= m) {
    ans += n * (b / m);
    b %= m;
  }
  long long y_max = (a * n + b) / m, x_max = (y_max * m - b);
  if (y_max == 0) return ans;
  ans += (n - (x_max + a - 1) / a) * y_max;
  ans += floor_sum(y_max, a, m, (a - x_max % a) % a);
  return ans;
}
long long int getNum(int a, int b, long long int c) {
  if (c < 0)
    return 0;
  else
    return floor_sum(c / a + 1, b, a, c % a) + c / a + 1;
}
int a[50000], num[100001], p[100001];
vector<pair<int, int> > v, v2;
int main() {
  int i;
  int n;
  scanf("%d", &n);
  for (i = 0; i < n; i++) scanf("%d", &a[i]);
  int j;
  for (i = 0; i < n; i++) {
    v.push_back(make_pair(a[i], 1));
    for (j = 0; j < v.size(); j++)
      v[j].first = gcd(v[j].first, a[i]), num[v[j].first] += v[j].second;
    sort(v.begin(), v.end());
    for (j = 0; j < v.size(); j++) {
      if (!v2.empty() && (v2.back().first == v[j].first))
        v2.back().second += v[j].second;
      else
        v2.push_back(v[j]);
    }
    v = v2, v2.clear();
  }
  for (i = 1; i <= 100000; i++) {
    if (num[i] > 0)
      p[i] = i;
    else
      p[i] = p[i - 1];
  }
  long long int n2 = (long long int)n * (n + 1) / 2;
  long long int n3 = n2 * (n2 + 1) / 2;
  long long int l = 1, r = 1e15;
  while (l < r) {
    long long int m = (l + r) / 2;
    long long int ans = 0, s = 0, s2 = 0;
    j = 1;
    for (i = 1; i <= 100000; i++) {
      if (num[i] > 0) {
        while ((s >= 0) && (s + (long long int)num[i] * i > m)) {
          s -= (long long int)num[j] * j, s2 -= num[j];
          if ((num[j] > 0) && (s >= 0))
            ans += getNum(j, i, m - s - j - i) -
                   getNum(j, i, m - s - j - i - (long long int)num[j] * j) -
                   getNum(j, i, m - s - j - i - (long long int)num[i] * i);
          j++;
        }
        if (s2 >= 0) ans += num[i] * s2;
        s += (long long int)num[i] * i, s2 += num[i];
        long long int a = min((long long int)num[i], m / i);
        ans += a * (2LL * num[i] - a + 1) / 2;
        if (p[j - 1] > 0)
          j = p[j - 1], s += (long long int)num[j] * j, s2 += num[j];
      }
    }
    if (ans < (n3 + 1) / 2)
      l = m + 1;
    else
      r = m;
  }
  printf("%I64d\n", l);
  return 0;
}
