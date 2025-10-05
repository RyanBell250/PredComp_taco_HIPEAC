#include "bits/stdc++.h"
using namespace std;
const int SIZE = 299;

const int dx[] = { -1,0,1,0,0 };
const int dy[] = { 0,1,0,-1,0 };
struct but{
	vector<shared_ptr<but>>chs;
	char c;
	but(char c_) :chs(), c(c_) {
	}
	pair<int,vector<string>>getst() {
		if (chs.empty()) {
			return make_pair(0,vector<string>(1, string(1, c)));
		}
		else if (chs.size() == 1) {
			auto p = chs[0]->getst();
			auto chst = p.second;
			int chroot = p.first;
			vector<string>nst(chst.size() + 2,string( chst[0].size(),' '));
			for (int i = 0;i<nst.size()-2; ++i) {
				for (int j = 0; j < nst[0].size(); ++j) {
					nst[i][j] = chst[i][j];
				}
			}
			nst[nst.size() - 2][chroot] = '-';
			nst[nst.size() - 1][chroot] = c;
			return make_pair(chroot, nst);
		}
		else {
			auto p1 = chs[0]->getst();
			auto p2 = chs[1]->getst();
			int chroot1 = p1.first;
			int chroot2 = p2.first;
			auto chst1 = p1.second;
			auto chst2 = p2.second;
			if (chst1.size() < chst2.size()) {
				int n = chst2.size() - chst1.size();
				while(n--){
					chst1.insert(chst1.begin(), string(chst1[0].size(), ' '));
				}
			}
			else if (chst1.size() > chst2.size()) {
				int n = chst1.size() - chst2.size();
				while(n--){
					chst2.insert(chst2.begin(), string(chst2[0].size(), ' '));
				}
			}
			int bet = 1;
			while (bet++) {
				int loff = bet / 2;
				int roff = (bet + 1) / 2;
				vector<string>nst(chst1.size() + 2, string(SIZE, ' '));
				const int center = SIZE/2;
				const int lm = center - loff;
				const int ll = lm - chroot1;
				const int lr = ll + chst1[0].size();
				const int rm = center + roff;
				const int rl = rm - chroot2;
				const int rr = rl + chst2[0].size();

				bool ok = true;
				for (int i = 0; i < nst.size() - 2; ++i) {
					for (int j = rl; j < rr; ++j) {
						if (chst2[i][j-rl] != ' ') {
							for (int way = 0; way < 5; ++way) {
								int ay = i + dy[way];
								int ax = j + dx[way];
								if (ay >= 0 && ay < chst1.size() && ax >= ll&&ax < lr) {
									if (chst1[ay][ax - ll] != ' ')ok = false;
								}
							}
						}
					}
				}
				if (!ok) {
					continue;
				}
				for (int i = 0; i < nst.size() - 2; ++i) {
					for (int j = ll; j < lr; ++j) {
						nst[i][j] = chst1[i][j - ll];
					}
					for (int j = rl; j < rr; ++j) {
						if (nst[i][j] == ' ') {
							nst[i][j] = chst2[i][j - rl];
						}
					}

				}
				{
					int i = nst.size() - 2;
					for (int j = lm; j <= rm; ++j) {
						nst[i][j] = '-';
					}
				}
				nst[nst.size() - 1][center] = c;
				while (1) {
					bool flag = true;
					for (int i = 0; i < nst.size(); ++i) {
						if (nst[i][0] != ' ')flag = false;
					}
					if (!flag)break;
					for (auto&ast:nst) {
						ast.erase(ast.begin());
					}
				}
				while (1) {
					bool flag = true;
					for (int i = 0; i < nst.size(); ++i) {
						if (nst[i].back() != ' ')flag = false;
					}
					if (!flag)break;
					for (auto&ast : nst) {
						ast.pop_back();
					}
				}
				int aa;
				for (int j = 0; j < nst[nst.size() - 1].size(); ++j) {
					if (nst[nst.size() - 1][j] != ' ') {
						aa = j;
						break;
					}
				}
				return make_pair(aa, nst);
			}
		}
	}
};
shared_ptr<but>mkbut(string st,int&a) {
	if (isalpha(st[a])) {
		shared_ptr<but>bt(make_shared<but>(st[a]));
		a++;
		if (st.size() == a || st[a] == ')'||st[a]==',') {
			return bt;
		}
		else if (st[a] == '(') {
			a++;
			shared_ptr<but>ch1(mkbut(st, a));
			bt->chs.push_back(ch1);
			if (st[a] == ')') {
				a++;
				return bt;
			}
			else {
				assert(st[a] == ',');
				a++;
				shared_ptr<but>ch2(mkbut(st, a));
				bt->chs.push_back(ch2);
				assert(st[a] == ')');
				a++;
				return bt;
			}
		}
	}
	else {
		assert(false);
	}
}

void solve(string st) {
	int a = 0;
	shared_ptr<but>head(mkbut(st, a));
	auto p = head->getst();
	for (int i = 0; i < p.second.size(); ++i) {
		while (!p.second[i].empty()&&p.second[i].back() == ' ')p.second[i].pop_back();
		cout << p.second[i] << endl;
	}
}

int main() {
	string nst;
	int num = 1;
	while (1) {
		string st; cin >> st;
		nst += st;
		if (nst.back() == ';'||nst.back()=='.') {
			bool flag = nst.back() == '.';
			nst.pop_back();
			cout << num << ":" << endl;
			solve(nst);
			num++;
			if (flag)break;
			nst.clear();
		}
	}
	return 0;
}