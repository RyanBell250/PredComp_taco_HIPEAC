#include<cstdio>
#include<bitset>
using namespace std;
const int N=4e6+7;
bitset<N>s;int n,i,x,sum;
int main(){
	s[0]=1;
	for(scanf("%d",&n),i=1;i<=n;++i)scanf("%d",&x),s|=(s<<x),sum+=x;
	for(x=(sum+1)/2;;++x)if(s[x])break;
	printf("%d\n",x);
}