public class CouponCollector
{
    public static void main(String[] args)
    {
        int N = Integer.parseInt(args[0]);
        int cardcnt = 0;
        int valcnt = 0;

        // Do simulation
        boolean[] found = new boolean[N];
        while(valcnt < N)
        {
            int val = (int) (Math.random() * N);
            cardcnt++;
            if (!found[val])
            {
                valcnt++;
                found[val] = true;
            }
        }

        // all N distinct cards found
        System.out.println(cardcnt);
    }
}
