
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
const int MAXW = 40010;
const int ofs = 20000;


template <typename MonoidType, typename OperatorType>
struct LazySegmentTree {
    using MMtoM = function< MonoidType(MonoidType, MonoidType) >;
    using OOtoO = function< OperatorType(OperatorType, OperatorType) >;
    using MOtoM = function< MonoidType(MonoidType, OperatorType) >;
    using OItoO = function< OperatorType(OperatorType, int) >;
    
    int n;
    vector<MonoidType> node;
    vector<OperatorType> lazy;
    vector<bool> need_update;
    MonoidType E0;
    OperatorType E1;
    
    MOtoM upd_f;
    MMtoM cmb_f;
    OOtoO lzy_f;
    OItoO acc_f;
    void build(int m, vector<MonoidType> v = vector<MonoidType>()) {
        if(v != vector<MonoidType>()) m = v.size();
        n = 1; while(n < m) n *= 2;
        node = vector<MonoidType>(2*n-1, E0);
        lazy = vector<OperatorType>(2*n-1, E1);
        need_update = vector<bool>(2*n-1, false);
        if(v != vector<MonoidType>()) {
            for(int i=0; i<m; i++) {
                node[n-1+i] = v[i];
            }
            for(int i=n-2; i>=0; i--) {
                node[i] = cmb_f(node[2*i+1], node[2*i+2]);
            }
        }
    }
    
    LazySegmentTree() {}
    LazySegmentTree(int n_, MonoidType E0_, OperatorType E1_,
                    MOtoM upd_f_, MMtoM cmb_f_, OOtoO lzy_f_, OItoO acc_f_,
                    vector<MonoidType> v = vector<MonoidType>()) :
        E0(E0_), E1(E1_),
        upd_f(upd_f_), cmb_f(cmb_f_), lzy_f(lzy_f_), acc_f(acc_f_) {
        build(n_, v);
    }
    void eval(int k, int l, int r) {
        if(!need_update[k]) return;
        node[k] = upd_f(node[k], acc_f(lazy[k], r - l));
        if(r - l > 1) {
            lazy[2*k+1] = lzy_f(lazy[2*k+1], lazy[k]);
            lazy[2*k+2] = lzy_f(lazy[2*k+2], lazy[k]);
            need_update[2*k+1] = need_update[2*k+2] = true;
        }
        lazy[k] = E1;
        need_update[k] = false;
    }
    void update(int a, int b, OperatorType x, int l, int r, int k) {
        eval(k, l, r);
        if(b <= l or  r <= a) return;
        if(a <= l and r <= b) {
            lazy[k] = lzy_f(lazy[k], x);
            need_update[k] = true;
            eval(k, l, r);
        }
        else {
            int mid = (l + r) / 2;
            update(a, b, x, l, mid, 2*k+1);
            update(a, b, x, mid, r, 2*k+2);
            node[k] = cmb_f(node[2*k+1], node[2*k+2]);
        }
    }
    MonoidType query(int a, int b, int l, int r, int k) {
        if(b <= l or  r <= a) return E0;
        eval(k, l, r);
        if(a <= l and r <= b) return node[k];
        int mid = (l + r) / 2;
        MonoidType vl = query(a, b, l, mid, 2*k+1);
        MonoidType vr = query(a, b, mid, r, 2*k+2);
        return cmb_f(vl, vr);
    }
    
    void update(int a, int b, OperatorType x) {
        update(a, b, x, 0, n, 0);
    }
    
    MonoidType query(int a, int b) {
        return query(a, b, 0, n, 0);
    }
    void dump() {
        fprintf(stderr, "[lazy]\n");
        for(int i=0; i<2*n-1; i++) {
            if(i == n-1) fprintf(stderr, "xxx ");
            if(lazy[i] == E1) fprintf(stderr, "  E ");
            else fprintf(stderr, "%3d ", lazy[i]);
        }
        fprintf(stderr, "\n");
        fprintf(stderr, "[node]\n");
        for(int i=0; i<2*n-1; i++) {
            if(i == n-1) fprintf(stderr, "xxx ");
            if(node[i] == E0) fprintf(stderr, "  E ");
            else fprintf(stderr, "%3d ", node[i]);
        }
        fprintf(stderr, "\n");
    }
};
int solve_testcase() {
    int N; scanf("%d", &N);
    if(N == 0) return 1;
    vector< vector< pair<int, int> > > add_y(MAXW), del_y(MAXW);
    vector<int> X(N), Y(N), pari(N);
    for(int i=0; i<N; i++) {
        scanf("%d%d", &X[i], &Y[i]);
        X[i] += ofs, Y[i] += ofs;
    }
    for(int i=0; i<N; i++) {
        int u = i, v = (i + 1) % N;
        if(Y[u] == Y[v]) continue;
        int mi = min(Y[u], Y[v]), ma = max(Y[u], Y[v]);
        add_y[mi].emplace_back(X[u], i);
        del_y[ma].emplace_back(X[u], i);
    }
    for(int i=0; i<MAXW; i++) {
        sort(add_y[i].begin(), add_y[i].end());
        sort(del_y[i].begin(), del_y[i].end());
    }
    int wx1 = INF, wx2 = -INF, wy1 = INF, wy2 = -INF;
    for(int i=0; i<4; i++) {
        int s, t; scanf("%d%d", &s, &t);
        s += ofs, t += ofs;
        chmin(wx1, s);
        chmax(wx2, s);
        chmin(wy1, t);
        chmax(wy2, t);
    }
    LazySegmentTree<int, int> seg1(MAXW, 0, 0,
                                   [](int a, int b) { return a + b; },
                                   [](int a, int b) { return a + b; },
                                   [](int a, int b) { return a + b; },
                                   [](int a, int x) { return a * x; });
    LazySegmentTree<int, int> seg2(MAXW, 0, 0,
                                   [](int a, int b) { return a + b; },
                                   [](int a, int b) { return a + b; },
                                   [](int a, int b) { return a + b; },
                                   [](int a, int x) { return a * x; });
    ll ans = 0;
    for(int i=0; i<MAXW; i++) {
        for(auto p : del_y[i]) {
            int x, k; tie(x, k) = p;
            seg1.update(x, x+1, -1);
            seg2.update(x, MAXW, (pari[k] ? +1 : -1));
        }
        for(auto p : add_y[i]) {
            int x, k; tie(x, k) = p;
            int m = seg1.query(0, x) % 2;
            pari[k] = m;
            
            seg1.update(x, x+1, +1);
            seg2.update(x, MAXW, (pari[k] ? -1 : +1));
        }
        ll add = 0;
        if(wy1 <= i and i < wy2) {
            add += seg2.query(0, wx1);
            add += seg2.query(wx2, MAXW);
        }
        else {
            add += seg2.query(0, MAXW);
        }
        
        ans += add;
    }
    printf("%lld\n", ans);
    return 0;
}
int main() {
    while(!solve_testcase());
    return 0;
}
