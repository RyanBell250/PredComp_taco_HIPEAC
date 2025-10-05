    
    #include<bits/stdc++.h>
    using namespace std ;
    #define ll long long 
    #define pb push_back 
    #define ff first
    #define ss second
    #define lb lower_bound
    #define ub upper_bound
    int main() {
        ios::sync_with_stdio(0);
        cin.tie(0);
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i <= n - 1; i++) cin >> a[i];
        int sum = 0;
        for(int i = 0; i <= n - 1; i++) sum += a[i];
        if(sum%2 == 1) cout << "0\n";
        else{
            vector<bool> possible(sum + 1, false);
            possible[0] = true;
            for(int i = 0; i <= n - 1; i++){
                for(int j = sum; j >= 0; j--){
                    if(possible[j]) possible[j + a[i]] = true;
                }
            }
            if(possible[sum/2] == false) cout << "0\n";
            else{
                int div = 1;
                while(1){
                    for(int i = 0; i <= n - 1; i++){
                        if((a[i]/div)%2 == 1){
                            cout << "1\n";
                            cout << i + 1 << '\n';
                            return 0;
                        }
                    }
                    div *= 2;
                }
            }
        }
        return 0;
    }      
    