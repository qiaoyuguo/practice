// java Gambler 5 25 10000
// java Gambler 5 25 1000
// java Gambler 500 2500 1000
public class Gambler
{
    public static void main(String[] args)
    {
        int stake = Integer.parseInt(args[0]);
        int goal = Integer.parseInt(args[1]);
        int trials = Integer.parseInt(args[2]);

        // Count wins among args[2] trials
        int wins = 0;
        for (int i = 0; i < trials; i++)
        {
            // Do one gambler's ruin experiment
            int t = stake;
            while(t > 0 && t < goal)
            {
                // flip coin and update
                if(Math.random() < 0.5) t++;
                else t--;
            }
            if(t == goal) wins++;
        }
        System.out.println(wins + " wins of " + trials);
    }
}
