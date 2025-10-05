#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
const int INF = 1000000000;

int main(){
	ios_base::sync_with_stdio(false);
	while(true){
		int n;
		cin >> n;
		if(n == 0){ break; }
		vector<int> a(n), b(n), c(n);
		for(int i = 0; i < n; ++i){ cin >> a[i] >> b[i] >> c[i]; }
		vector< vector<int> > possible(n);
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < 60; ++j){
				int t[3] = {
					(a[i] + j) % 60, (b[i] + j) % 60, (c[i] + j) % 60
				};
				sort(t, t + 3);
				do {
					const int h = t[0] / 5;
					const int m = t[1];
					const int s = t[2];
					if(t[0] % 5 == m / 12){
						possible[i].push_back(h * 60 * 60 + m * 60 + s);
					}
				} while(next_permutation(t, t + 3));
			}
			possible[i].push_back(INF);
			sort(possible[i].begin(), possible[i].end());
		}
		int answer_begin = 0, answer_end = 12 * 60 * 60;
		for(int i = 12 * 60 * 60 - 1; i >= 0; --i){
			int last = 0;
			for(int j = 0; j < n; ++j){
				last = max(last, *lower_bound(
					possible[j].begin(), possible[j].end(), i));
			}
			if(last - i <= answer_end - answer_begin){
				answer_begin = i;
				answer_end = last;
			}
		}
		cout << setfill('0') << setw(2) << answer_begin / 60 / 60 << ":";
		cout << setfill('0') << setw(2) << answer_begin / 60 % 60 << ":";
		cout << setfill('0') << setw(2) << answer_begin % 60 << " ";
		cout << setfill('0') << setw(2) << answer_end / 60 / 60 << ":";
		cout << setfill('0') << setw(2) << answer_end / 60 % 60 << ":";
		cout << setfill('0') << setw(2) << answer_end % 60 << endl;
	}
	return 0;
}