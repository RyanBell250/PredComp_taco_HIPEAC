#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

long long N, X[1 << 18], Y[1 << 18]; vector<long long>P, Q, V1, V2;

long long dist(long long px, long long py, long long qx, long long qy) {
	if (px == qx && px % 20 == 0) return abs(py - qy);
	if (py == qy && py % 20 == 0) return abs(px - qx);

	long long ans = 0;

	if (px % 20 == 0 && qx % 20 == 0) {
		if ((py / 20) == (qy / 20)) {
			long long V1 = abs(px - qx);
			long long A1 = py - ((py / 20) * 20), A2 = qy - ((qy / 20) * 20);
			V1 += min(A1 + A2, 40LL - (A1 + A2));
			ans = V1;
		}
		else ans = abs(px - qx) + abs(py - qy);
	}
	else if (py % 20 == 0 && qy % 20 == 0) {
		if ((px / 20) == (qx / 20)) {
			long long V1 = abs(py - qy);
			long long A1 = px - ((px / 20) * 20), A2 = qx - ((qx / 20) * 20);
			V1 += min(A1 + A2, 40LL - (A1 + A2));
			ans = V1;
		}
		else ans = abs(px - qx) + abs(py - qy);
	}
	else {
		ans = abs(px - qx) + abs(py - qy);
	}
	return ans;
}

long long solve(long long px, long long py) {
	long long sum = 0;
	for (int i = 0; i < N; i++) {
		sum = max(sum, dist(px, py, X[i], Y[i]));
	}
	return sum;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> X[i] >> Y[i]; X[i] *= 2; Y[i] *= 2;
		X[i] += 200000000; Y[i] += 200000000;
		P.push_back(X[i] + Y[i]);
		Q.push_back(X[i] - Y[i]);
	}
	sort(P.begin(), P.end());
	sort(Q.begin(), Q.end());
	long long CX = (P[0] + P[N - 1]) / 2;
	long long CY = (Q[0] + Q[N - 1]) / 2;
	long long DX = (CX + CY) / 2;
	long long DY = CX - DX;

	for (int i = -100; i <= 100; i++) V1.push_back(DX + i);
	for (int i = -100; i <= 100; i++) V2.push_back(DY + i);

	long long minx = (1LL << 60);
	for (int i = 0; i < V1.size(); i++) {
		for (int j = 0; j < V2.size(); j++) {
			if (!(V1[i] % 20 == 0 || V2[j] % 20 == 0)) continue;
			minx = min(minx, solve(V1[i], V2[j]));
		}
	}
	printf("%.12Lf\n", 0.5L * minx);
	return 0;
}
