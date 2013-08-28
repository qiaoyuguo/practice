import java.util.Stack;
import java.util.Scanner;
public class ex1001
{
    public static void main(String[] args)
    {
        long []arr = new long[128*1024];
        int count = 0;
        Scanner s = new Scanner(System.in);

        while(s.hasNextLong())
        {
            arr[count++] = s.nextLong();
        }
        for(int i = count-1; i >= 0; i--)
        {
            System.out.printf("%.4f\n", Math.sqrt(arr[i]));
        }
    }
}
