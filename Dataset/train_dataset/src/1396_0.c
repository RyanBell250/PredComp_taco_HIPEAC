#include <bits/stdc++.h>

#define FOR(x, a, b) for (int x = a; x <= b; ++x)
#define FOD(x, a, b) for (int x = a; x >= b; --x)
#define REP(x, a, b) for (int x = a; x < b; ++x)
#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A, n) { cout << #A << " = "; FOR(_, 1, n) cout << A[_] << " "; cout << endl; }
#define PR0(A, n)  { cout << #A << " = "; REP(_, 0, n) cout << A[_] << " "; cout << endl; }

using namespace std;

typedef long long LL;
typedef pair <int, int> II;

const int N = 2e5 + 10;

int n, m, q, LSize;
int L[N], ans[N], ban[N];

vector <int> c[N];

struct Ant {
    int x, y, d;
    Ant () {}
    Ant (int x, int y, int d) : x(x), y(y), d(d) {};
} A[N];

void Compress() {
    FOR(i, 1, q) L[i] = A[i].x + A[i].y;
    LSize = q;
    sort(L + 1, L + LSize + 1);
    LSize = unique(L + 1, L + LSize + 1) - (L + 1);
}

int Pos(int v) {
    return lower_bound(L + 1, L + LSize + 1, v) - L;
}

bool CMP(int x, int y) {
    return A[x].y < A[y].y;
}

struct State {
    int x, y, z;
    State () {}
    State (int x, int y, int z) : x(x), y(y), z(z) {}
    bool operator < (const State &that) const {
        if (x != that.x) return x < that.x;
        if (y != that.y) return y < that.y;
        return z < that.z;
    }
};

void Compute(const vector <int> &g) {
    vector <State> L;
    REP(p, 0, g.size()) {
        int i = g[p], x = A[i].x, y = A[i].y, d = A[i].d;
        if (d == 0) L.push_back(State(d, A[i].y, n - A[i].x));
            else L.push_back(State(d, n - A[i].x, m - A[i].y));
    }
    sort(L.begin(), L.end());
   // PR0(g, g.size());
    //REP(i, 0, g.size()) cout << L[i].z << endl;
    REP(i, 0, g.size()) ans[g[i]] = L[i].z;
}

void Solve(int idx) {
    sort(c[idx].begin(), c[idx].end(), CMP);
    if (L[idx] % 2 == 0) {
        FOR(f, 0, 1) {
            vector <int> g;
            REP(k, 0, c[idx].size()) {
                int i = c[idx][k];
                if (A[i].x % 2 != f) continue;
                g.push_back(i);
            }
            Compute(g);
        }
    } else {
        FOR(r, 0, 1) {
            vector <int> g;
            REP(k, 0, c[idx].size()) {
                int i = c[idx][k];
                if (A[i].d == 0) {
                    if (A[i].y % 2 == r) g.push_back(i);
                } else {
                    if (A[i].x % 2 == r) g.push_back(i);
                }
            }
            Compute(g);
        }
    }
}

int main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif // LOCAL
    scanf("%d%d%d", &n, &m, &q);
    FOR(i, 1, q) {
        char d[2]; int x, y; scanf("%d%d%s", &x, &y, d);
        A[i] = Ant(x, y, d[0] == 'E' ? 0 : 1);
    }
    /*FOR(i, 1, q)
        FOR(j, i + 1, q) assert((A[i].x == A[j].x && A[i].y == A[j].y) == false);*/
    Compress();
    FOR(i, 1, q) {
        int x = A[i].x, y = A[i].y, d = A[i].d;
        c[Pos(x + y)].push_back(i);
    }
    FOR(i, 1, LSize) Solve(i);
    vector <II> answ;
    FOR(i, 1, q) answ.push_back(II(ans[i], i));
    sort(answ.begin(), answ.end());
    FOR(i, 1, q) printf("%d\n", answ[i - 1].second);
    return 0;
}

