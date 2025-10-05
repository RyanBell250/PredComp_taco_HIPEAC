#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cstring>
#include <cctype>
#include <cassert>
#include <limits>
#include <functional>
#define rep(i,n) for(int (i)=0;(i)<(int)(n);++(i))
#define rer(i,l,u) for(int (i)=(int)(l);(i)<=(int)(u);++(i))
#define reu(i,l,u) for(int (i)=(int)(l);(i)<(int)(u);++(i))
#if defined(_MSC_VER) || __cplusplus > 199711L
#define aut(r,v) auto r = (v)
#else
#define aut(r,v) __typeof(v) r = (v)
#endif
#define each(it,o) for(aut(it, (o).begin()); it != (o).end(); ++ it)
#define all(o) (o).begin(), (o).end()
#define pb(x) push_back(x)
#define mp(x,y) make_pair((x),(y))
#define mset(m,v) memset(m,v,sizeof(m))
#define INF 0x3f3f3f3f
#define INFL 0x3f3f3f3f3f3f3f3fLL
using namespace std;
typedef vector<int> vi; typedef pair<int,int> pii; typedef vector<pair<int,int> > vpii; typedef long long ll;
template<typename T, typename U> inline void amin(T &x, U y) { if(y < x) x = y; }
template<typename T, typename U> inline void amax(T &x, U y) { if(x < y) x = y; }
struct Date {
	typedef int Integer; Integer offset;
	static const int days[12], dayscumsum[13], dayscumsuml[13];
	struct YMD {
		Integer Y; int M, D;
		YMD(Integer Y_, int M_, int D_): Y(Y_), M(M_), D(D_) { }
	};
	Date(): offset(0) { }
	explicit Date(Integer offset_): offset(offset_) { }
	Date(Integer Y, int M, int D): offset(toOffset(Y, M, D)) { }
	static bool isLeapYear(Integer Y) {
		return Y % 4 == 0 && (Y % 100 != 0 || Y % 400 == 0);
	}
	static int getDays(Integer Y, int M) {
		return days[M-1] + (M == 2 && isLeapYear(Y));
	}
	static Integer toOffset(Integer y, int m, int d) {
		if(m <= 2) y --, m += 12;
		return y*365 + div(y,4) - div(y,100) + div(y,400) + 153*(m+1)/5 + d - 428;
	}
	void getYearMonthDay(Integer &Y, int &M, int &D) const {
		Integer a = offset - 1, quadcent = div(a, 146097);
		Integer b = a - quadcent * 146097, cent = min(b / 36524, Integer(3));
		Integer c = b - cent * 36524, quad = c / 1461;
		Integer d = c - quad * 1461, y = min(d / 365, Integer(3));
		Y = quadcent * 400 + cent * 100 + quad * 4 + y + 1;
		int yd = (int)(d - y * 365 + 1);
		fromOrdinalDate(Y, yd, M, D);
	}
	static void fromOrdinalDate(const Integer &Y, int yd, int &M, int &D) {
		const int *cumsum = isLeapYear(Y) ? dayscumsuml : dayscumsum;
		M = upper_bound(cumsum, cumsum+13, yd - 1) - cumsum;
		D = yd - cumsum[M-1];
	}
	Integer getYear() const { Integer Y; int M, D; getYearMonthDay(Y, M, D); return Y; }
	int getMonth() const { Integer Y; int M, D; getYearMonthDay(Y, M, D); return M; }
	int getDay() const { Integer Y; int M, D; getYearMonthDay(Y, M, D); return D; }
	int getDayOfWeek() const { return offset % 7; }
	Date operator+(Integer that) const { return Date(offset + that); }
	Date &operator+=(Integer that) { offset += that; return *this; }
	Integer operator-(const Date &that) const { return offset - that.offset; }
	bool operator==(const Date &that) const { return offset == that.offset; }
	bool operator!=(const Date &that) const { return offset != that.offset; }
	bool operator< (const Date &that) const { return offset <  that.offset; }
	bool operator> (const Date &that) const { return offset >  that.offset; }
	bool operator<=(const Date &that) const { return offset <= that.offset; }
	bool operator>=(const Date &that) const { return offset >= that.offset; }
	friend ostream &operator<<(ostream &o, const Date &that) {
		Date::Integer Y; int M, D; that.getYearMonthDay(Y, M, D);
		return o << Y << "/" << M << "/" << D;
	}
private:
	static inline Integer div(Integer x, int y) { return x / y - (x % y != 0 && x < 0); };
};
const int Date::days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
const int Date::dayscumsum[13] = {0,31,59,90,120,151,181,212,243,273,304,334,365};
const int Date::dayscumsuml[13] = {0,31,60,91,121,152,182,213,244,274,305,335,366};
int DIGITAL_PTN[10] = {
	1|2|4|16|32|64,
	4|32,
	1|4|8|16|64,
	1|4|8|32|64,
	2|4|8|32,
	1|2|8|32|64,
	1|2|8|16|32|64,
	1|4|32,
	1|2|4|8|16|32|64,
	1|2|4|8|32|64
};
int popcnt[128];
int getNum(int x, int n, int broken[]) {
	int res = 0;
	rep(i, n) {
		int d = x % 10;
		res += popcnt[DIGITAL_PTN[d] & ~broken[n - 1 - i]];
		x /= 10;
	}
	return res;
}
int main() {
	mset(popcnt, 0);
	rep(i, 1 << 7) rep(j, 7) popcnt[i] += i >> j & 1;
	int N, K;
	scanf("%d%d", &N, &K);
	int broken[14] = {};
	rep(i, K) {
		int p, q;
		scanf("%d%d", &p, &q);
		broken[p] |= 1 << q;
	}
	vi dateCnt(N+1, 0);
	for(Date d(0, 1, 1); ; d += 1) {
		int Y, M, D;
		d.getYearMonthDay(Y, M, D);
		if(Y == 10000) break;
		int num = 0;
		num += getNum(Y, 4, broken + 0);
		num += getNum(M, 2, broken + 4);
		num += getNum(D, 2, broken + 6);
		if(num <= N)
			++ dateCnt[num];
	}
	long long ans = 0;
	rer(h, 0, 23) rer(m, 0, 59) rer(s, 0, 59) {
		int num = 0;
		num += getNum(h, 2, broken + 8);
		num += getNum(m, 2, broken + 10);
		num += getNum(s, 2, broken + 12);
		if(num <= N)
			ans += dateCnt[N - num];
	}
	printf("%lld\n", ans);
	return 0;
}
