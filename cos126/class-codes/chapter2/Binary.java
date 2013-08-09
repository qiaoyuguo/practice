public class Binary
{
    public static String convert(int x)
    {
        if(x == 1)
            return "1";
        return convert(x/2) + (x % 2);
    }
    public static void main(String[] args)
    {
        int x = Integer.parseInt(args[0]);
        System.out.println(convert(x));
    }
}
