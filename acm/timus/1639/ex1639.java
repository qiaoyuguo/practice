import java.util.Scanner;

public class ex1639
{
    public static void main(String[]  args)
    {
        Scanner s = new Scanner(System.in);
        int m = s.nextInt();
        int n = s.nextInt();

        if( (m*n) % 2 == 0)
            System.out.printf("%s\n", "[:=[first]");
        else
            System.out.printf("%s\n", "[second]=:]");
    }
}
