#include <bits/stdc++.h>
using namespace std;
template <typename T, typename U>
inline void smin(T &a, const U b) {
  if (a > b) a = b;
}
template <typename T, typename U>
inline void smax(T &a, const U b) {
  if (a < b) a = b;
}
template <class T>
inline void gn(T &first) {
  char c, sg = 0;
  while (c = getchar(), (c > '9' || c < '0') && c != '-')
    ;
  for ((c == '-' ? sg = 1, c = getchar() : 0), first = 0; c >= '0' && c <= '9';
       c = getchar())
    first = (first << 1) + (first << 3) + c - '0';
  if (sg) first = -first;
}
template <class T>
inline void print(T first) {
  if (first < 0) {
    putchar('-');
    return print(-first);
  }
  if (first < 10) {
    putchar('0' + first);
    return;
  }
  print(first / 10);
  putchar(first % 10 + '0');
}
template <class T, class T1>
inline void gn(T &first, T1 &second) {
  gn(first);
  gn(second);
}
template <class T, class T1, class T2>
inline void gn(T &first, T1 &second, T2 &z) {
  gn(first);
  gn(second);
  gn(z);
}
template <class T>
inline void println(T first) {
  print(first);
  putchar('\n');
}
template <class T>
inline void printsp(T first) {
  print(first);
  putchar(' ');
}
template <class T1, class T2>
inline void print(T1 x1, T2 x2) {
  printsp(x1), println(x2);
}
template <class T1, class T2, class T3>
inline void print(T1 x1, T2 x2, T3 x3) {
  printsp(x1), printsp(x2), println(x3);
}
template <class T1, class T2, class T3, class T4>
inline void print(T1 x1, T2 x2, T3 x3, T4 x4) {
  printsp(x1), printsp(x2), printsp(x3), println(x4);
}
int power(int a, int b, int m, int ans = 1) {
  for (; b; b >>= 1, a = 1LL * a * a % m)
    if (b & 1) ans = 1LL * ans * a % m;
  return ans;
}
int a[5050], b[5050], c[5050];
int fa[5050], fb[5050], fc[5050];
int hk[3];
int ac[3];
int st[11], ed[11];
int dp[111][111][111];
int bi[5050][11];
int len[5050];
int sa, sb, sc;
int ma, mb, mc;
int calc(int u) { return (u + 1); }
vector<int> hack;
vector<int> no;
int s[5050];
int main() {
  int n;
  cin >> n;
  memset(st, -1, sizeof st);
  for (int i = 1; i <= n; i++) {
    gn(a[i], b[i], c[i]);
    if (a[i] < 0) hk[0]++;
    if (b[i] < 0) hk[1]++;
    if (c[i] < 0) hk[2]++;
    if (a[i]) ac[0]++;
    if (b[i]) ac[1]++;
    if (c[i]) ac[2]++;
    if (i * 2 > n) {
      ed[0] = i;
      if (st[0] == -1) st[0] = i;
    } else if (4 * i > n) {
      ed[1] = i;
      if (st[1] == -1) st[1] = i;
    } else if (8 * i > n) {
      ed[2] = i;
      if (st[2] == -1) st[2] = i;
    } else if (16 * i > n) {
      ed[3] = i;
      if (st[3] == -1) st[3] = i;
    } else if (32 * i > n) {
      ed[4] = i;
      if (st[4] == -1) st[4] = i;
    } else {
      ed[5] = i;
      if (st[5] == -1) st[5] = i;
    }
    int val = 0;
    if (a[i] < 0) val |= 1;
    if (b[i] < 0) val |= 2;
    if (c[i] < 0) val |= 4;
    for (int j = 0; j < 8; j++)
      if (val - j == (val ^ j)) bi[i][len[i]++] = j;
    if (i == 1) continue;
    if (val)
      hack.push_back(i);
    else
      no.push_back(i);
  }
  if (hk[0] + hk[1] + hk[2] >= 90) return puts("1");
  int ans = 0;
  for (int aa = 0; aa < 6; aa++) {
    if (ac[0] < st[aa]) continue;
    if (ac[0] - hk[0] > ed[aa]) continue;
    sa = calc(aa);
    ma = min(hk[0], ac[0] - st[aa]);
    for (int bb = 0; bb < 6; bb++) {
      if (ac[1] < st[bb]) continue;
      if (ac[1] - hk[1] > ed[bb]) continue;
      sb = calc(bb);
      mb = min(hk[1], ac[1] - st[bb]);
      for (int cc = 0; cc < 6; cc++) {
        if (ac[2] < st[cc]) continue;
        if (ac[2] - hk[2] > ed[cc]) continue;
        sc = calc(cc);
        mc = min(hk[2], ac[2] - st[cc]);
        for (int i = 0; i <= ma; i++)
          for (int j = 0; j <= mb; j++)
            for (int k = 0; k <= mc; k++) dp[i][j][k] = -1;
        for (int p = 1; p <= n; p++) {
          fa[p] = 250 - abs(a[p]);
          fa[p] <<= 1;
          fa[p] *= sa;
          fb[p] = 250 - abs(b[p]);
          fb[p] <<= 1;
          fb[p] *= sb;
          fc[p] = 250 - abs(c[p]);
          fc[p] <<= 1;
          fc[p] *= sc;
        }
        dp[0][0][0] = 0;
        int wo = 0;
        if (a[1]) wo += fa[1];
        if (b[1]) wo += fb[1];
        if (c[1]) wo += fc[1];
        wo += (ma + mb + mc) * 100;
        for (int q = 0; q < ((int)no.size()); q++) {
          int p = no[q];
          int now = 0;
          if (a[p]) now += fa[p];
          if (b[p]) now += fb[p];
          if (c[p]) now += fc[p];
          if (now <= wo) dp[0][0][0]++;
        }
        for (int q = 0; q < ((int)hack.size()); q++) {
          int p = hack[q];
          for (int i = ma; i >= 0; i--) {
            for (int j = mb; j >= 0; j--) {
              for (int k = mc; k >= 0; k--)
                if (dp[i][j][k] != -1) {
                  int nx[3] = {i, j, k};
                  int now = 0;
                  for (int bt = len[p]; bt--;) {
                    nx[0] = i, nx[1] = j, nx[2] = k;
                    now = 0;
                    int fit = bi[p][bt];
                    if (fit & 1)
                      nx[0]++;
                    else if (a[p])
                      now += fa[p];
                    if (fit & 2)
                      nx[1]++;
                    else if (b[p])
                      now += fb[p];
                    if (fit & 4)
                      nx[2]++;
                    else if (c[p])
                      now += fc[p];
                    smax(dp[nx[0]][nx[1]][nx[2]], dp[i][j][k] + (wo >= now));
                  }
                }
            }
          }
        }
        smax(ans, dp[ma][mb][mc]);
      }
    }
  }
  cout << n - ans << endl;
  return 0;
}
