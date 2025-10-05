#include <bits/stdc++.h>
using namespace std;
char given[110], pattern[110];
int failure[110];
void compute_prefix(void) {
  int m = strlen(pattern), k = -1;
  failure[0] = 0;
  for (int q = 1; q < m; q++) {
    while (k >= 0 && pattern[k + 1] != pattern[q]) k = failure[k] - 1;
    if (pattern[k + 1] == pattern[q]) k++;
    failure[q] = k + 1;
  }
}
void kmp_matcher(void) {
  int n = strlen(given), m = strlen(pattern), q = -1;
  compute_prefix();
  for (int i = 0; i < n; i++) {
    while (q >= 0 && pattern[q + 1] != given[i]) q = failure[q] - 1;
    if (pattern[q + 1] == given[i]) q++;
    if (q == m - 1) {
      printf("%d\n", i - m + 1);
      q = failure[q] - 1;
    }
  }
}
int lenN, lenX, lenY;
char strY[110], strX[110];
char strN[110];
int match[110][30];
int dp[110][110][110];
pair<int, pair<int, int> > myback[110][110][110];
inline void ReadInput(void) {
  scanf("%s", strX);
  scanf("%s", strY);
  scanf("%s", strN);
}
inline void solve(void) {
  lenN = strlen(strN);
  lenX = strlen(strX);
  lenY = strlen(strY);
  for (int i = 0; i <= lenN; i++) {
    for (int j = 0; j < 26; j++) {
      pattern[i] = 'A' + j;
      pattern[i + 1] = '\0';
      compute_prefix();
      match[i][j] = failure[i];
    }
    pattern[i] = strN[i];
  }
  for (int i = 0; i < 110; i++) {
    for (int j = 0; j < 110; j++) {
      for (int k = 0; k < 110; k++)
        myback[i][j][k] =
            pair<int, pair<int, int> >(-1, pair<int, int>(-1, -1));
    }
  }
  if (strX[0] == strY[0] and strX[0] == strN[0]) {
    dp[0][0][1] = 1;
    myback[0][0][1] = pair<int, pair<int, int> >(-1, pair<int, int>(-1, -1));
  } else if (strX[0] == strY[0]) {
    dp[0][0][0] = 1;
    myback[0][0][0] = pair<int, pair<int, int> >(-1, pair<int, int>(-1, -1));
  }
  for (int i = 1; i < lenX; i++) {
    if (strY[0] == strX[i]) {
      if (strN[0] == strY[0]) {
        dp[i][0][1] = 1;
        myback[i][0][1] =
            pair<int, pair<int, int> >(-1, pair<int, int>(-1, -1));
      } else {
        dp[i][0][0] = 1;
        myback[i][0][0] =
            pair<int, pair<int, int> >(-1, pair<int, int>(-1, -1));
      }
    } else {
      dp[i][0][1] = dp[i - 1][0][1];
      dp[i][0][0] = dp[i - 1][0][0];
      myback[i][0][1] = pair<int, pair<int, int> >(1, pair<int, int>(i - 1, 0));
      myback[i][0][0] = pair<int, pair<int, int> >(0, pair<int, int>(i - 1, 0));
    }
  }
  for (int i = 1; i < lenY; i++) {
    if (strX[0] == strY[i]) {
      if (strN[0] == strX[0]) {
        dp[0][i][1] = 1;
        myback[0][i][1] =
            pair<int, pair<int, int> >(-1, pair<int, int>(-1, -1));
      } else {
        myback[0][i][0] =
            pair<int, pair<int, int> >(-1, pair<int, int>(-1, -1));
        dp[0][i][0] = 1;
      }
    } else {
      dp[0][i][1] = dp[0][i - 1][1];
      dp[0][i][0] = dp[0][i - 1][0];
      myback[0][i][1] = pair<int, pair<int, int> >(1, pair<int, int>(0, i - 1));
      myback[0][i][0] = pair<int, pair<int, int> >(0, pair<int, int>(0, i - 1));
    }
  }
  for (int i = 1; i < lenX; i++) {
    for (int j = 1; j < lenY; j++) {
      for (int k = 0; k < lenN; k++) {
        if (strX[i] != strY[j]) {
          if (dp[i][j - 1][k] > dp[i - 1][j][k])
            myback[i][j][k] =
                pair<int, pair<int, int> >(k, pair<int, int>(i, j - 1));
          else
            myback[i][j][k] =
                pair<int, pair<int, int> >(k, pair<int, int>(i - 1, j));
          dp[i][j][k] = max(dp[i][j][k], max(dp[i][j - 1][k], dp[i - 1][j][k]));
        } else {
          if (dp[i][j][k] < max(dp[i][j - 1][k], dp[i - 1][j][k])) {
            if (dp[i][j - 1][k] > dp[i - 1][j][k])
              myback[i][j][k] =
                  pair<int, pair<int, int> >(k, pair<int, int>(i, j - 1));
            else
              myback[i][j][k] =
                  pair<int, pair<int, int> >(k, pair<int, int>(i - 1, j));
          }
          dp[i][j][k] = max(dp[i][j][k], max(dp[i][j - 1][k], dp[i - 1][j][k]));
          if (k != lenN - 1 and strX[i] == strN[k] and
              dp[i - 1][j - 1][k] >= k) {
            if (dp[i][j][k + 1] < dp[i - 1][j - 1][k] + 1)
              myback[i][j][k + 1] =
                  pair<int, pair<int, int> >(k, pair<int, int>(i - 1, j - 1));
            dp[i][j][k + 1] = max(dp[i][j][k + 1], dp[i - 1][j - 1][k] + 1);
          }
          if (strX[i] != strN[k] and dp[i - 1][j - 1][k] >= k) {
            if (dp[i][j][match[k][strX[i] - 'A']] < dp[i - 1][j - 1][k] + 1)
              myback[i][j][match[k][strX[i] - 'A']] =
                  pair<int, pair<int, int> >(k, pair<int, int>(i - 1, j - 1));
            dp[i][j][match[k][strX[i] - 'A']] =
                max(dp[i][j][match[k][strX[i] - 'A']], dp[i - 1][j - 1][k] + 1);
          }
          if (dp[i - 1][j - 1][k] >= k) {
            if (dp[i][j][k] < dp[i - 1][j - 1][k])
              myback[i][j][k] =
                  pair<int, pair<int, int> >(k, pair<int, int>(i - 1, j - 1));
            dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j - 1][k]);
          }
        }
      }
    }
  }
  int ans = 0, pos = -1;
  for (int i = 0; i < lenN; i++) {
    if (dp[lenX - 1][lenY - 1][i] > ans) pos = i;
    ans = max(ans, dp[lenX - 1][lenY - 1][i]);
  }
  if (ans == 0) {
    cout << 0;
    return;
  }
  stack<char> myans;
  int posi = lenX - 1, posj = lenY - 1;
  while (1) {
    if (myback[posi][posj][pos] ==
            pair<int, pair<int, int> >(-1, pair<int, int>(-1, -1)) and
        dp[posi][posj][pos] == 0)
      break;
    else if (myback[posi][posj][pos] ==
             pair<int, pair<int, int> >(-1, pair<int, int>(-1, -1))) {
      myans.push(strX[posi]);
      break;
    } else if (dp[posi][posj][pos] > dp[myback[posi][posj][pos].second.first]
                                       [myback[posi][posj][pos].second.second]
                                       [myback[posi][posj][pos].first]) {
      myans.push(strX[posi]);
    }
    int a, b, c;
    a = posi;
    b = posj;
    c = pos;
    posi = myback[a][b][c].second.first;
    posj = myback[a][b][c].second.second;
    pos = myback[a][b][c].first;
  }
  while (!myans.empty()) {
    cout << myans.top();
    myans.pop();
  }
}
inline void Refresh(void) {}
int main() {
  ReadInput();
  solve();
  return 0;
}
