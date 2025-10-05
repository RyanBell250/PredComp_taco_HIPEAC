#include <bits/stdc++.h>
using namespace std;
typedef pair<string,string> P;
int bnf();
set<P> used;
map<char,int> M;
string S;
int idx,valid;
char ch[8]={'0','1','+','-','*','(',')','='};
int ord[8];
 
bool check(string a){//??????????????????°???¨???????????????????????¢????
  int par=0;
  for(char s:a){
    par += (s == '(') - (s == ')');
    if(s == '=') return 0;
    if(par < 0) return 0;
  }
  return par==0;
}
 
int getNum(){ //???????????????°????????????
  int res = 0;
  if(S[idx] == '0' && isdigit(S[idx+1])) valid  = 0;
  while(isdigit(S[idx]))res = res*2 + S[idx++]-'0';
  return res;
}
 
int cal(){
  char ch = S[idx];
  int res = 0,sign = 1;
  if(ch=='+'||ch=='*'||ch==')'){ valid = 0;return 0;}
 
  while(S[idx] == '-') idx++, sign *= -1;
  ch = S[idx];
 
  if(isdigit(ch)){
    res = sign*getNum();
    if(S[idx] == '*'){idx++; return res * cal();}
    return res;
  }
  else if(ch == '(') {
    idx++;res = sign*bnf();idx++;
    return res;
  }
 
  valid = 0;
  return 0;
}
 
int bnf(){
  int res = cal();
  while(idx<(int)S.size()){
    if(valid == 0) return -1;
    char ch = S[idx];
    if(ch == '('){valid = 0;}
    else if(ch == '*'){idx++;res *= cal();}
    else if(ch == '+'){idx++;res += cal();}
    else if(ch == '-'){idx++;res -= cal();}
    else if(ch != ')') valid = 0;
    else break;
  }
  if(valid ==0) return -1;
  return res;
}
 
string mkS(string a){
  string res;
  for(char s:a){
    if(isalpha(s))res += ch[ ord[ M[s] ] ];
    else res += s;
  }
  return res;
}
 
int calc(string A,string B){
  if(A.size()==0 || B.size()==0) return 0;
  if(used.count(P(A,B)))return 0;
  used.insert(P(A,B));
  valid = check(A) && check(B);
  idx = 0;
  S = A;
  int ra = bnf();
  idx = 0;
  S = B;
  int rb = bnf();
  //if(valid)cout<<A<<"="<<B<<" "<<valid<<" "<<ra<<" "<<rb<<endl;
  return ra == rb && valid;
}
 
int calc(string s){
  s = mkS(s);
  for(int i=0;i<(int)s.size();i++)
    if(s[i]=='=') return calc(s.substr(0,i),s.substr(i+1,s.size()-i-1));
  return 0;
}
 
int dfs(int num,string &s){
  if(num == 8) return calc(s);
   
  int res = 0;
  for(int i=0;i<8;i++){
    if(ord[i] != -1)continue;
    ord[i] = num;
    res +=dfs(num+1,s);
    ord[i] = -1;
  }
  return res;
}
 
 
int main(){
  string str;
  cin>>str;
  if(str.size()<3)cout<<0<<endl,exit(0);
 
  map<char,int> cnt;
  for(int i=0;i<(int)str.size();i++)if(isalpha(str[i]))cnt[str[i]]++;
  if(cnt.size()>8)cout<<0<<endl,exit(0);
 
  int c = 0;
  for(pair<char,int> p:cnt)if(isalpha(p.first)) M[p.first] = c++;
   
  memset(ord,-1,sizeof(ord));  
  cout<<dfs(0,str)<<endl;
  return 0;
}