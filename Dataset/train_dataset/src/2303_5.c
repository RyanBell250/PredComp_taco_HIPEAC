#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <cstdint>
#include <algorithm>
#include <iterator>
#define repeat_from(i,m,n) for (int i = (m); (i) < (n); ++(i))
#define repeat(i,n) repeat_from(i,0,n)
using namespace std;
enum we_t { W, E };
template <typename It>
void step(vector<string> const & s, map<pair<int,we_t>,vector<pair<int,we_t> > > const & g, It it) {
    int x = s.size();
    repeat (i,x) {
        repeat (n,s[i].size()+1) {
            string l = s[i].substr(0, n);
            string r = s[i].substr(n);
            for (we_t p : { W, E }) {
                if ((l.empty() and p == W) or (r.empty() and p == E)) continue;
                auto v = make_pair(i,p);
                for (auto w : g.at(v)) {
                    int  j = w.first;
                    we_t q = w.second;
                    vector<string> t = s;
                    t[i]     = p == W ? r : l;
                    string u = p == W ? l : r;
                    if (p == q) reverse(u.begin(), u.end());
                    t[j] = q == W ? u + s[j] : s[j] + u;
                    *(it ++) = t;
                }
            }
        }
    }
}
map<vector<string>,int> steps(vector<string> const & s, map<pair<int,we_t>,vector<pair<int,we_t> > > const & g, int n) {
    map<vector<string>,int> ms;
    ms[s] = 0;
    vector<vector<string> > vs;
    vs.push_back(s);
    repeat (i,n) {
        vector<vector<string> > ws;
        for (auto it : vs) {
            step(it, g, back_inserter(ws));
        }
        vs.clear();
        for (auto it : ws) {
            if (not ms.count(it)) {
                ms[it] = i+1;
                vs.push_back(it);
            }
        }
    }
    return ms;
}
int main() {
    while (true) {
        int x, y; cin >> x >> y;
        if (x == 0 and y == 0) break;
        map<pair<int,we_t>,vector<pair<int,we_t> > > g;
        repeat (i,x) for (we_t j : { W, E }) g[make_pair(i,j)];
        repeat (i,y) {
            char p, P, q, Q; cin >> p >> P >> q >> Q;
            auto a = make_pair(p - '0', P == 'W' ? W : E);
            auto b = make_pair(q - '0', Q == 'W' ? W : E);
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<string> s(x); repeat (i,x) { cin >> s[i]; if (s[i] == "-") s[i].clear(); }
        vector<string> t(x); repeat (i,x) { cin >> t[i]; if (t[i] == "-") t[i].clear(); }
        map<vector<string>,int> s2 = steps(s, g, 2);
        map<vector<string>,int> t2 = steps(t, g, 2);
        int result = 6;
        for (auto it : s2) {
            if (t2.count(it.first)) {
                result = min(result, it.second + t2[it.first]);
            }
            if (it.second == 2) {
                vector<vector<string> > s3;
                step(it.first, g, back_inserter(s3));
                for (auto that : s3) {
                    if (t2.count(that)) {
                        result = min(result, 1 + it.second + t2[that]);
                    }
                }
            }
        }
        cout << result << endl;
    }
    return 0;
}