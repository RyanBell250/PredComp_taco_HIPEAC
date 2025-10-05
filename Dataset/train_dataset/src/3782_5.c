#include<iostream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<map>

using namespace std;

typedef pair<string, int> P;
const int MAX = 10001;
const int SIZE = 4;
int dp[MAX], N, T;
char grid[SIZE][SIZE];
vector<P> word;
map<string, int> able;
int dh[] = {1,0,-1,0,1,1,-1,-1};
int dw[] = {0,1,0,-1,1,-1,1,-1};

void input(){
  cin >> N;
  word.resize(N);
  for(int i = 0; i < N; i++){
    cin >> word[i].first >> word[i].second;
    able[word[i].first] = 0;
  }
  for(int i = 0; i < SIZE; i++) for(int j = 0; j < SIZE; j++) cin >> grid[i][j];
  cin >> T;
}

void rec(const int& h, const int& w, const string& s, const int& used){
  if(able.count(s)) able[s]++;
  if(s.length() == 8) return;
  for(int i = 0; i < 8; i++){
    int nh = h+dh[i], nw = w+dw[i];
    if(nh < 0 || nh >= SIZE || nw < 0 || nw >= SIZE) continue;
    if(used & (1 << (4*nh+nw))) continue;
    rec(nh, nw, s+grid[nh][nw], used | (1<<(4*nh+nw)));
  }
}

void find(){
  for(int h = 0; h < SIZE; h++)
    for(int w = 0; w < SIZE; w++)
      rec(h,w,string(1,grid[h][w]),(1<<(4*h+w)));
}

void solve(){
  memset(dp, -1, sizeof(dp));
  dp[0] = 0;
  
  for(int i = 0; i < (int)word.size(); i++)
    for(int t = T; t >= 0; t--)
      if(dp[t] != -1){
	int lim = able[word[i].first];
	for(int q = 1; q <= lim; q++)
	  if(t+q*(int)word[i].first.length() <= T) dp[t+q*word[i].first.length()] = max(dp[t+q*word[i].first.length()], dp[t]+q*word[i].second);
	  else break;
      }

  int res = 0;
  for(int i = 0; i <= T; i++) res = max(res, dp[i]);
  cout << res << endl;
}
int main(){
  input();
  find();
  solve();
  return 0;
}