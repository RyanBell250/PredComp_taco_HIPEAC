#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n >> s;
    map<pair<int, int>, int> cnt;
    for (int i = 0; i < n - 1; i++) {
        int a = s[i] - '0', b = s[i + 1] - '0';
        cnt[{a, b}]++;
    }

    int nin = 1e9;
    vector<int> best;
    vector<int> pm(9);
    iota(pm.begin(), pm.end(), 1);

    do {
        int tmp = 0;
        pair<int, int> pos[10];
        for (int i = 1; i < 10; i++) {
            pos[pm[i - 1]] = {(i - 1) / 3, (i - 1) % 3};
        }
        for (auto& p : cnt) {
            int dist = abs(pos[p.first.first].first - pos[p.first.second].first) + abs(pos[p.first.first].second - pos[p.first.second].second);
            tmp += dist * p.second;
        }
        if (tmp < nin) {
            nin = tmp;
            best = pm;
        }
    } while (next_permutation(pm.begin(), pm.end()));

    for (int i = 0; i < 9; i++) {
        cout << best[i];
        if (i % 3 == 2) cout << '\n';
    }
}
