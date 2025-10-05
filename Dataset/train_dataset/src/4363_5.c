#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
constexpr int INF = (1 << 30) - 1;
int main(){
    int n;
    while(cin >> n){
        vector< vector<int> > g(n);
        for(int i = 0 ; i < n ; ++i){
            int r, k;
            cin >> r >> k;
            --r;
            for(int j = 0 ; j < k ; ++j){
                int t;
                cin >> t;
                g[r].push_back(t - 1);
            }
        }
        vector< vector<int> > cost(n, vector<int>(n, INF));
        for(int i = 0 ; i < n ; ++i){
            cost[i][i] = 1;
            queue< pair<int, int> > que;
            que.push({1, i});
            while(!que.empty()){
                pair<int, int> now = que.front();
                que.pop();
                if(cost[i][now.second] < now.first){
                    continue;
                }
                for(auto to : g[now.second]){
                    if(cost[i][to] > now.first + 1){
                        cost[i][to] = now.first + 1;
                        que.push({now.first + 1, to});
                    }
                }
            }
        }
        int p;
        cin >> p;
        while(p--){
            int s, d, v;
            cin >> s >> d >> v;
            --s;
            --d;
            if(cost[s][d] <= v){
                cout << cost[s][d] << endl;
            }else{
                cout << "NA" << endl;
            }
        }
    }
    return 0;
}
