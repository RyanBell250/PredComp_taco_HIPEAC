#include<iostream>
#include<queue>
using namespace std;
#define REP(i,b,n) for(int i=b;i<n;i++)
#define rep(i,n)   REP(i,0,n)
int m[4][4];
int ans=6;
bool haveans=false;
int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};
bool isok(){
  rep(i,4)rep(j,4)if (m[i][j] != 0)return false;
  return true;
}
bool isout(int y,int x){
  return x==-1||y==-1||x==4||y==4;
}
typedef pair<int,int> pii;
void hit(int y,int x){
  queue<pii> Q[2];
  m[y][x]=0;
  rep(k,4){
    Q[0].push(make_pair(y*4+x,k));
  }
  int now = 0;
  while(!Q[now].empty()){
    int next=(now+1)%2;
    while(!Q[now].empty()){
      int nx=Q[now].front().first%4,ny=Q[now].front().first/4;
      int dir=Q[now].front().second;
      Q[now].pop();
      while(!isout(ny,nx)){
	if (m[ny][nx] != 0){
	  m[ny][nx]++;
	  break;
	}
	nx+=dx[dir],ny+=dy[dir];
      }
    }
    rep(i,4)rep(j,4){
      if (m[i][j] >= 5){
	m[i][j]=0;
	rep(k,4)Q[next].push(make_pair(i*4+j,k));
      }
    }
    now = next;
  }
}
void test(){
  while(true){
    if (cin.eof())return;
    rep(i,4)rep(j,4)cin>>m[i][j];
    int y,x;
    cin>>y>>x;
    hit(y,x);
  }
}
void search(int cnt){
  if (cnt >= ans)return;
  int tmp[4][4];
  if (isok()){
    ans=cnt;
    haveans=true;
    return;
  }
  if (cnt+1 >= ans)return;
  rep(i,4)rep(j,4)tmp[i][j]=m[i][j];
  rep(i,4){
    rep(j,4){
      m[i][j]++;
      if (m[i][j] == 5)hit(i,j);
      search(cnt+1);
      rep(ii,4)rep(jj,4)m[ii][jj]=tmp[ii][jj];
    }
  }
}
int main(){
  rep(i,4)rep(j,4)cin>>m[i][j];
  search(0);
  if (haveans)cout << ans << endl;
  else cout << -1 << endl;
}