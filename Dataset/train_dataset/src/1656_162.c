#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll,ll> mp;
ll inf =  1e9;
#define MAXN 1000001

vector<bool> prime;
void seive(){
    prime = vector<bool> ( MAXN , true );
    prime[0] = prime[1] = false;
    for(int i=2; i*i< MAXN ; i++){
	if( !prime[i] ) continue;
	for(int j=2*i; j < MAXN;j += i ) prime[j] = false;
    }
}



int main(){
    seive();
    while(1){
	int a,d,n;
	cin>>a>>d>>n;
	if( a == 0 )break;;
	while( n != 0 ){
	    if( prime [a] ) n--;
	    a+=d;
	}
	cout<<a-d<<endl;
    }
    return 0;
}

