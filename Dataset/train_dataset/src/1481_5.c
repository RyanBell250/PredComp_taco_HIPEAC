#include <iostream>

using namespace std;
unsigned long long int dp[11][1001];

void solve()
{
	dp[0][0] = 1;
	for(int i = 0; i < 101; ++i)
	{
		for(int j = 9; j >= 0; --j)
		{
			for(int k = 0; k + i < 1001; ++k)
			{
				 dp[j + 1][k + i] += dp[j][k];
			}
		}
	}

	int n, s;
	while(cin >> n >> s, n || s)
	{
		cout << dp[n][s] << endl;
	}
}

int main()
{
	solve();
	return(0);
}