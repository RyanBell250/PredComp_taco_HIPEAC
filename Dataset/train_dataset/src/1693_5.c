#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<map>
#define ll long long
#define F(i,s,t) for(int i=s;i<=t;i++)
#define DF(i,s,t) for(int i=s;i>=t;i--)
#define mp make_pair
using namespace std;
map<pair<string,string>,ll>sa;
char s[233];
ll sum=0;
int n;
string a,b;
int main(){
	scanf("%d",&n);
    scanf("%s",s);
    F(i,0,(1<<n)-1){
        a="",b="";
        F(j,0,n-1) (i&(1<<j))?(a+=s[j]):(b+=s[j]);
        sa[mp(a,b)]++;
    }
    F(i,0,(1<<n)-1){
        a="",b="";
        DF(j,n-1,0) (i&(1<<j))?(b+=s[j+n]):(a+=s[j+n]);
        sum+=sa[mp(a,b)];
    }
    printf("%lld\n",sum);
    return 0;
}


