public class Diff
{
    public static void main(String[] args)
    {
        In in0 = new In(args[0]);
        In in1 = new In(args[1]);

        String s = in0.readAll();
        String t = in1.readAll();
        StdOut.println(s.equals(t));
    }
}
