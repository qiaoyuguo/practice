import java.util.*;


public class Inversion {
  static int[] arr;
  
  static long count(int start, int end) {
    if (start >= end - 1) return 0;
    int mid = (start + end) / 2;
    long ans = count(start, mid) + count(mid, end);
    
    int[] merge = new int[end - start];
    int lidx = start, uidx = mid, midx = 0;
    while (lidx < mid && uidx < end) {
      if (arr[lidx] > arr[uidx]) {
        ans += mid - lidx;
        merge[midx++] = arr[uidx++];
      } else merge[midx++] = arr[lidx++];
    }
    
    while (lidx < mid) merge[midx++] = arr[lidx++];
    while (uidx < end) merge[midx++] = arr[uidx++];
    
    for (int i = 0; i < merge.length; i++) arr[start + i] = merge[i];
    
    return ans;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    arr = new int[n];
    for (int i = 0; i < n; i++) arr[i] = s.nextInt();
    
    System.out.println(count(0, n));
  }
}

