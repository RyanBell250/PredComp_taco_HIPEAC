#include<bits/stdc++.h>
typedef long long int ll;
typedef unsigned long long int ull;
#define BIG_NUM 2000000000
#define HUGE_NUM 99999999999999999
#define MOD 1000000007
#define EPS 0.000000001
using namespace std;
#define NUM 100005
enum Type{
	UNDEFINED,
	A,
	B,
};
enum Which{
	EVEN,
	ODD,
};
struct GROUP{
	vector<int> nodes;
};
struct Edge{
	Edge(int arg_from_node,int arg_to_node){
		from_node = arg_from_node;
		to_node = arg_to_node;
	}
	int from_node,to_node;
};
struct Info{
	void set(int arg_start_node,int arg_sum_value,Which arg_start_which){
		start_node = arg_start_node;
		sum_value = arg_sum_value;
		start_which = arg_start_which;
	}
	bool operator<(const struct Info &arg) const{
		return sum_value < arg.sum_value; 
	}
	int start_node,sum_value;
	Which start_which;
};
GROUP group[NUM]; 
vector<int> G[NUM];
vector<int> reverse_G[NUM];
stack<int> S;
vector<Edge> Group_G[NUM];
bool check[NUM];
int V,E;
int value[NUM];
int table[NUM];
int group_index,sum_A[NUM],sum_B[NUM],sum_ALL[NUM];
int dp[NUM][2],in_num[NUM];
bool FLG,is_bipartie[NUM],can_go[NUM];
Type type[NUM],rev_type[3] = {UNDEFINED,B,A};
Which rev_which[2] = {ODD,EVEN};
priority_queue<Info> Q[NUM];
void dfs(int node_id){
	check[node_id] = true;
	for(int i = 0; i < G[node_id].size(); i++){
		if(!check[G[node_id][i]])dfs(G[node_id][i]);
	}
	S.push(node_id);
}
void reverse_dfs(int node_id){
	check[node_id] = true;
	group[group_index].nodes.push_back(node_id); 
	table[node_id] = group_index;
	for(int i = 0; i < reverse_G[node_id].size(); i++){
		if(!check[reverse_G[node_id][i]])reverse_dfs(reverse_G[node_id][i]);
	}
}
void recursive(int node_id){
	if(!FLG)return;
	for(int i = 0; i < G[node_id].size(); i++){
		int next = G[node_id][i];
		if(table[next] != table[node_id])continue;
		if(type[next] == type[node_id]){
			FLG = false;
			return;
		}else if(type[next] == UNDEFINED){
			type[next] = rev_type[type[node_id]];
			recursive(next);
		}else{ 
		}
	}
}
void make_can_go(int node_id){
	for(int i = 0; i < G[node_id].size(); i++){
		int next = G[node_id][i];
		if(can_go[next])continue;
		can_go[next] = true;
		make_can_go(next);
	}
}
int main(){
	scanf("%d %d",&V,&E);
	for(int i = 0; i < V; i++){
		scanf("%d",&value[i]);
	}
	int from,to;
	for(int loop = 0; loop < E; loop++){
		scanf("%d %d",&from,&to);
		G[from].push_back(to);
		reverse_G[to].push_back(from);
	}
	for(int i = 0; i < V; i++)check[i] = false;
	for(int i = 0; i < V;i++){
		if(!check[i])dfs(i);
	}
	for(int i = 0; i < V;i++)check[i] = false;
	group_index = -1;
	while(!S.empty()){
		if(!check[S.top()]){
			group_index++;
			reverse_dfs(S.top());
		}
		S.pop();
	}
	for(int i = 0; i < V; i++){
		type[i] = UNDEFINED;
		in_num[i] = 0;
	}
	int tmp,tmp_A,tmp_B;
	for(int i = 0; i <= group_index; i++){
		FLG = true;
		type[group[i].nodes[0]] = A;
		recursive(group[i].nodes[0]);
		is_bipartie[i] = FLG;
		if(is_bipartie[i]){
			tmp_A = 0;
			tmp_B = 0;
			for(int k = 0; k < group[i].nodes.size(); k++){
				int tmp_node = group[i].nodes[k];
				if(type[tmp_node] == A){
					tmp_A += value[tmp_node];
				}else{
					tmp_B += value[tmp_node];
				}
			}
			sum_A[i] = tmp_A;
			sum_B[i] = tmp_B;
		}else{
			tmp = 0;
			for(int k = 0; k < group[i].nodes.size(); k++){
				int tmp_node = group[i].nodes[k];
				tmp += value[tmp_node];
			}
			sum_ALL[i] = tmp;
		}
	}
	for(int i = 0; i < V; i++){
		can_go[i] = false;
	}
	can_go[0] = true;
	make_can_go(0);
	for(int i = 0; i <= group_index; i++){
		for(int k = 0; k < group[i].nodes.size(); k++){
			int from_node = group[i].nodes[k];
			if(!can_go[from_node])continue; 
			for(int p = 0; p < G[from_node].size(); p++){
				int next_group = table[G[from_node][p]];
				if(next_group != i){
					Group_G[i].push_back(Edge(from_node,G[from_node][p]));
					in_num[next_group]++;
				}
			}
		}
	}
	for(int i = 0; i <= group_index; i++){
		dp[i][EVEN] = -BIG_NUM;
		dp[i][ODD] = -BIG_NUM;
	}
	Info first_info;
	int first_value;
	if(is_bipartie[table[0]]){ 
		if(type[0] == A){
			first_value = sum_A[table[0]];
		}else{
			first_value = sum_B[table[0]];
		}
	}else{
		first_value = sum_ALL[table[0]];
	}
	int ans = first_value;
	first_info.set(0,first_value,EVEN);
	Q[table[0]].push(first_info);
	queue<int> NODE;
	NODE.push(table[0]);
	vector<Which> WHICH;
	bool even_FLG,odd_FLG;
	while(!NODE.empty()){
		int current_group = NODE.front();
		NODE.pop();
		even_FLG = false;
		odd_FLG = false;
		while(Q[current_group].empty() == false && (even_FLG == false || odd_FLG == false)){
			Info info = Q[current_group].top();
			Q[current_group].pop();
			if(info.sum_value < dp[table[info.start_node]][info.start_which]){
				continue;
			}else{
				if(info.start_which == EVEN){
					even_FLG = true;
				}else{
					odd_FLG = true;
				}
				for(int i = 0; i < Group_G[current_group].size(); i++){
					int next_start = Group_G[current_group][i].to_node;
					int next_group = table[next_start];
					WHICH.clear();
					if(is_bipartie[current_group]){ 
						if(type[info.start_node] == type[Group_G[current_group][i].from_node]){
							WHICH.push_back(rev_which[info.start_which]);
						}else{
							WHICH.push_back(info.start_which);
						}
					}else{ 
						WHICH.push_back(EVEN);
						WHICH.push_back(ODD);
					}
					int next_value = 0;
					for(int k = 0; k < WHICH.size(); k++){
						if(is_bipartie[next_group]){
							if(WHICH[k] == EVEN){
								if(type[next_start] == A){
									next_value = info.sum_value+sum_A[next_group];
								}else{
									next_value = info.sum_value+sum_B[next_value];
								}
							}else{ 
								if(type[next_start] == A){
									next_value = info.sum_value+sum_B[next_group];
								}else{
									next_value = info.sum_value+sum_A[next_value];
								}
							}
						}else{ 
							next_value = info.sum_value+sum_ALL[next_group];
						}
						if(dp[next_group][WHICH[k]] >= next_value)continue;
						dp[next_group][WHICH[k]] = next_value;
						ans = max(ans,next_value);
						Info next_info;
						next_info.set(next_start,next_value,WHICH[k]);
						Q[next_group].push(next_info);
					}
				}
			}
		}
		for(int i = 0; i < Group_G[current_group].size(); i++){
			int adj_node = Group_G[current_group][i].to_node;
			in_num[table[adj_node]]--;
			if(in_num[table[adj_node]] == 0){
				NODE.push(table[adj_node]);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
