#include<cassert>
#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;
typedef long long LL;
typedef vector<int> VI;
#define REP(i,n) for(int i=0, i##_len=(n); i<i##_len; ++i)
#define EACH(i,c) for(__typeof((c).begin()) i=(c).begin(),i##_end=(c).end();i!=i##_end;++i)
#define eprintf(s...)  fprintf(stderr, s)
template<class T> inline void amin(T &x, const T &y) { if (y<x) x=y; }
template<class T> inline void amax(T &x, const T &y) { if (x<y) x=y; }
vector<LL> num[127];
void rec(int cur = 0, int I = 0, int sum = 0, LL prod = 1) {
    if (cur == 14) {
	num[sum].push_back(prod);
    } else {
	for (int i=I; i<=9; i++) rec(cur+1, i, sum + i, prod * (i+1));
    }
}
char S[33];
LL dp[15][127][3786][3];
int main() {
    rec();
    int sz = 0;
    REP (i, 127) {
	vector<LL> &a = num[i];
	sort(a.begin(), a.end());
	a.erase(unique(a.begin(), a.end()), a.end());
    }
    scanf("%s", S);
    int n = strlen(S);
    dp[0][0][0][0] = 1;
    REP (i, n) REP (sum, 9*(i+1)+1) REP (prod, num[sum].size()) REP (b, 3) if (dp[i][sum][prod][b]) {
	REP (c, 10) {
	    int nsum = sum + c;
	    int nprod = lower_bound(num[nsum].begin(), num[nsum].end(), num[sum][prod] * (c+1)) - num[nsum].begin();
	    assert(num[nsum][nprod] == num[sum][prod] * (c+1));
	    int nb = b;
	    if (b == 0 && c < S[i] - '0') nb = 1;
	    if (b == 0 && c > S[i] - '0') nb = 2;
	    dp[i+1][nsum][nprod][nb] += dp[i][sum][prod][b];
	}
    }
    LL ans = 0;
    int sum = 0;
    LL P = 1;
    REP (i, n) {
	int c = S[i] - '0';
	sum += c;
	P *= c + 1;
    }
    REP (s, 127) REP (p, num[s].size()) REP (b, 3) {
	if (s < sum ||
		(s == sum && num[s][p] < P) ||
		(s == sum && num[s][p] == P && b == 1))
	    ans += dp[n][s][p][b];
    }
    printf("%lld\n", ans);
    return 0;
}