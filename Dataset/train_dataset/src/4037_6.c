#include <bits/stdc++.h>
using namespace std;

int bfs(const string &start) {
	const string goal = "1112131415161700212223242526270031323334353637004142434445464700";

	unordered_map<string, int> dist;
	queue<string> que;
	dist[start] = 0;
	que.emplace(start);

	while(!que.empty()) {
		const string current = que.front();
		que.pop();

		if(current == goal) return dist[current];
		const int next_dist = dist[current] + 1;

		for(int i = 2; i < 64; i += 2) {
			if(current[i] == '0') {
				string tmp = current.substr(i - 2, 2);
				++tmp[1];

				int pos = -1;
				for(int j = 2; j < 64; j += 2) {
					if(current[j] == tmp[0] && current[j + 1] == tmp[1]) {
						pos = j;
						break;
					}
				}

				if(pos == -1) continue;

				string next(current);
				next[i] = tmp[0];
				next[i + 1] = tmp[1];
				next[pos] = '0';
				next[pos + 1] = '0';

				if(!dist.count(next)) {
					dist[next] = next_dist;
					que.emplace(next);
				}
			}
		}
	}
	return -1;
}

void solve() {
	string start = "";
	for(int i = 0; i < 4; ++i) {
		string tmp = string(1, '1' + i) + "1";
		for(int j = 0; j < 7; ++j) {
			int card;
			cin >> card;
			if(card % 10 == 1) {
				tmp += "00";
			}
			else {
				tmp += to_string(card);
			}
		}
		start += tmp;
	}

	cout << bfs(start) << endl;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	int t;
	cin >> t;
	while(t--) solve();
}