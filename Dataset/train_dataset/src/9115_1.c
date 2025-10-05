#include<bits/stdc++.h>
using namespace std;

int main(){
    int num[300000]={};
    for(int i=6;i<300000;i++){
        if(num[i]==1) continue;
        if(i%7==1 || i%7==6) for(int j=i+i;j<300000;j+=i)num[j]=1;
        else num[i]=1;
    }
    int N;
    while(1){
        cin>>N;
        int tmp=N;
        if(N==1) break;
        vector<int> ans;
        for(int i=6;i<300000;i++){
            if(num[i]==1) continue;
            if(N%i==0){
                ans.push_back(i);
            }
            if(N<i) break;
        }
        
        cout<<tmp<<": ";
        for(int i=0;i<ans.size();i++){
            cout<<ans[i];
            if(i!=ans.size()-1) cout<<" ";
        }
        cout<<endl;
    }
    return 0;
}

