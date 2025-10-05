#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#define llint long long
#define inf 1e18

using namespace std;
typedef pair<llint, llint> P;
typedef pair<P, llint> E;

struct SegTree{
	int size;
	vector<llint> seg;
	
	SegTree(){}
	SegTree(int size){
		this->size = size;
		seg.resize(1<<(size+1));
	}
	
	void init()
	{
		for(int i = 0; i < (1<<(size+1)); i++) seg[i] = -inf;
	}
	
	void update(int i, llint val)
	{
		i += (1 << size);
		seg[i] = val;
		while(i > 1){
			i /= 2;
			seg[i] = max(seg[i*2], seg[i*2+1]);
		}
	}

	llint query(int a, int b, int k, int l, int r)
	{
		if(b < l || r < a) return -inf;
		if(a <= l && r <= b) return seg[k];
		llint lval = query(a, b, k*2, l, (l+r)/2);
		llint rval = query(a, b, k*2+1, (l+r)/2+1, r);
		return max(lval, rval);
	}
	llint query(int a, int b)
	{
		if(a > b) return -inf;
		return query(a, b, 1, 0, (1<<size)-1);
	}
};

llint n, Q;
llint a[100005], b[100005], c[100005], d[100005];
llint x[100005], y[100005], z[100005], w[100005];
bool ans[100005];

vector<llint> xvec[100005], avec[100005];
vector<P> cvec;
SegTree seg(17);
llint cpos[100005];

void calc(llint l, llint r)
{
	if(r-l+1 <= 1) return;
	llint m = (l+r)/2;
	
	vector<E> vec;
	for(int i = l; i <= m; i++){
		for(int j = 0; j < xvec[i].size(); j++){
			int id = xvec[i][j];
			vec.push_back(E(P(y[id], 2), id));
		}
	}
	for(int i = m+1; i <= r; i++){
		for(int j = 0; j < avec[i].size(); j++){
			int id = avec[i][j];
			vec.push_back(E(P(a[id], 3), id));
			vec.push_back(E(P(b[id], 1), id));
		}
	}
	sort(vec.begin(), vec.end());
	
	for(int i = 0; i < vec.size(); i++){
		int type = vec[i].first.second, id = vec[i].second;
		if(type == 1) seg.update(cpos[id], -inf);
		if(type == 3) seg.update(cpos[id], d[id]);
		if(type == 2){
			llint lb = upper_bound(cvec.begin(), cvec.end(), P(z[id], inf)) - cvec.begin();
			llint ub = lower_bound(cvec.begin(), cvec.end(), P(w[id], 0)) - cvec.begin() - 1;
			if(seg.query(lb, ub) > w[id]) ans[id] = true;
		}
	}
	calc(l, m), calc(m+1, r);
}

int main(void)
{
	cin >> n >> Q;
	for(int i = 1; i <= n; i++) cin >> a[i] >> b[i] >> c[i] >> d[i];
	for(int i = 1; i <= Q; i++) cin >> x[i] >> y[i] >> z[i] >> w[i];
	
	for(int i = 1; i <= n; i++) avec[a[i]].push_back(i);
	for(int i = 1; i <= Q; i++) xvec[x[i]].push_back(i);
	
	for(int i = 1; i <= n; i++) cvec.push_back(P(c[i], i));
	sort(cvec.begin(), cvec.end());
	for(int i = 0; i < cvec.size(); i++) cpos[cvec[i].second] = i;
	
	seg.init();
	
	calc(1, 100000);
	for(int i = 1; i <= Q; i++){
		if(ans[i]) cout << "Yes" << endl;
		else cout << "No" << endl;
	}
	
	return 0;
}
