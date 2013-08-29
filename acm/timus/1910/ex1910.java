import java.util.Scanner;

public class ex1910
{
    public static void main(String[] args)
    {
        int sum;
        int max_sum = 0;
        int count = 0;
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        int a = s.nextInt();
        int b = s.nextInt();
       
        for(int i = 2; i < n; i++)
        {
            int c = s.nextInt();
            sum = a + b + c;
            if(sum > max_sum)
            {
                max_sum = sum;
                count = i;
            }
            a = b;
            b = c;
        }
        System.out.printf("%d %d\n", max_sum, count);


    }
}
