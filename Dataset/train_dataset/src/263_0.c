#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
int main() {
  int N, K;
  string S;
  cin >> N >> K;
  cin >> S;
  set<char> second;
  vector<char> V;
  for (int i = 0; i < (int)S.size(); i++) {
    second.insert(S[i]);
  }
  for (set<char>::iterator it = second.begin(); it != second.end(); it++) {
    V.push_back(*it);
  }
  if (N < K) {
    for (int i = 0; i < N; i++) {
      cout << S[i];
    }
    for (int i = 0; i < K - N; i++) {
      cout << V[0];
    }
    cout << endl;
  } else {
    vector<char> ans;
    for (int i = 0; i < K; i++) {
      ans.push_back(S[i]);
    }
    for (int i = K - 1; i >= 0; i--) {
      vector<char>::iterator it;
      it = upper_bound(V.begin(), V.end(), ans[i]);
      if (it == V.end()) {
        continue;
      } else {
        ans[i] = *it;
        for (int j = i + 1; j < K; j++) {
          ans[j] = V[0];
        }
        break;
      }
    }
    for (int i = 0; i < K; i++) {
      cout << ans[i];
    }
    cout << endl;
  }
  return 0;
}
