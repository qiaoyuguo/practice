public class Reverse 
{
    public static void main(String[] args)
    {
        StackOfStrings stack = new StackOfStrings();
        while(!StdIn.isEmpty())
        {
            String s = StdIn.readString();
            stack.push(s);
        }

        while(!stack.isEmpty())
        {
            String s = stack.pop();
            StdOut.println(s);
        }
    }
}
