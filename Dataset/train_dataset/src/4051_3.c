#include <bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i=a;i<(int)b;i++)
#define rep(i,n) REP(i,0,n)
#define zero(a) memset(a, 0, sizeof a)
#define minus(a) memset(a, -1, sizeof a)
#define watch(a) { cout << #a << " = " << a << endl; }
template<class T1, class T2> inline bool minimize(T1 &a, T2 b) { return b < a && (a = b, 1); }
template<class T1, class T2> inline bool maximize(T1 &a, T2 b) { return a < b && (a = b, 1); }

typedef long long ll;
int const inf = 1<<29;

int main() {

  const string cols = "RGB";

  int N; cin >> N;
  vector<pair<int, int>> vs(N);
  rep(i, N) {
    cin >> vs[i].first >> vs[i].second;
  }

  vector<string> G(4);
  rep(i, 4) cin >> G[i];

  static int dist[1<<16];
  minus(dist);
  dist[0] = 0;

  queue<int> q;
  q.push(0);

  while(!q.empty()) {
    if(~dist[(1<<16)-1]) break;

    int curr = q.front(); q.pop();

    for(auto hw: vs) {
      int h = hw.first, w = hw.second;

      for(auto col: cols)
      REP(i, -h + 1, 4) REP(j, -w + 1, 4) {
        int next = curr;
        REP(y, max(0, i), min(i + h, 4)) REP(x, max(0, j), min(j + w, 4)) {
          if(G[y][x] == col) next |= 1<<(y * 4 + x);
          else next &= ~(1<<(y * 4 + x));
        }
        if(dist[next] < 0) {
          dist[next] = dist[curr] + 1;
          q.push(next);
        }
      }
    }
  }

  cout << dist[(1<<16)-1] << endl;
    
  return 0;
}