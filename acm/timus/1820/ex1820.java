import java.util.Scanner;

public class ex1820
{
    public static void main(String []args)
    {
        Scanner s= new Scanner(System.in);
        int n = s.nextInt();
        int k = s.nextInt();

        if(k >= n)
            System.out.printf("%d\n", 2);
        else
        {
            if( (n*2) % k != 0)
                System.out.printf("%d\n", (n*2)/k + 1);
            else
                System.out.printf("%d\n", (n*2)/k);
        }
    }
}
