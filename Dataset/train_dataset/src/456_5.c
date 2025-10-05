#include <bits/stdc++.h>
using namespace std;
int n;
int a[2005];
int prob[5005];
int suffix[10010];
int main() {
  memset(a, 0, 2005 * sizeof(int));
  memset(prob, 0, 5005 * sizeof(int));
  memset(suffix, 0, 10010 * sizeof(int));
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      prob[a[i] - a[j]]++;
    }
  }
  for (int i = 4999; i >= 0; i--) {
    suffix[i] = suffix[i + 1] + prob[i];
  }
  long double answer = 0;
  for (int i = 0; i < 5000; i++) {
    for (int j = 0; j < 5000; j++) {
      answer += 1.0 * prob[i] * prob[j] * suffix[i + j + 1];
    }
  }
  double nc2 = (n) * (n - 1) / 2;
  answer /= (nc2 * nc2 * nc2);
  cout << answer << endl;
  return 0;
}
