#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> l_l;
typedef pair<int, int> i_i;
typedef pair<int, l_l> Vll;
template<class T>
inline bool chmax(T &a, T b) {
    if(a < b) {
        a = b;
        return true;
    }
    return false;
}
template<class T>
inline bool chmin(T &a, T b) {
    if(a > b) {
        a = b;
        return true;
    }
    return false;
}
#define EPS (1e-7)
#define INF (1e9)
#define PI (acos(-1))
int dp[205][2400][12][12];
ll N, M, K;
int maxmask(int bit, int l = K + 2) {
    if(l < 0) return -1;
    if((bit >> l) & 1)  return l;
    return maxmask(bit, l - 1);
}
int main() {
    cin >> N >> K >> M;
    dp[0][0][0][0] = 1;
    for(int val = 1; val <= 2 * N; val++) {
        for(int bits = 0; bits < (1 << (K)); bits++) {
        for(int i = 0; i <= K + 1; i++) {
        for(int j = 0; j <= K + 1; j++) {
            if(maxmask(bits) >= 0) {
                int nowbit = bits;
                nowbit &= ~(1 << maxmask(bits));
                nowbit <<= 1;
                if(j <= K && maxmask(bits) + 1 <= K) dp[val][nowbit][i+1][1] = (dp[val][nowbit][i+1][1] + dp[val-1][bits][i][j]) % M;
            }
            if(i > K) continue;
            int nowbit = (bits << 1);
            nowbit |= 1;
            dp[val][nowbit][1][j+1] = (dp[val][nowbit][1][j+1] + dp[val-1][bits][i][j]) % M;
        }
        }
        }
    }
    ll ans = 0;
    for(int i = 0; i <= K + 1; i++) {
        for(int j = 0; j <= K + 1; j++) ans = (ans + dp[2 * N][0][i][j]) % M;
    }
    cout << ans << endl;
    return 0;
}
