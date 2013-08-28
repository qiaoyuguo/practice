import java.util.Scanner;
public class ex1068
{
    public static void main(String []args)
    {
        Scanner s  = new Scanner(System.in);
        int n = s.nextInt();
        int sum = 0;
        if(n >= 1)
        {
            for(int i = 1; i <= n; i++)
                sum += i;
        } 
        else
        {
            for(int i = n; i <= 1; i++)
                sum += i;
        }

        System.out.println(sum);
    }
}
