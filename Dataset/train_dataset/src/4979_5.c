#include <bits/stdc++.h>
using namespace std;
long er;
vector<long> v;
long n;
int main() {
  ios_base::sync_with_stdio(0);
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  for (int i = 4; i <= 1000; i++) {
    er = 0;
    for (int a = 0; a < v.size(); a++)
      for (int b = 0; b < v.size(); b++)
        for (int c = 0; c < v.size(); c++)
          if (a != b && a != c && b != c)
            if (v[a] + v[b] - v[c] == i) er = 1;
    if (er == 0) v.push_back(i);
  }
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j) cout << " ";
      if (i == j)
        cout << 0;
      else
        cout << v[i] + v[j];
    }
    cout << endl;
  }
  cin.get();
  cin.get();
  return 0;
}
