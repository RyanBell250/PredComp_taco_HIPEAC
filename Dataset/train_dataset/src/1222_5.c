#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef double db;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef pair<pii, int> piipi;
typedef pair<int, pii> pipii;
typedef pair<pii, pii> piipii;
typedef pair<ll, pii> plpii;
typedef pair<db, db> pdd;
typedef pair<ld, ld> pldd;
#define mp make_pair
#define fi first
#define se second
#define sz(x) (int)x.size()
#define all(x) (x).begin(), (x).end()
#define eb emplace_back
#define pf push_front
#define pb push_back
const int mod = 1e9 + 7;

const int P1 = 999983, P2 = 999979;
const ld PI = acos((ld)-1);
const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
const ll INF = 1e18;
const int N = 1e6+5;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int a[N];
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        map<int, int> dp;
        ll ans = 0;
        for(int i=1;i<=n;i++){
            scanf("%d", &a[i]);
            ans += dp[a[i]-i];
            dp[a[i]-i]++;
        }
        printf("%lld\n", ans);
    }       
}
