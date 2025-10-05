#include <bits/stdc++.h>
using namespace std;
void getint(int &v) {
  char ch, fu = 0;
  for (ch = '*'; (ch < '0' || ch > '9') && ch != '-'; ch = getchar())
    ;
  if (ch == '-') fu = 1, ch = getchar();
  for (v = 0; ch >= '0' && ch <= '9'; ch = getchar()) v = v * 10 + ch - '0';
  if (fu) v = -v;
}
const int INF = 1e9 + 10;
vector<int> ans;
int n, a[500010], m, las[15][35000], tmp[500010], ts, d[15][35000], q[35000];
void bfs(int n) {
  int ts = 0;
  for (int i = 0; i <= n - 1; ++i)
    for (int j = i + 1; j <= n - 1; ++j) {
      int k = j + j - i;
      if (k > n - 1) break;
      tmp[++ts] = (1 << i) ^ (1 << j) ^ (1 << k);
    }
  int he = 0, ta = 1;
  q[1] = 0;
  d[n][0] = 0;
  for (int i = 1; i <= (1 << n) - 1; ++i) d[n][i] = INF;
  while (he != ta) {
    int x = q[++he];
    for (int i = 1; i <= ts; ++i) {
      int y = x ^ tmp[i];
      if (d[n][y] < INF) continue;
      q[++ta] = y;
      d[n][y] = d[n][x] + 1;
      las[n][y] = x;
    }
  }
}
void FLIP(int x) {
  ans.push_back(x);
  a[x] ^= 1;
}
void BF(int n) {
  int t = 0;
  for (int i = 1; i <= n; ++i) t ^= a[i] << (i - 1);
  if (d[n][t] >= INF) {
    puts("NO");
    return;
  }
  puts("YES");
  while (t) {
    int l = las[n][t];
    for (int i = 0; i <= n - 1; ++i)
      if (((t ^ l) >> i) & 1) FLIP(i + 1);
    t = l;
  }
  cout << (int)ans.size() / 3 << endl;
  for (int i = 0; i < ans.size(); ++i) {
    printf("%d ", ans[i]);
    if (i % 3 == 2) puts("");
  }
}
void doit(int n) {
  if (n < 14) {
    BF(n);
    return;
  }
  if (a[n] + a[n - 1] + a[n - 2] == 3) {
    FLIP(n - 2);
    FLIP(n - 1);
    FLIP(n);
    doit(n - 3);
  } else if (a[n] + a[n - 1] + a[n - 2] == 0) {
    doit(n - 3);
  } else if (a[n] + a[n - 1] + a[n - 2] == 1) {
    int h = 0;
    for (int j = n - 2; j <= n; ++j)
      if (a[j] == 1) h = j;
    FLIP(n + n - 6 - h);
    FLIP(n - 3);
    FLIP(h);
    doit(n - 3);
  } else if (a[n] == 0) {
    FLIP(n - 3);
    FLIP(n - 2);
    FLIP(n - 1);
    doit(n - 3);
  } else if (a[n - 1] == 0) {
    FLIP(n - 4);
    FLIP(n - 2);
    FLIP(n);
    doit(n - 3);
  } else if (a[n - 5] + a[n - 4] + a[n - 3] == 0) {
    FLIP(n - 8);
    FLIP(n - 4);
    FLIP(n);
    FLIP(n - 7);
    FLIP(n - 4);
    FLIP(n - 1);
    doit(n - 6);
  } else if (a[n - 5] + a[n - 4] + a[n - 3] == 3) {
    FLIP(n - 5);
    FLIP(n - 3);
    FLIP(n - 1);
    FLIP(n - 8);
    FLIP(n - 4);
    FLIP(n);
    doit(n - 6);
  } else if (a[n - 5] + a[n - 4] + a[n - 3] == 1) {
    int h = 0;
    for (int i = n - 5; i <= n - 3; ++i)
      if (a[i] == 1) h = i;
    FLIP(h + h - n);
    FLIP(h);
    FLIP(n);
    FLIP(n - 11);
    FLIP(n - 6);
    FLIP(n - 1);
    doit(n - 6);
  } else if (a[n - 5] + a[n - 4] + a[n - 3] == 2) {
    int ts = 0;
    for (int i = n - 5; i <= n - 3; ++i)
      if (a[i] == 1) tmp[++ts] = i;
    FLIP(tmp[2] * 2 - n);
    FLIP(tmp[2]);
    FLIP(n);
    FLIP(tmp[1] * 2 - n + 1);
    FLIP(tmp[1]);
    FLIP(n - 1);
    doit(n - 6);
  }
}
int main() {
  cin >> n;
  for (int i = 1; i <= n; ++i) getint(a[i]);
  for (m = 1; m <= 14; ++m) bfs(m);
  doit(n);
  return 0;
}
