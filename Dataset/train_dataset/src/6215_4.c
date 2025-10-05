#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
#include<algorithm>
#include<vector>
#include<queue>
#include<map>
#include<string>
#include<cmath>
#include<set>
#include<stack>
using namespace std;
typedef unsigned long long ll;
map<string, int>ma;
vector<pair<int, string> >vec;
struct sortVec{
    bool operator()(string m1, string m2){
        return ma[m1]<ma[m2];
    }
}sv;
int main(){
    int n,p;
    while(cin>>n,n){
        ma.clear();
        vec.clear();
        string s;
        for(int i=0;i<n;i++){
            int day,time;
            cin>>s>>day>>time;
            if(time>=2400){
                day=(day+1);
                time-=2400;
            }
            time=(time/100)*60+time%100+day*24*60;
            ma[s]=time;
            vec.push_back(make_pair(time,s));
        }
        sort(vec.begin(),vec.end());
        cin>>p;
        vector<string>fav;
        for(int i=0;i<p;i++){
            cin>>s;
            fav.push_back(s);
        }
        sort(fav.begin(),fav.end(),sv);
        vector<string>res;
        res.push_back(fav[0]);
        bool nex=false;
        for(int i=1;i<fav.size();i++){
            if(ma[fav[i]]<ma[fav[i-1]]+30){
                cout<<-1<<endl;
                nex=true;
                break;
            }
            res.push_back(fav[i]);
            sort(res.begin(),res.end(),sv);
        }
        if(nex){
            continue;
        }
        for(int i=0;i<vec.size();i++){
            int start=vec[i].first;
            int resi=0;
            while(resi<res.size()&&ma[res[resi]]+30<=start){
                resi++;
            }
            if(resi==res.size()||start+30<=ma[res[resi]]){
                if(resi>0&&ma[res[resi-1]]+30>start){
                    continue;
                }
                res.push_back(vec[i].second);
                sort(res.begin(),res.end(),sv);
            }
        }
        cout<<res.size()<<endl;
    }
    return 0;
}
