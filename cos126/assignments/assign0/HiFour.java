public class HiFour
{
    public static void main(String[] args)
    {
        String str = "Hi ";
        for(int i = args.length-1; i >=1; i--)
        {
            str += args[i] + ", ";
        }
        str += "and " + args[0] + ".";
        StdOut.println(str);
    }
}
