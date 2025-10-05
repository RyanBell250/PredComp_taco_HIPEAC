#include<bits/stdc++.h>
using namespace std;
#define N 6005
vector<int>v;
deque<int>q;
int n,id[N],idd[N],tot[N<<1],a[N][3];
long long sum;
int red(int k){
    if (!k)return 0;
    return a[id[k]][0]<a[id[k-1]][1];
}
int find(){
    int j=red(n-1)+1,ans=0x3f3f3f3f;
    if ((j==2)&&(red(1)))return 0;
    for(int i=1;i<n;i++)
        if ((red(i-1))&&(red(i)))return 0;
    tot[0]=1;
    for(int i=1;i<2*n;i++)tot[i]=tot[i-1]+(!red(i%n));
    q.clear();
    for(int i=0;i<2*n;i++)
        if (red(i%n)){
            while ((!q.empty())&&(a[id[q.front()%n]][1]<a[id[i%n]][0])){
                ans=min(ans,tot[i]-tot[q.front()]-1);
                q.pop_front();
            }
        }
        else{
            while ((!q.empty())&&(a[id[q.back()%n]][1]>a[id[i%n]][1]))q.pop_back();
            q.push_back(i);
        }
    v.clear();
    for(int i=0;i<n;i++)
        if (!red(i))v.push_back(i);
    if ((j==2)&&(a[id[v[0]]][2]>a[id[v[1]]][0]))return 0;
    int lst=-1;
    if (a[id[v.back()]][2]>a[id[v[0]]][0]){
		lst=0;
		if (j==2)ans=min(ans,1);
	}
    for(int i=1;i<v.size();i++){
        if (a[id[v[i-1]]][2]>a[id[v[i]]][0]){
            if (v[i-1]+1<v[i])return 0;
            lst=v[i];
        }
        if ((lst>=0)&&(v[i-1]+1<v[i]))ans=min(ans,v[i]-lst-1);
    }
    if (lst>=0){
        if (j==2)ans=min(ans,n-lst);
        for(int i=1;i<v.size();i++)
            if (v[i-1]+1<v[i])ans=min(ans,v[i]+(n-lst)-1);
    }
    if (j==2){
        if (a[id[v[0]]][0]<a[id[v.back()]][1])return 0;
        for(int i=1;i<v.size();i++)
            if (a[id[v[i]]][0]<a[id[v[i-1]]][1])ans=min(ans,n-v[i]);
    }
    if (ans>n)return -1;
    return ans;
}
void turn(int k){
    sum+=k*(n-1);
    v.clear();
    for(int i=0;i<n;i++){
        if (red(i))idd[i]=id[i];
        else v.push_back(i);
    }
    for(int i=0;i<v.size();i++)idd[v[i]]=id[v[(i+v.size()-k)%v.size()]];
    memcpy(id,idd,sizeof(id));
}
int calc(int j){
    int lst=id[0];
    for(int i=1;i<n;i++){
        sum++;
        if (a[lst][j]>a[id[i]][0]){
            idd[i]=id[i];
            if (++j>=3){
                printf("%d %lld",lst,sum);
                exit(0);
            }
        }
        else{
            idd[i]=lst;
            lst=id[i];
            j=1;
        }
    }
    idd[0]=lst;
    memcpy(id,idd,sizeof(id));
    return j;
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<3;j++)scanf("%d",&a[i][j]);
    for(int i=1;i<n;i++)id[i]=i+1;
    sum=1;
    if (a[0][0]<a[1][0]){
        id[0]=1;
        id[n-1]=0;
    }
    else{
        id[n-1]=1;
        id[0]=0;
    }
    int j=1;
    while (1){
        while (j!=red(n-1)+1)j=calc(j);
        int i=find();
        if (i<0){
            printf("-1 -1");
            return 0;
        }
        turn(i);
        j=calc(j);
    }
}