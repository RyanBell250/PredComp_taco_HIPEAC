#include<bits/stdc++.h>

#define REP(i,s,n) for(int i=s;i<n;i++)
#define rep(i,n) REP(i,0,n)
#define EMPTY 0

using namespace std;

typedef long long ll;
ll LLINF = LLONG_MAX;

int n,a[5][5],tmp[5][5];
ll score[5],maxi;
int dx[] = {0,1,0,-1}; // ???,???,?????????
int dy[] = {1,0,-1,0};
bool used[5][5];

inline bool isValid(int x,int y) { return 0 <= x && x < 5 && 0 <= y && y < 5; }

void update(){

  rep(i,5) rep(j,5) tmp[i][j] = a[i][j];
  ll point = 0, phase = 0;
  bool update = true;
  while( update ){
    ++phase;
    update = false;
    memset(used,false,sizeof(used));
    rep(y,5){
      rep(x,5){
        if(  a[y][x] == EMPTY ) continue;
        rep(i,2) {
          int cnt = 0;
          int cx = x, cy = y, color = a[cy][cx];
          while( isValid(cx,cy) && a[cy][cx] == color ) {
            ++cnt, cx += dx[i], cy += dy[i];
          }
          if( cnt >= 3 ) {
            update = true;
            cx = x, cy = y;
            while( isValid(cx,cy) && a[cy][cx] == color ) {
              used[cy][cx] = true;
              ++cnt, cx += dx[i], cy += dy[i];
            } 
          }
        }
      }
    }
    ll sum = 0;
    rep(y,5) rep(x,5) if( used[y][x] ) {
      assert( 1 <= a[y][x] && a[y][x] <= 5 );
      sum += score[a[y][x]-1] * phase;
      a[y][x] = EMPTY;
    }
    point += sum;
    rep(x,5){
      for(int y=4;y>=0;y--) if( a[y][x] != EMPTY ) {
          int cx = x + dx[0], cy = y + dy[0];
          while( isValid(cx,cy) && a[cy][cx] == EMPTY ){
            swap(a[cy][cx],a[cy+dy[2]][cx+dx[2]]);
            cx += dx[0], cy += dy[0];
          }          
      }
    }
  }
  maxi = max(maxi,point);
  rep(i,5) rep(j,5) a[i][j] = tmp[i][j];
}

void dfs(int cx,int cy,int prev,int depth){
  update();
  if( depth >= n ) return;

  rep(i,4) if( ( i + 2 ) % 4 != prev ) {
    int nx = cx + dx[i], ny = cy + dy[i];
    if( !isValid(nx,ny) ) continue;
    swap(a[ny][nx],a[cy][cx]);
    dfs(nx,ny,i,depth+1);
    swap(a[ny][nx],a[cy][cx]);
  }
}

void compute(){
  maxi = -LLINF;
  rep(i,5) rep(j,5) dfs(j,i,-1,0);
  cout << maxi << endl;
}

int main(){
  while( cin >> n, n != -1 ){
    rep(i,5) rep(j,5) cin >> a[i][j];
    rep(i,5) cin >> score[i];
    compute();
  }
  return 0;
}