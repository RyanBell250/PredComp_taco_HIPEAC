#include <iostream>
#include <string>
#include <set>
#include <queue>
using namespace std;

typedef pair<string, int> P;

int bfs(string worm){
	queue<P> que;
	que.push(P(worm, 0));

	set<string> d;
	
	while(!que.empty()){
		P p = que.front();
		que.pop();
		if(d.count(p.first)) continue;

		string str = p.first;
		
		bool flag = false;
		for(int i=0;i<str.size()-1;i++){
			if(str[i] != str[i+1]){
				flag = true;
				break;
			}
		}
		if(!flag) return p.second;
		d.insert(p.first);

		for(int i=0;i<str.size()-1;i++){
			if(str[i] != str[i+1]){
				char temp;
				string next;

				if(str[i] != 'b' && str[i+1] != 'b'){
					temp = 'b';
				}else if(str[i] != 'g' && str[i+1] != 'g'){
					temp = 'g';
				}else{
					temp = 'r';
				}

				next = str;
				next[i] = next[i+1] = temp;

				que.push(P(next, p.second+1));
			}
		}
	}
	return -1;
}

int main(){
	string worm;
	while(cin >> worm && worm != "0"){
		int ret = bfs(worm);
		if(ret>=0) cout << ret << endl;
		else cout << "NA" << endl;
	}
}