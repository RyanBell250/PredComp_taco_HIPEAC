#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128_t LL;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define F first
#define S second
#define pb push_back
mt19937 rnd;

struct Point {
    int x, y;
    void flip() {
        swap(x, y);
    }
    int calc() const {
        return abs(x - y);
    }
    bool operator<(const Point& ot) const {
        return std::tie(x, y) < std::tie(ot.x, ot.y);
    }
};

const int N = 2e5 + 10;
Point a[N];
int pref[N];

ll solve(int n) {
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1];
        if (a[i].x <= a[i].y) {
            pref[i] = max(pref[i], a[i].y);
        }
    }
    int res = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i].x >= a[i].y && a[1].x <= a[i].y) {
            int lef = 1, rig = n;
            while (lef < rig) {
                int mid = (lef + rig) / 2;
                if (a[mid + 1].x <= a[i].y) {
                    lef = mid + 1;
                }
                else {
                    rig = mid;
                }
            }
            res = max(res, min(a[i].x, pref[lef]) - a[i].y);
        }
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
#ifdef LOCAL
    freopen("input.txt", "r", stdin);
#endif

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x;
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i].y;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        ans += a[i].calc();
    }
    sort(a + 1, a + n + 1);
    ll mx = 0;
    mx = max(mx, solve(n));
    for (int i = 1; i <= n; i++) {
        a[i].flip();
    }
    sort(a + 1, a + n + 1);
    mx = max(mx, solve(n));
    cout << ans - 2 * mx << "\n";

#ifdef LOCAL
    cerr << "\nTime elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
