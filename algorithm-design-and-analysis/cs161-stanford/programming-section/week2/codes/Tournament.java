import java.util.*;


public class Tournament {
  static long[] adj = new long[64];
  
  static int n, ans = 1;
  static long allCovered;
  
  static boolean search(int start, long cover, int size) {
    if (cover == allCovered) return true;
    if (size == ans) return false;
    for (int i = start; i < n; i++) {
      if (search(i + 1, cover | adj[i], size + 1)) return true;
    }
    return false;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    n = s.nextInt();
    allCovered = (1L << n) - 1;
    
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        adj[i] = (adj[i] << 1) + s.nextInt();
        if (i == j) adj[i]++;
      }
    }
    
    while (!search(0, 0L, 0)) ans++;
    
    System.out.println(ans);
  }
}

