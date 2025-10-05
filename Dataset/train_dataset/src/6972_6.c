#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
using namespace std;
#define FOR(i,k,n) for(int i=(k); i<(int)(n); ++i)
#define REP(i,n) FOR(i,0,n)
#define FORIT(i,c) for(__typeof((c).begin())i=(c).begin();i!=(c).end();++i)
template<class T> void debug(T begin, T end){ for(T i = begin; i != end; ++i) cerr<<*i<<" "; cerr<<endl; }
inline bool valid(int x, int y, int W, int H){ return (x >= 0 && y >= 0 && x < W && y < H); }
typedef long long ll;
const int INF = 100000000;
const double EPS = 1e-8;
const int MOD = 1000000007;
int dx[8] = {1, 0, -1, 0, 1, -1, -1, 1};
int dy[8] = {0, 1, 0, -1, 1, 1, -1, -1};
struct Chara{
  string name;
  int vote;
  bool operator < (const Chara& c) const {
    if(vote != c.vote) return vote > c.vote;
    return name < c.name;
  }
};
int main(){
  int N, M, K, L;
  while(cin >> N >> M >> K >> L && N){
    Chara cs[100000];
    REP(i, N){
      char s[11];
      scanf("%s %d", s, &cs[i].vote);
      cs[i].name = string(s);
    }
    sort(cs, cs + N);
    set<string> favs;
    REP(i, M){
      char s[11];
      scanf("%s", s);
      favs.insert(string(s));
    }
    int lb = 0, ub = min(M + 1, K + 1); 
    while(lb + 1 < ub){
      int X = (ub + lb) / 2; 
      ll S = 0;
      int idx = K - X;
      int Rest = X;
      for(int i = 0; i < N; i++) if(Rest > 0 && favs.count(cs[i].name)){
        if(i > idx){
          S += cs[idx].vote - cs[i].vote;
          if(cs[idx].name < cs[i].name) S++;
        }else{
          idx++;
        }
        if(S > L) break;
        Rest--;
      }
      if(S <= L) {
        lb = X;
      }else{
        ub = X;
      }
    }
    cout << lb << endl;
  }
  return 0;
}