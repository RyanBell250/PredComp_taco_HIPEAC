#include <bits/stdc++.h>
using namespace std;
const int R = 1010;

int main() {
    int n;
    cin >> n;
    vector<vector<int>> s(R, vector<int>(R, 0));
    while (n--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        s[a][b]++;
        s[a][d]--;
        s[c][b]--;
        s[c][d]++;
    }
    
    for (int i = 0; i < R; i++) {
        for (int j = 0; j+1 < R; j++) {
            s[i][j+1] += s[i][j];
        }
    }
    for (int i = 0; i+1 < R; i++) {
        for (int j = 0; j < R; j++) {
            s[i+1][j] += s[i][j];
        }
    }
    
    int ans = 0;
    for (int i = 0; i < R; i++) {
        ans = max(ans, *max_element(s[i].begin(), s[i].end()));
    }

    cout << ans << endl;
    return 0;
}
