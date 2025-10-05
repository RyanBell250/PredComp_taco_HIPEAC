#include <bits/stdc++.h>
using namespace std;
string a;
string kthSubstring(string &s, int k) {
  priority_queue<pair<string, int>, vector<pair<string, int>>,
                 greater<pair<string, int>>>
      pq;
  int len = s.length();
  for (int i = 0; i < len; i++) {
    string c;
    c = s[i];
    pq.push(make_pair(c, i));
  }
  while (!pq.empty()) {
    string throwaway;
    a = pq.top().first;
    int b = pq.top().second;
    pq.pop();
    k--;
    if (k == 0) {
      return a;
    }
    if (b < len - 1) {
      a += s[b + 1];
      pq.push(make_pair(a, b + 1));
    }
  }
  return "";
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  int k;
  cin >> s >> k;
  int len = s.length();
  long long possible = ((long long)len * (long long)(len + 1)) / 2LL,
            required = k;
  if (required > possible)
    cout << "No such line." << '\n';
  else
    cout << kthSubstring(s, k) << '\n';
  return 0;
}
