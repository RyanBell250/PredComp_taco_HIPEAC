#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

long long N, M, S, T, U, V, A[1 << 18], B[1 << 18], C[1 << 18], dist[1 << 18], dp1[1 << 18], dp2[1 << 18];
long long dista[1 << 18], distb[1 << 18], distc[1 << 18], distd[1 << 18];
vector<pair<long long, long long>>X[1 << 18];
int Order[1 << 18];

vector<long long>getdist(int pos) {
	priority_queue<pair<long long, long long>, vector<pair<long long, long long>>, greater<pair<long long, long long>>>Q;
	for (int i = 1; i <= N; i++) dist[i] = (1LL << 60);
	Q.push(make_pair(0, pos)); dist[pos] = 0;

	while (!Q.empty()) {
		int pos = Q.top().second; long long cost = Q.top().first; Q.pop();
		for (int i = 0; i < X[pos].size(); i++) {
			int to = X[pos][i].first; long long tm = X[pos][i].second;
			if (dist[to] > cost + tm) {
				dist[to] = cost + tm;
				Q.push(make_pair(dist[to], to));
			}
		}
	}
	vector<long long>E;
	for (int i = 1; i <= N; i++) E.push_back(dist[i]);
	return E;
}

int main() {
	cin >> N >> M >> S >> T >> U >> V;
	for (int i = 0; i < M; i++) {
		cin >> A[i] >> B[i] >> C[i];
		X[A[i]].push_back(make_pair(B[i], C[i]));
		X[B[i]].push_back(make_pair(A[i], C[i]));
	}
	vector<long long>A1 = getdist(S); for (int i = 1; i <= N; i++) dista[i] = A1[i - 1];
	vector<long long>A2 = getdist(T); for (int i = 1; i <= N; i++) distb[i] = A2[i - 1];
	vector<long long>A3 = getdist(U); for (int i = 1; i <= N; i++) distc[i] = A3[i - 1];
	vector<long long>A4 = getdist(V); for (int i = 1; i <= N; i++) distd[i] = A4[i - 1];

	vector<pair<long long, long long>>vec1;
	for (int i = 1; i <= N; i++) { if (dista[i] + distb[i] == dista[T]) vec1.push_back(make_pair(dista[i], i)); }
	sort(vec1.begin(), vec1.end());

	for (int i = 1; i <= N; i++) { dp1[i] = (1LL << 60); dp2[i] = (1LL << 60); Order[i] = -1; }
	for (int i = 0; i < vec1.size(); i++) Order[vec1[i].second] = i;

	for (int i = 0; i < vec1.size(); i++) {
		int pos = vec1[i].second; dp1[pos] = min(dp1[pos], distc[pos]);
		for (int j = 0; j < X[pos].size(); j++) {
			if (Order[X[pos][j].first] != -1 && Order[X[pos][j].first] > i) {
				dp1[X[pos][j].first] = min(dp1[X[pos][j].first], dp1[pos]);
			}
		}
	}
	for (int i = vec1.size() - 1; i >= 0; i--) {
		int pos = vec1[i].second; dp2[pos] = min(dp2[pos], distc[pos]);
		for (int j = 0; j < X[pos].size(); j++) {
			if (Order[X[pos][j].first] != -1 && Order[X[pos][j].first] < i) {
				dp2[X[pos][j].first] = min(dp2[X[pos][j].first], dp2[pos]);
			}
		}
	}

	long long ans = distc[V];
	for (int i = 1; i <= N; i++) ans = min(ans, min(dp1[i], dp2[i]) + distd[i]);
	cout << ans << endl;
	return 0;
}
