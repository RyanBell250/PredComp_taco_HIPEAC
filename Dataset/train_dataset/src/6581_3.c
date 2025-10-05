#include <bits/stdc++.h>
using namespace std;
struct NODE{
	int val[2][2];
	int lazy[2];
	NODE(){
		memset(val,0,sizeof(val));
		memset(lazy,0,sizeof(lazy));
	}
};
struct LazySegmentTree{
	inline void lazy(int k,int a,int b){
		if( seg[k].lazy[0] ){
			swap(seg[k].val[1][0],seg[k].val[0][0]);
			swap(seg[k].val[0][1],seg[k].val[1][1]);
		}
		if( seg[k].lazy[1] ){
			swap(seg[k].val[0][1],seg[k].val[0][0]);
			swap(seg[k].val[1][1],seg[k].val[1][0]);
		}	
		if( a != b ){
			for(int j = 0 ; j < 2 ; j++){
				seg[k*2].lazy[j] ^= seg[k].lazy[j];
				seg[k*2+1].lazy[j] ^= seg[k].lazy[j]; 
			}
		}
		seg[k].lazy[0] = seg[k].lazy[1] = 0;
	}
	NODE merge(NODE a,NODE b){
		for(int i = 0 ; i < 2 ; i++)
			for(int j = 0 ; j < 2 ; j++)
				a.val[i][j] += b.val[i][j];
		return a;
	}
	int n_;
	vector<NODE> seg;
	
	LazySegmentTree(int N){
		n_ = 1;
		while(n_ < N ) n_ *= 2;
		seg.resize(2*n_,NODE()); 
		init(1,1,n_);
	}
	void init(int k,int a,int b){
		if( a == b ){
			seg[k].val[0][0] = 1;
			return;
		}
		int m = (a+b)/2;
		init(k*2,a,m);
		init(k*2+1,m+1,b);
		seg[k] = merge(seg[k*2],seg[k*2+1]);
	}
	NODE get(int l,int r,int k,int a,int b){
		lazy(k,a,b);
		if( b < l || r < a ) return NODE(); 
		if( l <= a && b <= r ){
			return seg[k];
		}
		int m = (a+b)/2;
		return merge(get(l,r,k*2,a,m),get(l,r,k*2+1,m+1,b)); 
	}
	void add(int l,int r,int v,int k,int a,int b){
		lazy(k,a,b);
		if( b < l || r < a ) return;
		if( l <= a && b <= r ){
			seg[k].lazy[v] ^= 1;
			lazy(k,a,b);
			return;
		}
		int m = (a+b)/2;
		add(l,r,v,k*2,a,m);
		add(l,r,v,k*2+1,m+1,b);
		seg[k] = merge(seg[k*2],seg[k*2+1]);
	}
	inline NODE get(int l,int r){
		return get(l,r,1,1,n_);
	}
	inline void add(int l,int r,int v){
		add(l,r,v,1,1,n_);
	}
	int find(int a,int b){
		int l = 1 , r = n_;
		while( l != r ){
			int m = (l+r) / 2;
			if( get(1,m).val[a][b] > 0 ){
				r = m;
			}else{
				l = m + 1;
			}
		}
		if( get(1,l).val[a][b] == 0 ) return 1e9;
		return l;
	}
	int findR(int a,int b){
		int l = 1 , r = n_;
		while( l != r ){
			int m = (l+r+1) / 2;
			if( get(m,n_).val[a][b] > 0 ){
				l = m;
			}else{
				r = m - 1;
			}
		}
		if( get(l,n_).val[a][b] == 0 ) return 1e9;
		return l;
	}
	string output(int n,int x){
		string s;
		for(int i = 1 ; i <= n ; i++){
			for(int j = 0 ; j < 2 ; j++){
				for(int k = 0 ; k < 2 ; k++){
					if( get(i,i).val[j][k] ){
						s += (x?k:j)+'0';
					}
				}
			}
		}
		return s;
	}
};
int toDec(string s){
	reverse(s.begin(),s.end());
	int ans = 0;
	for(int i = 0 ; i < s.size() ; i++)
		ans = ans * 2 + s[i] - '0';
	return ans;
}
string toBin(int n,int d){
	string s;
	for(int i = 0 ; i < d ; i++){
		s = string(1,'0'+n%2) + s;
		n /= 2;
	}
	return s;
}
int naive(int A,int B){
	int ans = 0;
	int maximum = 0;
	for(int i = A ; i < A+B ; i++){
		int t = __builtin_popcount(i);
		if( t > ans ){
			ans = t;
			maximum = i;
		}
	}
	return maximum;
}


void view(NODE a){
		for(int i = 0 ; i < 2 ; i++)
			for(int j = 0 ; j < 2 ; j++)
				cout << "(" << i << "," << j << "): " << a.val[i][j] << endl;
}
int main(){
	int N;
	string A,B;
	cin >> N >> A >> B;
	reverse(A.begin(),A.end());
	reverse(B.begin(),B.end());
	A = A + string(300010-A.size(),'0');
	B = B + string(300010-B.size(),'0');
	int n = A.size();
	LazySegmentTree tr(A.size());
	for(int i = 0 ; i < A.size() ; i++)
		if( A[i] == '1' ) tr.add(i+1,i+1,0);
	for(int i = 0 ; i < B.size() ; i++)
		if( B[i] == '1' ) tr.add(i+1,i+1,1);
	
	string Q;
	for(int i = 0 ; i < N ; i++){
		char Q[2];
		scanf("%s",Q);
		int x;
		if( Q[0] == 'Q' ){
			int fstOne = min(tr.find(0,1),tr.find(1,1));
			
			
			tr.add(1,fstOne,1); 
			
			
			int P01 = tr.findR(0,1);
			NODE tmp = tr.get(1,n);
			int ans = tmp.val[0][1] + tmp.val[1][1] + tmp.val[1][0];
			if( P01 != 1e9 ){
				NODE tmp = tr.get(P01+1,n);
				int x = tmp.val[0][1] + tmp.val[1][1] + tmp.val[1][0];
				int y = P01 - 1;
				ans = max(ans,x+y);
			}
			int P11 = tr.findR(1,1);
			if( P11 != 1e9 ){
				NODE tmp = tr.get(P11+1,n);
				int x = tmp.val[0][1] + tmp.val[1][1] + tmp.val[1][0];
				int y = P11;
				ans = max(ans,x+y);
			}
			tr.add(1,fstOne,1); 
			
			printf("%d\n",ans);
		}else if( Q[0] == 'A' ){
			scanf("%d",&x);
			A[x] ^= 1;
			tr.add(x+1,x+1,0);
		}else{
			scanf("%d",&x);
			tr.add(x+1,x+1,1);
			B[x] ^= 1;
		}
	}
}
