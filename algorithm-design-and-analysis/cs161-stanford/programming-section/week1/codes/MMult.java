import java.util.*;


public class MMult {
  static int[][] A = new int[1024][1024];
  static int[][] B = new int[1024][1024];
  
  static int[][] C = new int[1024][1024];
  
  static int m, n, p;
  
  static void multiply() {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < p; j++) {
        C[i][j] = 0;
        for (int k = 0; k < n; k++) {
          C[i][j] += A[i][k] * B[k][j];
        }
      }
    }
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    m = s.nextInt();
    n = s.nextInt();
    p = s.nextInt();
    
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        A[i][j] = s.nextInt();
      }
    }
    
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < p; j++) {
        B[i][j] = s.nextInt();
      }
    }
    
    multiply();
    
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < p; j++) {
        System.out.print(C[i][j] + " ");
      }
      System.out.println();
    }
  }
}
