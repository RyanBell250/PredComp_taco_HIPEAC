#include <bits/stdc++.h>
using namespace std;
using ll = long long;
ll h, w;
vector<vector<int>> z;
bool ok(int x, int y, int c) {
  if (y != 0) {
    if (c - w == z[y - 1][x]) return 0;
    if (c + w == z[y - 1][x]) return 0;
    if (c % w != 1 && c - 1 == z[y - 1][x]) return 0;
    if (c % w != 0 && c + 1 == z[y - 1][x]) return 0;
  }
  if (x != 0) {
    if (c - w == z[y][x - 1]) return 0;
    if (c + w == z[y][x - 1]) return 0;
    if (c % w != 1 && c - 1 == z[y][x - 1]) return 0;
    if (c % w != 0 && c + 1 == z[y][x - 1]) return 0;
  }
  return 1;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> h >> w;
  vector<int> v;
  for (int i = 1; i <= h * w; ++i) v.push_back(i);
  random_shuffle(v.begin(), v.end());
  for (int y = 0; y < h; ++y) {
    z.push_back({});
    for (int x = 0; x < w; ++x) {
      z[y].push_back(v.back());
      v.pop_back();
    }
  }
  ll amt = 0;
  bool done = 0;
  while (!done) {
    ++amt;
    done = 1;
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) {
        if (!ok(x, y, z[y][x])) {
          done = 0;
          int x2 = rand() % w;
          int y2 = rand() % h;
          while (x2 == x && y2 == y) {
            x2 = rand() % w;
            y2 = rand() % h;
          }
          swap(z[y][x], z[y2][x2]);
        }
      }
    }
    if (!done && amt * w * h >= 1e7) break;
  }
  if (done) {
    cout << "YES\n";
    for (int y = 0; y < h; ++y) {
      for (int x = 0; x < w; ++x) cout << z[y][x] << " ";
      cout << '\n';
    }
  } else
    cout << "NO\n";
}
