#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

typedef vector<double> VD;

#define sgn(x) (((x) > 0) - ((x) < 0))

struct poly {
  VD coeff;
  
  poly(const VD &coeff) : coeff(coeff) {}
  
  bool is_constant() const {return coeff.size() == 1;}
  
  poly derivative() const {
    if (is_constant()) return poly(VD(1, 0.0));
    VD d(coeff.size() - 1);
    for (int i = 1; i < coeff.size(); i++) d[i - 1] = coeff[i] * i;
    return poly(d);
  }
  
  double eval(double x) const {
    double ans = 0;
    for (int i = coeff.size() - 1; i >= 0; i--) {
      ans *= x;
      ans += coeff[i];
    }
    return ans;
  }
};

double bisect(const poly &p, double lower, double upper) {
  if (upper - lower < 1e-5) return lower;
  double mid = (lower + upper) / 2;
  if (sgn(p.eval(mid)) == sgn(p.eval(lower))) {
    return bisect(p, mid, upper);
  } else {
    return bisect(p, lower, mid);
  }
}

VD roots(const poly &p) {
  if (p.is_constant()) return VD(0);
  VD critical_values = roots(p.derivative());
  critical_values.push_back(1e6);
  
  VD ans;
  double lower = -1e6;
  for (int i = 0; i < critical_values.size(); i++) {
    double upper = critical_values[i];
    if (sgn(p.eval(lower)) != sgn(p.eval(upper)))
      ans.push_back(bisect(p, lower, upper));
    
    lower = upper;
  }
  
  return ans;
}

int main() {
  int n;
  cin >> n;
  VD arr(n+1);
  for (int i = 0; i <= n; i++) cin >> arr[i];
  
  VD ans = roots(poly(arr));
  cout << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++) printf("%.4f\n", ans[i]);
  
  return 0;
}

