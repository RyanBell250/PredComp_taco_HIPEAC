#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main() {
    int m;
    vector<int> res(1000001, 0);
    for(int i=1; i<1000001; ++i) {
        int t = i;
        while(t % 2 == 0) {
            t /= 2;
        }
        while(t % 3 == 0) {
            t /= 3;
        }
        while(t % 5 == 0) {
            t /= 5;
        }
        res[i] = t == 1;
    }
    for(int i=1; i<1000001; ++i) {
        res[i] += res[i-1];
    }
    while(cin >> m, m) {
        int n;
        cin >> n;
        cout << res[n] - res[m-1] << endl;
    }
}
