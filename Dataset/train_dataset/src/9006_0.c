#include <iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<math.h>
using namespace std;
typedef long long ll;
#define int long long
typedef vector<int> VI;
typedef pair<int, int> pii;
#define fore(i,a) for(auto &i:a)
#define REP(i,n) for(int i=0;i<n;i++)
#define eREP(i,n) for(int i=0;i<=n;i++)
#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define eFOR(i,a,b) for(int i=(a);i<=(b);++i)
#define SORT(c) sort((c).begin(),(c).end())
#define rSORT(c) sort((c).rbegin(),(c).rend())
#define LB(x,a) lower_bound((x).begin(),(x).end(),(a))
#define UB(x,a) upper_bound((x).begin(),(x).end(),(a))
#define INF 1000000000
#define LLINF 9223372036854775807
#define mod 1000000007
//vector<vector<int> > dp;
//vector<vector<vector<int> > > vvvi;
//dp=vector<vector<int> >(N, vector<int>(M,0));
//vector<pair<int,int> > v;
//v.push_back(make_pair(x,y));
//priority_queue<int,vector<int>, greater<int> > q2;

class UnionFind {
public:
	vector<int> Parent;

	UnionFind(int N) {
		Parent = vector<int>(N, -1);
	}

	int root(int A) {
		if (Parent[A] < 0)return A;
		return Parent[A] = root(Parent[A]);
	}

	int size(int A) {
		return -Parent[root(A)];
	}

	bool unite(int A, int B) {
		A = root(A);
		B = root(B);
		if (A == B)
			return false;

		if (size(A) < size(B))
			swap(A, B);

		Parent[A] += Parent[B];
		Parent[B] = A;

		return true;
	}

	bool same(int A, int B) {
		if (root(A) == root(B))
			return true;
		else
			return false;
	}
};

signed main(){
cin.tie(0);
ios::sync_with_stdio(false);

	int N;
	const int C = 1e+5;
	cin >> N;
	UnionFind uni(222222);
	VI A(N),B;
	REP(i, N) {
		cin >> A[i];
		int n = A[i];
		A[i] += C;
		for (int j = 1; j*j <= n; ++j){
			if (n%j == 0) {
				if(j!=1)uni.unite(j, A[i]);
				if (j*j != n)uni.unite(n / j, A[i]);

			}
		}
	}
	B = A;
	SORT(B);

	REP(i, N) {
		if (A[i] != B[i]) {
			if (uni.root(A[i]) != uni.root(B[i])) {
				cout << 0 << endl;
				return 0;
			}
		}
	}
	cout << 1 << endl;

	return 0;
}


