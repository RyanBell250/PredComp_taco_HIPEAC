#include <bits/stdc++.h>
#define int long long
using namespace std;
int H, W, a[6][6], ans;
int pepi[6][6];
int dy[6] = {-1,0,1,1,1,0};
int dx[6] = {0,1,1,0,-1,-1};
int dy2[6] = {-1,-1,-1,0,1,0};
int dx2[6] = {-1,0,1,1,0,-1};
int XXX_cnt;
int XXX[7][19];
void dfs1(int hako, int tama){
  if( hako == 0 ){
    if( tama != 0 )return;
    XXX_cnt++;
    return;
  }
  for(int i=0;i<=3;i++){
    if( tama - i < 0 )continue;
    dfs1( hako - 1, tama - i );
  }
}
void INIT(){
  for(int i=1;i<=6;i++){
    for(int j=1;j<=18;j++){
      XXX_cnt = 0;
      dfs1( i, j );
      XXX[i][j] = XXX_cnt;
    }
  }
}
void init(){
  int memo[6][6] = {};
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      if( a[i][j] != 0 ){
	for(int k=0;k<6;k++){
	  int ni = i + dy[k];
	  int nj = j + dx[k];
	  if( ni < 0 || nj < 0 || H <= ni || W <= nj ) continue;
	  if( a[ni][nj] != 0 ) continue;
	  memo[ni][nj]++;
	}
      }      
    }
  }
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      if( a[i][j] == 0 ){
	if( memo[i][j] == 1 ) pepi[i][j] = 1;
	if( memo[i][j] >= 2 ) pepi[i][j] = 2;
	if( memo[i][j] == 0 ) pepi[i][j] = 3;
      }
    }
  }
}
typedef long long ll;
const ll mod = 1e9+7;
ll mod_pow(ll x,ll n){
  ll res=1;
  while(n){
    if(n%2) res=res*x%mod;
    x=x*x%mod;
    n/=2;
  }
  return res;
}
int cal(){
  int cnt = 0;
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      if( pepi[i][j] == 3 ) cnt++;
    }
  }
  int res = mod_pow( 4, cnt );
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      if( pepi[i][j] == 0 ){
	int cnt = 0;
	for(int k=0;k<6;k++){
	  int ni = i + dy[k];
	  int nj = j + dx[k];
	  if( ni < 0 || nj < 0 || H <= ni || W <= nj ) continue;
	  if( pepi[ni][nj] == 1 ) cnt++;
	}
	if( a[i][j] == 0 ) continue;
	if( cnt * 3 < a[i][j] ) return 0;
	res *= XXX[cnt][ a[i][j] ];
	res %= mod;
      }
    }
  }
  return res;
}
bool check(int y, int x, int cnt){
  for(int i=0;i<6;i++){
    int ny = y + dy2[i];
    int nx = x + dx2[i];
    if( ny < 0 || nx < 0 || H <= ny || W <= nx ) continue;
    if( pepi[ny][nx] == 0 && a[ny][nx] - cnt < 0 ) return false;
  }
  return true;
}
void update(int y, int x, int cnt){
  for(int i=0;i<6;i++){
    int ny = y + dy2[i];
    int nx = x + dx2[i];
    if( ny < 0 || nx < 0 || H <= ny || W <= nx ) continue;
    if( pepi[ny][nx] == 0 ) a[ny][nx] -= cnt;
  }
}
void downdate(int y, int x, int cnt){
  for(int i=0;i<6;i++){
    int ny = y + dy2[i];
    int nx = x + dx2[i];
    if( ny < 0 || nx < 0 || H <= ny || W <= nx ) continue;
    if( pepi[ny][nx] == 0 ) a[ny][nx] += cnt;
  }
}
bool dame(int y, int x){
  y -= 1;
  x -= 2;
  if( y < 0 || x < 0 || H <= y || W <= x ) return false;
  if( pepi[y][x] != 0 ) return false;
  int cnt = 0;
  for(int k=0;k<6;k++){
    int ni = y + dy[k];
    int nj = x + dx[k];
    if( ni < 0 || nj < 0 || H <= ni || W <= nj ) continue;
    if( pepi[ni][nj] == 1 ) cnt++;
  }
  if( cnt * 3 < a[y][x] ) return true;
  return false;
}
void dfs(int y, int x){
  if( y == H && x == 0 ){
    ans += cal();
    ans %= mod;
    return;
  }
  if( dame( y, x ) == true ) return;
  if( pepi[y][x] != 2 ){
    int ny = y, nx = x + 1;
    if( nx == W ){
      ny = y + 1;
      nx = 0;
    }
    dfs( ny, nx );
    return;
  }
  for(int i=0;i<=3;i++){
    if( check( y, x, i ) == false ) break;
    update( y, x, i );
    int ny = y, nx = x + 1;
    if( nx == W ){
      ny = y + 1;
      nx = 0;
    }
    dfs( ny, nx );
    downdate( y, x, i );
  }
}
signed main(){
  cin>>H>>W;
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      cin>>a[i][j];
    }
  }
  init();
  INIT();
  dfs( 0, 0 );
  cout<<ans<<endl;
  return 0;
}
