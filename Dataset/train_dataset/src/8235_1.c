#include<iostream>
#include<map>
#include<queue>
#include<string>

using namespace std;

int BFS(string);
int ok(string);
char change(char, char);


int main(){

  string s;
  while(1){
    cin >> s;
    if(s == "0") break;
    int res = BFS(s);
    if(res == -1) cout << "NA" << endl;
    else cout << res << endl;
  }
}


int BFS(string s){
  queue<string> Q;
  map<string, int> dist;
  Q.push(s);
  dist[s] = 1;
  while(!Q.empty()){
    string now = Q.front();
    Q.pop();
    if(ok(now) == 1) return dist[now]-1;
    for(int i = 0; i < now.length()-1; i++){
      char res = change(now[i], now[i+1]);
      if(res == '*') continue;

      string tmp = now;
      tmp[i] = tmp[i+1] = res;
      if(dist[tmp] == 0){
	dist[tmp] = dist[now] + 1;
	Q.push(tmp);
      }
    }
  }
  return -1;
}

int ok(string s){
  for(int i = 1; i < s.length(); i++){
    if(s[0] != s[i]) return 0;
  }
  return 1;
}

char change(char c1, char c2){
  string s = "rgb";
  if(c1 == c2) return '*';
    for(int i = 0; i < 3; i++){
      if(c1 != s[i] && c2 != s[i]) return s[i];
    }
}