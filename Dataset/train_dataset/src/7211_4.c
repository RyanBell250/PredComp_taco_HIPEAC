#include <bits/stdc++.h>
using namespace std;
int n, n1, n2;
deque<int> f, s;
void input() {
  cin >> n;
  cin >> n1;
  for (int i = 0; i < n1; i++) {
    int t;
    cin >> t;
    f.push_back(t);
  }
  cin >> n2;
  for (int i = 0; i < n2; i++) {
    int t;
    cin >> t;
    s.push_back(t);
  }
  {
    cerr << "n1"
         << " = ";
    cerr << (n1) << endl;
  };
  {
    cerr << "n2"
         << " = ";
    cerr << (n2) << endl;
  };
}
void solve() {
  int cnt = 0;
  int res = 0;
  while (f.size() && s.size()) {
    int t1 = 0;
    t1 = f.front();
    f.pop_front();
    int t2 = 0;
    t2 = s.front();
    s.pop_front();
    {
      cerr << "t1"
           << " = ";
      cerr << (t1) << endl;
    };
    {
      cerr << "t2"
           << " = ";
      cerr << (t2) << endl;
    };
    if (t1 < t2) {
      s.push_back(t1);
      s.push_back(t2);
    } else {
      f.push_back(t2);
      f.push_back(t1);
    }
    cnt++;
    if (cnt >= 10000) {
      res = -1;
      break;
    }
  }
  {
    cerr << "f.size()"
         << " = ";
    cerr << (f.size()) << endl;
  };
  {
    cerr << "s.size()"
         << " = ";
    cerr << (s.size()) << endl;
  };
  {
    cerr << "res"
         << " = ";
    cerr << (res) << endl;
  };
  {
    cerr << "cnt"
         << " = ";
    cerr << (cnt) << endl;
  };
  if (res != -1) {
    if (f.size() == 0)
      res = 2;
    else
      res = 1;
    {
      cerr << "res"
           << " = ";
      cerr << (res) << endl;
    };
  }
  if (res == -1)
    cout << res << '\n';
  else
    cout << cnt << ' ' << res << '\n';
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(NULL);
  cout.tie(NULL);
  int t = 1;
  while (t--) {
    input();
    solve();
  }
}
