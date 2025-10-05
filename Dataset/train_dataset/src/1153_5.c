#include<iostream>
#include <string>
#include <algorithm>
using namespace std;
string ume_c="89605+32471-*";
string ume[13][5]={
    {
    "111",
    "101",
    "111",
	"101",
    "111"
    },
	{
    "111",
    "101",
    "111",
	"001",
    "111"
    },
	{
    "111",
    "100",
    "111",
	"101",
    "111"
    },
	{
    "111",
    "101",
    "101",
	"101",
    "111"
    },
	{
    "111",
    "100",
    "111",
	"001",
    "111"
    },
	{
    "000",
    "010",
    "111",
	"010",
    "000"
    },
	{
    "111",
    "001",
    "111",
	"001",
    "111"
    },
	{
    "111",
    "001",
    "111",
	"100",
    "111"
    },
	{
    "101",
    "101",
    "111",
	"001",
    "001"
    },
	{
    "111",
    "001",
    "001",
	"001",
    "001"
    },
	{
    "001",
    "001",
    "001",
	"001",
    "001"
    },
	{
    "000",
    "000",
    "111",
	"000",
    "000"
    },
	{
    "000",
    "000",
    "010",
	"000",
    "000"
    }
};
string S;
int pos;
int expr();
int term();
int num();
int expr(){
	int res = term();
	while(1){
		if(S[pos]=='+'){
			pos++;
			res += term();
		}else if(S[pos]=='-'){
			pos++;
			res -= term();
		}else{
			break;
		}
	}
	return res;
}
int term(){
	int res = num();
	while(1){
		if(S[pos]=='*'){
			pos++;
			res *= num();
		}else{
			break;
		}
	}
	return res;
}
int num(){
	int c = S[pos++]-'0';
	while('0' <= S[pos] && S[pos] <= '9'){
		c *= 10;
		c += S[pos++]-'0';
	}
	return c;
}
int main(){
	int n;
	cin>>n;
	int mp[321][321]={0};
	char s[322]={};
	for(int i=0;i<321;i++)s[i]=' ';
	for(int i=0;i<n;i++){
		int x1,y1,x2,y2;
		cin>>x1>>y1>>x2>>y2;
		x1 += 20;
		y1 += 20;
		x2 += 20;
		y2 += 20;
		if(x1==x2){
			if( y1 > y2 ) swap(y1,y2);
			for(int j=y1;j<=y2;j++){
				mp[x1][j]=1;
			}
		}else{
			if( x1 > x2 ) swap(x1,x2);
			for(int j=x1;j<=x2;j++){
				mp[j][y1]=1;
			}
		}
	}
	for(int i=0;i<ume_c.size();i++){
		for(int j=0;j<=300;j++){
			for(int k=0;k<=300;k++){
				int t=1;
				int minx = 1e9;
				for(int l=0;l<=4;l++){
					for(int m=0;m<=2;m++){
						if(ume[i][l][m]=='1'){
							minx = min(minx,k+m);
							if(mp[k+m][j+l]==0){
								t=0;
							}
						}
					}
				}
				if(t==1){
					s[minx]=ume_c[i];
					for(int l=0;l<=4;l++){
						for(int m=0;m<=2;m++){
							if(ume[i][l][m]=='1'){
								mp[k+m][j+l]=0;
							}
						}
					}
				}
			}
		}
	}
	S = string(s);
	S.erase(remove(S.begin(),S.end(),' '),S.end());
	pos = 0;
	S += "~";
	cout<<expr()<<endl;
}
