#include <bits/stdc++.h>
using namespace std;
const long double PI = acos((long double)-1.0);
template <class T>
void dbs(string str, T t) {
  cerr << str << " : " << t << "\n";
}
template <class T, class... S>
void dbs(string str, T t, S... s) {
  int idx = str.find(',');
  cerr << str.substr(0, idx) << " : " << t << ",";
  dbs(str.substr(idx + 1), s...);
}
template <class S, class T>
ostream& operator<<(ostream& os, const pair<S, T>& p) {
  return os << "(" << p.first << ", " << p.second << ")";
}
template <class T>
ostream& operator<<(ostream& os, const vector<T>& p) {
  os << "[ ";
  for (auto& it : p) os << it << " ";
  return os << "]";
}
template <class T>
ostream& operator<<(ostream& os, const set<T>& p) {
  os << "[ ";
  for (auto& it : p) os << it << " ";
  return os << "]";
}
template <class S, class T>
ostream& operator<<(ostream& os, const map<S, T>& p) {
  os << "[ ";
  for (auto& it : p) os << it << " ";
  return os << "]";
}
template <class T>
void prc(T a, T b) {
  cerr << "[";
  for (T i = a; i != b; ++i) {
    if (i != a) cerr << ", ";
    cerr << *i;
  }
  cerr << "]\n";
}
vector<long long> a, b;
const long long U = 1e18;
void recurse(int index1, long long currNum, vector<int>& temp,
             vector<long long>& a) {
  if (index1 == int(temp.size())) {
    a.push_back(currNum);
    return;
  }
  recurse(index1 + 1, currNum, temp, a);
  while (currNum <= U / (long long)temp[index1]) {
    currNum *= (long long)temp[index1];
    recurse(index1 + 1, currNum, temp, a);
  }
}
void precompute(vector<int>& temp) {
  vector<int> temp1, temp2;
  for (int i = (int)(0); i <= (int)(int(temp.size()) - 1); i++) {
    if (i % 2 == 0)
      temp1.push_back(temp[i]);
    else
      temp2.push_back(temp[i]);
  }
  recurse(0, 1LL, temp1, a);
  recurse(0, 1LL, temp2, b);
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  reverse(a.begin(), a.end());
}
bool possible(long long val1, long long lowerThan) {
  int j = 0;
  long long answer1 = 0;
  for (int i = (int)(0); i <= (int)(int(a.size()) - 1); i++) {
    while (j < int(b.size()) && b[j] <= val1 / a[i]) j++;
    answer1 += (long long)j;
  }
  if (answer1 < lowerThan)
    return false;
  else
    return true;
}
long long solve(long long k) {
  long long low1 = 1;
  long long high1 = 1e18;
  while (low1 < high1) {
    if (low1 + 1 == high1) {
      if (possible(low1, k))
        high1 = low1;
      else
        low1 = high1;
      break;
    }
    long long mid = (low1 + high1) / 2LL;
    if (possible(mid, k))
      high1 = mid;
    else
      low1 = mid + 1;
  }
  return low1;
}
int main() {
  int n;
  cin >> n;
  vector<int> v;
  for (int i = (int)(0); i <= (int)(n - 1); i++) {
    int temp;
    cin >> temp;
    v.push_back(temp);
  }
  precompute(v);
  long long k;
  cin >> k;
  cout << solve(k) << "\n";
  return 0;
}
