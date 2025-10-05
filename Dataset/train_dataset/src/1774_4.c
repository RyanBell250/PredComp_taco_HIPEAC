#include <bits/stdc++.h>
using namespace std;
int main() {
  int h;
  cin >> h;
  h++;
  vector<int> a(h, 0);
  for (int i = 0; i < h; i++) cin >> a[i];
  vector<int> p, q;
  p.push_back(0);
  q.push_back(0);
  int fidx = 1;
  bool flag = true;
  for (int i = 1; i < h; i++) {
    for (int j = 0; j < a[i]; j++) p.push_back(fidx);
    for (int j = 0; j < a[i] - 1; j++) q.push_back(fidx);
    if (a[i - 1] > 1 && a[i] > 1 && flag) {
      q.push_back(fidx + 1);
      flag = false;
    } else
      q.push_back(fidx);
    fidx += a[i - 1];
  }
  if (flag)
    cout << "perfect" << endl;
  else {
    cout << "ambiguous" << endl;
    for (int i = 0; i < p.size(); i++) cout << p[i] << " ";
    cout << endl;
    for (int i = 0; i < q.size(); i++) cout << q[i] << " ";
  }
}
