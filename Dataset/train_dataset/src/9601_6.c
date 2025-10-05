#include<cstdio>
int main(){
	int n,y;
	scanf("%d%d",&n,&y);
	int p=0;
	y=y/1000;
	for(int a=0;a<=y/10;a++){
		for(int b=0;b<=(y-a*10)/5;b++){
			if(y-9*a-4*b==n){
				printf("%d %d %d\n",a,b,y-10*a-5*b);
				p=1;
				break;
			}
		}
		if(p==1)break;
	}
	if(p==0)printf("-1 -1 -1\n");
	return 0;
}