#include<bits/stdc++.h>
using namespace std;
using P = pair<int, int>;
int main() {
    int n, m;
    cin >> n;
    vector<vector<int>> c(100010);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        c[a].push_back(i);
    }
    cin >> m;
    vector<vector<int>> edge(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a;
        --b;
        edge[a].push_back(b);
        edge[b].push_back(a);
    }
    vector<int> num(n);
    vector<int> adjmax(n);
    for (int i = 0; i < 100010; ++i) {
        if (!c[i].size()) continue;
        bool f = true;
        while (f) {
            for (int a : c[i]) {
                adjmax[a] = max(adjmax[a], num[a] - 1);
                for (int b : edge[a]) {
                    adjmax[a] = max(adjmax[a], num[b] - 1);
                    adjmax[b] = max(adjmax[b], num[a] - 1);
                }
            }
            f = false;
            for (int a : c[i]) {
                for (int b : edge[a]) {
                    if (num[a] < adjmax[b] + 1) {
                        f = true;
                        num[a] = adjmax[b] + 1;
                    }
                }
            }
        }
        for (int a : c[i]) {
            adjmax[a] = max(adjmax[a], num[a]);
            for (int b : edge[a]) {
                adjmax[a] = max(adjmax[a], num[b]);
                adjmax[b] = max(adjmax[b], num[a]);
            }
        }
    }
    long long ans = 0;
    for (int i : num) ans += max(i, 1);
    cout << ans << "\n";
    return 0;
}
