#include <bits/stdc++.h>
using namespace std;
int const N = 20;
int seat[N];
vector<bool> used;
int n;
long long year;
int m;
int cover[N];
long long dp[(1 << (16))];
long long calc_remain(int start) {
  int to_enum = ((1 << (n - start)) - 1) << start;
  for (int subset = to_enum;; subset--, subset &= to_enum) {
    dp[subset] = 0;
    if (subset == 0) break;
  }
  dp[0] = 1;
  int cnt = 0;
  for (int n_ = (n), i = 0; i < n_; ++i) {
    if (used[i]) continue;
    for (int subset = to_enum;; subset--, subset &= to_enum) {
      if (bitset<32>(subset).count() == cnt) {
        for (int k = start; k < n; ++k)
          if (((1 << (k)) & subset) == 0) {
            if ((cover[k] & subset) == (cover[k] & to_enum)) {
              bool consitence_previous = true;
              for (int n_ = (start), j = 0; j < n_; ++j) {
                if ((1 << (j)) & cover[k]) {
                  if (seat[j] > i) consitence_previous = false;
                }
                if ((1 << (k)) & cover[j]) {
                  if (seat[j] < i) consitence_previous = false;
                }
              }
              if (consitence_previous) {
                dp[subset ^ (1 << (k))] += dp[subset];
              }
            }
          }
      }
      if (subset == 0) break;
    }
    cnt++;
  }
  return dp[to_enum];
}
int main() {
  while (cin >> n >> year >> m) {
    year -= 2000;
    used = vector<bool>(n, false);
    memset(cover, 0, (sizeof cover));
    for (int n_ = (m), i = 0; i < n_; ++i) {
      int a, b;
      scanf("%d%d", &a, &b);
      a--;
      b--;
      cover[b] |= (1 << (a));
    }
    memset(seat, -1, (sizeof seat));
    long long discard = 0;
    bool has_solution;
    for (int n_ = (n), i = 0; i < n_; ++i) {
      has_solution = false;
      long long remain;
      for (int n_ = (n), cand = 0; cand < n_; ++cand)
        if (!used[cand]) {
          used[cand] = true;
          seat[i] = cand;
          remain = calc_remain(i + 1);
          if (remain + discard >= year) {
            has_solution = true;
            break;
          }
          discard += remain;
          seat[i] = -1;
          used[cand] = false;
        }
      if (!has_solution) break;
    }
    if (!has_solution) {
      puts("The times have changed");
    } else {
      for (int n_ = (n), i = 0; i < n_; ++i) {
        if (i) putchar(' ');
        printf("%d", seat[i] + 1);
      }
      puts("");
    }
  }
  return 0;
}
