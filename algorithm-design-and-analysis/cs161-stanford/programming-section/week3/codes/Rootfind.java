import java.util.*;
import java.text.*;


public class Rootfind {
  static class Poly {
    public static final Poly ZERO = new Poly(new double[]{0});
    double[] coeff;
    
    public Poly(double[] coeff) {this.coeff = coeff;}
    
    public Poly derivative() {
      if (isConstant()) return Poly.ZERO;
      double[] d = new double[coeff.length - 1];
      for (int i = 1; i < coeff.length; i++) d[i - 1] = coeff[i] * i;
      return new Poly(d);
    }
    
    public double eval(double x) {
      double ans = 0;
      for (int i = coeff.length - 1; i >= 0; i--) {
        ans *= x;
        ans += coeff[i];
      }
      return ans;
    }
    
    public boolean isConstant() {return coeff.length == 1;}
  }
  
  static double bisect(Poly p, double lower, double upper) {
    if (upper - lower < 1e-5) return lower;
    double mid = (lower + upper) / 2;
    if (Math.signum(p.eval(mid)) == Math.signum(p.eval(lower))) {
      return bisect(p, mid, upper);
    } else {
      return bisect(p, lower, mid);
    }
  }
  
  static ArrayList<Double> roots(Poly p) {
    if (p.isConstant()) return new ArrayList<Double>();
    ArrayList<Double> criticalValues = roots(p.derivative());
    criticalValues.add(1e6);
    
    ArrayList<Double> ans = new ArrayList<Double>();
    double lower = -1e6;
    for (double upper : criticalValues) {
      if (Math.signum(p.eval(lower)) != Math.signum(p.eval(upper)))
        ans.add(bisect(p, lower, upper));
      
      lower = upper;
    }
    
    return ans;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    double[] arr = new double[n + 1];
    for (int i = 0; i <= n; i++) arr[i] = s.nextDouble();
    ArrayList<Double> ans = roots(new Poly(arr));
    DecimalFormat fmt = new DecimalFormat("0.0000");
    System.out.println(ans.size());
    for (double root : ans) System.out.println(fmt.format(root));
  }
}

