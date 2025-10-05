#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
int n, m, ans = INT_MAX;
pair<int, int> from = {-1, -1};
string s[N], v[N];
string t[] = {"AC", "AG", "AT", "CG", "CT", "GT"};
string u[] = {"GT", "CT", "CG", "AT", "AG", "AC"};
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    cin >> s[i];
  }
  for (int x = 0; x < 6; x++) {
    int now = 0;
    for (int i = 0; i < n; i++) {
      if (i & 1) {
        int p = 0, q = 0;
        for (int j = 0; j < m; j++) {
          if (s[i][j] != t[x][j & 1]) {
            p++;
          }
          if (s[i][j] != t[x][!(j & 1)]) {
            q++;
          }
        }
        now += min(p, q);
      } else {
        int p = 0, q = 0;
        for (int j = 0; j < m; j++) {
          if (s[i][j] != u[x][j & 1]) {
            p++;
          }
          if (s[i][j] != u[x][!(j & 1)]) {
            q++;
          }
        }
        now += min(p, q);
      }
    }
    if (now < ans) {
      ans = now;
      from = {0, x};
    }
    now = 0;
    for (int i = 0; i < m; i++) {
      if (i & 1) {
        int p = 0, q = 0;
        for (int j = 0; j < n; j++) {
          if (s[j][i] != t[x][j & 1]) {
            p++;
          }
          if (s[j][i] != t[x][!(j & 1)]) {
            q++;
          }
        }
        now += min(p, q);
      } else {
        int p = 0, q = 0;
        for (int j = 0; j < n; j++) {
          if (s[j][i] != u[x][j & 1]) {
            p++;
          }
          if (s[j][i] != u[x][!(j & 1)]) {
            q++;
          }
        }
        now += min(p, q);
      }
    }
    if (now < ans) {
      ans = now;
      from = {1, x};
    }
  }
  if (from.first) {
    for (int i = 0; i < m; i++) {
      if (i & 1) {
        int p = 0, q = 0;
        for (int j = 0; j < n; j++) {
          if (s[j][i] != t[from.second][j & 1]) {
            p++;
          }
          if (s[j][i] != t[from.second][!(j & 1)]) {
            q++;
          }
        }
        if (p < q) {
          for (int j = 0; j < n; j++) {
            v[j] += t[from.second][j & 1];
          }
        } else {
          for (int j = 0; j < n; j++) {
            v[j] += t[from.second][!(j & 1)];
          }
        }
      } else {
        int p = 0, q = 0;
        for (int j = 0; j < n; j++) {
          if (s[j][i] != u[from.second][j & 1]) {
            p++;
          }
          if (s[j][i] != u[from.second][!(j & 1)]) {
            q++;
          }
        }
        if (p < q) {
          for (int j = 0; j < n; j++) {
            v[j] += u[from.second][j & 1];
          }
        } else {
          for (int j = 0; j < n; j++) {
            v[j] += u[from.second][!(j & 1)];
          }
        }
      }
    }
  } else {
    for (int i = 0; i < n; i++) {
      if (i & 1) {
        int p = 0, q = 0;
        for (int j = 0; j < m; j++) {
          if (s[i][j] != t[from.second][j & 1]) {
            p++;
          }
          if (s[i][j] != t[from.second][!(j & 1)]) {
            q++;
          }
        }
        if (p < q) {
          for (int j = 0; j < m; j++) {
            v[i] += t[from.second][j & 1];
          }
        } else {
          for (int j = 0; j < m; j++) {
            v[i] += t[from.second][!(j & 1)];
          }
        }
      } else {
        int p = 0, q = 0;
        for (int j = 0; j < m; j++) {
          if (s[i][j] != u[from.second][j & 1]) {
            p++;
          }
          if (s[i][j] != u[from.second][!(j & 1)]) {
            q++;
          }
        }
        if (p < q) {
          for (int j = 0; j < m; j++) {
            v[i] += u[from.second][j & 1];
          }
        } else {
          for (int j = 0; j < m; j++) {
            v[i] += u[from.second][!(j & 1)];
          }
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cout << v[i][j];
    }
    cout << "\n";
  }
}
