/*
 * Compilation: javac Palindrome.java
 * Execution:   java Palindrome "A MAN, A PLAN, A CANAL - PANAMA"
 * 
 * Find if the input string is a Palindrome
 ******************************************/
public class Palindrome
{
    public static void main(String[] args)
    {
        String inputStr = args[0];
        Stack<Character> s = new Stack<Character>();
        Queue<Character> q = new Queue<Character>();

        for(int i = 0; i < inputStr.length(); i++)
        {
            char c = inputStr.charAt(i);
            s.push(c);
            q.enqueue(c);
        }

        boolean isPalindrome = true;
        while(!s.isEmpty() &&  !q.isEmpty())
        {
            char c1 = s.peek(); 
            if(!(Character.isLetter(c1)))
            {
                s.pop();
                continue;
            }
            char c2 =  q.peek();
            if(!(Character.isLetter(c2)))
            {
                q.dequeue();
                continue;
            }
            if(s.pop() != q.dequeue())
            {
                isPalindrome = false;
            }
        }

        if(isPalindrome)
            System.out.println(inputStr + " is palindrome");
        else
            System.out.println(inputStr + " is not palindrome");
    }
}
