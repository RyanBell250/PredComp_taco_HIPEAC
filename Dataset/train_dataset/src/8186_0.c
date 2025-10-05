#include <bits/stdc++.h>
using namespace std;
const int INF = (1LL << 30) - 1;
const long long int LINF = (1LL << 62) - 1;
const int MOD = (int)1e9 + 7;
const int NMAX = (int)1e6;
int P, K;
int root[NMAX + 5];
unordered_set<int> M;
int expLog(int B, int E) {
  int Q = B, sol = 1;
  for (int i = E; i; i /= 2) {
    if (i & 1) sol = (sol * 1LL * Q) % MOD;
    Q = (Q * 1LL * Q) % MOD;
  }
  return sol;
}
int find(int x) {
  if (x != root[x]) root[x] = find(root[x]);
  return root[x];
}
void unite(int x, int y) {
  x = find(x), y = find(y);
  root[y] = x;
}
int main() {
  cin.sync_with_stdio(false);
  scanf("%d%d", &P, &K);
  if (K == 0) {
    printf("%d\n", expLog(P, P - 1));
    return 0;
  } else if (K == 1) {
    printf("%d\n", expLog(P, P));
    return 0;
  }
  for (int i = 1; i <= P - 1; i++) root[i] = i;
  for (int i = 1, j; i <= P - 1; i++) {
    j = (K * 1LL * i) % P;
    unite(i, j);
  }
  for (int i = 1; i <= P - 1; i++) M.insert(find(i));
  int sol = expLog(P, (int)M.size());
  printf("%d\n", sol);
  return 0;
}
