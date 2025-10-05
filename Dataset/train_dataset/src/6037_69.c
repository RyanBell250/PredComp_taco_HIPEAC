#include <bits/stdc++.h>
template <typename T>
void UpdateMin(T& a, const T b) {
  a = std::min(a, b);
}
template <typename T>
void UpdateMax(T& a, const T b) {
  a = std::max(a, b);
}
static const long double Eps = 1.0e-09;
template <typename T>
bool IsEqual(const T a, const T b) {
  return std::abs(a - b) < Eps;
}
template <typename T>
bool IsGreater(const T a, const T b) {
  return a > b + Eps;
}
template <typename T>
bool IsLess(const T a, const T b) {
  return a + Eps < b;
}
template <typename T>
std::string ToStr(const T& val) {
  std::ostringstream ostr;
  ostr << val;
  return ostr.str();
}
template <typename T>
bool FromStr(const std::string& str, T& val) {
  std::istringstream istr(str);
  istr >> val;
  return !!istr;
}
template <typename T>
std::istream& operator>>(std::istream& ist, std::vector<T>& data) {
  ;
  for (size_t i = 0; i < data.size(); i++) {
    ist >> data[i];
  }
  return ist;
}
template <typename T>
T Read(std::istream& ist) {
  ;
  T val;
  ist >> val;
  return val;
}
template <typename T>
std::ostream& operator<<(std::ostream& ost, const std::vector<T>& data) {
  for (size_t i = 0; i < data.size(); i++) {
    if (i != 0) {
      ost << ' ';
    }
    ost << data[i];
  }
  return ost;
}
template <size_t id>
class StopWatch {};
const size_t Inf = 999999;
std::vector<std::vector<size_t> > GetDists(
    const std::vector<std::vector<size_t> >& a) {
  const size_t n = a.size();
  std::vector<std::vector<size_t> > ds(n, std::vector<size_t>(n, Inf));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      if (a[i][j] != 0) ds[i][j] = a[i][j];
    }
  }
  for (size_t k = 0; k < n; k++) {
    for (size_t i = 0; i < n; i++) {
      for (size_t j = 0; j < n; j++) {
        ds[i][j] = std::min(ds[i][j], ds[i][k] + ds[k][j]);
      }
    }
  }
  return ds;
}
bool Solve(std::istream& ist, std::ostream& ost, const bool multipleTestMode) {
  StopWatch<1> sw;
  (void)sw;
  size_t n, m;
  ist >> n >> m;
  if (multipleTestMode && !ist) return false;
  std::vector<std::vector<size_t> > train(n, std::vector<size_t>(n));
  for (size_t i = 0; i < m; i++) {
    size_t b, e;
    ist >> b >> e;
    --b;
    --e;
    train[b][e] = 1;
    train[e][b] = 1;
  }
  std::vector<std::vector<size_t> > bus(n, std::vector<size_t>(n));
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      bus[i][j] = 1 - train[i][j];
    }
    bus[i][i] = 0;
    train[i][i] = 0;
  }
  const std::vector<std::vector<size_t> > td = GetDists(train);
  const std::vector<std::vector<size_t> > bd = GetDists(bus);
  const size_t pathB = bd[0][n - 1];
  const size_t pathT = td[0][n - 1];
  if ((pathB == Inf) || (pathT == Inf)) {
    ost << "-1" << std::endl;
  } else {
    ost << std::max(pathB, pathT) << std::endl;
  }
  return multipleTestMode;
}
int main(int argc, const char* argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::istream* ist = &std::cin;
  std::ostream* ost = &std::cout;
  std::unique_ptr<std::istream> fileInput;
  if (argc > 1) {
    fileInput.reset(new std::ifstream(argv[1]));
    if (!(*fileInput)) {
      std::cout << "File not found: " << argv[1] << std::endl;
    }
    ist = fileInput.get();
  }
  Solve(*ist, *ost, false);
}
