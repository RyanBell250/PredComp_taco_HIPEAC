#include <bits/stdc++.h>
using namespace std;
const int N = 1000010;
char arr[N], sub[N];
int n, m;
vector<bool> ante(10);
void print(string &str) {
  for (int i = 0; i < (int)str.size(); i++) str[i] += '0';
  printf("%s\n", str.c_str());
  exit(0);
}
string parse(vector<int> freq) {
  string str;
  for (int i = 0; i < 10; i++) assert(freq[i] >= 0);
  for (int i = 0; i < 10; i++)
    if (ante[i]) str += string(freq[i], i);
  for (int i = 0; i < m; i++) str += sub[i];
  for (int i = 0; i < 10; i++)
    if (!ante[i]) str += string(freq[i], i);
  return str;
}
void print(vector<int> vet) {
  for (int i : vet) printf("%d ", i);
  printf("\n");
}
void solve(vector<int> freq, int num) {
  for (int i = 0; i < m; i++) freq[sub[i]]--;
  while (num) {
    freq[num % 10]--;
    num /= 10;
  }
  for (int i = 0; i < 10; i++)
    if (freq[i] < 0) return;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < m; j++)
      if (i != sub[j]) {
        ante[i] = i < sub[j];
        break;
      }
  string str = parse(freq);
  if (str[0]) print(str);
  string str2 = "";
  for (int i = 1; i < 10; i++)
    if (freq[i]) {
      str2 = string(1, i);
      freq[i]--;
      str2 += parse(freq);
      freq[i]++;
      break;
    }
  str = "";
  for (int i = 0; i < m; i++) str += sub[i];
  for (int i = 0; i < 10; i++) str += string(freq[i], i);
  if (!str[0]) str = "";
  if (str.empty() and str2.empty()) return;
  if (str.empty()) print(str2);
  if (str2.empty()) print(str);
  assert((int)str.size() == (int)str2.size());
  print(str < str2 ? str : str2);
}
int main() {
  vector<int> dig = {1, 1};
  for (int i = 2; i <= 10; i++) dig.push_back(10 * dig.back());
  scanf("%s %s", arr, sub);
  vector<int> freq(10);
  n = (int)strlen(arr);
  m = (int)strlen(sub);
  for (int i = 0; i < n; i++) {
    arr[i] -= '0';
    freq[arr[i]]++;
  }
  for (int i = 0; i < m; i++) sub[i] -= '0';
  for (int i = N;; i--) {
    if (!i) {
      printf("0\n");
      exit(0);
    }
    int x = 1;
    for (; dig[x + 1] <= i; x++)
      ;
    if (n - x == i) solve(freq, i);
  }
  return 0;
}
