public class Merge
{
    public static void sort(String[] a)
    {
        sort(a, 0, a.length);
    }
    public static void sort(String[] a, int lo, int hi)
    {
        int N = hi - lo;
        if(N <= 1)
            return;
        int mid = lo + N/2;
        sort(a, lo, mid);
        sort(a, mid, hi);

        String[] aux = new String[N];
        int i = lo,j = mid;
        for(int k = 0; k < N; k++)
        {
            if (i == mid) aux[k] = a[j++];
            else if(j == hi) aux[k] = a[i++];
            else if(a[j].compareTo(a[i])<0) aux[k] = a[j++];
            else aux[k] = a[i++];
        }
        for(int k = 0; k < N; k++)
            a[lo + k] = aux[k];
    }
    private static void printArray(String[] a)
    {
        for(int i = 0; i < a.length; i++)
        {
            if(i > 0)
                System.out.print(" ");
            System.out.print(a[i]);
        }
        System.out.println();
    }


    public static void main(String[] args)
    {
        int n = 10;
        String[] strs = new String[n];
        for(int i = 0; i < n; i++)
        {
            char c = "abcdefghijklmn".charAt(i);
            strs[i] = Character.toString(c);
        }
        String[] a = new String[n];
        for(int i = 0; i < n; i++)
        {
            a[i] = strs[(int)(Math.random() * 10)];

        }
        printArray(a);
        sort(a);
        printArray(a);
    }
}
