#include<stdio.h>
#include<algorithm>
#include<string>
#include<string.h>
#include<map>
using namespace std;
char cs[20]="*+-&^|0123456789";
char in[20];
map<pair<string,int>,int>dp;
int n;
int m;
int cur;
string str;
int e1();
int e2();
int e3();
int e4();
int e5();
int fact(){
	if(str[cur]=='('){
		cur++;
		int ret=e5();
		cur++;
		return ret;
	}
	int ret=0;
	while('0'<=str[cur]&&str[cur]<='9'){
		ret*=10;
		ret+=str[cur]-'0';
		cur++;
	}
	return ret;
}
int e1(){
	int ret=fact();
	while(str[cur]=='*'){
		cur++;
		ret*=fact();
	}
	return ret;
}
int e2(){
	int ret=e1();
	while(str[cur]=='+'||str[cur]=='-'){
		char t=str[cur];
		cur++;
		if(t=='+')ret+=e1();
		else ret-=e1();
	}
	return ret;
}
int e3(){
	int ret=e2();
	while(str[cur]=='&'){
		cur++;
		ret&=e2();
	}
	return ret;
}
int e4(){
	int ret=e3();
	while(str[cur]=='^'){
		cur++;
		ret^=e3();
	}
	return ret;
}
int e5(){
	int ret=e4();
	while(str[cur]=='|'){
		cur++;
		ret|=e4();
	}
	return ret;
}
bool valid(){
	int kk=0;
	if(str[0]=='0')return false;
	if((str[0]<'0'||str[0]>'9')&&str[0]!='('&&str[0]!=')')return false;
	if((str[m-1]<'0'||str[m-1]>'9')&&str[m-1]!='('&&str[m-1]!=')')return false;
	for(int i=0;i<m;i++){
		if(str[i]=='(')kk++;
		if(str[i]==')')kk--;
		if(kk<0)return false;
	}
	if(kk)return false;
	for(int i=0;i<m-1;i++){
		if(str[i]=='('&&(str[i+1]<'0'||str[i+1]>'9')&&str[i+1]!='(')return false;
		if(str[i]==')'&&!(str[i+1]<'0'||str[i+1]>'9'))return false;
		if(str[i+1]==')'&&(str[i]<'0'||str[i]>'9')&&str[i]!=')')return false;
		if(str[i+1]=='('&&!(str[i]<'0'||str[i]>'9'))return false;
		if((str[i]<'0'||str[i]>'9')&&str[i+1]=='0')return false;
		if((str[i]<'0'||str[i]>'9')&&str[i]!='('&&str[i]!=')'&&
			(str[i+1]<'0'||str[i+1]>'9')&&str[i+1]!='('&&str[i+1]!=')')return false;
	}
	return true;
}
int solve(int a,string b){
	if(dp.count(make_pair(b,a)))return dp[make_pair(b,a)];
	if(a==n){
		cur=0;
		str=b;
		int ret=e5();
		return dp[make_pair(b,a)]=ret;
	}
	int len=b.size();
	int ret=-999999999;
	if(a%2)ret=999999999;
	for(int i=0;i<len;i++){
		string c="";
		for(int j=0;j<i;j++)c=c+b[j];
		for(int j=i+1;j<len;j++)c=c+b[j];
		cur=0;
		str=c;
		m=c.size();
		if(valid()){
			if(a%2)ret=min(ret,solve(a+1,c));
			else ret=max(ret,solve(a+1,c));
		}
	}
	for(int i=0;i<=len;i++){
		string c="";
		for(int j=0;j<i;j++)c=c+b[j];
		c+='*';
		for(int j=i;j<len;j++)c=c+b[j];
		for(int j=0;j<16;j++){
			c[i]=cs[j];
			str=c;
			m=c.size();
			if(valid()){
				if(a%2)ret=min(ret,solve(a+1,c));
				else ret=max(ret,solve(a+1,c));
			}
		}
	}
	return dp[make_pair(b,a)]=ret;
}
int main(){
	int a;
	while(scanf("%d",&a),a){
		scanf("%s",in);
		dp.clear();
		while(a>2)a-=2;
		n=a;
		string tmp=in;
		printf("%d\n",solve(0,tmp));
	}
}