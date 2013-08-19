public class ArrayStackOfStrings
{
    private String[] a;
    private int N = 0;

    public ArrayStackOfStrings(int max) { a = new String[max];}
    public boolean isEmpty() { return (N == 0);}
    public void push(String item) {a[N++] = item;}
    public String pop()  {return a[--N];}
}
