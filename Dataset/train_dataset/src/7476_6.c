#include <vector>
#include <set>
#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

using vector2D = vector< vector<int> >;
const int B = 5;
int N;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

struct State {
  vector2D board;
  int x, y;
};

vector<int> score;
long long int solve(vector2D board) {
  long long int ret = 0, bonus = 1;
  for(; ; bonus++) {
    bool update = false;
    vector2D checked(B, vector<int>(B));
    
    for(int i=0; i<B; i++) {
      for(int j=0; j<B; j++) {
        // empty
        if(board[i][j] == 0) continue;

        vector<int> dirs = {2, 0};
        for(auto k : dirs) {
          // right or down
          int cons = 0;
          int nx = i, ny = j;
          while(nx < B && ny < B) {
            if(board[nx][ny] != board[i][j]) break;
            cons++;
            nx += dx[k], ny += dy[k];
          }
          if(cons >= 3) {
            update = true;
            nx = i, ny = j;
            while(nx < B && ny < B) {
              if(board[nx][ny] != board[i][j]) break;
              checked[nx][ny] = 1;
              nx += dx[k], ny += dy[k];
            }
          }
        }
      }
    }
    // printf("bonus = %lld, update = %d\n", bonus, update);
    if(!update) break;

    for(int i=0; i<B; i++) {
      for(int j=0; j<B; j++) {
        // empty or no change
        if(board[i][j] == 0 || checked[i][j] == false) continue;

        int col = board[i][j] - 1;
        board[i][j] = 0;
        ret += bonus * score[col];
      }
    }

    // blockfall
    for(int i=B-1; i>=0; i--) {
      for(int j=0; j<B; j++) {
        int row = i;
        for(; row < B-1 && board[row+1][j] == 0; row++) {
          swap(board[row][j], board[row+1][j]);
        }
      }
    }
  }
  
  return ret;
}

int main() {
  while(cin >> N, N >= 0) {
    vector2D board(B, vector<int>(B));
    for(int i=0; i<B; i++) {
      for(int j=0; j<B; j++) {
        cin >> board[i][j];
      }
    }
    score.clear();
    for(int i=0; i<B; i++) {
      int val; cin >> val;
      score.push_back(val);
    }

    set<vector2D> cand;
    cand.insert(board);
    queue<State> que;
    for(int i=0; i<B; i++) {
      for(int j=0; j<B; j++) {
        que.push(State{board, i, j});
      }
    }

    // printf("enumerate begin\n");
    for(int i=0; i<N; i++) {
      queue<State> nxt;
      while(que.size()) {
        State cur = que.front(); que.pop();
        vector2D board = cur.board;
        int x = cur.x, y = cur.y;

        for(int k=0; k<4; k++) {
          int nx = x + dx[k], ny = y + dy[k];
          if(nx < 0 || nx >= B || ny < 0 || ny >= B) continue;
          swap(board[x][y], board[nx][ny]);
          nxt.push(State{board, nx, ny});
          cand.insert(board);
          swap(board[x][y], board[nx][ny]);
        }
      }
      swap(nxt, que);
    }
    // printf("enumerate end\n");

    long long int ans = 0;
    for(auto b : cand) {
      ans = max(ans, solve(b));
    }
    cout << ans << endl;
  }
  return 0;
}

