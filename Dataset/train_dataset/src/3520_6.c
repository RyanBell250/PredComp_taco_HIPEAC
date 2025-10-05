#include <bits/stdc++.h>
using namespace std;
int n, x;
vector<int> arr;
set<int> el;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> n >> x;
  for (int i = 1; i <= ((1 << n) - 1); i++) el.insert(i);
  el.erase(x);
  while (!el.empty()) {
    int eh = *el.begin();
    arr.push_back(eh);
    el.erase(eh ^ x);
    el.erase(eh);
  }
  cout << ((int)(arr).size()) << "\n";
  if (((int)(arr).size())) {
    cout << arr[0] << " ";
    for (int i = 1; i <= (((int)(arr).size()) - 1); i++)
      cout << (arr[i - 1] ^ arr[i]) << " ";
  }
  return 0;
}
