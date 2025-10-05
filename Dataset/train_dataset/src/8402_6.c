#include <bits/stdc++.h>
using namespace std;

vector<long> ans;

void dfs(long n, int d) {
  ans.push_back(n);
  if (d == 10) return;
  int end = n % 10;
  int mi = max(0, end - 1);
  int mx = min(9, end + 1);
  for (int i = mi; i <= mx; i++) dfs(n * 10 + i, d + 1);
}

int main() {
  int K;
  cin >> K;
  for (int i = 1; i <= 9; i++) dfs(i, 1);
  sort(ans.begin(), ans.end());
  cout << ans.at(K - 1) << "\n";
}