import java.util.*;
import java.text.*;


public class MInv {
  static double[][] A = new double[1024][2048];
  static int n;
  
  static final double EPS = 1e-7;

  static boolean rref() {
    int i, j;
    
    for (int r = 0; r < n; r++) {
      int maxrow = r;
      for (i = r + 1; i < n; i++) {
        if (Math.abs(A[i][r]) > Math.abs(A[maxrow][r])) maxrow = i;
      }
      if (Math.abs(A[maxrow][r]) < EPS) return false;
      double[] temp = A[r]; A[r] = A[maxrow]; A[maxrow] = temp;
      
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

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    n = s.nextInt();
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        A[i][j] = s.nextDouble();
        A[i][j+n] = (i == j ? 1.0 : 0.0);
      }
    }
    
    DecimalFormat fmt = new DecimalFormat("0.0000");
    
    if (rref()) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          System.out.print(fmt.format(A[i][j+n]) + " ");
        }
        System.out.println();
      }
    } else {
      System.out.println("not invertible");
    }
  }
}

