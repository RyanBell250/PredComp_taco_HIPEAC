#include <bits/stdc++.h>
using namespace std;
bool isPrime(long long n) {
  if (n < 0) throw "is prime: n < 0";
  if (n == 0 || n == 1) return false;
  if (n != 2 && n % 2 == 0) return false;
  long long sq = sqrt(n);
  for (long long i = 3; i <= sq + 1; i += 2)
    if (n % i == 0) return false;
  return true;
}
long long conc(long long a, long long b) {
  stack<int> s;
  do {
    s.push(b % 10);
    b /= 10;
  } while (b);
  while (!s.empty()) {
    a = a * 10 + s.top();
    s.pop();
  }
  return a;
}
bool test(const vector<bool>& mask, long long a, long long b) {
  size_t x = conc(a, b);
  if (x < mask.size() && !mask[x]) return false;
  if (x >= mask.size() && !isPrime(x)) return false;
  size_t y = conc(b, a);
  if (y < mask.size() && !mask[y]) return false;
  if (y >= mask.size() && !isPrime(y)) return false;
  return true;
}
void printVec(const vector<int>& s) {
  for (const auto& i : s) cout << i << ' ';
  cout << endl;
}
void eratosfen(vector<bool>& m) {
  long long n = m.size();
  long long firstPrime = 2;
  for (long long i = 0; i < min(n, firstPrime); ++i) m[i] = false;
  for (long long i = min(n, firstPrime); i < n; ++i) m[i] = true;
  for (long long i = firstPrime; i < n; ++i) {
    if (m[i]) {
      for (long long j = i + i; j < n; j += i) m[j] = false;
    }
  }
}
vector<long long> generatePrimes(long long maximal) {
  vector<bool> m(maximal + 1);
  eratosfen(m);
  vector<long long> primes;
  for (long long i = 2; i <= maximal; ++i) {
    if (m[i]) primes.push_back(i);
  }
  return primes;
}
long long powMod(long long g, long long pow,
                 long long mod = std::numeric_limits<int>::max()) {
  long long x = 1;
  g %= mod;
  pow %= mod;
  unsigned long long mask = 1ul << 63;
  while (mask) {
    x = (x * x) % mod;
    if (pow & mask) x = (x * g) % mod;
    mask >>= 1;
  }
  return x;
}
int digitCount(long long value) {
  int count = 0;
  do {
    value /= 10;
    ++count;
  } while (value);
  return count;
}
vector<short> digitVec(long long value) {
  vector<short> v;
  do {
    v.push_back(value % 10);
    value /= 10;
  } while (value);
  return v;
}
long long gcd(long long x, long long y) {
  if (y == 0) return x;
  return gcd(y, x % y);
}
long long totient(long long value) {
  if (value < 1) throw "totient(): value < 1";
  long long result = value;
  if (value % 2 == 0) {
    result = result / 2;
    while (value % 2 == 0) value /= 2;
  }
  for (long long divisor = 3; divisor * divisor <= value; divisor += 2) {
    if (value % divisor == 0) {
      long long p = divisor;
      result = result * (p - 1) / p;
      while (value % divisor == 0) value /= divisor;
    }
  }
  if (value != 1) result = result * (value - 1) / value;
  return result;
}
struct ContinuedFraction {
  ContinuedFraction(const vector<int>& values) : Values(values) {}
  pair<long long, long long> getFrac(size_t k) const {
    if (k >= Values.size()) throw "k is too big";
    long long n = 0;
    long long d = 1;
    for (int index = k; index >= 0; --index) {
      long long n_ = Values[index] * n + d;
      long long d_ = n;
      n = n_;
      d = d_;
    }
    return make_pair(n, d);
  }

 private:
  vector<int> Values;
};
int PeriodContinuedFractionSqrt(long long value) {
  long long sq = sqrt(value);
  if (sq * sq == value) return 0;
  long long a = sq;
  long long b = 1;
  long long c = 0;
  map<pair<int, pair<int, int>>, int> m;
  int index;
  for (index = 1; !m[make_pair(a, make_pair(b, c))]; ++index) {
    m[make_pair(a, make_pair(b, c))] = index;
    long long c_ = b * a - c;
    long long b_ = (value - c_ * c_) / b;
    long long a_ = (sq + c_) / b_;
    a = a_;
    b = b_;
    c = c_;
  }
  return index - m[make_pair(a, make_pair(b, c))];
}
string getNumberName(int value) {
  const vector<string> digit = {"",        "one",       "two",      "three",
                                "four",    "five",      "six",      "seven",
                                "eight",   "nine",      "ten",      "eleven",
                                "twelve",  "thirteen",  "fourteen", "fifteen",
                                "sixteen", "seventeen", "eighteen", "nineteen"};
  const vector<string> tens = {"",      "",      "twenty",  "thirty", "forty",
                               "fifty", "sixty", "seventy", "eighty", "ninety"};
  string result = "";
  if (value > 999) {
    result += digit[value / 1000] + " thousand ";
    value %= 1000;
  }
  if (value > 99) {
    result += digit[value / 100] + " hundred ";
    value %= 100;
    if (value != 0) result += "and";
  }
  if (value >= 20 && value < 100) {
    result += tens[value / 10];
    if (value % 10) result += "-" + digit[value % 10];
    value = 0;
  }
  if (value > 9 && value < 20) {
    result += digit[value];
    value = 0;
  }
  if (value > 0 && value < 20) result += digit[value % 20];
  return result;
}
long long rect2(const pair<int, int>& a, const pair<int, int>& b,
                const pair<int, int>& c) {
  long long s = (b.first - a.first) * (c.second - a.second) -
                (c.first - a.first) * (b.second - a.second);
  if (s < 0) return -s;
  return s;
}
bool intoTriangle(const vector<pair<int, int>>& points,
                  const pair<int, int>& point) {
  long long s1 = rect2(points[0], points[1], point);
  long long s2 = rect2(points[0], points[2], point);
  long long s3 = rect2(points[1], points[2], point);
  long long s = rect2(points[1], points[2], points[0]);
  if (s1 + s2 + s3 == s) return true;
  return false;
}
int main() {
  int n;
  int k;
  cin >> n;
  cin >> k;
  vector<pair<int, int>> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i].first >> v[i].second;
  }
  int START = n * 2000000 + 1;
  int minimal = START;
  for (unsigned int mask = 0; mask != (1 << n); ++mask) {
    vector<int> points(n);
    int point = 0;
    int count = 0;
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) {
        ++point;
        count += v[i].second;
        points[i] = v[i].first;
      } else {
        points[i] = v[i].first + 1;
      }
    }
    int position = 1;
    for (int i = 0; i < n; ++i) {
      if (points[i] > point) {
        position++;
      } else if (points[i] == point && (mask & (1 << i)) == 0) {
        position++;
      }
    }
    if (position <= k) minimal = min(minimal, count);
  }
  if (minimal != START)
    cout << minimal << endl;
  else
    cout << -1 << endl;
}
