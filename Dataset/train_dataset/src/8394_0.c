#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  const int MAX_CARDS = 9;

  int T;
  scanf("%d", &T);
  for (int t = 0; t < T; ++t) {
    vector<int> gates(MAX_CARDS), jackie(MAX_CARDS);
    for (int i = 0; i < MAX_CARDS; ++i)
      scanf("%d", &gates[i]);
    for (int i = 0; i < MAX_CARDS; ++i)
      scanf("%d", &jackie[i]);
    sort(gates.begin(), gates.end());
    sort(jackie.begin(), jackie.end());

    int win_g = 0, win_j = 0;
    do {
      int cnt_g = 0, cnt_j = 0;
      for (int i = 0; i < MAX_CARDS; ++i) {
	if (gates[i] > jackie[i])
	  cnt_g += (gates[i]+jackie[i]);
	else
	  cnt_j += (gates[i]+jackie[i]);
      }
      if (cnt_g > cnt_j)
	++win_g;
      else
	++win_j;
    } while (next_permutation(jackie.begin(), jackie.end()));
    printf("%.5f %.5f\n", win_g/static_cast<double>(win_g+win_j), win_j/static_cast<double>(win_g+win_j));
  }
  return 0;
}