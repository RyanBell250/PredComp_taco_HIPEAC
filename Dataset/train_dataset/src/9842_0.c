#include<bits/stdc++.h>
using namespace std;

int main(){

    auto S = [](long a, long b, long h){
        a -= h;
        b -= h;
        if(a * b >= 0){
            return abs(a + b) / static_cast<long double>(2);
        }else{
            return (a * a + b * b) / static_cast<long double>(2 * (abs(a) + abs(b)));
        }
    };

    long n;
    cin >> n;

    vector<long> h(n);
    for(auto& i : h)cin >> i;

    constexpr int mx = 300;

    vector<vector<long double>> dp(n + 1, vector<long double>(mx, numeric_limits<long double>::max() / 100));

    dp[0][1] = 0;

    for(int i = 1; i <= n; ++i){
        for(int j = 1; j < mx; ++j){
            for(int k = 1; k < mx; ++k){
                dp[i][j] = min(dp[i][j], dp[i - 1][k] + S(j, k, h[i - 1]));
            }
        }
    }

    cout << setprecision(20) << *min_element(dp[n].begin(), dp[n].end()) << endl;

    return 0;
}
