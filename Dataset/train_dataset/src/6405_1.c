#include <bits/stdc++.h>
#define int long long
using namespace std;
struct se {
    mutable int first, second;
    se(int first, int second) : first(first), second(second) {}
    bool operator<(const se &o) const {
        if (first != o.first) return first < o.first;
        return second < o.second;
    }
};
int n, q, s, d;
int a[200000];
vector<pair<int, int>> queries[1000001];
bool res[200000];
set<se> seg;
int curk;
map<int, int> rem;
void addPoint(int i);
void addSeg(int p) {
    auto it = rem.begin();
    while ((it = rem.lower_bound(p)) != rem.end() && it->first <= p+2*curk) {
        addPoint(it->second);
    }
    seg.insert(se(p, p+2*curk));
}
void addPoint(int i) {
    rem.erase(a[i]);
    addSeg(a[i]-d-curk);
    addSeg(a[i]+d-curk);
}
void fixSegments() {
    for (auto it = seg.begin(); it != seg.end(); ++it) {
        auto it2 = it; ++it2;
        if (it2 == seg.end()) break;
        if (it->second >= it2->first-1) {
            it->second = max(it->second, it2->second);
            seg.erase(it2);
        }
    }
}
void widenSegments() {
    set<int> added;
    for (auto it = seg.begin(); it != seg.end(); ++it) {
        it->first--;
        it->second++;
        if (rem.count(it->first)) added.insert(rem[it->first]);
        if (rem.count(it->second)) added.insert(rem[it->second]);
    }
    for (int a : added) addPoint(a);
}
int32_t main() {
    cin >> n >> q >> s >> d; s--;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
        rem[a[i]] = i;
    }
    for (int i = 0; i < q; ++i) {
        int t, k; cin >> t >> k; t--;
        queries[k].push_back({t, i});
    }
    addPoint(s);
    fixSegments();
    while (curk < 1000000) {
        curk++;
        widenSegments();
        fixSegments();
        for (auto x : queries[curk]) res[x.second] = rem.count(a[x.first]) == 0;
    }
    for (int i = 0; i < q; ++i) {
        if (res[i]) cout << "yes\n";
        else cout << "no\n";
    }
}
