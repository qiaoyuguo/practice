/* Chapter 1.3 web exercise 8
 * Compilation: javac Tag.java
 * Execution:   java Tag 10010100100100100100100
 **/
public class Tag
{
    public static void main(String[] args)
    {
        String str = args[0];
        Queue<Character> s= new Queue<Character>();
        
        for(int i = 0; i < str.length(); i++)
           //s.enqueue(str[i]); 
           s.enqueue(str.charAt(i)); 
        while(s.size() >= 3)
        {
            if(s.peek() == '0')
            {
                for(int  i = 0; i < 3; i++)
                    s.dequeue();
                s.enqueue('0');
                s.enqueue('0');
            }
            else if(s.peek() == '1')
            {
                for(int i = 0; i < 3; i++)
                    s.dequeue();
                s.enqueue('1');
                s.enqueue('1');
                s.enqueue('0');
                s.enqueue('1');
            }
            System.out.println(s);
        }
    }
}
