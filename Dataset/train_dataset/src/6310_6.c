
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
#include <bitset>
using namespace std;
using ll = long long int;
using int64 = long long int;
template<typename T> void chmax(T &a, T b) {a = max(a, b);}
template<typename T> void chmin(T &a, T b) {a = min(a, b);}
template<typename T> void chadd(T &a, T b) {a = a + b;}
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
const int INF = 1LL << 29;
const ll LONGINF = 1LL << 60;
const ll MOD = 1000000007LL;
ll dp[30][60000], exist[30][30], cost[30][30], three[12];
int main() {
    int N; cin >> N;
    for(int i=0; i<N; i++) {
        char u; ll v; cin >> u >> v;
        exist[u-'A'][v] = true;
    }
    int M; cin >> M;
    fill(cost[0], cost[28], LONGINF);
    for(int i=0; i<M; i++) {
        char x; ll y, z; cin >> x >> y >> z;
        chmin(cost[x-'A'][y], z);
    }
    three[0] = 1;
    for(int i=1; i<=10; i++) three[i] = three[i-1] * 3;
    fill(dp[0], dp[28], LONGINF);
    dp[0][0] = 0;
    for(int i=0; i<26; i++) {
        for(int bit=0; bit<three[10]; bit++) {
            if(dp[i][bit] == LONGINF) continue;
            for(int d=0; d<10; d++) {
                int nbit = bit - (bit%three[d+1]/three[d]*three[d]) + three[d]*2;
                chmin(dp[i][nbit], dp[i][bit] + cost[i][d]);
                chmin(dp[i+1][nbit], dp[i][bit] + cost[i][d]);
            }
            int b = bit;
            for(int d=0; d<10; d++) {
                if(!exist[i][d] or b%three[d+1]/three[d] != 0) continue;
                b += three[d];
            }
            chmin(dp[i+1][b], dp[i][bit]);
        }
    }
    ll ans = LONGINF;
    for(int bit=0; bit<three[10]; bit++) {
        bool ok = true;
        for(int d=0; d<10; d++) {
            if(bit%three[d+1]/three[d] == 1) {
                ok = false;
                break;
            }
        }
        if(ok) chmin(ans, dp[26][bit]);
    }
    if(ans == LONGINF) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}
