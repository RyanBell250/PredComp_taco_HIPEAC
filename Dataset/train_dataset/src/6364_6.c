#include "bits/stdc++.h"

using namespace std;
using LL = long long;

constexpr int N = 1e5 + 5;
constexpr int MOD = 998244353;

LL fac[N], inv[N];

LL power(LL a, LL b) {
    LL rv = 1;
    while (b) {
        if (b&1) rv = rv * a % MOD;
        b /= 2;
        a = a * a % MOD;
    }

    return rv;
}

LL C(int n, int k) {
    LL rv = fac[n];
    (rv *= inv[k]) %= MOD;
    (rv *= inv[n - k]) %= MOD;
    return rv;
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;

    vector< int> parts;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') cnt++;
        else if (cnt > 0) {
            parts.push_back(cnt);
            cnt = 0;
        }
    }
    if (cnt) parts.push_back(cnt);

    int k = 0;
    for (auto x : parts) {
        if (x & 1) {
            x--;
            n--;
        }
        n -= x / 2;
        k += x / 2;
    }


    cout << C(n, k) << "\n";
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false); 

    fac[0] = 1;
    for (int i = 1; i < N; i++) fac[i] = fac[i - 1] * i % MOD;
    inv[N - 1] = power(fac[N - 1], MOD - 2);
    for (int i = N - 2; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % MOD;

    int T;
    cin >> T;

    for (int i = 1; i <= T; i++) {
        solve();
    }
}

