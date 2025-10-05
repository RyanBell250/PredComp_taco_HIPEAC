#include <bits/stdc++.h>
using namespace std;
const int INF = 1000000000;
int number, length;
int main(int argc, char const *argv[]) {
  cin >> number >> length;
  char numeros[number][length];
  for (int i = 0; i < number; i++) {
    cin >> numeros[i];
  }
  int bit[length], ans, n_max, n_min, sum;
  for (int i = 0; i < length; i++) {
    bit[i] = i;
  }
  ans = INF;
  do {
    n_max = 0, n_min = INF;
    for (int i = 0; i < number; i++) {
      sum = 0;
      for (int j = 0; j < length; j++) {
        sum = sum * 10 + (numeros[i][bit[j]]);
      }
      n_max = max(n_max, sum);
      n_min = min(n_min, sum);
    }
    ans = min(ans, n_max - n_min);
  } while (next_permutation(bit, bit + length));
  cout << ans << endl;
  return 0;
}
