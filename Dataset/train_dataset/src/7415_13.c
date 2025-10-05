#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <cstdint>
using namespace std;
using llong = long long;
template<typename Monoid, typename Laz>
struct LazySegmentTree {
    const function<Monoid(Monoid, Monoid)> mergeMonoid;
    const function<Monoid(Monoid, Laz, int)> applyLaz;
    const function<Laz(Laz, Laz)> mergeLaz;
    const Monoid e; 
    vector<Monoid> seg;
    vector<Laz> lazy;
    vector<bool> isUpdated;
    int size;
    LazySegmentTree(int nmemb, const Monoid &e,
                    function<Monoid(Monoid, Monoid)> f,
                    function<Monoid(Monoid, Laz, int)> g,
                    function<Laz(Laz, Laz)> h):
        e(e), mergeMonoid(f), applyLaz(g), mergeLaz(h)
    {
        size = 1;
        while (size < nmemb) {
            size *= 2;
        }
        seg.assign(2 * size - 1, e);
        isUpdated.assign(2 * size - 1, true);
        lazy.resize(2 * size - 1); 
    }
    inline void propagation(int k, int len) {
        if (!isUpdated[k]) {
            seg[k] = applyLaz(seg[k], lazy[k], len);
            if (len > 1) {
                if (isUpdated[2 * k + 1])
                    lazy[2 * k + 1] = lazy[k], isUpdated[2 * k + 1] = false;
                else
                    lazy[2 * k + 1] = mergeLaz(lazy[2 * k + 1], lazy[k]);
                if (isUpdated[2 * k + 2])
                    lazy[2 * k + 2] = lazy[k], isUpdated[2 * k + 2] = false;
                else
                    lazy[2 * k + 2] = mergeLaz(lazy[2 * k + 2], lazy[k]);
            }
            isUpdated[k] = true;
        }
    }
    Monoid update(int k, int nl, int nr, int ql, int qr, Laz dat) {
        propagation(k, nr - nl);
        if (nr <= ql || qr <= nl) return seg[k];
        if (ql <= nl && nr <= qr) {
            lazy[k] = dat;
            isUpdated[k] = false;
            propagation(k, nr - nl);
            return seg[k];
        }
        else {
            seg[k] = mergeMonoid(update(2 * k + 1, nl, (nl + nr) / 2, ql, qr, dat),
                                 update(2 * k + 2, (nl + nr) / 2, nr, ql, qr, dat));
            return seg[k];
        }
    }
    void update(int l, int r, Laz dat) {
        update(0, 0, size, l, r, dat);
    }
    Monoid fold(int k, int nl, int nr, int ql, int qr) {
        propagation(k, nr - nl);
        if (nr <= ql || qr <= nl) return e;
        if (ql <= nl && nr <= qr) return seg[k];
        else return mergeMonoid(fold(2 * k + 1, nl, (nl + nr) / 2, ql, qr),
                                fold(2 * k + 2, (nl + nr) / 2, nr, ql, qr));
    }
    Monoid fold(int l, int r) {
        if (r <= l) return e;
        return fold(0, 0, size, l, r);
    }
    Monoid operator [](const int &k) {
        return fold(k, k + 1);
    }
};
template<uint64_t mod, uint64_t base>
struct RollingHashMonoid {
    using rh = RollingHashMonoid<mod, base>;
    int sz;
    uint64_t h;
    static vector<uint64_t> p;
    RollingHashMonoid() {};
    RollingHashMonoid(uint64_t ch): sz(1), h(ch % mod) {};
    static rh neutral() {
        RollingHashMonoid res;
        res.sz = 0, res.h = 0;
        return res;
    };
    rh operator + (const rh &r) const {
        const rh &l = *this;
        rh res = neutral();
        while (p.size() <= r.sz) p.push_back(p.back() * base % mod);
        res.sz = l.sz + r.sz;
        res.h = (l.h * p[r.sz] % mod + r.h) % mod;
        return res;
    };
};
template<uint64_t mod, uint64_t base>
vector<uint64_t> RollingHashMonoid<mod, base>::p = vector<uint64_t>(1, 1);
const uint64_t base = 100;
const uint64_t mod  = (uint64_t)(1e9) + 9;
using rh = RollingHashMonoid<mod, base>;
uint64_t pow_t[200005];
LazySegmentTree<rh, char> hash_str(200005, rh::neutral(),
                                   [](rh l, rh r){
                                       return l + r;
                                   },
                                   [](rh l, char r, int len){
                                       rh res(r * pow_t[len] % mod);
                                       res.sz = len;
                                       return res;
                                   },
                                   [](char l, char r) {
                                       return r;
                                   } );
int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    {
        uint64_t b = 1;
        pow_t[0] = pow_t[1] = 1;
        for (int i = 2; i <= 200003; i++) {
            b = b * base % mod;
            pow_t[i] = (pow_t[i - 1] + b) % mod;
        }
    }
    llong n;
    llong q;
    string u;
    string com;
    cin >> n >> u >> q;
    for (int i = 0; i < n; i++) {
        hash_str.update(i, i + 1, u[i]);
    }
    while (q--) {
        llong a, b, c, d;
        llong x, y;
        char z;
        cin >> com;
        if (com == "set") {
            cin >> x >> y >> z;
            hash_str.update(x - 1, y, z);
        }
        else {
            cin >> a >> b >> c >> d;
            --a, --c;
            llong valid = 0;
            llong invalid = min(b - a, d - c) + 1;
            llong mid;
            while (invalid - valid > 1) {
                mid = (valid + invalid) / 2;
                if (hash_str.fold(a, a + mid).h ==
                    hash_str.fold(c, c + mid).h) {
                    valid = mid;
                }
                else {
                    invalid = mid;
                }
            }
            if (valid == min(b - a, d - c)) {
                if (b - a < d - c) {
                    cout << "s\n";
                }
                else if (b - a == d - c) {
                    cout << "e\n";
                }
                else {
                    cout << "t\n";
                }
            }
            else {
                if (hash_str[a + valid].h < hash_str[c + valid].h) {
                    cout << "s\n";
                }
                else {
                    cout << "t\n";
                }
            }
        }
    }
    return 0;
}
