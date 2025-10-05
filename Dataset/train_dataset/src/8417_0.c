#include <bits/stdc++.h>
using namespace std;
const int MAX_D = 1e5;
const int TASK_COUNT = 5;
const int STATE_COUNT = 6;
const vector<int> COEF = {2, 4, 8, 16, 32};
const vector<int> SCORE = {500, 1000, 1500, 2000, 2500, 3000};
int n;
int answer = MAX_D;
vector<int> s;
vector<int> success;
vector<int> taskScore;
vector<int> successBuffer;
vector<int> precalcTotal;
vector<vector<int>> a;
inline void UpdateAnswer(int d) {
  int total = d + n;
  successBuffer.assign(TASK_COUNT, 0);
  for (int i = 0; i < TASK_COUNT; ++i) {
    if (a[0][i] == -1) {
      continue;
    }
    if (s[i] == 5) {
      successBuffer[i] = 0;
    } else {
      int x = total - COEF[s[i]] * success[i];
      if (x < 0) {
        successBuffer[i] = 0;
      } else {
        successBuffer[i] = x / COEF[s[i]] + 1;
      }
    }
  }
  for (int i = 0; i < TASK_COUNT; ++i) {
    if (successBuffer[i] > d) {
      return;
    }
  }
  taskScore.assign(TASK_COUNT, 0);
  for (int i = 0; i < TASK_COUNT; ++i) {
    int x = success[i] + successBuffer[i];
    if (total < x * 2) {
      taskScore[i] = 500;
    } else if (total < x * 4) {
      taskScore[i] = 1000;
    } else if (total < x * 8) {
      taskScore[i] = 1500;
    } else if (total < x * 16) {
      taskScore[i] = 2000;
    } else if (total < x * 32) {
      taskScore[i] = 2500;
    } else {
      taskScore[i] = 3000;
    }
  }
  int score[2];
  score[0] = score[1] = 0;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < TASK_COUNT; ++j) {
      if (a[i][j] != -1) {
        score[i] += taskScore[j] - a[i][j] * taskScore[j] / 250;
      }
    }
  }
  if (score[0] > score[1]) {
    answer = min(answer, d);
  }
}
void UpdateAnswer() {
  for (int d = 0; d < MAX_D; ++d) {
    UpdateAnswer(d);
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cin >> n;
  a.resize(n, vector<int>(TASK_COUNT, -1));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < TASK_COUNT; ++j) {
      cin >> a[i][j];
    }
  }
  success.resize(TASK_COUNT, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < TASK_COUNT; ++j) {
      if (a[i][j] >= 0) {
        ++success[j];
      }
    }
  }
  for (int d = 0; d <= MAX_D; ++d) {
    int total = n + d;
    successBuffer.assign(TASK_COUNT, 0);
    for (int i = 0; i < TASK_COUNT; ++i) {
      if (a[1][i] != -1 && a[0][i] != -1 && a[1][i] < a[0][i]) {
        successBuffer[i] = d;
      }
    }
    taskScore.assign(TASK_COUNT, 0);
    for (int i = 0; i < TASK_COUNT; ++i) {
      int x = success[i] + successBuffer[i];
      if (total < x * 2) {
        taskScore[i] = 500;
      } else if (total < x * 4) {
        taskScore[i] = 1000;
      } else if (total < x * 8) {
        taskScore[i] = 1500;
      } else if (total < x * 16) {
        taskScore[i] = 2000;
      } else if (total < x * 32) {
        taskScore[i] = 2500;
      } else {
        taskScore[i] = 3000;
      }
    }
    int score[2];
    score[0] = score[1] = 0;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < TASK_COUNT; ++j) {
        if (a[i][j] != -1) {
          score[i] += taskScore[j] - a[i][j] * taskScore[j] / 250;
        }
      }
    }
    if (score[0] > score[1]) {
      answer = min(answer, d);
    }
  }
  if (answer == MAX_D) {
    cout << -1 << endl;
  } else {
    cout << answer << endl;
  }
  return 0;
}
