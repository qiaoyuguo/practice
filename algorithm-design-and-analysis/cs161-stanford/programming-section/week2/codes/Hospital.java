import java.util.*;


public class Hospital {
  static int[][] dist = new int[1024][1024];
  
  static class Cell {
    int r, c;
    public Cell(int r, int c) {this.r = r; this.c = c;}
  }
  
  static int[] dr = new int[]{1, 0, -1, 0};
  static int[] dc = new int[]{0, 1, 0, -1};
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int r = s.nextInt(), c = s.nextInt(), k = s.nextInt();
    
    for (int i = 0; i < r; i++) {
      for (int j = 0; j < c; j++) dist[r][c] = -1;
    }
    
    Queue<Cell> queue = new LinkedList<Cell>();
    for (int i = 0; i < k; i++) {
      int curR = s.nextInt();
      int curC = s.nextInt();
      dist[curR][curC] = 0;
      queue.add(new Cell(curR, curC));
    }
    
    int maxDist = 0;
    while (!queue.isEmpty()) {
      Cell cur = queue.remove();
      for (int i = 0; i < 4; i++) {
        int curR = cur.r + dr[i];
        int curC = cur.c + dc[i];
        if (curR >= 0 && curR < r && curC >= 0 && curC < c && dist[curR][curC] == -1) {
          dist[curR][curC] = dist[cur.r][cur.c] + 1;
          maxDist = Math.max(maxDist, dist[curR][curC]);
          queue.add(new Cell(curR, curC));
        }
      }
    }
    
    System.out.println(maxDist);
  }
}
