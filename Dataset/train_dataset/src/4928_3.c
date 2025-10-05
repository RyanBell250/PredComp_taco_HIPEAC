#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

vector<int*> dat;
int r, c;

int topow2(int a){
	while( a & (a - 1) ) {
		a += a & -a;
	}
	return a;
}


int query2(int c1, int c2, int kr, int k = 0, int left = 0, int right = c){
	if( right <= c1 || c2 <= left ) return INT_MAX;
	if( c1 <= left && right <= c2 ){
		return dat[kr][k];
	}
	
	int mid = (left + right) / 2;
	int vl = query2(c1, c2, kr, k * 2 + 1, left, mid);
	int vr = query2(c1, c2, kr, k * 2 + 2, mid, right);
	return min(vl, vr);
}

int query1(int r1, int r2, int c1, int c2, int k = 0, int left = 0, int right = r){
	if( right <= r1 || r2 <= left ) return INT_MAX;
	if( r1 <= left && right <= r2 ) return query2(c1, c2, k);
	
	int mid = (left + right) / 2;
	int vl = query1(r1, r2, c1, c2, k * 2 + 1, left, mid);
	int vr = query1(r1, r2, c1, c2, k * 2 + 2, mid, right);
	return min(vl, vr);
}


int main(){
	int r0, c0, q;
	int r1, c1, r2, c2;
	
	vector<int> buf(8388608);

	while( scanf("%d%d%d", &r0, &c0, &q), r0 != 0 ){
		r = topow2(r0);
		c = topow2(c0);

		dat.resize(r * 2 - 1);
		for(int i = r * 2 - 2; i >= 0; --i){
			dat[i] = &buf[i * (c * 2 - 1)];
			fill(dat[i], dat[i] + (c * 2 - 1), INT_MAX);
		}

		vector<int> datr(c * 2 - 1, INT_MAX);

		for(int i = 0; i < r0; ++i){
			for(int j = 0; j < c0; ++j){
				scanf("%d", &datr[j + c - 1]);
			}
			
			for(int j = c - 2; j >= 0; --j){
				datr[j] = min(datr[j * 2 + 1], datr[j * 2 + 2]);
			}
			copy(datr.begin(), datr.end(), dat[i + r - 1]);
		}

		for(int j = 0; j < c * 2 - 1; ++j){
			for(int i = r - 2; i >= 0; --i){
				dat[i][j] = min(dat[i * 2 + 1][j], dat[i * 2 + 2][j]);
			}
		}

		for(int i = 0; i < q; ++i){
			scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
			printf("%d\n", query1(r1, r2 + 1, c1, c2 + 1) );
		}
	}
}