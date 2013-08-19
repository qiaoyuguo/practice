public class Freq
{
    public static void main(String[] args)
    {
        ST<String, Integer> st = new ST<String, Integer>();
        while(!StdIn.isEmpty())
        {
            String key = StdIn.readString();
            if(st.contains(key)) st.put(key, st.get(key)+1);
            else                 st.put(key, 1);
        }

        for(String s :st)
        {
            StdOut.println(st.get(s) + " " + s);
        }
    }
}
