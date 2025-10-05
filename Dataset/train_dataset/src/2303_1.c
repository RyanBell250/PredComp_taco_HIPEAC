#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
 
using namespace std;
 
typedef pair<vector<string>, int> P;
 
bool G[4][2][4][2];
map<vector<string>, int> dat, dat2;
int n, m;
 
void init(){
  fill(G[0][0][0], G[4][0][0], false);
  dat.clear();
  dat2.clear();
}
 
void bfs1(vector<string> &s){
  queue<P> que;
  dat[s] = 0;
  que.push(P(s, 0));
  while(!que.empty()){
    vector<string> u = que.front().first;
    int dist = que.front().second;
    que.pop();
    for(int i=0;i<n;i++){
      for(int j=-1;j<(int)u[i].size();j++){
        int p1 = i;
        for(int d1=0;d1<2;d1++){
          for(int p2=0;p2<n;p2++){
            for(int d2=0;d2<2;d2++){
              if(G[p1][d1][p2][d2]){
                vector<string> v;
                v.resize(n);
                string next;
                for(int k=0;k<n;k++){
                  if(k == p1){
                    if(d1 == 0){
                      next = u[k].substr(j+1);
                      v[k] = next;
                    }else{
                      next = u[k].substr(0, j+1);
                      v[k] = next;
                    }
                  }else{
                    v[k] = u[k];
                  }
                }
                if(d1 == 0){
                  if(d2 == 0){
                    next = u[p1].substr(0, j+1);
                    reverse(next.begin(), next.end());                  
                    v[p2] = next + v[p2];
                  }else{
                    next = u[p1].substr(0, j+1);
                    v[p2] = v[p2] + next;
                  }
                }else{
                  if(d2 == 0){
                    next = u[p1].substr(j+1);
                    v[p2] = next + v[p2];
                  }else{
                    next = u[p1].substr(j+1);
                    reverse(next.begin(), next.end());                  
                    v[p2] = v[p2] + next;
                  }
                }
                if(dat.find(v) == dat.end()){
                  dat[v] = dist + 1;
                  if(dist + 1 < 2) que.push(P(v, dist + 1));
                }
              }
            }
          }
        }
      }
    }
  }
}
 
int bfs2(vector<string> &s){
  queue<P> que;
  dat2[s] = 0;
  que.push(P(s, 0));
  if(dat.find(s) != dat.end()) return dat[s];
  int res = 6;
  while(!que.empty()){
    vector<string> u = que.front().first;
    int dist = que.front().second;
    que.pop();
    if(dist >= 3) continue;
    for(int i=0;i<n;i++){
      for(int j=-1;j<(int)u[i].size();j++){
        int p1 = i;
        for(int d1=0;d1<2;d1++){
          for(int p2=0;p2<n;p2++){
            for(int d2=0;d2<2;d2++){
              if(G[p1][d1][p2][d2]){
                vector<string> v;
                v.resize(n);
                string next;
                for(int k=0;k<n;k++){
                  if(k == p1){
                    if(d1 == 0){
                      next = u[k].substr(j+1);
                      v[k] = next;
                    }else{
                      next = u[k].substr(0, j+1);
                      v[k] = next;
                    }
                  }else{
                    v[k] = u[k];
                  }
                }
                if(d1 == 0){
                  if(d2 == 0){
                    next = u[p1].substr(0, j+1);
                    reverse(next.begin(), next.end());                  
                    v[p2] = next + v[p2];
                  }else{
                    next = u[p1].substr(0, j+1);
                    v[p2] = v[p2] + next;
                  }
                }else{
                  if(d2 == 0){
                    next = u[p1].substr(j+1);
                    v[p2] = next + v[p2];
                  }else{
                    next = u[p1].substr(j+1);
                    reverse(next.begin(), next.end());                  
                    v[p2] = v[p2] + next;
                  }
                }
                if(dat2.find(v) == dat2.end()){
                  if(dat.find(v) != dat.end()){
                    res = min(res, dist + 1 + dat[v]);
                    continue;
                  }
                  dat2[v] = dist + 1;
                  if(dist + 1 < 3) que.push(P(v, dist + 1));
                }
              }
            }
          }
        }
      }
    }
  }
  return res;
}
 
vector<string> cre(){
  vector<string> vec;
  for(int i=0;i<n;i++){
    string in;
    cin >> in;
    if(in == "-") in = "";
    vec.push_back(in);
  }
  return vec;
}
 
int main(){
  while(cin >> n >> m && (n|m)){
    init();
    for(int i=0;i<m;i++){
      string a, b;
      cin >> a >> b;
      int p1 = a[0] - '0';
      int d1 = (a[1] == 'W' ? 0 : 1);
      int p2 = b[0] - '0';
      int d2 = (b[1] == 'W' ? 0 : 1);
      G[p1][d1][p2][d2] = true;
      G[p2][d2][p1][d1] = true;
    }
    vector<string> s = cre();
    bfs1(s);
    vector<string> t = cre();
    cout << bfs2(t) << endl;
  }
}