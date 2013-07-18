#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

int dist[1024][1024];

struct cell {
  int r, c;
  cell(int r, int c) : r(r), c(c) {}
};

int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};

int main() {
  int r, c, k;
  cin >> r >> c >> k;
  
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) dist[i][j] = -1;
  }
  
  queue<cell> q;
  int curR, curC;
  for (int i = 0; i < k; i++) {
    cin >> curR >> curC;
    dist[curR][curC] = 0;
    q.push(cell(curR, curC));
  }
  
  int maxDist = 0;
  while (!q.empty()) {
    cell cur = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {
      curR = cur.r + dr[i];
      curC = cur.c + dc[i];
        if (curR >= 0 && curR < r && curC >= 0 && curC < c && dist[curR][curC] == -1) {
          dist[curR][curC] = dist[cur.r][cur.c] + 1;
          maxDist = max(maxDist, dist[curR][curC]);
          q.push(cell(curR, curC));
        }
    }
  }
  
  cout << maxDist << endl;
  
  return 0;
}

