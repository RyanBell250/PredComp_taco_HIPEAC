#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
struct segment {
  int l, r;
  long long w;
  bool operator<(const segment &rhs) const { return (l < rhs.l); }
};
multiset<long long> Ms;
set<segment> S;
int A[MAXN];
long long pre[MAXN];
int main() {
  int N;
  scanf("%d", &N);
  for (int i = 1; i <= N; ++i) {
    scanf("%d", &A[i]);
    pre[i] = pre[i - 1] + A[i];
  }
  Ms.insert(pre[N]);
  Ms.insert(0);
  S.insert((segment){1, N, pre[N]});
  int x;
  while (N--) {
    scanf("%d", &x);
    set<segment>::iterator it = S.upper_bound((segment){x, MAXN, -1});
    --it;
    long long w = it->w;
    Ms.erase(Ms.find(w));
    int l = it->l, r = it->r;
    S.erase(it);
    if (l <= x - 1) {
      S.insert((segment){l, x - 1, pre[x - 1] - pre[l - 1]});
      Ms.insert(pre[x - 1] - pre[l - 1]);
    }
    if (x + 1 <= r) {
      S.insert((segment){x + 1, r, pre[r] - pre[x]});
      Ms.insert(pre[r] - pre[x]);
    }
    printf("%lld\n", *(--(Ms.end())));
  }
  return 0;
}
