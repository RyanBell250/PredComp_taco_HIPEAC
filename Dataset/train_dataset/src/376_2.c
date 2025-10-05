#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
#include<cassert>
#include<cmath>
using namespace std;
typedef long long ll;
struct Point{
  ll x,y;
  Point operator - (const Point& p) const {
    Point res = *this;
    res.x -= p.x;
    res.y -= p.y;
    return res;
  }
};
typedef pair<ll,ll> P;
struct State{
  int now,pre;
  P t;
  bool operator < (const State& st) const {
    return t > st.t;
  }
};
ll cross(Point a, Point b){return a.x*b.y-a.y*b.x; }
bool isRight(Point p0, Point p1, Point p2){
  Point a = p1-p0;
  Point b = p2-p0;
  return cross(a,b) < 0;
}
const int MAX = 1050;
const ll INF = (1LL<<60);
map<string,int> idx;
vector<int> E[MAX];
Point pos[MAX];
int M,N;
P T[MAX][MAX];
void init(){
  idx.clear();
  for(int i = 0; i < MAX; i++) E[i].clear();
}
void input(){
  int cnt = 0;
  for(int i = 0; i < M; i++){
    string s;
    Point p;
    cin >> s >> p.x >> p.y;
    if(!idx.count(s)) idx[s] = cnt++;
    pos[idx[s]] = p;
  }
  for(int i = 0; i < N; i++){
    string p,q;
    cin >> p >> q;
    E[idx[p]].push_back(idx[q]);
    E[idx[q]].push_back(idx[p]);
  }
}
ll getDist(const Point& p1, const Point& p2){
  return abs(p1.x-p2.x)+abs(p1.y-p2.y);
}
void solve(const int& src, const int& dst){
  fill(T[0], T[0]+MAX*MAX, P(INF,INF));
  priority_queue<State> Q;
  for(int i = 0; i < (int)E[src].size(); i++){
    ll d = getDist(pos[E[src][i]], pos[src]);
    T[E[src][i]][src] = P(d,2);
    Q.push((State){E[src][i],src,P(d,2)});
  }
  while(!Q.empty()){
    const State st = Q.top();
    Q.pop();
    if(T[st.now][st.pre] < st.t) continue;
    for(int i = 0; i < (int)E[st.now].size(); i++){
      if(st.pre == E[st.now][i]) continue;
      if(isRight(pos[st.pre], pos[st.now], pos[E[st.now][i]])) continue;
      State nex = st;
      nex.t.first += getDist(pos[st.now], pos[E[st.now][i]]);
      nex.t.second++;
      nex.now = E[st.now][i];
      nex.pre = st.now;
      if(T[nex.now][nex.pre] > nex.t){
	T[nex.now][nex.pre] = nex.t;
	Q.push(nex);
      }
    }
  }
  ll minDist = INF, res = INF;
  for(int i = 0; i < MAX; i++) minDist = min(minDist, T[dst][i].first);
  for(int i = 0; i < MAX; i++) if(T[dst][i].first == minDist) res = min(res, T[dst][i].second);
  if(res == INF) cout << "impossible" << endl;
  else cout << res << endl;
}
int main(){
  while(cin >> M >> N && M+N){
    init();
    input();
    string src, dst;
    cin >> src >> dst;
    solve(idx[src],idx[dst]);
  }
  return 0;
}