import java.util.Scanner;

public class ex1787
{
    public static void main(String[] args)
    {
        Scanner s = new Scanner(System.in);
        int k = s.nextInt();
        int n = s.nextInt();
        int sum = 0;

        for(int i = 0; i < n; i++)
        {
            int tmp = s.nextInt();
            sum += tmp - k;
            if(sum < 0)
                sum = 0;
        }
        System.out.printf("%d\n", sum);
    }
}
