#include <bits/stdc++.h>
using namespace std;
unsigned long long result = 0;
vector<int> nums, pat;
int n, l, r, x;
void check() {
  vector<int> cur;
  unsigned long long sum = 0;
  for (int i = 0; i < pat.size(); i++) {
    if (pat[i] == 1) cur.push_back(nums[i]), sum += nums[i];
  }
  sort(cur.begin(), cur.end());
  if (cur.size() < 2) return;
  if (cur[cur.size() - 1] - cur[0] < x) return;
  if (sum >= l && sum <= r) result++;
}
void go(int index) {
  if (index == n) {
    check();
    return;
  }
  pat.push_back(1);
  go(index + 1);
  pat.pop_back();
  pat.push_back(0);
  go(index + 1);
  pat.pop_back();
}
int main() {
  cin >> n >> l >> r >> x;
  int temp;
  for (int i = 0; i < n; i++) {
    cin >> temp;
    nums.push_back(temp);
  }
  go(0);
  cout << result << endl;
  return 0;
}
