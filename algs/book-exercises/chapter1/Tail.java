/***************************************
 * Compilation:  javac Tail.java
 * Execution:    java Tail k < file.txt
 *
 * print the last k lines of 'file.txt'
 *
 * ***************************************/
public class Tail
{
    public static void main(String[] args)
    {
        int k = Integer.parseInt(args[0]);
        Stack<String> s = new Stack<String>();
        Stack<String> q = new Stack<String>();

        while(StdIn.hasNextLine())
            s.push(StdIn.readLine());

        for(int i=0; i < k ; i++)
        {
            if(s.isEmpty())
                break;
            q.push(s.pop());
        }

        while(!q.isEmpty())
        {
            System.out.println(q.pop());
        }

    }
}
