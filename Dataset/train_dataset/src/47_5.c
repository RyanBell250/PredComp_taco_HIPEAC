#include<iostream>

using namespace std;

typedef long long llint;

const int MAXN = 2005;
const int MOD = 1000000007;

llint a, b, sol;
llint nck[MAXN] [MAXN];
llint sum[MAXN] [MAXN];
llint dp[MAXN] [MAXN];

llint add (llint x, llint y) {
    if (x+y>=MOD) return x+y-MOD; return x+y;
}

llint mul (llint x, llint y) {
    return x*y%MOD;
}

void precompute () {
    for (int i=0; i<MAXN; i++) {
        nck[i] [0]=nck[i] [i]=1;
        sum[i] [0]=1;
    }
    for (int i=1; i<MAXN; i++) {
        for (int j=1; j<=i; j++) {
            nck[i] [j]=add(nck[i-1] [j-1], nck[i-1] [j]);
            sum[i] [j]=add(sum[i] [j-1], nck[i] [j]);
        }
    }
}

int main () {
    cin >> a >> b;
    precompute();
    for (int i=0; i<MAXN; i++) {
        dp[i] [0]=1;
        for (int j=1; j<MAXN; j++) {
            if (i==0) {
                dp[i] [j]=1;
            } else {
                dp[i] [j]=add(dp[i-1] [j], sum[j-1] [min(i, j-1)]);
            }
        }
    }
    for (int i=0; i<=a; i++) {
        int lim=min(a-i, b-1);
        for (int j=0; j<=lim; j++) {
            sol=add(sol, mul(nck[b-1] [j], dp[a-i-j] [j]));
        }
    }
    cout << sol;
    return 0;
}
