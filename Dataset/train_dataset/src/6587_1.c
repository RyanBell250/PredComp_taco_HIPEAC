#include <iostream>
#include <vector>
using namespace std;

#define rep(i,n) for (int i = 0; i < int(n); i++)
#define show(x) #x " = " << x

template <class T, size_t N, size_t M>
struct matrix {
    static matrix<T, N, N> one() {
        matrix<T, N, N> r;
        rep (i,N) r(i,i) = T::one();
        return r;
    }
    vector<vector<T>> a;
    matrix() : a(N, vector<T>(M)) { }
    int size1() const { return N; }
    int size2() const { return M; }
    T& operator()(int i, int j) { return a[i][j]; }
    T  operator()(int i, int j) const { return a[i][j]; }
    template <size_t K>
    matrix<T, N, K> operator*(matrix<T, M, K> const& rhs) {
        matrix<T, N, K> r;
        rep (i,N) rep (j,M) rep (k,K) {
            r(i,k) += a[i][j]*rhs(j,k);
        }
        return r;
    }
    template <size_t K>
    matrix<T, N, K>& operator*=(matrix<T, M, K> const& rhs) {
        return *this = operator*(rhs);
    }
};
    
struct bit {
    static bit one() { return 1; }
    int value;
    bit(int v = 0) : value(v) {}
    bit& operator+=(bit x) { value |= x.value; return *this; }
    bit& operator*=(bit x) { value &= x.value; return *this; }
    bit operator+(bit x) { return value | x.value; }
    bit operator*(bit x) { return value & x.value; }
};

template <class T>
T pow(T x, unsigned int n) {
    T r = T::one();
    while (n > 0) {
        if (n & 1) r *= x;
        x *= x;
        n >>= 1;
    }
    return r;
}    

int main() {
    int N, M, Z;
    int s[100], d[100];
    while (cin >> N >> M >> Z && N > 0) {
        rep (i,M) {
            cin >> s[i] >> d[i];            
            if (s[i] > d[i]) swap(s[i], d[i]);
            s[M+i] = d[i];
            d[M+i] = s[i];
        }

        matrix<bit,   1, 100> v;
        matrix<bit, 100, 100> A;
        matrix<bit, 100,   1> u;
        rep (i,2*M) {
            if (s[i] == 1) u(i,0) = 1;
            if (d[i] == N) v(0,i) = 1;
        }
        rep (i,2*M) rep (j,2*M) {
            if (d[i] == s[j] && s[i] != d[j]) A(j,i) = 1;
        }

   // rep (i,2*M) cout << v(0,i).value << " "; cout << endl;
   // rep (i,2*M) { rep (j,2*M) cout << A(i,j).value << " "; cout << endl; }
   // rep (i,2*M) { cout << u(i,0).value << " "; cout << endl; }

        auto r = v*pow(A,Z-1)*u;
        cout << (r(0,0).value > 0 ? "yes" : "no") << endl;
    }
}