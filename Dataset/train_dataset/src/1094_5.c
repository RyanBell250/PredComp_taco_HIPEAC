#include <bits/stdc++.h>
using namespace std;
int main() {
  cin.sync_with_stdio(0);
  cin.tie(0);
  int N, K;
  cin >> N >> K;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  int ans = -1234567890LL;
  for (int i = 0; i < N; i++)
    for (int j = i; j < N; j++) {
      multiset<int> S, T;
      for (int k = 0; k < i; k++) S.insert(A[k]);
      for (int k = j + 1; k < N; k++) S.insert(A[k]);
      for (int k = i; k <= j; k++) T.insert(A[k]);
      for (int k = 0; k < K; k++) {
        if (S.empty() || T.empty()) break;
        if (*S.rbegin() > *T.begin()) {
          T.insert(*S.rbegin());
          S.insert(*T.begin());
          T.erase(T.begin());
          S.erase(--S.end());
        } else
          break;
      }
      int akt = 0;
      for (auto it = T.begin(); it != T.end(); it++) akt += *it;
      ans = max(ans, akt);
    }
  cout << ans << "\n";
  return 0;
}
