public class Sort3
{
    public static void main(String[] args)
    {
        int a = Integer.parseInt(args[0]);
        int b = Integer.parseInt(args[1]);
        int c = Integer.parseInt(args[2]);

        if(b > c) {int t = b; b = c; c = t;}
        if(a > b) {int t = a; a = b; b = t;}
        if(a > c) {int t = a; a = c; b = t;}

        System.out.println(a + " " + b + " " + c);
    }
}
