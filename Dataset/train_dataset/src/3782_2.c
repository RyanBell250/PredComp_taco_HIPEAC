#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#define REP(i,n) for(int i=0; i<(int)(n); ++i)

using namespace std;
typedef long long ll;

const int    INF = 1000000000;
const int    MOD = 1000000007;
const double EPS = 1e-8;

int dx[8] = {1, 0, -1, 0, 1, 1, -1, -1};
int dy[8] = {0, 1, 0, -1, 1, -1, 1, -1};

string line[4];
set<string> dict;
map<string, int> cnt;
bool used[4][4];
void dfs(int x, int y, string s){
    if(dict.count(s)){
        cnt[s]++;
    }
    if(s.size() == 8) return;

    REP(r, 8){
        int nx = x + dx[r];
        int ny = y + dy[r];
        if(nx >= 0 && nx < 4 && ny >= 0 && ny < 4 && !used[ny][nx]){
            used[ny][nx] = true;
            dfs(nx, ny, s + line[ny][nx]);
            used[ny][nx] = false;
        }
    }
}

int main(){
    int N;
    while(cin >> N){
        cnt.clear();

        vector<string> words(N);
        vector<int> scores(N);
        REP(i, N) cin >> words[i] >> scores[i];
        REP(i, N) dict.insert(words[i]);
        REP(i, 4) cin >> line[i];
        REP(y, 4) REP(x, 4){
            used[y][x] = true;
            dfs(x, y, string(1, line[y][x]));
            used[y][x] = false;
        }

        int T;
        cin >> T;
        int dp[10001] = {};
        for(int i = 0; i < N; i++){
            int w = words[i].size();
            int s = scores[i];
            int rest = cnt[words[i]];
            for(int mul = 1; rest > 0; mul <<= 1){
                int use = min(mul, rest);
                rest -= use;
                for(int j = T; j >= use * w; j--){
                    dp[j] = max(dp[j], dp[j - use * w] + use * s);
                }
            }
        }
        cout << dp[T] << endl;
    }
    return 0;
}