public class TenDice
{
    // Roll six-sided dice n times
    public static int rollDice(int n)
    {
        int sum = 0;
        for(int i = 0; i < n; i++)
        {
            double rand = Math.random();
            if(rand < 1.0/6)
                sum += 1;
            else if(rand < 2.0/6)
                sum += 2;
            else if(rand < 3.0/6)
                sum += 3;
            else if(rand < 4.0/6)
                sum += 4;
            else if(rand < 5.0/6)
                sum += 5;
            else if(rand < 1.0)
                sum += 6;
        }
        return sum;
    }
    public static void main(String[] args)
    {
        int n = Integer.parseInt(args[0]);
        int[] arr = new int[61];

        for(int i = 0; i < n; i++)
        {
            ++arr[rollDice(10)];
        }
        for(int i = 10; i <= 60; i++)
        {
            System.out.print(i + ":");
            if(arr[i] > 0)
            {
                System.out.print(" ");
                System.out.print(new String(new char[arr[i]]).replace("\0","*"));
            }
            System.out.println();
        }
    }
}
