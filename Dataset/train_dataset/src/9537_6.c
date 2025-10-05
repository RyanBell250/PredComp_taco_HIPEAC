#include<bits/stdc++.h>
#define int long long
inline int read(){
	char c=getchar();while (c!='-'&&(c<'0'||c>'9'))c=getchar();
	int k=1,kk=0;if (c=='-')c=getchar(),k=-1;
	while (c>='0'&&c<='9')kk=kk*10+c-'0',c=getchar();return kk*k;
}using namespace std;
void write(int x){if (x<0)putchar('-'),x=-x;if (x/10)write(x/10);putchar(x%10+'0');}
void writeln(int x){write(x);puts("");}
int n,m,x,y,a[1010][1010],f[10010],ff[10010],z[10010],dd;
int fa(int x){return f[x]==x?x:f[x]=fa(f[x]);} 
bitset<10010>qaq;
signed main(){
	n=read();m=read();for (int i=1;i<=m;i++)x=read(),y=read(),a[x][y]=a[y][x]=1;
	for (int i=1;i<=n;i++)f[i]=i,f[i+n]=i+n;
	for (int i=1;i<=n;i++)
		for (int j=i+1;j<=n;j++)if (!a[i][j])f[fa(i)]=fa(j+n),f[fa(i+n)]=fa(j);
	for (int i=1;i<=n;i++)ff[fa(i)]++,ff[fa(i+n)]--;
	for (int i=1;i<=n;i++)if (f[fa(i)]==f[fa(i+n)])return puts("-1"),0;
	for (int i=1;i<=n;i++)if (fa(i)==i)z[++dd]=abs(ff[i]);
	qaq[n]=1;for (int i=1;i<=dd;i++)qaq=(qaq<<z[i])|(qaq>>z[i]);
	for (int i=0;i<=n;i++)if (qaq[i+n]){
		int xx=(n-i)/2,yy=xx+i;writeln(xx*(xx-1)/2+yy*(yy-1)/2);
		return 0;
	}puts("-1");
}


