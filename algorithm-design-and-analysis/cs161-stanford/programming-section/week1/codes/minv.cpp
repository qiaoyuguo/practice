#include <iostream>
#include <cstdio>
#include <cmath>
#include <utility>

using namespace std;

#define EPS 1e-7

double A[1024][2048];
int n;

bool rref() {
  int i, j;
  
  for (int r = 0; r < n; r++) {
    int maxrow = r;
    for (i = r + 1; i < n; i++) {
      if (fabs(A[i][r]) > fabs(A[maxrow][r])) maxrow = i;
    }
    if (fabs(A[maxrow][r]) < EPS) return false;
    swap(A[r], A[maxrow]);
    
    double entry = A[r][r];
    for (j = 0; j < 2 * n; j++) A[r][j] /= entry;
    for (i = 0; i < n; i++) {
      if (i == r) continue;
      double toElim = A[i][r];
      for (j = 0; j < 2 * n; j++) A[i][j] -= toElim * A[r][j];
    }
  }
  
  return true;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> A[i][j];
      A[i][j+n] = (i == j ? 1.0 : 0.0);
    }
  }
  
  if (rref()) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        printf("%.4f ", A[i][j+n]);
      }
      cout << endl;
    }
  } else {
    cout << "not invertible" << endl;
  }
}

