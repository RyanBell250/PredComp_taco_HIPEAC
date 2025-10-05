#include <bits/stdc++.h>
#pragma warning(disable : 4996)
#pragma comment(linker, "/STACK:336777216")
using namespace std;
int IT_MAX = 1 << 17;
int MOD = 1000000007;
const int INF = 0x3f3f3f3f;
const long long LL_INF = 0x3f3f3f3f3f3f3f3f;
const double PI = acos(-1);
const double ERR = 1e-10;
bool pchk[300050];
int cnt[300050];
vector<int> Vp;
vector<int> conn[300050];
vector<int> Vu;
set<pair<int, int> > Su;
bool dchk[300050];
int sz[300050];
int main() {
  int N, K, i, j, k;
  scanf("%d %d", &N, &K);
  for (i = 2; i <= N; i++) {
    if (pchk[i]) continue;
    Vp.push_back(i);
    for (j = 2 * i; j <= N; j += i) pchk[j] = true;
  }
  for (i = 1; i <= N; i++)
    for (j = i; j <= N; j += i) cnt[j]++;
  if (K <= 30) N = min(N, 15);
  if (N <= 15) {
    for (i = 0; i < (1 << N); i++) {
      int c = 0;
      for (j = 0; j < N; j++) {
        if (!(i & (1 << j))) continue;
        for (k = 0; k < j; k++) {
          if (!(i & (1 << k))) continue;
          if ((j + 1) % (k + 1) == 0) c++;
        }
      }
      if (c != K) continue;
      printf("Yes\n");
      c = 0;
      for (j = 0; j < N; j++)
        if (i & (1 << j)) c++;
      printf("%d\n", c);
      for (j = 0; j < N; j++)
        if (i & (1 << j)) printf("%d ", j + 1);
      printf("\n");
      return 0;
    }
    return !printf("No\n");
  }
  int pc = 0;
  for (i = 1; i <= N; i++) {
    pc += cnt[i] - 1;
    if (pc >= K) break;
  }
  if (pc < K) return !printf("No\n");
  int mx = i;
  for (i = 1; i <= mx; i++) {
    for (j = 2 * i; j <= mx; j += i) {
      conn[i].push_back(j);
      conn[j].push_back(i);
      sz[i]++;
      sz[j]++;
    }
  }
  for (i = 1; i <= mx; i++)
    if (sz[i] <= 2) Su.emplace(sz[i], i);
  while (pc != K && !Su.empty()) {
    auto it = Su.end();
    it--;
    if (pc - 1 == K) it = Su.begin();
    int x = it->second;
    pc -= sz[x];
    for (auto it : conn[x]) {
      if (dchk[it]) continue;
      if (sz[it] <= 2) Su.erase(pair<int, int>(sz[it], it));
      sz[it]--;
      if (sz[it] <= 2 && sz[it]) Su.emplace(sz[it], it);
    }
    conn[x].clear();
    Su.erase(it);
    dchk[x] = true;
  }
  if (pc != K) {
    printf("ERROR\n");
    while (1)
      ;
  }
  printf("Yes\n");
  int c = 0;
  for (i = 1; i <= mx; i++)
    if (!dchk[i]) c++;
  printf("%d\n", c);
  for (i = 1; i <= mx; i++)
    if (!dchk[i]) printf("%d ", i);
  return !printf("\n");
}
