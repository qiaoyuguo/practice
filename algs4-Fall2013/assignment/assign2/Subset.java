public class Subset
{
    public static void main(String[] args)
    {
        int n = Integer.parseInt(args[0]);
        String []a = StdIn.readStrings();

        RandomizedQueue<String> rndQueue = new RandomizedQueue<String>();
        for(int i = 0; i < a.length; i++)
            rndQueue.enqueue(a[i]);
        for(int i = 0; i < n; i++)
        {
            StdOut.println(rndQueue.sample());
        }
    }
}
