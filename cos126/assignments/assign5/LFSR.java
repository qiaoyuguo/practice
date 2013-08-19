public class LFSR
{
    private String reg;
    private int N;
    private int tapPos;

    public LFSR(String seed, int tap)
    {
        reg = seed;
        tapPos = tap;
        N = seed.length();
    }
    public static int ithConv(String str, int i)
    {
        return (int)(str.charAt(i) - '0');
    }
    public int step()
    {
        String oldReg = reg;
        int tapBit = ithConv(oldReg, N-tapPos -1);
        int fstBit = ithConv(oldReg, 0);
        int curLastBit = tapBit ^ fstBit;
        char lastChar;
        if(curLastBit == 0)
            lastChar = '0';
        else
            lastChar = '1';
        
        reg = oldReg.substring(1) + lastChar;
        return curLastBit;
    }

    public int generate(int k)
    {
        int sum = 0;
        for(int i = 0; i < k; i++)
        {
            int curBit = step();
            sum = (sum << 1) + curBit;
        }
        return sum;
    }
    public String toString()
    {
        return reg;
    }
    public static void main(String[] args)
    {
        String seed = "01101000010";
        LFSR sr = new LFSR(seed, 8);
        StdOut.println(sr);

        for(int i = 0; i < 10; i++)
        {
            int bit = sr.step();
            StdOut.println(sr + " " + bit);
        }

        sr = new LFSR(seed, 8);
        for(int i = 0; i < 10; i++)
        {
            int r = sr.generate(5);
            StdOut.println(sr + " " + r);
        }
    }
}
