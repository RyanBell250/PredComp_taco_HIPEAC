#include<bits/stdc++.h>
typedef long long int ll;
typedef unsigned long long int ull;
#define BIG_NUM 2000000000
#define HUGE_NUM 99999999999999999
#define MOD 1000000007
#define EPS 0.000000001
using namespace std;
#define SIZE 100005
vector<int> G[SIZE],children[SIZE];
int N;
bool visited[SIZE],is_art_point[SIZE];
int visited_order[SIZE],parent[SIZE],lowest[SIZE],number;
ll sum_W;
ll W[SIZE],dp[SIZE];
void dfs(int current_node,int pre_node){
	visited_order[current_node] = lowest[current_node] = number;  
	number++;
	visited[current_node] = true;
	dp[current_node] = W[current_node];
	int next;
	for(int i = 0; i < G[current_node].size(); i++){
		next = G[current_node][i];
		if(!visited[next]){
			parent[next] = current_node;
			children[current_node].push_back(next);
			dfs(next,current_node);
			dp[current_node] += dp[next];
			lowest[current_node] = min(lowest[current_node],lowest[next]); 
		}else if(visited[next] == true && next != pre_node){ 
			lowest[current_node] = min(lowest[current_node],visited_order[next]);
		}
	}
}
void func(){
	for(int i = 0; i < N; i++){
		visited[i] = false;
		is_art_point[i] = false;
		dp[i] = 0;
	}
	number = 1;
	dfs(0,-1);
	int tmp_parent,root_num = 0;
	vector<int> V;
	for(int i = 1; i < N; i++){
		tmp_parent = parent[i];
		if(tmp_parent == 0){
			root_num++;
		}else if(visited_order[tmp_parent] <= lowest[i]){
			V.push_back(tmp_parent);
		}
	}
	if(root_num >= 2){
		V.push_back(0);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(int i = 0; i < V.size(); i++){
		is_art_point[V[i]] = true;
	}
	for(int i = 0; i < N; i++){
		if(!is_art_point[i]){
			printf("%lld\n",sum_W-W[i]);
			continue;
		}
		ll ans = 0;
		int child;
		if(i == 0){
			for(int k = 0; k < children[i].size(); k++){
				child = children[i][k];
				ans = max(ans,dp[child]);
			}
		}else{
			ll parent_sum = sum_W-dp[i];
			for(int k = 0; k < children[i].size(); k++){
				child = children[i][k];
				ans = max(ans,dp[child]);
				if(lowest[child] < visited_order[i]){ 
					parent_sum += dp[child];
				}
			}
			ans = max(ans,parent_sum);
		}
		printf("%lld\n",ans);
	}
}
int main(){
	int E;
	scanf("%d %d",&N,&E);
	sum_W = 0;
	for(int i = 0; i < N; i++){
		scanf("%lld",&W[i]);
		sum_W += W[i];
	}
	int from,to;
	for(int i = 0; i < E; i++){
		scanf("%d %d",&from,&to);
		from--;
		to--;
		G[from].push_back(to);
		G[to].push_back(from);
	}
	func();
	return 0;
}
