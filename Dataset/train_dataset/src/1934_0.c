#include <iostream>
#include <iomanip>
#include <cstdio>
#include <string>
#include <cstring>
#include <deque>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <complex>
#include <cmath>
#include <limits>
#include <cfloat>
#include <climits>
#include <ctime>
#include <cassert>
#include <numeric>
#include <fstream>
#include <functional>
using namespace std;
  
#define rep(i,a,n) for(int (i)=(a); (i)<(n); (i)++)
#define repq(i,a,n) for(int (i)=(a); (i)<=(n); (i)++)
#define repr(i,a,n) for(int (i)=(a); (i)>=(n); (i)--)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define int long long int
  
template<typename T> void chmax(T &a, T b) {a = max(a, b);}
template<typename T> void chmin(T &a, T b) {a = min(a, b);}
template<typename T> void chadd(T &a, T b) {a = a + b;}
  
typedef pair<int, int> pii;
typedef long long ll;
  
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
const ll INF = 1001001001001001LL;
const ll MOD = 1000000007LL;
 
pair<int, int> dp[510][510];
const pair<int, int> INFII(INF, -1);
  
void update(pair<int, int> &A, pair<int, int> B) {
    B.first = B.first + 1;
    if(A.first > B.first) A = B;
    else if(A.first == B.first) {
        (A.second += B.second) %= MOD;
    }
}
 
struct Elem {
    int x, y, ans, cnt;
};
 
signed main() {
    int R, C, sx, sy, tx, ty; cin >> R >> C >> sx >> sy >> tx >> ty;
    fill(dp[0], dp[R], INFII);
    dp[sx][sy] = make_pair(0, 1);
 
    queue<Elem> que;
    que.push(Elem{sx, sy, 0, 1});
 
    const int ex[] = {-1, 0, -1, R-1};
    const int ey[] = {0, -1, C-1, -1};
    for(int step=0; step<R+C; step++) {
        set< pair<int, int> > checked;
        while(que.size()) {
            Elem cur = que.front(); que.pop();
            // 隣接
            for(int k=0; k<4; k++) {
                int nx = cur.x + dx[k], ny = cur.y + dy[k];
                if(nx < 0 || ny < 0 || nx >= R || ny >= C) continue;
                if(dp[nx][ny].first < dp[cur.x][cur.y].first + 1) continue;
                update(dp[nx][ny], dp[cur.x][cur.y]);
                checked.insert(make_pair(nx, ny));
            }
 
            // テレポート
            for(int k=0; k<4; k++) {
                int nx = (ex[k] < 0 ? cur.x : ex[k]);
                int ny = (ey[k] < 0 ? cur.y : ey[k]);
                if(dp[nx][ny].first < dp[cur.x][cur.y].first + 1) continue;
                update(dp[nx][ny], dp[cur.x][cur.y]);
                checked.insert(make_pair(nx, ny));
            }
        }
         
        for(auto x : checked) {
            int nx, ny; tie(nx, ny) = x;
            int vl, vr; tie(vl, vr) = dp[nx][ny];
            que.push(Elem{nx, ny, vl, vr});
        }
    }
 
    int ans1, ans2;
    tie(ans1, ans2) = dp[tx][ty];
    printf("%lld %lld\n", ans1, ans2);
    return 0;
}
