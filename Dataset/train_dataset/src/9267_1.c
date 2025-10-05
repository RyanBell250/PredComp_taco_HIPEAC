#include <bits/stdc++.h>
using namespace std;
int va, vb, vc;
int A, B, C;
vector<int> as, bs, cs;
bool dp[33][2][11][11][11];
struct state {
  int L, c, A, B, C, aa, bb, cc;
  state() {}
  state(int L, int c, int A, int B, int C, int aa, int bb, int cc)
      : L(L), c(c), A(A), B(B), C(C), aa(aa), bb(bb), cc(cc) {}
};
state pre[33][2][11][11][11];
void cal(int alen, int blen, int clen) {
  memset(dp, 0, sizeof(dp));
  dp[0][0][0][0][0] = 1;
  int L = clen;
  for (int i = 0; i < L; i++)
    for (int cc = 0; cc < 2; cc++)
      for (int a = 0; a <= A; a++)
        for (int b = 0; b <= B; b++)
          for (int c = 0; c <= C; c++)
            if (dp[i][cc][a][b][c])
              for (int ca = 0; ca < 10; ca++)
                for (int cb = 0; cb < 10; cb++) {
                  int CC = ca + cb + cc, ncc = 0;
                  if (CC >= 10) CC -= 10, ncc = 1;
                  if (i >= alen && ca != 0) continue;
                  if (i >= blen && cb != 0) continue;
                  if (i >= clen && CC != 0) continue;
                  int pa = a + ((a < A && as[a] == ca) ? 1 : 0);
                  int pb = b + ((b < B && bs[b] == cb) ? 1 : 0);
                  int pc = c + ((c < C && cs[c] == CC) ? 1 : 0);
                  dp[i + 1][ncc][pa][pb][pc] = 1;
                  pre[i + 1][ncc][pa][pb][pc] =
                      state(i, cc, a, b, c, ca, cb, CC);
                }
  if (dp[L][0][A][B][C]) {
    int l = L, c = 0, aa = A, bb = B, cc = C;
    string sa = "", sb = "", sc = "";
    while (l > 0) {
      state cur = pre[l][c][aa][bb][cc];
      l = cur.L, c = cur.c, aa = cur.A, bb = cur.B, cc = cur.C;
      if (l < alen) sa.push_back(cur.aa + '0');
      if (l < blen) sb.push_back(cur.bb + '0');
      if (l < clen) sc.push_back(cur.cc + '0');
    }
    cout << sa << "+" << sb << "=" << sc << endl;
    exit(0);
  }
}
int main() {
  scanf("%d+%d=%d", &va, &vb, &vc);
  while (va) {
    as.push_back(va % 10);
    va /= 10;
  }
  while (vb) {
    bs.push_back(vb % 10);
    vb /= 10;
  }
  while (vc) {
    cs.push_back(vc % 10);
    vc /= 10;
  }
  A = as.size(), B = bs.size(), C = cs.size();
  for (int sum = 0;; sum++)
    for (int alen = A; alen <= sum; alen++)
      for (int blen = B; blen + alen <= sum; blen++) {
        int clen = sum - alen - blen;
        if (clen < C) break;
        int tmp = clen - max(alen, blen);
        if (tmp != 0 && tmp != 1) continue;
        cal(alen, blen, clen);
      }
  return 0;
}
