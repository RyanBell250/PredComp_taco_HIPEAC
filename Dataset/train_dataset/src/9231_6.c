#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int t;
    cin >> t;
    while(t>0){
        ll n;
        double x;
        cin >> n >> x;
        ll max_sum = 0, min_sum = 0,sum = 0;
        for(int i=0;i<n;i++){
            ll ele;
            cin >> ele;
            max_sum += ceil(ele/x);
            sum += ele;
        }
        min_sum = ceil(sum/x);
        cout<<min_sum<<" "<<max_sum;
        
        cout<<endl;
        t--;
    }
    
    
    
    
    return 0;
}