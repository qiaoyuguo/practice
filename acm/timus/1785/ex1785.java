import java.util.Scanner;
public class ex1785
{
    public static int getIndex(int n)
    {
        if(n >= 1 && n <= 4)
            return 0;
        else if(n >= 5 && n <= 9)
            return 1;
        else if(n >= 10 && n <= 19)
            return 2;
        else if(n >= 20 && n <= 49)
            return 3;
        else if(n >= 50 && n <= 99)
            return 4;
        else if(n >= 100 && n <= 249)
            return 5;
        else if(n >= 250 && n <= 499)
            return 6;
        else if(n >= 500 && n <= 999)
            return 7;
        else if(n >= 1000)
            return 8;
        else 
            return 9;
    }

    public static void main(String[] args)
    {
        String []arr = {"few", "several", "pack", "lots", "horde", "throng",
                        "swarm", "zounds", "legion", "below zero"};
        int n;
        Scanner s = new Scanner(System.in);

        while(s.hasNextInt())
        {
            n = s.nextInt();
            System.out.println(arr[getIndex(n)]);
        }
    }

}
