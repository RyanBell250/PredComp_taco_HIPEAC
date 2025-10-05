#include <bits/stdc++.h>
using namespace std;
int find_max(vector<int>& v) {
  if (v.size() == 1) return v[0];
  if (v.size() == 2) {
    cout << "? " << v[0] << " " << v[1] << endl;
    char c;
    cin >> c;
    if (c == '<') return v[1];
    return v[0];
  }
  vector<int> w;
  int n = v.size();
  if (n % 2 == 1) {
    w.push_back(v[n - 1]);
    n--;
  }
  for (int k = 0; k < n; k += 2) {
    cout << "? " << v[k] << " " << v[k + 1] << endl;
    char c;
    cin >> c;
    if (c == '<')
      w.push_back(v[k + 1]);
    else
      w.push_back(v[k]);
  }
  return find_max(w);
}
int find_min(vector<int>& v) {
  if (v.size() == 1) return v[0];
  if (v.size() == 2) {
    cout << "? " << v[0] << " " << v[1] << endl;
    char c;
    cin >> c;
    if (c == '>') return v[1];
    return v[0];
  }
  vector<int> w;
  int n = v.size();
  if (n % 2 == 1) {
    w.push_back(v[n - 1]);
    n--;
  }
  for (int k = 0; k < n; k += 2) {
    cout << "? " << v[k] << " " << v[k + 1] << endl;
    char c;
    cin >> c;
    if (c == '>')
      w.push_back(v[k + 1]);
    else
      w.push_back(v[k]);
  }
  return find_min(w);
}
void solve() {
  int n;
  cin >> n;
  vector<int> Min, Max;
  if (n % 2 == 1) {
    Min.push_back(n);
    Max.push_back(n);
    n--;
  }
  for (int k = 1; k <= n; k += 2) {
    cout << "? " << k << " " << k + 1 << endl;
    char c;
    cin >> c;
    if (c == '<') {
      Min.push_back(k);
      Max.push_back(k + 1);
    } else {
      Min.push_back(k + 1);
      Max.push_back(k);
    }
  }
  int i_min = find_min(Min);
  int i_max = find_max(Max);
  cout << "! " << i_min << " " << i_max << endl;
}
int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t) {
    t--;
    solve();
  }
  return 0;
}
