#include <bits/stdc++.h>
using namespace std;
namespace gao {
int B = 512, N = 300001, tot = N / B;
long long sumb[1010], sumpre[303000];
long long cb[1010], cpre[303000];
void add(int pos) {
  for (int i = pos / B + 1; i <= tot; ++i) sumb[i] += pos, cb[i] += 1;
  for (int i = pos; i / B == pos / B; ++i) {
    sumpre[i] += pos, cpre[i] += 1;
  }
}
pair<long long, long long> que(int pos) {
  pos = min(pos, N);
  return (pair<long long, long long>){sumb[pos / B] + sumpre[pos],
                                      cb[pos / B] + cpre[pos]};
}
}  
int n;
long long ans;
const int maxn = 300000;
int main() {
  for (cin >> n; n--;) {
    int x;
    scanf("%d", &x);
    {
      pair<long long, long long> las = {0ll, 0ll};
      for (int i = 0; i * x <= maxn; ++i) {
        pair<long long, long long> now = gao::que((i + 1) * x - 1);
        long long sum = now.first - las.first, c = now.second - las.second;
        las = now;
        ans += sum - c * x * i;
      }
    }
    {
      pair<long long, long long> las = {0ll, 0ll};
      int i = 1, sqr = sqrt(x) - 3;
      for (; i < x;) {
        int ne = i;
        if (i >= sqr) ne = x / (x / i);
        pair<long long, long long> now = gao::que(ne);
        long long sum = now.first - las.first, c = now.second - las.second;
        las = now;
        ans += x * c - sum * (x / i);
        i = ne + 1;
      }
      ans += (gao::que(maxn).second - gao::que(x).second) * x;
    }
    gao::add(x);
    printf("%lld ", ans);
  }
  puts("");
}
