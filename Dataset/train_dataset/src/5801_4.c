#include <bits/stdc++.h>
using namespace std;
struct TopTwo {
  int highest, second;
  TopTwo() : highest(-1), second(-1) {}
  void add(int pos) {
    if (pos > highest) {
      swap(highest, second);
      highest = pos;
    } else {
      second = max(second, pos);
    }
  }
  void add(const TopTwo& t) {
    add(t.highest);
    add(t.second);
  }
};
int easy_solution(int n, vector<int>& xs) {
  int k = 21;
  vector<TopTwo> places(1 << k);
  for (int i = 0; i < n; ++i) {
    places[xs[i]].add(i);
  }
  for (int j = 0; j < k; ++j) {
    for (int i = 0; i < (1 << k); ++i) {
      if ((1 << j) & i) {
        places[i - (1 << j)].add(places[i]);
      }
    }
  }
  int best = 0;
  for (int j = k - 1; j >= 0; --j) {
    int tmp = best + (1 << j);
    bool possible = false;
    for (int i = 0; i < n; ++i) {
      int search_for = (~xs[i]) & tmp;
      if (places[search_for].second > i) {
        possible = true;
      }
    }
    if (possible) {
      best += (1 << j);
    }
  }
  return best;
}
int main() {
  int n;
  cin >> n;
  vector<int> xs(n);
  for (int i = 0; i < n; ++i) {
    cin >> xs[i];
  }
  cout << easy_solution(n, xs) << endl;
  return 0;
}
