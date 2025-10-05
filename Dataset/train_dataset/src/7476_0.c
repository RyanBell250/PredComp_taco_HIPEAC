#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <complex>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
#include <assert.h>
#include <array>
#include <cstdio>
#include <cstring>
#include <random>
#include <functional>
#include <numeric>
#include <bitset>
#include <fstream>

using namespace std;

#define REP(i,a,b) for(int i=a;i<(int)b;i++)
#define rep(i,n) REP(i,0,n)
template<class T1, class T2> inline bool maximize(T1 &a, T2 b) { return a < b && (a = b, 1); }

int dx[4] = {-1,0,1,0};
int dy[4] = {0,-1,0,1};
template<class T> constexpr bool in_range(T y, T x, T H, T W) { return 0<=y&&y<H&&0<=x&&x<W; }

int N;
int a[5][5];
int score[6];

void drop() {
  rep(j, 5) {
    deque<int> d;
    rep(i, 5) {
      if(a[i][j] != -1) {
        d.push_back(a[i][j]);
      }
    }

    int dsize = d.size();
    for(int i=4; i>=0 && !d.empty(); i--) {
      a[i][j] = d.back();
      d.pop_back();
    }
    rep(i, 5-dsize) {
      a[i][j] = -1;
    }
  }
}

int dist(int num, int i, int j, int dy, int dx, int sum = 0) {
  i += dy, j += dx;
  if(!in_range(i, j, 5, 5)) return sum;
  if(a[i][j] != num) return sum;
  return dist(num, i, j, dy, dx, sum + 1);
}

int simulate() {
  int ret = 0;
  int bonus = 1;

  while(1) {
    set<int> used;
    rep(i, 5) rep(j, 5) {
      if(a[i][j] == -1) continue;
      int movel = dist(a[i][j], i, j, 0, -1);
      int mover = dist(a[i][j], i, j, 0, +1);
      int movet = dist(a[i][j], i, j, -1, 0);
      int moveb = dist(a[i][j], i, j, +1, 0);
      if(mover - movel + 1 >= 3) {
        REP(x, j - movel, j + mover + 1) {
          assert(a[i][x] != -1);
          assert(a[i][x] == a[i][j]);
          used.insert(i*5+x);
        }
      }
      if(moveb - movet + 1 >= 3) {
        REP(y, i - movet, i + moveb + 1) {
          assert(a[y][j] != -1);
          assert(a[y][j] == a[i][j]);
          used.insert(y*5+j);
        }
      }
    }

    for(auto && e: used) {
      ret += score[a[e/5][e%5]] * bonus;
      a[e/5][e%5] = -1;
    }

    bonus ++;
    if(!used.size()) break;
    drop();
  }

  return ret;
}



int dfs(int y, int x, int idx = 0) {
  int aa[5][5]; rep(i, 5) rep(j, 5) aa[i][j] = a[i][j];
  int ret = simulate();
  if(idx < N) {
    rep(k, 4) {
      int ny = y + dy[k], nx = x + dx[k];
      if(!in_range(ny, nx, 5, 5)) continue;
      rep(i, 5) rep(j, 5) a[i][j] = aa[i][j];
      swap(a[y][x], a[ny][nx]);
      maximize(ret, dfs(ny, nx, idx + 1));
    }
  }
  rep(i, 5) rep(j, 5) a[i][j] = aa[i][j];
  return ret;
}

int solve() {
  int ret = 0;
  rep(i, 5) rep(j, 5)  {
    maximize(ret, dfs(i, j));
  }
  return ret;
}

int main() {

  for(; cin >> N && N >= 0;) {
    rep(i, 5) rep(j, 5) cin >> a[i][j];
    rep(i, 5) cin >> score[i+1];
    cout << solve() << endl;
  }
  
  return 0;
}