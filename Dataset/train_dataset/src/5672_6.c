#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 7;

int dp[N], p1[N], p2[N];

int main() {
	ios_base :: sync_with_stdio(0); cin.tie(0); cout.tie(0);
	dp[0] = 0;
	for(int i = 1; i < N; i++) {
		int k = __builtin_popcount(i);
		dp[i] = 1 + dp[i % k];
	}
	int n, cnt = 0; string str; cin >> n >> str;
	for(auto ch: str) {
		cnt += ch == '1';
	}

	int x = cnt + 1, y = cnt - 1, s1 = 0, s2 = 0;

	p1[0] = p2[0] = 1;

	for(int i = 1; i <= n; i++) {
		p1[i] = (p1[i - 1] * 2) % x;
		if(y > 0) {
			p2[i] = (p2[i - 1] * 2) % y;
		}
	}

	for(auto ch: str) {
		s1 = (s1 * 2 + (ch == '1')) % x;
		if(y > 0) {
			s2 = (s2 * 2 + (ch == '1')) % y;
		}
	}
	int len = 0;
	for(auto ch: str) { ++len;
		if(ch == '1') {
			if(cnt - 1 == 0) {
				cout << 0 << endl;
			} else {
				int s22 = (s2 - p2[n - len] + y) % y;
				cout << 1 + dp[s22] << endl;
			}
		} else {
			int s11 = (s1 + p1[n - len]) % x;
			cout << 1 + dp[s11] << endl;
		}
	}

}