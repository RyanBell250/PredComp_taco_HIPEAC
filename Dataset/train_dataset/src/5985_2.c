
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <bitset>
#include <stack>
#include <algorithm>
#include <complex>
#include <numeric>
#include <functional>
#include <random>
#include <regex>
using namespace std;
typedef long long ll;typedef unsigned long long ull;typedef long double ld;
#define ALL(c) c.begin(),c.end()
#define IN(l,v,r) (l<=v && v < r)
template<class T> void UNIQUE(T& v){
	sort(ALL(v));
	v.erase(unique(ALL(v)),v.end());
}
#define DUMP(x) cerr << #x <<" = " << (x)
#define LINE() cerr<< " (L" << __LINE__ << ")"
#define range(i,l,r) for(int i=(int)l;i<(int)(r);i++)
template<typename T1,typename T2> istream& operator >> (istream& is,pair<T1,T2>& p){return is>>p.first>>p.second;}
template<typename T1> istream& operator >> (istream& is,tuple<T1>& t){return is >> get<0>(t);}
template<typename T1,typename T2> istream& operator >> (istream& is,tuple<T1,T2>& t){return is >> get<0>(t) >> get<1>(t);}
template<typename T1,typename T2,typename T3> istream& operator >> (istream& is,tuple<T1,T2,T3>& t){return is >>get<0>(t)>>get<1>(t)>>get<2>(t);}
template<typename T1,typename T2,typename T3,typename T4> istream& operator >> (istream& is,tuple<T1,T2,T3,T4>& t){return is >> get<0>(t)>>get<1>(t)>>get<2>(t)>>get<3>(t);}
template<typename T> istream& operator >> (istream& is,vector<T>& as){range(i,0,as.size())is >>as[i];return is;}
template<typename T> ostream& operator << (ostream& os, const set<T>& ss){for(auto a:ss){if(a!=ss.begin())os<<" "; os<<a;}return os;}
template<typename T1,typename T2> ostream& operator << (ostream& os, const pair<T1,T2>& p){return os<<p.first<<" "<<p.second;}
template<typename K,typename V> ostream& operator << (ostream& os, const map<K,V>& m){bool isF=true;for(auto& p:m){if(!isF)os<<endl;os<<p;isF=false;}return os;}
template<typename T1> ostream& operator << (ostream& os, const tuple<T1>& t){return os << get<0>(t);}
template<typename T1,typename T2> ostream& operator << (ostream& os, const tuple<T1,T2>& t){return os << get<0>(t)<<" "<<get<1>(t);}
template<typename T1,typename T2,typename T3> ostream& operator << (ostream& os, const tuple<T1,T2,T3>& t){return os << get<0>(t)<<" "<<get<1>(t)<<" "<<get<2>(t);}
template<typename T1,typename T2,typename T3,typename T4> ostream& operator << (ostream& os, const tuple<T1,T2,T3,T4>& t){return os << get<0>(t)<<" "<<get<1>(t)<<" "<<get<2>(t)<<" "<<get<3>(t);}
template<typename T> ostream& operator << (ostream& os, const vector<T>& as){range(i,0,as.size()){if(i!=0)os<<" "; os<<as[i];}return os;}
template<typename T> ostream& operator << (ostream& os, const vector<vector<T>>& as){range(i,0,as.size()){if(i!=0)os<<endl; os<<as[i];}return os;}
struct Edge{
	char c;int f,t;
};
class NFA{
public:
	int N;
	vector<Edge> es;
	vector<vector<int>> f_cache, t_cache;
	int s,t;
	NFA(int N = 0):N(N),s(0),t(1){
		f_cache = t_cache = vector<vector<int>>(N);
	}
	void add_edge(char c,int f,int t){
		int eid = es.size();
		es.push_back({c,f,t});
		f_cache[f].push_back(eid);t_cache[t].push_back(eid);
	}
	void disjoint(NFA& b){
		f_cache.resize(N+b.N);
		t_cache.resize(N+b.N);
		for(Edge& e:b.es){
			e.f+=N; e.t+=N;
			int eid = es.size();
			es.push_back(e);
			f_cache[e.f].push_back(eid); t_cache[e.t].push_back(eid);
		}
		N +=b.N;
	}
	void Union(NFA b){
		int as = s,at = t,aN = N, bs = b.s,bt = b.t, bN = b.N;
		disjoint(b);
		NFA sp = NFA(1);
		disjoint(sp);
		NFA tp = NFA(1);
		disjoint(tp);
		add_edge('-',aN+bN,as);
		add_edge('-',aN+bN,aN + bs);
		add_edge('-',at,aN+bN+1);
		add_edge('-',aN+bt,aN+bN+1);
		s = aN+bN; t = aN + bN +1;
	}
	void Concat(NFA b){
		int as = s,at = t,aN = N, bs = b.s,bt = b.t, bN = b.N;
		disjoint(b);
		add_edge('-',at,aN + bs);
		s = as;t = aN + bt;
	}
	void Star(){
		NFA sp = NFA(1);
		disjoint(sp);
		add_edge('-',N-1,s);
		add_edge('-',t,N-1);
		s = t = N-1;
	}
	static NFA pattern(string& s,int& i,int e){
		NFA p = simple(s,i,e);
		while(i < e && s[i]=='|'){
			i++;
			p.Union(simple(s,i,e));
		}
		return p;
	}
	static NFA simple(string& s,int& i,int e){
		NFA p = basic(s,i,e);
		while(i < e && s[i]!='|'){
			p.Concat(basic(s,i,e));
		}
		return p;
	}
	static NFA basic(string& s,int& i,int e){
		NFA p = elementary(s,i,e);
		if(i < (int)s.size() && s[i]=='*'){
			i++;
			p.Star();
		}
		return p;
	}
	static NFA elementary(string& s,int& i,int e){
		NFA p;
		if(s[i]=='('){
			i++; 
			int d=1;
			for(int j=i;j<e;j++){
				if(s[j]=='(') d++;
				if(s[j]==')') d--;
				if(d==0){
					e = j;break;
				}
			}
			p = pattern(s,i,e);
			i++; 
		}else{
			p = NFA(2);
			p.add_edge(s[i],p.s,p.t);
			i++;
		}
		return p;
	}
};
int rc = 0;
class Main{
	public:
	int h,w;
	vector<string> tmp,res;
	vector<NFA> NFAs;
	vector<vector<int>> stats;
	vector<vector<vector<int>>> reachable;
	vector<vector<vector<vector<int>>>> trans;
	void create_reachable(int nind){
		NFA& nfa = NFAs[nind];
		queue<pair<int,int>> que; que.push({nfa.t,0});
		reachable[nind][nfa.t][0] = true;
		while(!que.empty()){
			int t,d;tie(t,d) = que.front();que.pop();
			for(int eid:nfa.t_cache[t]){
				Edge& e = nfa.es[eid];
				if(e.c=='-'){
					if(!reachable[nind][e.f][d]){
						reachable[nind][e.f][d] = true;
						que.push({e.f,d});
					}
				}else{
					if(d+1 <reachable[nind][e.f].size() && !reachable[nind][e.f][d+1]){
						reachable[nind][e.f][d+1] = true;
						que.push({e.f,d+1});
					}
				}
			}
		}
	}
	void create_trans(int nind,int st,char nc){
		NFA& nfa = NFAs[nind];
		vector<bool> passed(nfa.N);
		passed[st] = true;
		{
			queue<int> que;
			range(i,0,passed.size())if(passed[i])que.push(i);
			while(!que.empty()){
				int s = que.front();que.pop();
				for(int eid : nfa.f_cache[s])if(nfa.es[eid].c =='-' && !passed[nfa.es[eid].t]){
					passed[nfa.es[eid].t] = true;
					que.push(nfa.es[eid].t);
				}
			}
		}
		{
			vector<bool> npassed(nfa.N);
			range(s,0,nfa.N)if(passed[s]) for(int eid : nfa.f_cache[s]){
				char c = nfa.es[eid].c;
				int t = nfa.es[eid].t;
				if(nc==c || c=='.') npassed[t] = true;
			}
			passed = npassed;
		}
		{
			queue<int> que;
			range(i,0,passed.size())if(passed[i])que.push(i);
			while(!que.empty()){
				int s = que.front();que.pop();
				for(int eid : nfa.f_cache[s])if(nfa.es[eid].c =='-' && !passed[nfa.es[eid].t]){
					passed[nfa.es[eid].t] = true;
					que.push(nfa.es[eid].t);
				}
			}
		}
		range(s,0,passed.size())if(passed[s]){
			bool exeps = false, alleps = true;
			for(int eid : nfa.f_cache[s]){
				exeps |= nfa.es[eid].c=='-';
				alleps &= nfa.es[eid].c=='-';
			}
			if(exeps && alleps && nfa.t != s)continue; 
			trans[nind][st][nc-'A'].push_back(s);
		}
	}
	void dfs(int y,int x,int c){
		if(rc>1)return;
		if(y==h){
			rc+=c;
			res = tmp;
			return;
		}
		vector<vector<int>> ynstats(26),xnstats(26);
		for(char nc = 'A';nc <= 'Z'; nc++){
			for(int s:stats[y])for(int t:trans[y][s][nc-'A'])ynstats[nc-'A'].push_back(t);
			UNIQUE(ynstats[nc-'A']);
		}
		for(char nc = 'A';nc <= 'Z'; nc++){
			for(int s:stats[h+x])for(int t:trans[h+x][s][nc-'A'])xnstats[nc-'A'].push_back(t);
			UNIQUE(xnstats[nc-'A']);
		}
		vector<int> gid(26);iota(ALL(gid),0);
		for(char c1='A'; c1 <= 'Z';c1++){
			for(char c2='A'; c2 < c1;c2++)if(gid[c2-'A']==c2-'A'){
				if(ynstats[c1-'A'].size() == ynstats[c2-'A'].size() && xnstats[c1-'A'].size() == xnstats[c2-'A'].size()){
					bool eq = true;
					range(i,0,ynstats[c1-'A'].size())eq &= ynstats[c1-'A'][i] == ynstats[c2-'A'][i];
					range(i,0,xnstats[c1-'A'].size())eq &= xnstats[c1-'A'][i] == xnstats[c2-'A'][i];
					if(eq){
						gid[c1-'A']=gid[c2-'A'];
						break;
					}
				}
			}
		}
		vector<int> gc(26);
		range(i,0,26)gc[gid[i]]++;
		for(char c='A'; c <= 'Z';c++)if(gid[c-'A']==c-'A'){
			tmp[y][x] = c;
			bool tmpOK = true;
			{
				bool ok = false;
				for(int s:ynstats[c-'A'])ok |= reachable[y][s][w-1-x];
				tmpOK &= ok;
			}
			{
				bool ok = false;
				for(int s:xnstats[c-'A'])ok |= reachable[h+x][s][h-1-y];
				tmpOK &= ok;
			}
			if(x == w-1){
				bool ok = false;
				for(int s:ynstats[c-'A'])ok |= s == NFAs[y].t;
				tmpOK &= ok;
			}
			if(y == h-1){
				bool ok = false;
				for(int s:xnstats[c-'A'])ok |= s == NFAs[h+x].t;
				tmpOK &= ok;
			}
			if(tmpOK){
				vector<int> tmpp = stats[y],tmpq = stats[h+x];
				stats[y] = ynstats[c-'A']; stats[h+x] = xnstats[c-'A'];
				if(x+1 < w) dfs(y,x+1,gc[c-'A']);
				else dfs(y+1,0,gc[c-'A']);
				stats[y] = tmpp; stats[h + x] = tmpq;
			}
		}
	}
	void run(){
		while(true){
			cin >> h >> w;
			if(h==0 && w==0)break;
			rc = 0;
			tmp = res = vector<string>(h,string(w,'-'));
			vector<string> ss(h+w);cin >> ss;
			NFAs = vector<NFA>(h+w);
			range(i,0,h+w){
				string s = "";
				range(j,1,ss[i].size()-1)s+=ss[i][j];
				int cur = 0, e = s.size();
				NFAs[i]= NFA::pattern(s,cur,e);
			}
			stats = vector<vector<int>>(h+w);
			range(i,0,h+w) stats[i].push_back(NFAs[i].s);
			reachable = vector<vector<vector<int>>>(h+w);
			range(i,0,h){
				reachable[i] = vector<vector<int>>(NFAs[i].N);
				range(s,0,NFAs[i].N) reachable[i][s] = vector<int>(h+1);
			}
			range(i,0,w){
				reachable[h+i] = vector<vector<int>>(NFAs[h+i].N);
				range(s,0,NFAs[h+i].N) reachable[h+i][s] = vector<int>(w+1);
			}
			range(i,0,h+w) create_reachable(i);
			trans = vector<vector<vector<vector<int>>>>(h+w);
			range(i,0,h+w){
				trans[i] = vector<vector<vector<int>>>(NFAs[i].N,vector<vector<int>>(26));
				range(s,0,NFAs[i].N)range(c,'A','Z'+1)create_trans(i,s,c);
			}
			dfs(0,0,1);
			if(rc > 1){
				cout << "ambiguous" <<endl; 
			}else if(rc == 0){
				cout << "none" <<endl;
			}else{
				range(i,0,h) cout << res[i] <<endl;
			}
		}
	}
};
int main(){
	cout <<fixed<<setprecision(20);
	cin.tie(0);
	ios::sync_with_stdio(false);
	Main().run();
	return 0;
}