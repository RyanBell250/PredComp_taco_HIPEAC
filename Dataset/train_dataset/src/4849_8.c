#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100 * 1000 + 7, MAX_EDGE = 2 * 100 * 1000 + 7;
int n, m, k, parent[MAXN], pmp, bus, height[MAXN];
vector<int> adj[MAXN], specialAdj[MAXN], volunteers;
bool isVolunteer[MAXN], isPassed[MAXN];
queue<int> BFSQue;
void BFS(int root, int heightLimit) {
  isPassed[root] = true;
  BFSQue.push(root);
  while (BFSQue.size()) {
    root = BFSQue.front();
    BFSQue.pop();
    for (int i = 0; i < adj[root].size(); ++i) {
      int neighbor = adj[root][i];
      if (!isPassed[neighbor]) {
        if (isVolunteer[neighbor]) {
          if (parent[root] != -1) {
            specialAdj[neighbor].push_back(parent[root]);
            specialAdj[parent[root]].push_back(neighbor);
          }
          parent[neighbor] = neighbor;
          height[neighbor] = 0;
        } else {
          parent[neighbor] = parent[root];
          height[neighbor] = height[root] + 1;
        }
        if (height[neighbor] < heightLimit) {
          BFSQue.push(neighbor);
        }
        isPassed[neighbor] = true;
      } else {
        if (parent[root] != parent[neighbor] and parent[root] != -1 and
            parent[neighbor] != -1 and
            height[root] + height[neighbor] + 1 <= heightLimit) {
          specialAdj[parent[neighbor]].push_back(parent[root]);
          specialAdj[parent[root]].push_back(parent[neighbor]);
        }
      }
    }
  }
}
void specialAdjBFS(int root) {
  memset(isPassed, 0, sizeof isPassed);
  isPassed[root] = true;
  BFSQue.push(root);
  isPassed[root] = true;
  while (BFSQue.size()) {
    root = BFSQue.front();
    BFSQue.pop();
    for (int i = 0; i < specialAdj[root].size(); ++i) {
      int neighbor = specialAdj[root][i];
      if (!isPassed[neighbor]) {
        BFSQue.push(neighbor);
        isPassed[neighbor] = true;
      }
    }
  }
  for (int i = 0; i <= n; ++i) {
    specialAdj[i].clear();
  }
  return;
}
bool check(int moveLimit) {
  memset(isPassed, 0, sizeof isPassed);
  memset(parent, -1, sizeof parent);
  memset(height, 0, sizeof height);
  for (int i = 0; i < (int)volunteers.size(); ++i) {
    int temp = volunteers[i];
    BFSQue.push(temp);
    parent[temp] = temp;
  }
  BFS(pmp, moveLimit);
  specialAdjBFS(pmp);
  return isPassed[bus];
}
int binarySearch(int spanBegin, int spanEnd) {
  while (spanEnd - spanBegin > 1) {
    int middle = (spanBegin + spanEnd) / 2;
    if (check(middle)) {
      spanEnd = middle;
    } else {
      spanBegin = middle;
    }
  }
  return spanEnd;
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin >> n >> m >> k;
  for (int i = 0; i < k; ++i) {
    int temp;
    cin >> temp;
    temp--;
    isVolunteer[temp] = true;
    volunteers.push_back(temp);
  }
  for (int i = 0; i < m; ++i) {
    int tempOne, tempTwo;
    cin >> tempOne >> tempTwo;
    tempOne--;
    tempTwo--;
    adj[tempOne].push_back(tempTwo);
    adj[tempTwo].push_back(tempOne);
  }
  cin >> pmp >> bus;
  pmp--;
  bus--;
  isVolunteer[pmp] = isVolunteer[bus] = true;
  int answer = binarySearch(0, MAX_EDGE);
  if (answer == MAX_EDGE) {
    cout << -1 << endl;
    return 0;
  }
  cout << answer << endl;
  return 0;
}
