#include <iostream>
#include <algorithm>
#include <array>
#include <math.h>
#include <set>
#include <stdlib.h>
#include <string>
#include <vector>

#define INT_MAX 2000000000
#define INF 1000000000
#define MOD 1000000007
#define ll long long
#define rep(i,a,b) for(i = (a); i < (b); i++)
#define bitget(a,b) (((a) >> (b)) & 1)

using namespace std;

int i, j, k;

int main() {
	int n;
	int a[100000], b[100000];
	cin >> n;
	rep(i, 0, n)
		cin >> a[i] >> b[i];
	int c[100000] = {};
	int d[100000] = {};
	rep(i, 0, n)
		d[i] = a[i] + b[i];
	sort(d, d + n);
	rep(i, 0, n) {
		c[d[i] / 31] += (1 << (d[i] % 31));
		if (c[d[i]/31] < 0) {
			c[d[i]/31] = c[d[i]/31] & 2147483647;
			c[d[i]/31+ 1] += 1;
		}
	}
	rep(i, 0, 1000000) {
		if (bitget(c[i / 31], i % 31) == 1) {
			cout << i << " " << "0" << endl;
		}
	}

	return 0;
}