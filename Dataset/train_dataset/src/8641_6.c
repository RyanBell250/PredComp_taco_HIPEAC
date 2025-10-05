#include <bits/stdc++.h>
using namespace std;
int ind, N;
map<int, int> U;
pair<int, int> T[200005];
void read() {
  int i, a, b, t;
  scanf("%d", &N);
  for (i = 1; i <= N; i++) {
    scanf("%d %d", &a, &b);
    t = U[a];
    if (t)
      a = t;
    else {
      U[a] = ++ind;
      a = ind;
    }
    t = U[b];
    if (t)
      b = t;
    else {
      U[b] = ++ind;
      b = ind;
    }
    T[a].first++;
    if (a != b) T[b].second++;
  }
}
bool cmp(pair<int, int> a, pair<int, int> b) {
  return (a.first + a.second) > (b.first + b.second);
}
void solve() {
  int i, res = INT_MAX, n2 = N / 2;
  if (N & 1) n2++;
  sort(T + 1, T + ind + 1, cmp);
  for (i = 1; i <= ind; i++) {
    if (T[i].first + T[i].second < n2) break;
    res = ((res) < (((0) > (n2 - T[i].first) ? (0) : (n2 - T[i].first)))
               ? (res)
               : (((0) > (n2 - T[i].first) ? (0) : (n2 - T[i].first))));
  }
  if (res != INT_MAX)
    printf("%d\n", res);
  else
    printf("%d\n", -1);
}
int main() {
  read();
  solve();
}
