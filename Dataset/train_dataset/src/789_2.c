#include <bits/stdc++.h>
using namespace std;
long long arr[200007];
int sum(string s) {
  int sm = 0;
  for (int i = 0; i < s.size(); i++) sm += s[i] - '0';
  return sm;
}
int main() {
  string x;
  cin >> x;
  string ans, tmp;
  ans = tmp = x;
  int maxx = sum(x);
  for (int i = x.size() - 1; i > 0; i--) {
    tmp[i] = '9';
    if (tmp[i - 1] != '0') tmp[i - 1]--;
    if (maxx < sum(tmp)) {
      maxx = sum(tmp);
      ans = tmp;
    }
  }
  int f = 0;
  for (int i = 0; i < ans.size(); i++) {
    if (i == 0 && ans[i] == '0')
      continue;
    else
      cout << ans[i];
  }
  return 0;
}
