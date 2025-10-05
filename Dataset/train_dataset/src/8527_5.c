#include <bits/stdc++.h>
using namespace std;
vector<vector<long long>> Pal;
vector<vector<long long>> DP;
vector<vector<long long>> V;
string s;
long long k;
long long solve(int index, int subsSoFar) {
  if (index >= s.size()) {
    return 0;
  }
  if (index == (s.size() - 1)) {
    V.at(index).at(subsSoFar) = index;
    return 0;
  }
  if (subsSoFar == k) {
    V.at(index).at(subsSoFar) = s.size() - 1;
    return Pal.at(index).back();
  }
  long long &dp = DP.at(index).at(subsSoFar);
  if (dp != -1) {
    return dp;
  }
  long long mn = INT32_MAX, curr;
  for (int i = index; i < s.size(); i++) {
    curr = Pal.at(index).at(i) + solve(i + 1, subsSoFar + 1);
    if (curr < mn) {
      mn = curr;
      V.at(index).at(subsSoFar) = i;
    }
  }
  return (dp = mn);
}
int makePalindrome(int tmpLow, int tmpHigh) {
  int ans = 0;
  while (tmpLow < tmpHigh) {
    if (s.at(tmpLow) != s.at(tmpHigh)) ++ans;
    tmpLow++;
    tmpHigh--;
  }
  return ans;
}
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> s >> k;
  long long l = s.size();
  Pal = vector<vector<long long>>(l, vector<long long>(l));
  DP = vector<vector<long long>>(l, vector<long long>(k + 1, -1));
  V = vector<vector<long long>>(l, vector<long long>(k + 1, -1));
  for (long long i = 0; i < l; i++) {
    for (long long j = 0; j < l; j++) {
      Pal.at(i).at(j) = makePalindrome(i, j);
    }
  }
  cout << solve(0, 1) << endl;
  int from = 0, to = V.at(0).at(1), substrings = 1;
  vector<pair<int, int>> P;
  while (true) {
    P.push_back({from, to});
    from = to + 1;
    if (to >= (l - 1)) break;
    ++substrings;
    to = V.at(from).at(substrings);
  }
  for (auto [low, high] : P) {
    int tmpLow = low, tmpHigh = high;
    while (tmpLow < tmpHigh) {
      s.at(tmpHigh) = s.at(tmpLow);
      tmpLow++;
      tmpHigh--;
    }
    for (int i = low; i <= high; i++) {
      cout << s.at(i);
    }
    if (high != (l - 1)) cout << "+";
  }
  return 0;
}
