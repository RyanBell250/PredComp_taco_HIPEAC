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
#include <functional>
using namespace std;

#define rep(i,a,n) for(int (i)=(a); (i)<(n); (i)++)
#define repq(i,a,n) for(int (i)=(a); (i)<=(n); (i)++)
#define repr(i,a,n) for(int (i)=(a); (i)>=(n); (i)--)
#define int long long int

template<typename T> void chmax(T &a, T b) {a = max(a, b);}
template<typename T> void chmin(T &a, T b) {a = min(a, b);}
template<typename T> void chadd(T &a, T b) {a = a + b;}

typedef pair<int, int> pii;
typedef long long ll;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
constexpr ll INF = 1001001001001001LL;
constexpr ll MOD = 1000000007LL;

int N, M, L;
int dp[1 << 16][2];

signed main() {
    while(cin >> N, N) {
        memset(dp, -1, sizeof(dp));
        dp[0][0] = 0;

        int ans = 0;
        rep(p,0,N) {
            int mo = p%2, info = 0;
            cin >> M >> L;
            rep(i,0,M) {
                int S, E; cin >> S >> E;
                S -= 6, E -= 6;

                int val = 0;
                rep(j,S,E) val += (1 << j);
                info += val;
            }

            rep(bit,0,1<<16) {
                chmax(dp[bit][mo^1], dp[bit][mo]);
                if(bit & info) continue;
                if(dp[bit][mo] == -1) continue;
                chmax(dp[bit | info][mo^1], dp[bit][mo] + L);
                dp[bit][mo] = -1;
            }
        }
        rep(i,0,1<<16) chmax(ans, dp[i][N%2]);
        cout << ans << endl;
    }
    return 0;
}