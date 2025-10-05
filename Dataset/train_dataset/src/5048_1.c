#include <iostream>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <vector>
#include <valarray>
#include <array>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <complex>
#include <random>
#include <bitset>
#include <stack>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using R = double;
using P = pair<int, int>;
using Pol = vector<P>;
int cross(P a, P b) {
    return a.first*b.second - a.second*b.first;
}
P sub(P a, P b) {
    return P(a.first-b.first, a.second-b.second);
}
Pol convex(Pol p) {
    sort(p.begin(), p.end());
    if (p.size() <= 2) return p;
    Pol down;
    for (P d: p) {
        if (down.size() && down.back().first == d.first) continue;
        while (down.size() > 1 && cross(sub(d, down[down.size()-2]), sub(d, down[down.size()-1])) <= 0) {
            down.pop_back();
        }
        down.push_back(d);
    }
    return down;
}
const int MN = 55;
const int MD = 5050;
const ll INF = 1LL<<55;
Pol dp[MN][MD];
int main() {
    int n, k;
    R A, B, C;
    R fx, fy, fz;
    cin >> n >> k >> A >> B >> C;
    cin >> fx >> fy >> fz;
    dp[0][0].push_back(P(0, 0));
    for (int i = 1; i < n; i++) {
        ll a, b, c;
        cin >> a >> b >> c;
        for (int j = MN-1; j >= 1; j--) {
            for (int o = a; o < MD; o++) {
                for (P p: dp[j-1][o-a]) {
                    dp[j][o].push_back(P(p.first+b, p.second+c));
                }
                dp[j][o] = convex(dp[j][o]);
            }
        }
    }
    ll D = INF;
    for (int x = 0; x < MD; x++) {
        for (P p : dp[k][x]) {
            int y, z;
            tie(y, z) = p;
            D = min(D, (ll)x*y*z);
        }
    }
    R res = 1e9;
    for (int x = 0; x < MD; x++) {
        for (P p: dp[k-1][x]) {
            R X = x, Y = p.first, Z = p.second;
            R c[3] = {A, B, C};
            R f[3] = {fx, fy, fz};
            R l = 0, r = 1e10;
            for (int i = 0; i < 100; i++) {
                R md = (l+r)/2;
                bool fl = false;
                int idx[3] = {0, 1, 2};
                do {
                    R mm = md;
                    R F[3] = {X+fx, Y+fy, Z+fz};
                    for (int j = 0; j < 3; j++) {
                        int now = idx[j];
                        R use = min(mm, c[now]);
                        F[now] -= f[now]*use/c[now];
                        mm -= use;
                    }
                    if (F[0]*F[1]*F[2] <= D) {
                        fl = true;
                        break;
                    }
                } while (next_permutation(idx, idx+3));
                if (!fl) {
                    l = md;
                } else {
                    r = md;
                }
            }
            res = min(res, r);
        }
    }
    printf("%.20lf\n", res);
    return 0;
}