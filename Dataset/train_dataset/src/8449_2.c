#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
long long n, ans, tp, tmp;
long long p;
queue<long long> q;
string s;
int main() {
  scanf("%lld%lld", &n, &p);
  for (int i = 1; i < 10; i++) q.push(i);
  while (n--) {
    tp = q.front();
    tmp = tp;
    tp *= 10;
    for (int i = 0; i < 10; ++i) {
      tp += i;
      q.push(tp);
      tp -= i;
    }
    tp /= 10;
    while (tmp > 0) {
      tp *= 10;
      tp += tmp % 10;
      tmp /= 10;
    }
    ans = (ans % p + tp % p) % p;
    q.pop();
  }
  printf("%lld", ans);
  return 0;
}
