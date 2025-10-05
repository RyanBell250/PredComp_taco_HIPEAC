#include <bits/stdc++.h>
using namespace std;
bool suc = 0;
bool ok(int r, int c, vector<string> &S) {
  if (r < 0 || r >= 8 || c < 0 || c >= 8 || S[r][c] == 'S') return false;
  return true;
}
void dfs(int d, int r, int c, vector<string> S) {
  if (d >= 9) {
    cout << "WIN" << endl;
    exit(0);
  }
  if (S[r][c] == 'A') {
    suc = 1;
    cout << "WIN" << endl;
    exit(0);
  }
  if (d) {
    int i;
    for (i = 0; i < 7; i++) {
      S[i] = S[i + 1];
    }
    if (S[r][c] == 'S') return;
  }
  if (ok(r, c + 1, S)) dfs(d + 1, r, c + 1, S);
  if (ok(r, c - 1, S)) dfs(d + 1, r, c - 1, S);
  if (ok(r + 1, c + 1, S)) dfs(d + 1, r + 1, c + 1, S);
  if (ok(r + 1, c - 1, S)) dfs(d + 1, r + 1, c - 1, S);
  if (ok(r - 1, c + 1, S)) dfs(d + 1, r - 1, c + 1, S);
  if (ok(r - 1, c - 1, S)) dfs(d + 1, r - 1, c - 1, S);
  if (ok(r + 1, c, S)) dfs(d + 1, r + 1, c, S);
  if (ok(r - 1, c, S)) dfs(d + 1, r - 1, c, S);
  if (ok(r, c, S)) dfs(d + 1, r, c, S);
}
int main() {
  int i, j, k, N, M, P, l, m, n;
  ifstream fin();
  ofstream fout();
  vector<string> S(8);
  for (i = 7; i >= 0; i--) cin >> S[i];
  dfs(0, 0, 0, S);
  cout << "LOSE" << endl;
}
