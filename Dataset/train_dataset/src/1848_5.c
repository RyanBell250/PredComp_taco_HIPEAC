#include<iostream>
#include<vector>
#include<tuple>
using namespace std;
#define YEAR 10000
#define MAX_IDS 100
#define MAX_DIGIT 14
#define MAX_ID 7
#define HOUR 24
#define MINUTE 60
#define SECOND 60
#define MONTH 12
#define MAX_NUM 10
#define DAY_ID 2
#define MONTH_ID 2
#define YEAR_ID 4
#define ELSE_ID 2
#define TYPES 4
int day1[MONTH + 1] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
int day2[MONTH + 1] = { 0,31,29,31,30,31,30,31,31,30,31,30,31 };
vector<tuple<int, int, int>>days;
bool Uruu(int a) {
	if (a % 400 == 0) { return true; }
	if (a % 100 == 0) { return false; }
	if (a % 4 == 0) { return true; }
	return false;
}
void calc() {
	for (int i = 0; i < YEAR; i++) {
		if (Uruu(i) == true) {
			for (int j = 1; j <= MONTH; j++) {
				for (int k = 1; k <= day2[j]; k++) {
					days.push_back(make_tuple(i, j, k));
				}
			}
		}
		else {
			for (int j = 1; j <= MONTH; j++) {
				for (int k = 1; k <= day1[j]; k++) {
					days.push_back(make_tuple(i, j, k));
				}
			}
		}
	}
}
int y[MAX_NUM][MAX_ID] =
{
	{1,1,1,0,1,1,1},
	{0,0,1,0,0,1,0},
	{1,0,1,1,1,0,1},
	{1,0,1,1,0,1,1},
	{0,1,1,1,0,1,0},
	{1,1,0,1,0,1,1},
	{1,1,0,1,1,1,1},
	{1,0,1,0,0,1,0},
	{1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1}
};
int z[MAX_DIGIT][MAX_NUM][MAX_ID];
int power[5] = { 1,10,100,1000,10000 };
int calc2(int a, int b, int c) {
	int p[DAY_ID+MONTH_ID+YEAR_ID];
	for (int i = 0; i < YEAR_ID; i++) {
		p[YEAR_ID - 1 - i] = (a / power[i]) % MAX_NUM;
	}
	for (int i = 0; i < MONTH_ID; i++) {
		p[YEAR_ID + MONTH_ID - 1 - i] = (b / power[i]) % MAX_NUM;
	}
	for (int i = 0; i < DAY_ID; i++) {
		p[YEAR_ID + MONTH_ID + DAY_ID - 1 - i] = (c / power[i]) % MAX_NUM;
	}
	int sum = 0;
	for (int i = 0; i < DAY_ID + MONTH_ID + YEAR_ID; i++) {
		for (int j = 0; j < MAX_ID; j++) {
			sum += z[i][p[i]][j];
		}
	}
	return sum;
}
int calc3(int a, int b) {
	int r[ELSE_ID];
	r[0] = a / 10; r[1] = a % 10;
	int sum = 0;
	for (int i = 0; i < ELSE_ID; i++) {
		for (int j = 0; j < MAX_ID; j++) {
			sum += z[i + b][r[i]][j];
		}
	}
	return sum;
}
int n, q, a, b;
int x[MAX_DIGIT][MAX_ID];
long long dp[MAX_IDS][TYPES];
long long h[MAX_IDS], m[MAX_IDS], s[MAX_IDS];
int main() {
	calc();
	cin >> n >> q;
	for (int i = 0; i < q; i++) {
		cin >> a >> b;
		x[a][b] = 1;
	}
	for (int i = 0; i < MAX_DIGIT; i++) {
		for (int j = 0; j < MAX_ID; j++) {
			if (x[i][j] == 1) {
				for (int k = 0; k < MAX_NUM; k++) {
					z[i][k][j] = 0;
				}
			}
			else {
				for (int k = 0; k < MAX_NUM; k++) {
					z[i][k][j] = y[k][j];
				}
			}
		}
	}
	for (int i = 0; i < days.size(); i++) {
		int a1 = get<0>(days[i]);
		int a2 = get<1>(days[i]);
		int a3 = get<2>(days[i]);
		dp[calc2(a1, a2, a3)][0]++;
	}
	for (int i = 0; i < HOUR; i++) {
		h[calc3(i, 8)]++;
	}
	for (int i = 0; i < MINUTE; i++) {
		m[calc3(i, 10)]++;
	}
	for (int i = 0; i < SECOND; i++) {
		s[calc3(i, 12)]++;
	}
	for (int i = 0; i < MAX_IDS; i++) {
		if (dp[i][0] >= 1) {
			for (int j = 0; j <= MAX_ID*ELSE_ID; j++) {
				dp[i + j][1] += dp[i][0] * h[j];
			}
		}
	}
	for (int i = 0; i < MAX_IDS; i++) {
		if (dp[i][1] >= 1) {
			for (int j = 0; j <= MAX_ID*ELSE_ID; j++) {
				dp[i + j][2] += dp[i][1] * m[j];
			}
		}
	}
	for (int i = 0; i < MAX_IDS; i++) {
		if (dp[i][2] >= 1) {
			for (int j = 0; j <= MAX_ID*ELSE_ID; j++) {
				dp[i + j][3] += dp[i][2] * s[j];
			}
		}
	}
	cout << dp[n][3] << endl;
	return 0;
}
