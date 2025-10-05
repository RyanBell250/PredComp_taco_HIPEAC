#include<cstdio>
#include<vector>
#include<algorithm>

#define	pb			push_back
#define	rep(i,n)	for(int i=0;i<(n);i++)

using namespace std;

typedef	vector<int>	vi;

int a[10];

bool isOK(){
	int M=a[9];
	int s=(a[0]+a[4]+a[8])%M;
	if(s!=(a[2]+a[4]+a[6])%M)	return false;
	rep(i,3)if(s!=(a[3*i]+a[3*i+1]+a[3*i+2])%M)	return false;
	rep(i,3)if(s!=(a[i]+a[3+i]+a[6+i])%M)		return false;
	return true;
}

int main(){
	while(1){
		rep(i,10)	scanf("%d",a+i);
		if(a[0]==-1)	break;

		vi pos,num;
		bool used[11]={};
		rep(i,10){
			if(a[i]==0)	pos.pb(i);
			else	used[a[i]]=true;
		}
		rep(i,10)if(!used[i+1])	num.pb(i+1);
		sort(num.begin(),num.end());

		int cnt=0;
		do{
			rep(i,pos.size())	a[pos[i]]=num[i];
			if(isOK())	cnt++;
		}while(next_permutation(num.begin(),num.end()));
		printf("%d\n",cnt);
	}

	return 0;
}