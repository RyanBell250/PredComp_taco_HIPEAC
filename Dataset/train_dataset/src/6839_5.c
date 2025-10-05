#include <bits/stdc++.h>
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;
int n, m, q;
int tree[2 * 262144][2][5 + 1];
bool lazy[2 * 262144];
void pullChildren(int idx) {
  for (int i = 0; i < (2); i++)
    for (int j = 0; j < (m + 1); j++)
      tree[idx][i][j] = tree[2 * idx][i][tree[2 * idx + 1][i][j]];
}
void buildTree(int idx) {
  if (idx >= 262144) return;
  buildTree(2 * idx);
  buildTree(2 * idx + 1);
  pullChildren(idx);
}
void propLazy(int idx) {
  if (lazy[idx]) {
    lazy[2 * idx] ^= 1;
    swap(tree[2 * idx][0], tree[2 * idx][1]);
  }
  if (lazy[idx]) {
    lazy[2 * idx + 1] ^= 1;
    swap(tree[2 * idx + 1][0], tree[2 * idx + 1][1]);
  }
  lazy[idx] = 0;
}
void flipRange(int idx, int s, int e, int l, int r) {
  if (e <= l || s >= r) return;
  if (s >= l && e <= r) {
    swap(tree[idx][0], tree[idx][1]);
    lazy[idx] ^= 1;
    return;
  }
  propLazy(idx);
  int mid = (s + e) >> 1;
  flipRange(2 * idx, s, mid, l, r);
  flipRange(2 * idx + 1, mid, e, l, r);
  pullChildren(idx);
}
int evaluate(int idx, int s, int e, int l, int r, int v) {
  if (e <= l || s >= r) return v;
  if (s >= l && e <= r) return tree[idx][0][v];
  propLazy(idx);
  int mid = (s + e) >> 1;
  return evaluate(2 * idx, s, mid, l, r,
                  evaluate(2 * idx + 1, mid, e, l, r, v));
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m >> q;
  for (int i = 0; i < (n); i++) {
    for (int j = 0; j < (m + 1); j++) tree[262144 + i][0][j] = min(m, j + 1);
    for (int j = 0; j < (m); j++) tree[262144 + i][1][j] = j + 1;
    tree[262144 + i][1][m] = 0;
  }
  for (int i = 0; i < (n); i++) {
    long long a;
    cin >> a;
    if (a % 2 == 1) swap(tree[262144 + i][0], tree[262144 + i][1]);
  }
  buildTree(1);
  for (int i = 0; i < (q); i++) {
    int t;
    cin >> t;
    if (t == 1) {
      int l, r;
      long long d;
      cin >> l >> r >> d;
      l--;
      if (d & 1) flipRange(1, 0, 262144, l, r);
    } else {
      int l, r;
      cin >> l >> r;
      l--;
      int v = evaluate(1, 0, 262144, l, r, m);
      if (v == 0)
        cout << "2\n";
      else
        cout << "1\n";
    }
  }
}
