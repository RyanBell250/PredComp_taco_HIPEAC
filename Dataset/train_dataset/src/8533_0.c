#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>
using namespace std;
#define int long long
#define inf 3000000000000
typedef pair<int, int>P;
int dp[160][10][80];
vector<P>s[160];//P(??????,???????????????)

void init(int m) {
	for (int i = 0; i < 160; i++) {
		s[i].clear();
		for (int j = 0; j < 10; j++) {
			for (int k = 0; k < 80; k++) {
				if (!i&&k==m)dp[i][j][k]=0;
				else if (i == 1 && k == m - 1)dp[i][j][k] = 0;
				else dp[i][j][k] = inf;
			}
		}
	}
	return;
}

signed main() {
	int n, m;
	while (cin >> n >> m) {
		if (!n && !m)break;
		init(m);
		for (int i = 0; i < n; i++) {
			int a;
			cin >> a;
			for (int j = 0; j < a; j++) {
				int b, c;
				cin >> b >> c;
				s[i].push_back(P(b, c));
			}
		}

		for (int i = 1; i < n; i++) {//?¬?????????????
			for (int j = 0; j < s[i].size(); j++) {//??????????????????
				for (int k = m; k >= 0; k--) {//???????????§?????£??????
					for (int l = 0; l < s[i - 1].size(); l++) {
						int dang = (s[i-1][l].second+s[i][j].second)*abs(s[i][j].first-s[i-1][l].first);
						dp[i][j][k] = min(dp[i][j][k], dp[i - 1][l][k] + dang);
					}
					if (i > 1) {
						for (int l = 0; l < s[i - 2].size(); l++) {
							int dang = (s[i - 2][l].second + s[i][j].second)*abs(s[i][j].first - s[i - 2][l].first);
							dp[i][j][k] = min(dp[i][j][k], dp[i - 2][l][k + 1] + dang);
						}
					}
				}

			}
		}
		int ans = inf;
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 80; j++) {
				ans = min(ans, dp[n - 1][i][j]);
			}
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 1; j < 80; j++) {
				ans = min(ans, dp[n - 2][i][j]);
			}
		}
		cout << ans << endl;
	}
}