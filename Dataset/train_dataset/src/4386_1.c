#include <bits/stdc++.h>
using namespace std;
vector<int> s;
int min_turn(int x) {
    int level = 1;
    int strongest = s[s.size()-1];
    int count = 1;
    while (level + x <= strongest) {
        int flag = true;
        int pos = lower_bound(s.begin(), s.end(), level) - s.begin();
        int diff = 1;
        if (pos != 0 && level + x > s[pos - 1]) {
            diff = max(diff, x-abs(level-s[pos - 1]));
            flag = false;
        }
        if (level + x > s[pos]) {
            diff = max(diff, x-abs(level-s[pos]));
            flag = false;
        }
        if (flag) {
            return 1e9;
        }
        level += diff;
        count++;
    }
    return count;
}
int main() {
    int N, M;
    while(cin >> N >> M, N+M) {
        s = vector<int>(N);
        int high = -1e9, low = 1;
        for (int i = 0; i < N; i++) {
            cin >> s[i];
            high = max(high, s[i]);
        }
        int turn = -1;
        while (low + 1 < high) {
            int mid = (high + low) / 2;
            turn = min_turn(mid);
            if (turn < M) {
                high = mid;
            } else {
                low = mid;
            }
        }
        turn = min_turn(low);
        if (turn < M || turn > 1e7) {
            cout << -1 << endl;
        } else {
            cout << low << endl;
        }
    }
}
