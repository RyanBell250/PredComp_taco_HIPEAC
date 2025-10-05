#include <bits/stdc++.h>
using namespace std;
template <typename T>
T Abs(T first) {
  return (first < 0 ? -first : first);
}
template <typename T>
T Sqr(T first) {
  return (first * first);
}
string plural(string s) {
  return (int((s).size()) && s[int((s).size()) - 1] == 'x' ? s + "en"
                                                           : s + "s");
}
const int INF = (int)1e9;
const long double EPS = 1e-12;
const long double PI = acos(-1.0);
bool Read(int &first) {
  char c, r = 0, n = 0;
  first = 0;
  for (;;) {
    c = getchar();
    if ((c < 0) && (!r)) return (0);
    if ((c == '-') && (!r))
      n = 1;
    else if ((c >= '0') && (c <= '9'))
      first = first * 10 + c - '0', r = 1;
    else if (r)
      break;
  }
  if (n) first = -first;
  return (1);
}
bool done;
int ord[8];
int V[8][3], cur[8][3], ans[8][3];
long long dist(long long first, long long second, long long z) {
  return (Sqr(first) + Sqr(second) + Sqr(z));
}
bool test() {
  int i, j;
  int c1, c2, c3;
  long long m;
  long long d[8][8];
  m = (long long)INF * INF;
  for (i = 0; i < 8; i++)
    for (j = 0; j < i; j++) {
      d[i][j] = d[j][i] = dist(cur[i][0] - cur[j][0], cur[i][1] - cur[j][1],
                               cur[i][2] - cur[j][2]);
      m = min(m, d[i][j]);
    }
  if (!m) return (0);
  for (i = 0; i < 8; i++) {
    c1 = c2 = c3 = 0;
    for (j = 0; j < 8; j++)
      if (i != j)
        if (d[i][j] == m)
          c1++;
        else if (d[i][j] == m * 2)
          c2++;
        else if (d[i][j] == m * 3)
          c3++;
        else
          return (0);
    if ((c1 != 3) || (c2 != 3) || (c3 != 1)) return (0);
  }
  return (1);
}
void rec(int i) {
  int j;
  if (i == 8) {
    for (j = 0; j < 8; j++) {
      if (ord[j] == 0) {
        cur[j][0] = V[j][0];
        cur[j][1] = V[j][1];
        cur[j][2] = V[j][2];
      }
      if (ord[j] == 1) {
        cur[j][0] = V[j][0];
        cur[j][1] = V[j][2];
        cur[j][2] = V[j][1];
      }
      if (ord[j] == 2) {
        cur[j][0] = V[j][1];
        cur[j][1] = V[j][0];
        cur[j][2] = V[j][2];
      }
      if (ord[j] == 3) {
        cur[j][0] = V[j][1];
        cur[j][1] = V[j][2];
        cur[j][2] = V[j][0];
      }
      if (ord[j] == 4) {
        cur[j][0] = V[j][2];
        cur[j][1] = V[j][0];
        cur[j][2] = V[j][1];
      }
      if (ord[j] == 5) {
        cur[j][0] = V[j][2];
        cur[j][1] = V[j][1];
        cur[j][2] = V[j][0];
      }
    }
    if (test()) {
      done = 1;
      memcpy(ans, cur, sizeof(cur));
    }
    return;
  }
  for (j = 0; j < 6; j++) {
    ord[i] = j;
    rec(i + 1);
    if (done) break;
  }
}
int main() {
  if (0) freopen("in.txt", "r", stdin);
  int i, j;
  for (i = 0; i < 8; i++)
    for (j = 0; j < 3; j++) Read(V[i][j]);
  rec(1);
  if (!done)
    printf("NO\n");
  else {
    printf("YES\n");
    for (i = 0; i < 8; i++)
      for (j = 0; j < 3; j++) printf("%d%c", ans[i][j], j == 2 ? '\n' : ' ');
  }
  return (0);
}
