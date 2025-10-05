#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 10, SQ = 150, inf = 1e9, P = 972663749, mod = 1e9 + 9;
vector<int> vec;
vector<pair<int, int> > v[maxn];
vector<vector<int> > v1, v2;
int where[maxn], f[maxn];
set<int> Hashes;
int main() {
  memset(where, -1, sizeof where);
  memset(f, -1, sizeof f);
  int q;
  scanf("%d", &q);
  while (q--) {
    v1.clear(), v2.clear(), Hashes.clear();
    int n, t;
    scanf("%d%d", &n, &t);
    for (int i = 1; i <= n; i++) {
      v[i].clear();
    }
    while (t--) {
      int Sz, hsh = 0;
      scanf("%d", &Sz);
      vec.resize(Sz);
      for (int i = 0; i < Sz; i++)
        scanf("%d", &vec[i]), hsh = (1ll * hsh * P + 1ll * vec[i]) % mod;
      if (Hashes.count(hsh)) continue;
      Hashes.insert(hsh);
      if (Sz >= SQ)
        v1.push_back(vec);
      else
        v2.push_back(vec);
    }
    for (auto &A : v1) {
      for (int i = 0; i < int((A).size()); i++) where[A[i]] = i;
      for (auto &B : v1) {
        if (A == B) break;
        int lst = inf;
        bool is = 0;
        for (int i = 0; i < int((B).size()); i++) {
          if (where[B[i]] == -1) {
            is = 1;
            continue;
          }
          if (where[B[i]] - i > lst) {
            printf("Human\n");
            for (int x : A) where[x] = -1;
            goto Hell;
          }
          if (is && where[B[i]] - i == lst) {
            printf("Human\n");
            for (int x : A) where[x] = -1;
            goto Hell;
          }
          lst = where[B[i]] - i;
          is = 0;
        }
      }
      for (auto &B : v2) {
        int lst = inf;
        bool is = 0;
        for (int i = 0; i < int((B).size()); i++) {
          if (where[B[i]] == -1) {
            is = 1;
            continue;
          }
          if (where[B[i]] - i > lst) {
            printf("Human\n");
            for (int x : A) where[x] = -1;
            goto Hell;
          }
          if (is && where[B[i]] - i == lst) {
            printf("Human\n");
            for (int x : A) where[x] = -1;
            goto Hell;
          }
          lst = where[B[i]] - i;
          is = 0;
        }
      }
      for (int x : A) where[x] = -1;
    }
    for (auto &B : v2) {
      for (int i = 0; i < int((B).size()) - 1; i++) {
        for (int j = i + 1; j < int((B).size()); j++) {
          v[B[i]].push_back({B[j], B[i + 1]});
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      for (pair<int, int> p : v[i]) {
        if (f[p.first] != -1 && f[p.first] != p.second) {
          printf("Human\n");
          for (pair<int, int> p : v[i]) f[p.first] = -1;
          goto Hell;
        }
        f[p.first] = p.second;
      }
      for (pair<int, int> p : v[i]) {
        f[p.first] = -1;
      }
    }
    printf("Robot\n");
  Hell:;
  }
  return 0;
}
