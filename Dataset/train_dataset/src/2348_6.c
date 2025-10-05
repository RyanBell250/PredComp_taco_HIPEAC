#include<bits/stdc++.h>
using namespace std;
string S; int x, y, cnt, flag; bool dp[8009][32009]; vector<int> v1, v2, v3;
bool solve(vector<int>vec,int g ) {
	for (int i = 0; i <= vec.size(); i++) {
		for (int j = 0; j <= 32000; j++) { dp[i][j] = false; }
	}
	dp[0][16000] = true;
	for (int i = 0; i < vec.size(); i++) {
		for (int j = 0; j <= 32000; j++) {
			if (dp[i][j] == false) continue;
			dp[i + 1][j + vec[i]] = true;
			dp[i + 1][j - vec[i]] = true;
		}
	}
	return dp[vec.size()][16000 + g];
}
int main() {
	cin >> S >> x >> y;
	for (int i = 0; i <= S.size(); i++) {
		if (i != S.size() && S[i] == 'F') cnt++;
		else {
			if (flag == 0) v1.push_back(cnt);
			if (flag == 1) v2.push_back(cnt);
			cnt = 0; flag ^= 1;
		}
	}
	x -= v1[0];
	for (int i = 1; i < (int)v1.size(); i++) { v3.push_back(v1[i]); }
	if (solve(v3, x) == true && solve(v2, y) == true) {
		cout << "Yes" << endl;
	}
	else {
		cout << "No" << endl;
	}
}
