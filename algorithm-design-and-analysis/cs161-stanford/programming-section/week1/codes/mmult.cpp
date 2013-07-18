#include <iostream>

using namespace std;

int A[1024][1024], B[1024][1024], C[1024][1024];
int m, n, p;

void multiply() {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      C[i][j] = 0;
      for (int k = 0; k < n; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

int main() {
  cin >> m >> n >> p;
  
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
    }
  }
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      cin >> B[i][j];
    }
  }
  
  multiply();
  
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      cout << C[i][j] << " ";
    }
    cout << endl;
  }
}

