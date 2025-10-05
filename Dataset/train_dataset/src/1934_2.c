#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

#include <iostream>
#include <complex>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <functional>
#include <cassert>

typedef long long ll;
using namespace std;

#define debug(x) cerr << __LINE__ << " : " << #x << " = " << (x) << endl;

#define mod 1000000007 //1e9+7(prime number)
#define INF 1000000000 //1e9
#define LLINF 2000000000000000000LL //2e18
#define SIZE 100010

ll dp[600][600];
int dist[600][600];

int main(){
  int w, h, sx, sy, gx, gy;

  cin >> w >> h >> sx >> sy >> gx >> gy;

  for(int i=0;i<h;i++)
    for(int j=0;j<w;j++)
      dist[i][j] = INF;

  queue<pair<pair<int,int>,pair<int,int> > > q1;

  q1.push({{sy, sx}, {h, w}});
  dp[h][w] = 1;
  
  for(int i=0;q1.size();i++){
    queue<pair<pair<int,int>,pair<int,int> > > q2;

    while(q1.size()){
      auto p = q1.front(); q1.pop();
      int y = p.first.first;
      int x = p.first.second;
      ll cost = dp[p.second.first][p.second.second];

      if(y < 0 || h <= y || x < 0 || w <= x) continue;
      if(dist[y][x] < i) continue;
      
      if(dist[y][x] == i){
        dp[y][x] = (dp[y][x] + cost)%mod;
        continue;
      }

      dp[y][x] = cost;
      dist[y][x] = i;

      int dx[8] = {0,0,1,-1,1,1,-1,-1};
      int dy[8] = {1,-1,0,0,1,-1,1,-1};
      for(int i=0;i<4;i++){
        q2.push({{y+dy[i], x+dx[i]},{y,x}});
      }
      q2.push({{0,x},{y,x}});
      q2.push({{y,0},{y,x}});
      q2.push({{h-1,x},{y,x}});
      q2.push({{y,w-1},{y,x}});
    }

    q1 = q2;
  }

  cout << dist[gy][gx] << " " << dp[gy][gx] << endl;
  
  return 0;
}

