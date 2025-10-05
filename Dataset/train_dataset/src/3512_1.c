#include <bits/stdc++.h>
using namespace std;
int dp[2][52][52], sz, tz, nz, lps[2][57];
void complps(string ss, int pp, int r) {
  int len = 0;
  lps[r][0] = 0;
  int i = 1;
  while (i < pp) {
    if (ss[i] == ss[len]) {
      len++;
      lps[r][i] = len;
      i++;
    } else {
      if (len != 0) {
        len = lps[r][len - 1];
      } else {
        lps[r][i] = 0;
        i++;
      }
    }
  }
}
int main() {
  int ans, i, j, k, idx, fr, sc;
  char ch, sh, fh;
  string str, ttr, ntr;
  cin >> str;
  cin >> ttr;
  cin >> ntr;
  sz = str.size();
  tz = ttr.size();
  nz = ntr.size();
  complps(ttr, tz, 0);
  complps(ntr, nz, 1);
  for (idx = sz - 1; idx >= 0; idx--) {
    fr = idx & 1;
    sc = (idx + 1) & 1;
    for (j = tz - 1; j >= 0; j--) {
      for (k = nz - 1; k >= 0; k--) {
        int p = -9999999, q, r, s, w, z, t, x, y, e, f, flg = 0;
        sh = str[idx];
        fh = str[idx];
        if (str[idx] == '*') {
          sh = 'a';
          fh = 'z';
        }
        for (ch = sh; ch <= fh; ch++) {
          r = idx;
          s = j;
          e = 0;
          f = 0;
          if (ttr[j] == ch) {
            s++;
            r++;
          }
          if (s == tz) {
            s = lps[0][s - 1];
            e = 1;
          } else if (ttr[j] != ch) {
            while (s != 0) {
              s = lps[0][s - 1];
              if (ttr[s] == ch) {
                s = s + 1;
                flg = 1;
                break;
              }
            }
          }
          w = idx;
          t = k;
          flg = 0;
          if (ntr[k] == ch) {
            w++;
            t++;
          }
          if (t == nz) {
            t = lps[1][t - 1];
            f = 1;
          } else if (ntr[k] != ch) {
            while (t != 0) {
              t = lps[1][t - 1];
              if (ntr[t] == ch) {
                t = t + 1;
                flg = 1;
                break;
              }
            }
          }
          x = e - f;
          if (idx != sz - 1) {
            x = (e - f) + dp[sc][s][t];
          }
          p = max(p, x);
        }
        dp[fr][j][k] = p;
      }
    }
  }
  printf("%d\n", dp[0][0][0]);
  return 0;
}
