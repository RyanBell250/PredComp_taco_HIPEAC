
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;
int toSec(const int &h, const int &m, const int &s){
  return s + m * 60 + h * 3600;
}
void showTime(int sec){
  int h = sec / 3600;
  int m = (sec % 3600) / 60;
  int s = sec % 60;
  printf("%02d:%02d:%02d", h, m, s);
}
void showTime(int h, int m, int s){
  printf("%02d:%02d:%02d", h, m, s);
}
int times[60][60][60]; 
void mkTimes(){
  int hor = 0, posHor = 0;
  int min = 0;
  int sec = 0;
  memset(times, -1, sizeof(times));
  while(hor < 12){
    times[posHor][min][sec] = toSec(hor, min, sec);
    sec++;
    if(sec == 60){
      sec = 0;
      min++;
    }
    if(sec == 0 && min % 12 == 0){
      posHor++;
    }
    if(min == 60){
      min = 0;
      hor++;
    }
  }
}
void enumrate(vector<int> &v, vector<int> &allVec, int *perm){
  for(int i = 0; i < 60; i++){
    int tmp = times[perm[0]][perm[1]][perm[2]];
    perm[0] = (perm[0] + 1) % 60;
    perm[1] = (perm[1] + 1) % 60;
    perm[2] = (perm[2] + 1) % 60;
    if(tmp == -1) continue;
    v.push_back(tmp);
    allVec.push_back(tmp);
  }
}
bool check(int start, int end, const vector<int> &v){
  for(int i = 0; i < v.size(); i++){
    if(start <= v[i] && v[i] <= end) return true;
  }
  return false;
}
int main(){
  mkTimes();
  while(1){
    int n;
    cin >> n;
    if(n == 0) break;
    vector<int> t[12];
    vector<int> allVec;
    for(int i = 0; i < n; i++){
      int perm[3];
      for(int j = 0; j < 3; j++){
        cin >> perm[j];
      }
      sort(perm, perm + 3);
      do{
        enumrate(t[i], allVec, perm);
      }while(next_permutation(perm, perm + 3));
    }
    int ansStart = -1, ansEnd = 999999999;
    for(int i = 0; i < allVec.size(); i++){
      for(int j = i + 1; j < allVec.size(); j++){
        int start = allVec[i];
        int end = allVec[j];
        if(start > end) swap(start, end);
        bool flg = true;
        for(int k = 0; k < n; k++){
          if(!check(start, end, t[k])){
            flg = false;
            break;
          }
        }
        if(!flg) continue;
        if(ansEnd - ansStart > end - start ||
           ansEnd - ansStart == end - start && ansStart > start){
          ansStart = start;
          ansEnd = end;
        }
      }
    }
    showTime(ansStart);
    cout << " ";
    showTime(ansEnd);
    cout << endl;
  }
}