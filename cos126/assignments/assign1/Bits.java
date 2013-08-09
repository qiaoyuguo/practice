public class Bits
{
    public static void main(String[] args)
    {
        int n = Integer.parseInt(args[0]);
        if(n < 0)
        {
            System.out.println("Illegal input");
            return;
        }


        int result = 0;
        for(; n >= 1; n /= 2)
            result += 1;
        System.out.println(result);
    }
}
