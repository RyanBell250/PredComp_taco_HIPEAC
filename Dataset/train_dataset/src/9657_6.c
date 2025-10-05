#include <bits/stdc++.h>
using namespace std;
long long to_int(string s) {
  long long x = 0;
  for (long long i = 0; i < s.size(); i++) {
    x = x * 10 + (s[i] - 48);
  }
  return x;
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  long long t;
  cin >> t;
  while (t--) {
    long long n;
    cin >> n;
    string s;
    cin >> s;
    set<char> st;
    for (long long i = 0; i < s.size(); i++) {
      st.insert(s[i]);
    }
    if (st.size() == 1)
      cout << "-1 -1";
    else {
      for (long long i = 0; i < s.size(); i++) {
        if (s[i] != s[i + 1]) {
          cout << i + 1 << " " << i + 2;
          break;
        }
      }
    }
    cout << '\n';
  }
  return 0;
}
