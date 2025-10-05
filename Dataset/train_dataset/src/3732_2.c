#include <bits/stdc++.h>
using namespace std;
const int N = 201110, M = 501110;
int n, m, numeven, numodd;
int a[N];
stack<int> odd, even;
map<int, int> mp;
int main() {
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
    mp[a[i]]++;
    if (a[i] % 2 == 0)
      numeven++;
    else
      numodd++;
  }
  for (int i = 1; i <= min(M, m); i++) {
    if (i % 2 == 0 && mp[i] == 0) even.push(i);
    if (i % 2 == 1 && mp[i] == 0) odd.push(i);
  }
  int ans = 0;
  for (int i = 1; i <= n; i++)
    if (mp[a[i]] > 1) {
      if (a[i] % 2 == 0)
        numeven--;
      else
        numodd--;
      mp[a[i]]--;
      if (numeven > numodd) {
        ans++;
        if (odd.size() == 0) {
          cout << -1 << endl;
          return 0;
        }
        a[i] = odd.top();
        odd.pop();
        numodd++;
      } else {
        ans++;
        if (even.size() == 0) {
          cout << -1 << endl;
          return 0;
        }
        a[i] = even.top();
        even.pop();
        numeven++;
      }
    }
  for (int i = 1; i <= n; i++) {
    if (numeven > numodd && a[i] % 2 == 0) {
      ans++;
      if (odd.size() == 0) {
        cout << -1 << endl;
        return 0;
      }
      a[i] = odd.top();
      odd.pop();
      numeven--;
      numodd++;
    }
    if (numeven < numodd && a[i] % 2 == 1) {
      ans++;
      if (even.size() == 0) {
        cout << -1 << endl;
        return 0;
      }
      a[i] = even.top();
      even.pop();
      numeven++;
      numodd--;
    }
  }
  printf("%d\n", ans);
  for (int i = 1; i <= n; i++) printf("%d ", a[i]);
}
