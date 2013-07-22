import java.util.*;


public class Snow {
  static double[] x = new double[10], y = new double[10], z = new double[10], r = new double[10];
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    for (int i = 0; i < n; i++) {
      x[i] = s.nextDouble();
      y[i] = s.nextDouble();
      z[i] = s.nextDouble();
      r[i] = s.nextDouble();
    }
    
    Random rnd = new Random();
    int k = 10000000;
    int count = 0;
    for (int i = 0; i < k; i++) {
      double xt = rnd.nextDouble() * 10;
      double yt = rnd.nextDouble() * 10;
      double zt = rnd.nextDouble() * 10;
      for (int j = 0; j < n; j++) {
        if ((xt-x[j])*(xt-x[j]) + (yt-y[j])*(yt-y[j]) + (zt-z[j])*(zt-z[j]) < r[j]*r[j]) {
          count++;
          break;
        }
      }
    }
    System.out.println(Math.round(1000.0 * count / k));
  }
}

