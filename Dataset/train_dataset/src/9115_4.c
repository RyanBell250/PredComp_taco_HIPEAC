#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

const int MAX = 300001;
bool data[MAX+10];
vector<int> MSPrime;


void make(){
  fill(data,data+MAX,false);
  for(int i = 0; 7*i+6 < MAX; i++){
    data[7*i+1] = true;
    data[7*i+6] = true;
  }

  for(int i = 5; i < MAX; i++)
    if(data[i]) 
      for(int j = 2*i; j < MAX; j+=i) data[j] = false;

  for(int i = 2; i < MAX; i++)
    if(data[i])MSPrime.push_back(i);
}

void solve(int in){
  for(int i = 0; i < MSPrime.size(); i++)
    if(!(in%MSPrime[i])) cout << " " << MSPrime[i];				 
}
int main(){
  make();
  int in;
  while(cin >> in){
    if(in == 1) break;
    
    cout << in << ":";
    solve(in);
    cout << endl;
  }
  return 0;
}