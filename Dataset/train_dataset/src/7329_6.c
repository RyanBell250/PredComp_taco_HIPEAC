#include <bits/stdc++.h>
using namespace std;
map<long long, long long> mp[100001];
map<long long, long long>::iterator it;
vector<long long> g[100001];
long long arr[100001], ans = 0;
long long gcd(long long a, long long b) {
  if (!a) return b;
  return gcd(b % a, a);
}
void dfs(long long start, long long parent) {
  mp[start][arr[start]] = 1;
  ans = (ans + arr[start]) % 1000000007;
  long long len = g[start].size(), i, to, a, b, val;
  for (it = mp[parent].begin(); it != mp[parent].end(); it++) {
    a = (*it).first;
    b = (*it).second;
    val = gcd(arr[start], a);
    ans = (ans + (val * b) % 1000000007) % 1000000007;
    mp[start][val] += b;
  }
  for (i = 0; i < len; i++) {
    to = g[start][i];
    if (to == parent) continue;
    dfs(to, start);
  }
}
int main() {
  long long n, i, a, b;
  cin >> n;
  for (i = 1; i <= n; i++) cin >> arr[i];
  for (i = 1; i < n; i++) cin >> a >> b, g[a].push_back(b), g[b].push_back(a);
  dfs(1, 0);
  cout << ans << endl;
  return 0;
}
