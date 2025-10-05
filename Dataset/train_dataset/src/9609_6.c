#include <bits/stdc++.h>
using namespace std;
#define repl(i,a,b) for(int i=(int)(a);i<(int)(b);i++)
#define rep(i,n) repl(i,0,n)
#define mp(a,b) make_pair((a),(b))
#define pb(a) push_back((a))
#define all(x) (x).begin(),(x).end()
#define uniq(x) sort(all(x)),(x).erase(unique(all(x)),end(x))
#define fi first
#define se second
#define dbg(...) _dbg(#__VA_ARGS__, __VA_ARGS__)
void _dbg(string){cout<<endl;}
template<class H,class... T> void _dbg(string s,H h,T... t){int l=s.find(',');cout<<s.substr(0,l)<<" = "<<h<<", ";_dbg(s.substr(l+1),t...);}
template<class T,class U> ostream& operator<<(ostream& o, const pair<T,U> &p){o<<"("<<p.fi<<","<<p.se<<")";return o;}
template<class T> ostream& operator<<(ostream& o, const vector<T> &v){o<<"[";for(T t:v){o<<t<<",";}o<<"]";return o;}
#define INF 1120000000
vector<int> tree[105*105];
map<vector<int>,int> conv;
int pre[300005];
int val[300005];
bool checked[300005];
int tree2idx(int i, vector<int> *vec){
  function<int(int,int)> dfs = [&](int d, int from){
    vector<int> ord;
    queue<pair<int,int>> q;
    q.push(mp(d,from));
    while(q.size()){
      auto p = q.front(); q.pop();
      int node = p.first;
      int prev = p.second;
      ord.pb(node);
      pre[node] = prev;
      for(auto to : vec[node]) if(to != prev){
        q.push(mp(to, node));
      }
    }
    reverse(all(ord));
    for(auto node : ord){
      vector<int> v;
      for(auto to : vec[node]) if(to!=pre[node]) v.pb(val[to]);
      sort(all(v));
      if(conv.count(v)==0) conv[v] = conv.size();
      val[node] = conv[v];
    }
    return val[d];
  };
  return dfs(i, -1);
}
int calc(int h, int w){
  vector<string> vec(h+2);
  rep(i,h) cin>>vec[i+1];
  vec[0] = vec[h+1] = string(w+2, '.');
  rep(i,h) vec[i+1] = "." + vec[i+1] + ".";
  h += 2;
  w += 2;
  int cnt = 0;
  vector<vector<int>> num(h,vector<int>(w,-1));
  rep(i,h)rep(j,w)if(num[i][j]==-1){
    vector<int> dx,dy;
    if(vec[i][j]=='.'){dx = {0,1,0,-1}, dy={1,0,-1,0};}
    else{ dx={-1,-1,-1,0,0,1,1,1}, dy={-1,0,1,-1,1,-1,0,1};}
    queue<pair<int,int>> q;
    q.push(mp(i,j));
    num[i][j] = cnt;
    while(q.size()){
      auto p = q.front(); q.pop();
      rep(k, dx.size()){
        int nx = p.fi + dx[k], ny = p.se + dy[k];
        if(nx<0 || nx>=h || ny<0 || ny>=w || num[nx][ny]!=-1 || vec[i][j]!=vec[nx][ny]) continue;
        q.push(mp(nx,ny));
        num[nx][ny] = cnt;
      }
    }
    cnt++;
  }
  vector<bool> visited(cnt, false);
  rep(i,cnt) tree[i].clear();
  queue<pair<int,int>> nxt;
  nxt.push(mp(0,0));
  visited[0] = true;
  while(nxt.size()){
    auto pp = nxt.front(); nxt.pop();
    int i=pp.first;
    int j=pp.second;
    queue<pair<int,int>> q;
    q.push(mp(i,j));
    int crnt = num[i][j];
    num[i][j] = -1;
    vector<int> dx,dy;
    if(vec[i][j]=='.'){dx = {0,1,0,-1}, dy={1,0,-1,0};}
    else{ dx={-1,-1,-1,0,0,1,1,1}, dy={-1,0,1,-1,1,-1,0,1};}
    while(q.size()){
      auto p = q.front(); q.pop();
      rep(k, dx.size()){
        int nx = p.fi + dx[k], ny = p.se + dy[k];
        if(nx<0 || nx>=h || ny<0 || ny>=w || num[nx][ny]==-1) continue;
        if(num[nx][ny] != crnt){
          if(!visited[num[nx][ny]]){
            nxt.push(mp(nx,ny));
            int nn = num[nx][ny];
            visited[num[nx][ny]] = true;
            tree[crnt].pb(nn);
            tree[nn].pb(crnt);
          }
        }
        else {
          q.push(mp(nx,ny));
          num[nx][ny] = -1;
        }
      }
    }
  }
  return tree2idx(0,tree);
}
bool solve(int h, int w){
  auto v1 = calc(h,w);
  cin>>h>>w;
  auto v2 = calc(h,w);
  return v1==v2;
}
int main(){
  int h,w;
  while(cin>>h>>w, h|w){
    if(solve(h,w)) cout << "yes" << endl;
    else cout << "no" << endl;
  }
  return 0;
}