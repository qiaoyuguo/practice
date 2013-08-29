import java.util.Scanner;

public class ex1197
{
    public static boolean is_valid(int i,int j)
    {
        if(i < 1 || j < 1 || i > 8 || j > 8)
            return false;
        else
            return true;
    }
    public static int handle(Scanner s)
    {
        String input;
        int [][]tbl = {{1,2}, {1,-2}, {2,-1}, {2,1}, {-1,2}, {-1,-2}, {-2,1}, {-2,-1}};
        int i,j,k;
        int count = 0;

        input = s.nextLine(); 
        if(input.length() != 2)
           return -1;
        i = input.charAt(0) - 'a' + 1;
        j = input.charAt(1) - '0';

        for(k = 0; k < 8; k++)
        {
            if(is_valid(i+tbl[k][0], j+tbl[k][1]))
            {
                ++count;
            }
        }

        return count;
    }
    public static void main(String[] args)
    {
        Scanner s = new Scanner(System.in);
        
        int n = s.nextInt();
        s.nextLine(); // ignore the newline character after the number
        for(int i = 0; i < n; i++)
            System.out.println(handle(s));
    }


}
