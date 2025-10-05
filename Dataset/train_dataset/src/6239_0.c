#include<iostream>
#include<algorithm>
#include<set>
using namespace std;

int grundy[201][101];

int dfs(int w, int b){
    if(grundy[w][b] >= 0){
        return grundy[w][b];
    }

    set<int> st;
    if(w > 0){
        st.insert(dfs(w - 1, b));
    }
    if(b > 0){
        st.insert(dfs(w + 1, b - 1));
    }
    for(int i = 1 ; i <= b && i <= w ; ++i){
        st.insert(dfs(w, b - i));
    }

    int res = 0;
    while(st.count(res)){
        ++res;
    }

    return grundy[w][b] = res;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);

    fill(grundy[0], grundy[201], -1);
    grundy[0][0] = 0;

    int n;
    cin >> n;

    int v = 0;
    for(int i = 0 ; i < n ; ++i){
        int w, b;
        cin >> w >> b;
        v ^= dfs(w, b);
    }

    if(v == 0){
        cout << 1 << endl;
    }else{
        cout << 0 << endl;
    }

    return 0;
}
