#include <bits/stdc++.h>
using namespace std;
string itos(int a) {
  if (!a) return "0";
  string res;
  while (a) {
    res += (char)('0' + (a % 10));
    a /= 10;
  }
  reverse((res).begin(), (res).end());
  return res;
}
int main() {
  int n;
  int a[10], can = 0;
  ;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    can |= 1 << a[i];
  }
  if (n > 6) {
    cout << "0" << endl;
    return 0;
  }
  vector<string> v;
  vector<int> mask;
  for (int i = 0; i < 256; i++) {
    string s = itos(i);
    int tmp = 0;
    for (int j = 0; j < s.size(); j++) {
      tmp |= 1 << (int)(s[j] - '0');
    }
    if ((tmp & can) == tmp) {
      v.push_back(s);
      mask.push_back(tmp);
    }
  }
  vector<string> ans;
  for (int i = 0; i < (int)(v.size()); i++)
    for (int j = 0; j < (int)(v.size()); j++) {
      int size = min(v[i].size(), v[j].size());
      bool f = true;
      for (int k = 0; k < size; k++) {
        if (v[i][k] != v[j][v[j].size() - 1 - k]) {
          f = false;
          break;
        }
      }
      if (!f) continue;
      for (int k = 0; k < (int)(v.size()); k++)
        for (int l = 0; l < (int)(v.size()); l++) {
          if ((mask[i] | mask[j] | mask[k] | mask[l]) != can) continue;
          string s = v[i] + v[k] + v[l] + v[j];
          bool f = true;
          for (int x = 0; 2 * x < s.size(); x++) {
            if (s[x] != s[s.size() - 1 - x]) {
              f = false;
              break;
            }
          }
          if (f) ans.push_back(v[i] + "." + v[k] + "." + v[l] + "." + v[j]);
        }
    }
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++) cout << ans[i] << endl;
}
