#include <bits/stdc++.h>
using namespace std;
char a[32][32];
char p[32][32];
char out[32][32];
int N, M;
int br[7];
int used[7][7];
int x[14];
int ans = 0;
int l[32], r[32];
int k = 0;
void check() {
  int idx = 0;
  int delta = 2;
  for (int i = 0; i < N; i++)
    for (int j = l[i]; j < r[i]; j++)
      if (a[i][j] != '.' && p[i][j] == -100)
        p[i][j] = p[i][j + 1] = p[i + 1][j] = p[i + 1][j + 1] = x[idx++] + '0';
  for (int i = 0; i < N; ++i)
    for (int j = l[i]; j < r[i]; ++j) {
      if (a[i][j] != '.' && p[i][j] != -100) {
        if (i)
          if (a[i][j] == a[i - 1][j]) used[p[i][j] - '0'][p[i - 1][j] - '0']++;
        if (j)
          if (a[i][j] == a[i][j - 1]) used[p[i][j] - '0'][p[i][j - 1] - '0']++;
      }
    }
  int ok = 0;
  for (int i = 0; i < 7; ++i)
    for (int j = i; j < 7; ++j) {
      if (used[i][j] + used[j][i] - (i == j) != 1) ok = 1;
      used[i][j] = used[j][i] = 0;
    }
  if (!ok) {
    ++ans;
    if (ans == 1)
      for (int i = 0; i < N; i++)
        for (int j = l[i]; j < r[i]; j++) out[i][j] = p[i][j];
  }
  for (int i = 0; i < N; i++)
    for (int j = l[i]; j < r[i]; j++) p[i][j] = -100;
}
void gen(int idx) {
  if (idx == 14) {
    check();
    return;
  }
  int i = 0;
  while (br[i] != 2) {
    if (br[i]) {
      --br[i];
      x[idx] = i;
      gen(idx + 1);
      ++br[i];
    }
    ++i;
    if (i == 7) break;
  }
  if (i != 7) {
    x[idx] = i;
    --br[i];
    gen(idx + 1);
    ++br[i];
  }
}
void fill() {
  for (int i = 0; i < N; ++i) {
    int cnt = 0;
    for (int j = 0; j < M; ++j)
      if (a[i][j] != '.') ++cnt;
    if (!cnt) {
      l[i] = r[i] = 0;
      continue;
    }
    for (int j = 0; j < M; ++j)
      if (a[i][j] != '.') {
        l[i] = j;
        break;
      }
    for (int j = M - 1; j >= 0; --j)
      if (a[i][j] != '.') {
        r[i] = j + 1;
        break;
      }
  }
}
int main() {
  cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> a[i];
  for (int i = 0; i < 7; ++i) br[i] = 2;
  fill();
  for (int i = 0; i < 32; ++i)
    for (int j = 0; j < 32; ++j) p[i][j] = -100;
  gen(0);
  cout << (long long)ans * 1LL * 2LL * 3LL * 4LL * 5LL * 6LL * 7LL << endl;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < M; ++j) {
      if (j < l[i] || j >= r[i])
        cout << ".";
      else if (out[i][j] < 0)
        cout << ".";
      else
        cout << out[i][j];
    }
    cout << endl;
  }
}
