#include <bits/stdc++.h>
using namespace std;
const long long size = 111002;
void PLL(initializer_list<long long> li) {
  for (auto beg = li.begin(); beg != li.end(); beg++) {
    if (beg != li.begin()) cout << ' ';
    cout << *beg;
  }
  cout << endl;
}
template <typename T>
void disp(T val) {
  cout << val << endl;
}
long long mod = 1e9;
vector<int> vi[3333], vii[size];
int n, q, s;
long long T[size], L[size], R[size], V[size], W[size];
int mask[size];
long long dis[size];
long long inf = 1e16;
vector<int> tmp[size * 4];
void init(int p, int l, int r) {
  if (l == r) {
    mask[l] = p;
    return;
  }
  init((p * 2), l, ((l + r) / 2));
  init((p * 2 + 1), ((l + r) / 2) + 1, r);
}
void add(int p, int l, int r, int L, int R, int j) {
  if (l == L && r == R) {
    tmp[p].push_back(j);
    return;
  }
  if (((l + r) / 2) >= R)
    add((p * 2), l, ((l + r) / 2), L, R, j);
  else if (((l + r) / 2) < L)
    add((p * 2 + 1), ((l + r) / 2) + 1, r, L, R, j);
  else {
    add((p * 2), l, ((l + r) / 2), L, ((l + r) / 2), j);
    add((p * 2 + 1), ((l + r) / 2) + 1, r, ((l + r) / 2) + 1, R, j);
  }
}
int main() {
  cin >> n >> q >> s;
  memset(mask, 0, sizeof(mask));
  init(1, 1, n);
  for (int j = 0; j < q; j++) {
    int t, l, r, v, w;
    scanf("%d", &t);
    if (t == 1) {
      scanf("%d%d%d", &v, &l, &w);
      r = l;
      t = 2;
    } else
      scanf("%d%d%d%d", &v, &l, &r, &w);
    T[j] = t;
    L[j] = l;
    R[j] = r;
    V[j] = v;
    W[j] = w;
    if (t == 3) {
      add(1, 1, n, l, r, j);
    } else
      vii[v].push_back(j);
  }
  for (int i = 0; i <= n; i++) dis[i] = inf;
  priority_queue<pair<long long, pair<long long, long long>>> Q;
  dis[s] = 0;
  Q.push(pair<long long, pair<long long, long long>>(
      0, pair<long long, long long>(s, s)));
  set<int> S;
  for (int i = 1; i <= n; i++) S.insert(i);
  while (Q.size()) {
    auto p = Q.top();
    Q.pop();
    int u = p.second.first;
    int v = p.second.second;
    for (auto it = S.lower_bound(u); it != S.end() && *it <= v;) {
      int k = *it;
      dis[k] = -p.first;
      auto tt = it;
      it++;
      S.erase(tt);
      for (auto idx : vii[k]) {
        pair<long long, pair<long long, long long>> tmp;
        tmp.first = -(dis[k] + W[idx]);
        tmp.second.first = L[idx];
        tmp.second.second = R[idx];
        Q.push(tmp);
      }
      int p = mask[k];
      while (p > 0) {
        for (auto idx : tmp[p]) {
          pair<long long, pair<long long, long long>> tmp;
          tmp.first = -(dis[k] + W[idx]);
          tmp.second.first = V[idx];
          tmp.second.second = V[idx];
          Q.push(tmp);
        }
        tmp[p].clear();
        p /= 2;
      }
    }
  }
  for (int i = 1; i <= n; i++) {
    if (dis[i] == inf) dis[i] = -1;
    printf("%I64d ", dis[i]);
  }
}
