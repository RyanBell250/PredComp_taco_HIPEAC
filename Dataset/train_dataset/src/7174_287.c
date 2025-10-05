#include <bits/stdc++.h>
using namespace std;
#pragma comment(linker, "/STACK:16777216")
const int inf = 0x3f3f3f3f;
const long double pi = acos(-1.0);
const string debug_line = "yolo";
const double PI = 4 * atan(1);
int countG = 0;
bool poss[100010];
bool possible = 0;
vector<int> answer;
bool visited[100010];
vector<int> answerG[100010];
vector<int> groupM[100010];
int group[100010];
bool marked[100010];
vector<pair<pair<int, int>, int> > Adj[100010];
int prev1[100010];
vector<int> answerR;
vector<int> answerB;
bool possR = 1;
bool possB = 1;
int n;
void DFS1(int u, int p) {
  visited[u] = true;
  groupM[countG].push_back(u);
  group[u] = countG;
  for (auto &(t1) : (Adj[u])) {
    if (!visited[t1.first.first]) {
      DFS1(t1.first.first, u);
    }
  }
}
void DFS2(int u, int p) {
  visited[u] = true;
  int count1 = 0;
  int count2 = 0;
  for (auto &(t1) : (Adj[u])) {
    if (visited[t1.first.first]) {
      int colore = (prev1[t1.first.second] + t1.second) % 2;
      if (colore == 0) {
        count1++;
      } else {
        count2++;
      }
    }
  }
  if (count1 != 0 && count2 == 0) {
    answer.push_back(u);
    for (auto &(t1) : (Adj[u])) {
      prev1[t1.first.second]++;
      prev1[t1.first.second] %= 2;
    }
    for (auto &(t1) : (Adj[u])) {
      if (!visited[t1.first.first]) {
        DFS2(t1.first.first, u);
      }
    }
  } else if (count1 == 0) {
    for (auto &(t1) : (Adj[u])) {
      if (!visited[t1.first.first]) {
        DFS2(t1.first.first, u);
      }
    }
  } else if (count1 != 0 && count2 != 0) {
    answer.push_back(u);
    for (auto &(t1) : (Adj[u])) {
      prev1[t1.first.second]++;
      prev1[t1.first.second] %= 2;
    }
    for (auto &(t1) : (Adj[u])) {
      if (!visited[t1.first.first]) {
        DFS2(t1.first.first, u);
      }
    }
  }
}
void DFS(int u, int p) {
  visited[u] = true;
  int count1 = 0;
  int count2 = 0;
  for (auto &(t1) : (Adj[u])) {
    if (visited[t1.first.first]) {
      int colore = (prev1[t1.first.second] + t1.second) % 2;
      if (colore == 0) {
        count1++;
      } else {
        count2++;
      }
    }
  }
  if (count2 != 0 && count1 == 0) {
    answer.push_back(u);
    for (auto &(t1) : (Adj[u])) {
      prev1[t1.first.second]++;
      prev1[t1.first.second] %= 2;
    }
    for (auto &(t1) : (Adj[u])) {
      if (!visited[t1.first.first]) {
        DFS(t1.first.first, u);
      }
    }
  } else if (count2 == 0) {
    for (auto &(t1) : (Adj[u])) {
      if (!visited[t1.first.first]) {
        DFS(t1.first.first, u);
      }
    }
  } else if (count1 != 0 && count2 != 0) {
    answer.push_back(u);
    for (auto &(t1) : (Adj[u])) {
      prev1[t1.first.second]++;
      prev1[t1.first.second] %= 2;
    }
    for (auto &(t1) : (Adj[u])) {
      if (!visited[t1.first.first]) {
        DFS(t1.first.first, u);
      }
    }
  }
}
void solve(int color) {
  cerr << "color"
       << " = " << (color) << endl;
  answer.clear();
  for (int(i) = (0); (i) < (n + 1); ++(i)) {
    visited[i] = false;
    poss[i] = false;
    marked[i] = false;
    prev1[i] = 0;
  }
  if (color == 0) {
    for (int(i) = (0); (i) < (countG); ++(i)) {
      for (int(j) = (0); (j) < (2); ++(j)) {
        for (auto &(t1) : (groupM[i])) {
          visited[t1] = false;
          for (auto &(t2) : (Adj[t1])) {
            prev1[t2.first.second] = 0;
          }
        }
        answer.clear();
        if (j == 0) {
          visited[groupM[i][0]] = true;
          for (auto &(t1) : (Adj[groupM[i][0]])) {
            DFS(t1.first.first, groupM[i][0]);
          }
          bool isanswer = true;
          for (auto &(t1) : (groupM[i])) {
            for (auto &(t2) : (Adj[t1])) {
              if ((prev1[t2.first.second] + t2.second) % 2 == 1) {
                isanswer = false;
              }
            }
          }
          if (isanswer) {
            answerG[i] = answer;
            poss[i] = true;
          }
        } else {
          visited[groupM[i][0]] = true;
          for (auto &(t1) : (Adj[groupM[i][0]])) {
            prev1[t1.first.second] = 1;
          }
          for (auto &(t1) : (Adj[groupM[i][0]])) {
            DFS(t1.first.first, groupM[i][0]);
          }
          answer.push_back(groupM[i][0]);
          bool isanswer = true;
          for (auto &(t1) : (groupM[i])) {
            for (auto &(t2) : (Adj[t1])) {
              if ((prev1[t2.first.second] + t2.second) % 2 == 1) {
                isanswer = false;
              }
            }
          }
          if (isanswer) {
            if (answerG[i].size() > answer.size()) {
              answerG[i] = answer;
              poss[i] = true;
            }
          }
        }
      }
    }
    bool answeris = true;
    for (int(i) = (0); (i) < (countG); ++(i)) {
      if (!poss[i]) {
        possR = false;
        return;
      }
    }
    int size1 = 0;
    for (int(i) = (0); (i) < (countG); ++(i)) {
      for (auto &(t1) : (answerG[i])) {
        marked[t1] = true;
      }
    }
    int answer1 = 0;
    for (int(i) = (1); (i) < (n + 1); ++(i)) {
      if (marked[i]) {
        answer1++;
      }
    }
    if (answer1 < n - answer1) {
      for (int(i) = (1); (i) < (n + 1); ++(i)) {
        if (marked[i]) {
          answerR.push_back(i);
        }
      }
    } else {
      for (int(i) = (1); (i) < (n + 1); ++(i)) {
        if (!marked[i]) {
          answerR.push_back(i);
        }
      }
    }
  } else {
    for (int(i) = (0); (i) < (countG); ++(i)) {
      for (int(j) = (0); (j) < (2); ++(j)) {
        for (auto &(t1) : (groupM[i])) {
          visited[t1] = false;
          for (auto &(t2) : (Adj[t1])) {
            prev1[t2.first.second] = 0;
          }
        }
        answer.clear();
        if (j == 0) {
          visited[groupM[i][0]] = true;
          for (auto &(t1) : (Adj[groupM[i][0]])) {
            DFS2(t1.first.first, groupM[i][0]);
          }
          bool isanswer = true;
          for (auto &(t1) : (groupM[i])) {
            for (auto &(t2) : (Adj[t1])) {
              if ((prev1[t2.first.second] + t2.second) % 2 == 0) {
                isanswer = false;
              }
            }
          }
          if (isanswer) {
            answerG[i] = answer;
            poss[i] = true;
          }
        } else {
          visited[groupM[i][0]] = true;
          for (auto &(t1) : (Adj[groupM[i][0]])) {
            prev1[t1.first.second] = 1;
          }
          for (auto &(t1) : (Adj[groupM[i][0]])) {
            DFS2(t1.first.first, groupM[i][0]);
          }
          bool isanswer = true;
          answer.push_back(groupM[i][0]);
          for (auto &(t1) : (groupM[i])) {
            for (auto &(t2) : (Adj[t1])) {
              if ((prev1[t2.first.second] + t2.second) % 2 == 0) {
                isanswer = false;
              }
            }
          }
          if (isanswer) {
            if (answerG[i].size() > answer.size()) {
              answerG[i] = answer;
              poss[i] = true;
            }
          }
        }
      }
    }
    bool answeris = true;
    for (int(i) = (0); (i) < (countG); ++(i)) {
      if (!poss[i]) {
        possB = false;
        return;
      }
    }
    int size1 = 0;
    for (int(i) = (0); (i) < (countG); ++(i)) {
      for (auto &(t1) : (answerG[i])) {
        marked[t1] = true;
      }
    }
    int answer1 = 0;
    for (int(i) = (1); (i) < (n + 1); ++(i)) {
      if (marked[i]) {
        answer1++;
      }
    }
    if (answer1 < n - answer1) {
      for (int(i) = (1); (i) < (n + 1); ++(i)) {
        if (marked[i]) {
          answerB.push_back(i);
        }
      }
    } else {
      for (int(i) = (1); (i) < (n + 1); ++(i)) {
        if (!marked[i]) {
          answerB.push_back(i);
        }
      }
    }
  }
}
int main() {
  int m;
  scanf("%d%d", &n, &m);
  for (int(i) = (0); (i) < (m); ++(i)) {
    int a, b;
    string c;
    cin >> a >> b >> c;
    if (c[0] == 'B') {
      Adj[a].push_back(make_pair(make_pair(b, i), 0));
      Adj[b].push_back(make_pair(make_pair(a, i), 0));
    } else if (c[0] == 'R') {
      Adj[a].push_back(make_pair(make_pair(b, i), 1));
      Adj[b].push_back(make_pair(make_pair(a, i), 1));
    }
  }
  for (int(i) = (1); (i) < (n + 1); ++(i)) {
    if (!visited[i]) {
      DFS1(i, 0);
      countG++;
    }
  }
  solve(0);
  solve(1);
  vector<int> answerF;
  if (possR == 0 && possB == 0) {
    printf("-1\n");
    return 0;
  } else if (possR == 0) {
    answerF = answerB;
  } else if (possB == 0) {
    answerF = answerR;
  } else if (possR != 0 && possB != 0) {
    if (answerR.size() < answerB.size()) {
      answerF = answerR;
    } else {
      answerF = answerB;
    }
  }
  cerr << "( "
       << "answerB.size()"
       << " , "
       << "answerR.size()"
       << " ) = ( " << (answerB.size()) << " , " << (answerR.size()) << " )\n";
  ;
  printf("%d\n", answerF.size());
  for (auto &(t1) : (answerF)) {
    printf("%d ", t1);
  }
  printf("\n");
  return 0;
}
