#include <iostream>
using namespace std;
int n,k,s;
int total;
void solve(int i,int knum,int res){
	for(int j = i;j <= n;j++){
		if(j+res > s)break;
		if(knum == k && res + j == s)total++;
		else if(knum < k && res + j < s)solve(j+1,knum+1,res+j);
	}
}

int main(){
	while(1){
		cin >> n >> k >> s;
		if(n == 0)break;
		total = 0;
		solve(1,1,0);
		cout << total << endl;
	}
	return 0;
}