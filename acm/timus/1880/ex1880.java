import java.util.Scanner;

public class ex1880
{
    public static boolean binSearch(int []arr, int len, int to_be_find)
    {
        int low = 0; 
        int high = len - 1;
        while(low <= high)
        {
            int mid = (low + high) / 2;
            if(arr[mid] > to_be_find)
                high = mid - 1;
            else if(arr[mid] < to_be_find)
                low = mid + 1;
            else
                return true;
        }
        return false;
    }

    public static void main(String[] args)
    {
        int n = 3;
        int []len = new int[n];
        int [][]a = new int[n][];
        Scanner s = new Scanner(System.in);

        for(int i = 0; i < n; i++)
        {
            len[i] = s.nextInt();
            a[i] = new int[len[i]];
            for(int j = 0; j < len[i]; j++)
            {
                a[i][j] = s.nextInt();
            }
        }
        
        int count = 0;
        for(int j = 0; j < len[0]; j++)
        {
            if(binSearch(a[1], len[1], a[0][j]) 
               && binSearch(a[2], len[2], a[0][j]))
                ++count;
        }
        System.out.println(count);
    }
}
