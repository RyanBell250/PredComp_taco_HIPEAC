#include <bits/stdc++.h>
using namespace std;
const int maxn = 200005;
int ans, n, k;
int a[maxn], a_sum[maxn], b[maxn], b_sum[maxn], f[1000000][2], state[maxn];
bool pp[maxn];
void insert(int x, int y, int z, int l, int r, int tmp) {
  int k;
  if ((x >= l) && (y <= r)) {
    f[z][0] += tmp;
    f[z][1] += tmp;
    return;
  }
  if (f[z][1] != 0) {
    f[z * 2][0] += f[z][1];
    f[z * 2][1] += f[z][1];
    f[z * 2 + 1][0] += f[z][1];
    f[z * 2 + 1][1] += f[z][1];
    f[z][1] = 0;
  }
  k = (x + y) >> 1;
  if (k >= l) insert(x, k, z * 2, l, r, tmp);
  if (k + 1 <= r) insert(k + 1, y, z * 2 + 1, l, r, tmp);
  f[z][0] = min(f[z * 2][0], f[z * 2 + 1][0]);
}
void solve() {
  memset(f, 0, sizeof(f));
  memset(a_sum, 0, sizeof(a_sum));
  memset(b_sum, 0, sizeof(b_sum));
  for (int i = 1; i <= n * 2; i++) {
    a_sum[i] = a_sum[i - 1] + a[i];
    b_sum[i] = b_sum[i - 1] + b[i];
  }
  for (int i = 1; i <= n; i++) insert(1, n * 2, 1, i, i, a_sum[i] - b_sum[i]);
  for (int i = 1; i <= n; i++) {
    if ((f[1][0] >= 0) && (!pp[state[i]])) {
      ++ans;
      pp[state[i]] = true;
    }
    insert(1, n * 2, 1, i, i + n - 1, b[i] - a[i]);
    insert(1, n * 2, 1, i + n, i + n,
           (a_sum[i + n] - a_sum[i]) - (b_sum[i + n] - b_sum[i]));
  }
}
void init() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    a[i + n] = a[i];
    state[i] = i;
    state[i + n] = i;
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &b[i]);
    b[i + n] = b[i];
  }
  solve();
  for (int i = 2 * n + 1; i > 1; i--) b[i] = b[i - 1];
  b[1] = b[2 * n + 1];
  for (int i = 1; i <= n; i++) {
    swap(a[i], a[n * 2 - i + 1]);
    swap(b[i], b[n * 2 - i + 1]);
    swap(state[i], state[n * 2 - i + 1]);
  }
  solve();
  printf("%d\n", ans);
  for (int i = 1; i <= n; i++)
    if (pp[i]) printf("%d ", i);
}
int main() {
  init();
  return 0;
}
