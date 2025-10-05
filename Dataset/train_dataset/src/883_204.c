#include <bits/stdc++.h>
using namespace std;
class gfg {
 public:
  unsigned int countSetBits(int n) {
    unsigned int count = 0;
    while (n) {
      n &= (n - 1);
      count++;
    }
    return count;
  }
} g;
vector<long long> prime;
long long int fact(int n);
int hexadecimalToDecimal(char hexVal[]);
vector<vector<long long int> > power(vector<vector<long long int> > &a,
                                     long long int n, long long int p);
long long int fact(long long int n, long long int p);
long long int power(long long int x, long long int n, long long int p);
long long int nCr(long long int n, long long int r, long long int p);
vector<vector<long long int> > multiply(vector<vector<long long int> > &a,
                                        vector<vector<long long int> > &b,
                                        long long int p);
void manipulated_seive(long long int N);
int gcd(int a, int b);
void generatePrimeFactors();
long long int calculateNoOFactors(long long int n);
struct A {
  int val;
  int dis;
};
bool comparison(A a, A b) { return (a.val > b.val); }
void solve() {
  long long int n, sum = 0, flag1 = 1, flag2 = -1, minn, maxx;
  cin >> n;
  vector<long long int> A, B;
  for (long long int i = 0; i < (n); i++) {
    long long int a;
    cin >> a;
    A.push_back((a));
  };
  minn = A[0];
  maxx = A[0];
  if (A[0] > 0) {
    flag1 = 1;
    flag2 = 1;
  } else {
    flag1 = -1;
    flag2 = -1;
  }
  for (long long int i = 0; i < (n); i++) {
    if (A[i] > 0 && flag1 < 0) {
      B.push_back((minn));
      maxx = A[i];
      flag1 = 1;
      flag2 = 1;
    } else if (A[i] < 0 && flag2 > 0) {
      B.push_back((maxx));
      minn = A[i];
      flag1 = -1;
      flag2 = -1;
    } else if (A[i] > 0 && flag1 >= 0) {
      maxx = max(maxx, A[i]);
    } else if (A[i] < 0 && flag2 < 0) {
      minn = max(minn, A[i]);
    }
  }
  if (A[A.size() - 1] > 0) {
    B.push_back((maxx));
  } else {
    B.push_back((minn));
  }
  for (long long int i = 0; i < (B.size()); i++) {
    sum += B[i];
  }
  cout << sum;
  B.clear();
}
void template1() {
  long long int t;
  cin >> t;
  while (t--) {
    solve();
    cout << "\n";
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  template1();
  return 0;
}
long long int fact(int n) { return (n == 1 || n == 0) ? 1 : n * fact(n - 1); }
int hexadecimalToDecimal(char hexVal[]) {
  int len = strlen(hexVal);
  int base = 1;
  int dec_val = 0;
  for (int i = len - 1; i >= 0; i--) {
    if (hexVal[i] >= '0' && hexVal[i] <= '9') {
      dec_val += (hexVal[i] - 48) * base;
      base = base * 16;
    } else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
      dec_val += (hexVal[i] - 55) * base;
      base = base * 16;
    }
  }
  return dec_val;
}
long long int fact(long long int n, long long int p) {
  long long int ans = 1;
  for (long long int i = 1; i <= n; i++) {
    ans *= i;
    ans %= p;
  }
  return ans;
}
long long int power(long long int x, long long int n, long long int p) {
  long long int res = 1;
  if (n == 1) return x % p;
  if (n % 2 == 1) res = x % p;
  long long int temp = power(x, n / 2, p);
  return res * ((temp * temp) % p) % p;
}
long long int inv(long long int a, long long int p) {
  return power(a, p - 2, p);
}
long long int nCr(long long int n, long long int r, long long int p) {
  if (r > n) return 0;
  long long int t1 = fact(n, p);
  long long int t2 = inv(fact(r, p), p);
  long long int t3 = inv(fact(n - r, p), p);
  return (((t1 * t2) % p) * t3) % p;
}
vector<vector<long long int> > multiply(vector<vector<long long int> > &a,
                                        vector<vector<long long int> > &b,
                                        long long int p) {
  int r1, c1, r2, c2;
  r1 = a.size();
  c1 = a[0].size();
  r2 = b.size();
  c2 = b[0].size();
  vector<vector<long long int> > result(r1, vector<long long int>(c2, 0));
  if (c1 != r2) return result;
  for (int i = 0; i < r1; i++) {
    for (int j = 0; j < c2; j++) {
      for (int k = 0; k < c1; k++) {
        result[i][j] += a[i][k] * b[k][j];
        result[i][j] %= p;
      }
    }
  }
  return result;
}
vector<vector<long long int> > power(vector<vector<long long int> > &a,
                                     long long int n, long long int p) {
  int r = a.size();
  vector<vector<long long int> > result(r, vector<long long int>(r, 0));
  for (int i = 0; i < r; i++) result[i][i] = 1;
  while (n > 0) {
    if (n % 2 == 1) {
      result = multiply(result, a, p);
    }
    n /= 2;
    a = multiply(a, a, p);
  }
  return result;
}
const long long MAX_SIZE = 1000001;
vector<long long> isprime(MAX_SIZE, true);
vector<long long> SPF(MAX_SIZE);
void manipulated_seive(long long int N) {
  isprime[0] = isprime[1] = false;
  for (long long int i = 2; i < N; i++) {
    if (isprime[i]) {
      prime.push_back(i);
      SPF[i] = i;
    }
    for (long long int j = 0;
         j < (int)prime.size() && i * prime[j] < N && prime[j] <= SPF[i]; j++) {
      isprime[i * prime[j]] = false;
      SPF[i * prime[j]] = prime[j];
    }
  }
}
int gcd(int a, int b) {
  if (b == 0) return a;
  return gcd(b, a % b);
}
const int MAX = 1000001;
int factor[MAX] = {0};
void generatePrimeFactors() {
  factor[1] = 1;
  for (int i = 2; i < MAX; i++) factor[i] = i;
  for (int i = 4; i < MAX; i += 2) factor[i] = 2;
  for (int i = 3; i * i < MAX; i++) {
    if (factor[i] == i) {
      for (int j = i * i; j < MAX; j += i) {
        if (factor[j] == j) factor[j] = i;
      }
    }
  }
}
long long int calculateNoOFactors(long long int n) {
  if (n == 1) return 1;
  int ans = 1;
  int dup = factor[n];
  int c = 1;
  int j = n / factor[n];
  while (j != 1) {
    if (factor[j] == dup)
      c += 1;
    else {
      dup = factor[j];
      ans = ans * (c + 1);
      c = 1;
    }
    j = j / factor[j];
  }
  ans = ans * (c + 1);
  return ans;
}
