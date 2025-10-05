#include <bits/stdc++.h>
using namespace std;

struct StronglyConnectedComponent {
	const int V;
	vector<vector<int>> G, revG;
	vector<int> id;
	StronglyConnectedComponent(const int V) :
		V(V),
		G(vector<vector<int>>(V, vector<int>())),
		revG(vector<vector<int>>(V, vector<int>())),
		id(vector<int>(V))
		{}
	void addEdge(int from, int to) {
		G[from].push_back(to);
		revG[to].push_back(from);
	}
	void build() {
		vector<bool> used(V, false);
		stack<int> st;
		for(int from = 0; from < V; ++from) {
			if(not used[from]) {
				dfs(from, used, st);
			}
		}
		int num = 0;
		while(st.size()) {
			int from = st.top();
			st.pop();
			if(used[from]) {
				revdfs(from, num, used);
				++num;
			}
		}
	}
	void dfs(int from, vector<bool> &used, stack<int> &st) {
		used[from] = true;
		for(int to : G[from]) {
			if(not used[to]) {
				dfs(to, used, st);
			}
		}
		st.push(from);
	}
	void revdfs(int from, int num, vector<bool> &used) {
		used[from] = false;
		id[from] = num;
		for(int to : revG[from]) {
			if(used[to]) {
				revdfs(to, num, used);
			}
		}
	}
	int get(int x) {
		return id[x];
	}
};

struct TwoSatisfiability {
	const int V;
	vector<vector<int>> G;
	vector<bool> pos;
	StronglyConnectedComponent scc;
	TwoSatisfiability(const int V) :
		V(V),
		G(vector<vector<int>>(2 * V, vector<int>())),
		pos(vector<bool>(2 * V)),
		scc(StronglyConnectedComponent(2 * V))
		{}
	inline int NOT(int A) {
		return (A + V) % (2 * V);
	}
	// A -> B <=> not B -> not A
	inline void addIF(int A, bool Apos, int B, bool Bpos) {
		if(not Apos) A = NOT(A);
		if(not Bpos) B = NOT(B);
		scc.addEdge(A, B); // A -> B
		scc.addEdge(NOT(B), NOT(A)); // not B -> not A
	}
	// A <=> (not A -> A)
	void addUNARY(int A, bool Apos) {
		addIF(A, not Apos, A, Apos); // not A -> A
	}
	// A or B <=> not A -> B
	void addOR(int A, bool Apos, int B, bool Bpos) {
		addIF(A, not Apos, B, not Bpos); // not A -> B
	}
	// not(A and B) => A -> not B
	void addNAND(int A, bool Apos, int B, bool Bpos) {
		addIF(A, Apos, B, not Bpos); // A -> not B
	}
	// A xor B <=> not(A and B) and not(not A and not B)
	void addXOR(int A, bool Apos, int B, bool Bpos) {
		addNAND(A, Apos, B, Bpos); // not(A and B)
		addNAND(A, not Apos, B, not Bpos); // not(not A and not B)
	}
	// not(A xor B) <=> A xor not B
	void addXNOR(int A, bool Apos, int B, bool Bpos) {
		addXOR(A, Apos, B, not Bpos); // A xor not B
	}
	bool solve() {
		scc.build();
		for(int i = 0; i < V; ++i) {
			if(scc.get(i) == scc.get(i + V)) {
				return false;
			}
			pos[i] = (scc.get(i) > scc.get(i + V));
		}
		return true;
	}
	bool get(int x) {
		return pos[x];
	}
};

int main() {
	int n; cin >> n;
	int x, a, o; cin >> x >> a >> o;
	const int MAX = 1 << (n + 1);
	TwoSatisfiability sat(MAX);
	for(int i = 0; i < MAX; ++i) {
		for(int j = i; j < MAX; ++j) {
			if((i ^ j) == x) {
				sat.addXOR(i, true, j, true);
			}
			if((i & j) == a) {
				sat.addNAND(i, true, j, true);
			}
			if((i | j) == o) {
				sat.addNAND(i, true, j, true);
			}
		}
	}
	if(not sat.solve()) {
		cout << "No" << '\n';
		return 0;
	}
	cout << "Yes" << '\n';
	vector<int> ans;
	for(int i = 0; i < MAX; ++i) {
		if(sat.get(i)) ans.push_back(i);
	}
	int sz = MAX >> 1;
	for(int i = 0; i < sz; ++i) {
		cout << ans[i] << (i != sz - 1 ? ' ' : '\n');
	}
	return 0;
}

