#include <bits/stdc++.h>
#define INF 1000000000000007LL
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
typedef pair<P,ll> PP;
class getbridge{
public:
	static const int MAX=200000;
	vector<int> G[MAX];
	bool visited[MAX];
	int prenum[MAX],parent[MAX],lowest[MAX],timer;
	vector<P> bridge;
	void dfs(int v,int prev){
		prenum[v]=lowest[v]=timer;
		timer++;
		visited[v]=true;
		int next;
		for(int i=0;i<G[v].size();i++){
			next=G[v][i];
			if(!visited[next]){
				parent[next]=v;
				dfs(next,v);
				lowest[v]=min(lowest[v],lowest[next]);
				if(prenum[v]<lowest[G[v][i]]){
					bridge.push_back(P(min(v,G[v][i]),max(v,G[v][i])));
				}
			}else if(next!=prev){
				lowest[v]=min(lowest[v],prenum[next]);
			}
		}
	}
	set<int> art_points(int N){
		for(int i=0;i<N;i++){
			visited[i]=false;
		}
		timer=1;
		dfs(0,-1);
		set<int> ap;
		int np=0;
		for(int i=1;i<N;i++){
			int p=parent[i];
			if(p==0)np++;
			else if(prenum[p]<lowest[i])ap.insert(p);
		}
		if(np>1)ap.insert(0);
		return ap;
	}
};
getbridge bri;
int n,m;
vector<P> G[100001];
vector<P> rG[100001];
ll dist[100001];
ll cnt[100001];
ll dist2[100001];
int a[100001],b[100001];
ll c[100001];
set<PP> se;
set<PP> multi;
stack<int> s;
void dijk(){
	for(int i=0;i<n;i++){
		dist[i]=INF;
	}
	dist[0]=0;
	cnt[0]=1;
	priority_queue<P,vector<P>,greater<P> > que;
	que.push(P(0,0));
	while(que.size()){
		P p=que.top();
		que.pop();
		int v=p.second;
		ll co=p.first;
		if(co>dist[v])continue;
		for(int i=0;i<G[v].size();i++){
			if(dist[G[v][i].first]>dist[v]+G[v][i].second){
				dist[G[v][i].first]=dist[v]+G[v][i].second;
				cnt[G[v][i].first]=cnt[v];
				que.push(P(dist[G[v][i].first],G[v][i].first));
			}else if(dist[G[v][i].first]==dist[v]+G[v][i].second){
				cnt[G[v][i].first]+=cnt[v];
			}
		}
	}
}
bool used[100001];
void make_graph(){
	queue<int> que;
	que.push(1);
	used[1]=true;
	while(que.size()){
		int v=que.front();
		que.pop();
		for(int i=0;i<rG[v].size();i++){
			int next=rG[v][i].first;
			if(dist[v]==dist[next]+rG[v][i].second){
				if(!used[next]){
					used[next]=true;
					que.push(next);
				}
				bri.G[v].push_back(next);
				bri.G[next].push_back(v);
			}
		}
	}
}
void dijk2(){
	for(int i=0;i<n;i++){
		dist2[i]=INF;
	}
	dist2[1]=0;
	priority_queue<P,vector<P>,greater<P> > que;
	que.push(P(0,1));
	while(que.size()){
		P p=que.top();
		que.pop();
		int v=p.second;
		ll co=p.first;
		if(co>dist2[v])continue;
		for(int i=0;i<rG[v].size();i++){
			if(dist2[rG[v][i].first]>dist2[v]+rG[v][i].second){
				dist2[rG[v][i].first]=dist2[v]+rG[v][i].second;
				que.push(P(dist2[rG[v][i].first],rG[v][i].first));
			}
		}
	}
}
int main(void){
	scanf("%d%d",&n,&m);
	for(int i=0;i<m;i++){
		scanf("%d%d%lld",&a[i],&b[i],&c[i]);
		a[i]--;
		b[i]--;
		if(se.find(PP(P(a[i],b[i]),c[i]))==se.end()){
			se.insert(PP(P(a[i],b[i]),c[i]));
			G[a[i]].push_back(P(b[i],c[i]));
			rG[b[i]].push_back(P(a[i],c[i]));
		}else{
			multi.insert(PP(P(a[i],b[i]),c[i]));
		}
	}
	dijk();
	if(dist[1]<INF){
		make_graph();
		bri.art_points(n);
		sort(bri.bridge.begin(),bri.bridge.end());
	}
	dijk2();
	for(int i=0;i<m;i++){
		ll val=dist[b[i]];
		val+=dist2[a[i]];
		val+=c[i];
		if(val<dist[1]){
			puts("HAPPY");
		}else if(dist[1]>=INF){
			puts("SAD");
		}else if(val==dist[1]){
			puts("SOSO");
		}else{
			if(dist[b[i]]-dist[a[i]]!=c[i]){
				puts("SOSO");
			}else{
				if(multi.find(PP(P(a[i],b[i]),c[i]))!=multi.end()){
					puts("SOSO");
				}else if(dist[a[i]]+c[i]+dist2[b[i]]==dist[1]){
					int v=lower_bound(bri.bridge.begin(),bri.bridge.end(),P(min(a[i],b[i]),max(a[i],b[i])))-bri.bridge.begin();
					if(v<bri.bridge.size() && bri.bridge[v]==P(min(a[i],b[i]),max(a[i],b[i]))){
						puts("SAD");
					}else{
						puts("SOSO");
					}
				}else{
					puts("SOSO");
				}
			}
		}
	}
	return 0;
}