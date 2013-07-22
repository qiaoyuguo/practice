#include <iostream>
#include <cstdlib>

using namespace std;

double x[10], y[10], z[10], r[10];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> x[i] >> y[i] >> z[i] >> r[i];
  
  int k = 10000000;
  int count = 0;
  for (int i = 0; i < k; i++) {
    double xt = 10.0 * rand() / RAND_MAX;
    double yt = 10.0 * rand() / RAND_MAX;
    double zt = 10.0 * rand() / RAND_MAX;
    for (int j = 0; j < n; j++) {
      if ((xt-x[j])*(xt-x[j]) + (yt-y[j])*(yt-y[j]) + (zt-z[j])*(zt-z[j]) < r[j]*r[j]) {
        count++;
        break;
      }
    }
  }
  
  cout << (int) ((1000.0 * count / k) + 0.5) << endl;
    
  return 0;
}

