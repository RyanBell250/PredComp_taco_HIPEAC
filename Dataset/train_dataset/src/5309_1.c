#include <bits/stdc++.h>
using namespace std;
int N;
int A[200];
string S;
int cc2[200][200][200];
int dp2(int l, int r, int c) {
  if (l > r) return A[c] == -1 ? -1e9 : A[c];
  int &ret = cc2[l][r][c];
  if (ret != 1e9) return ret;
  ret = -1e9;
  if (c) {
    if (A[c] != -1) ret = max(ret, A[c] + dp2(l, r, 0));
    if (A[c + 1] != -1) {
      ret = max(ret, A[c + 1] + dp2(l + 1, r, 0));
      ret = max(ret, A[c + 1] + dp2(l, r - 1, 0));
    }
    if (l != r && S[l] == S[r]) {
      ret = max(ret, dp2(l + 1, r - 1, c + 2));
    }
    for (int i = l; i < r; i++) {
      ret = max(ret, dp2(l, i, 0) + dp2(i + 1, r, c));
      ret = max(ret, dp2(l, i, c) + dp2(i + 1, r, 0));
    }
    return ret;
  } else {
    if (A[1] != -1) {
      ret = max(ret, A[1] + dp2(l + 1, r, 0));
      ret = max(ret, A[1] + dp2(l, r - 1, 0));
    }
    if (l != r && S[l] == S[r]) {
      ret = max(ret, dp2(l + 1, r - 1, 2));
    }
    for (int i = l; i < r; i++) {
      ret = max(ret, dp2(l, i, 0) + dp2(i + 1, r, 0));
    }
    return ret;
  }
}
int cc1[200][200];
int dp1(int l, int r) {
  if (l > r) return 0;
  int &ret = cc1[l][r];
  if (ret != 1e9) return ret;
  ret = 0;
  ret = max(ret, dp2(l, r, 0));
  ret = max(ret, dp1(l + 1, r));
  ret = max(ret, dp1(l, r - 1));
  for (int i = l; i < r; i++) {
    ret = max(ret, dp1(l, i) + dp1(i + 1, r));
  }
  return ret;
}
int main() {
  scanf("%d", &N);
  for (int i = 1; i <= N; i++) {
    scanf("%d", &A[i]);
  }
  cin >> S;
  for (int i = 0; i < 200; i++)
    for (int j = 0; j < 200; j++) cc1[i][j] = 1e9;
  for (int i = 0; i < 200; i++)
    for (int j = 0; j < 200; j++)
      for (int k = 0; k < 200; k++) cc2[i][j][k] = 1e9;
  printf("%d", dp1(0, N - 1));
}
