#include <bits/stdc++.h>
using namespace std;
auto SEED = chrono::steady_clock::now().time_since_epoch().count();
mt19937 rng(SEED);
const int mod = 1e9 + 7, x = 864197532, N = 1001, logN = 18, K = 500, C = 1e9;
struct AC {
  vector<vector<int>> ch;
  vector<int> cnt, f;
  AC() { extend(); }
  void extend() {
    ch.push_back(vector<int>(26, 0));
    cnt.push_back(0);
  }
  int next(int u, int v) {
    if (!ch[u][v]) {
      ch[u][v] = ch.size();
      extend();
    }
    return ch[u][v];
  }
  void insert(string &s, int v) {
    int now = 0;
    for (char c : s) {
      now = next(now, c - 'a');
    }
    cnt[now] += v;
  }
  void build_fail() {
    f.assign(ch.size(), 0);
    queue<int> q;
    for (int i = 0; i < 26; ++i)
      if (ch[0][i]) q.push(ch[0][i]);
    while (q.size()) {
      int v = q.front();
      q.pop();
      for (int i = 0; i < 26; ++i)
        if (ch[v][i]) {
          int k = f[v];
          while (k && !ch[k][i]) k = f[k];
          if (ch[k][i]) k = ch[k][i];
          f[ch[v][i]] = k;
          cnt[ch[v][i]] += cnt[k];
          q.push(ch[v][i]);
        }
    }
  }
  int match(string &s) {
    int k = 0, ans = 0;
    for (char c : s) {
      while (k && !ch[k][c - 'a']) k = f[k];
      if (ch[k][c - 'a']) k = ch[k][c - 'a'];
      ans += cnt[k];
    }
    return ans;
  }
} ac;
int solve(string s, int m, int k) {
  int n = s.length();
  int N = ac.ch.size();
  int dp[n + 1][N][k + 1][2][2];
  for (int i = (0); i < (n + 1); i++)
    for (int j = (0); j < (N); j++)
      for (int ii = (0); ii < (k + 1); ii++)
        for (int f = (0); f < (2); f++)
          for (int z = (0); z < (2); z++) dp[i][j][ii][f][z] = 0;
  dp[0][0][0][0][0] = 1;
  for (int i = (0); i < (n); i++)
    for (int j = (0); j < (N); j++)
      for (int ii = (0); ii < (k + 1); ii++)
        for (int f = (0); f < (2); f++)
          for (int z = (0); z < (2); z++)
            if (dp[i][j][ii][f][z]) {
              if (z) {
                char d;
                if (f)
                  d = 'a' + m - 1;
                else
                  d = s[i];
                for (char c = 'a'; c <= d; ++c) {
                  int nj = j;
                  while (nj && !ac.ch[nj][c - 'a']) nj = ac.f[nj];
                  if (ac.ch[nj][c - 'a']) nj = ac.ch[nj][c - 'a'];
                  int nii = ii + ac.cnt[nj], nf = 1;
                  if (!f && c == d) nf = 0;
                  if (nii <= k)
                    dp[i + 1][nj][nii][nf][z] =
                        (dp[i + 1][nj][nii][nf][z] + dp[i][j][ii][f][z]) % mod;
                }
              } else {
                char d;
                if (f)
                  d = 'a' + m - 1;
                else
                  d = s[i];
                for (char c = 'a'; c <= d; ++c) {
                  int nj = j, nf = 1, nz = 1;
                  if (!f && c == d) nf = 0;
                  if (c == 'a') nz = 0;
                  if (nz) {
                    if (ac.ch[nj][c - 'a']) nj = ac.ch[nj][c - 'a'];
                  }
                  int nii = ii + ac.cnt[nj];
                  if (nii <= k)
                    dp[i + 1][nj][nii][nf][nz] =
                        (dp[i + 1][nj][nii][nf][nz] + dp[i][j][ii][f][z]) % mod;
                }
              }
            }
  int ans = 0;
  for (int i = (0); i < (N); i++)
    for (int j = (0); j < (k + 1); j++)
      for (int z = (0); z < (2); z++) ans = (ans + dp[n][i][j][1][z]) % mod;
  return ans;
}
int ok(string s, int m, int k) { return ac.match(s) <= k; }
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, k, len, x;
  cin >> n >> m >> k;
  string l, r;
  cin >> len;
  for (int i = (0); i < (len); i++) cin >> x, l.push_back('a' + x);
  cin >> len;
  for (int i = (0); i < (len); i++) cin >> x, r.push_back('a' + x);
  for (int i = (0); i < (n); i++) {
    cin >> len;
    string s;
    for (int i = (0); i < (len); i++) cin >> x, s.push_back('a' + x);
    cin >> x;
    ac.insert(s, x);
  }
  ac.build_fail();
  cout << (solve(r, m, k) - solve(l, m, k) + ok(r, m, k) + mod) % mod << endl;
}
