import java.util.Collections;
import java.util.ArrayList;
import java.util.Arrays;

public class Fast
{
    public static void main(String[] args)
    {
        In infile = new In(args[0]);
        int N = infile.readInt(); 
        StdDraw.setXscale(0, 32768) ;
        StdDraw.setYscale(0, 32768);
        Point []pts = new Point[N];
        Point []new_pts = new Point[N];
        //double []slopes = new double[N];
        //int count = 0;
        //ArrayList<Point> pts = new ArrayList<Point>();
        for(int i = 0; i < N; i++)
        {
            int x = infile.readInt();
            int y = infile.readInt();
            pts[i] = new Point(x,y);
            pts[i].draw();
            new_pts[i] = pts[i];
            //Point curPt = new Point(x,y);
            //pts.add(curPt);
            //curPt.draw();
        }
        Arrays.sort(pts);
        Arrays.sort(new_pts);
        
        /* 
        for(int i = 0; i < N; i++)
            System.out.print(pts.get(i) + " ");
        System.out.println();
        */
        
        
        //ArrayList<Point> new_pts = (ArrayList<Point>)pts.clone();
        //boolean []visited = new boolean[N];
        for(int i = 0; i < N-1; i++)
        {
            Point cur_point = pts[i];
            //Collections.sort(new_pts);
            Arrays.sort(new_pts);
            Arrays.sort(new_pts,i+1, N,  cur_point.SLOPE_ORDER);
            //Arrays.sort( new_pts, cur_point.SLOPE_ORDER);
            double []slopes = new double[N];
            for(int idxs = 0; idxs < N; idxs++)
                slopes[idxs] = cur_point.slopeTo(pts[idxs]);
            //Collections.sort(new_pts, cur_point.SLOPE_ORDER);

            //debug
            /* 
            System.out.print(i+","+cur_point+" ");
            for(int m = 0; m < N; m++)
                System.out.print(new_pts[m] + "," + cur_point.slopeTo(new_pts[m]) + " ");
                //System.out.print(new_pts.get(m) + "," + cur_point.slopeTo(new_pts.get(m)) + " ");
            System.out.println();
            */
            

            int j = i+1; 
            while(j < N)
            {
                Point start_point = new_pts[j];
                //if(cur_point.slopeTo(new Point(30000,0)) == Double.NEGATIVE_INFINITY)
                //    StdOut.println("start point " + start_point);
                double cur_slope = cur_point.slopeTo(start_point);
                int k;
                for(k = j+1; k < N; k++)
                {
                    //if(cur_point.slopeTo(new_pts.get(k)) != cur_slope)
                    if(cur_point.slopeTo(new_pts[k]) != cur_slope)
                        break;
                }
                if(k - j < 3)
                {
                    j = k;
                    continue;
                }
                /*
                int idx = pts.indexOf(start_point);
                if(visited[idx])
                {
                    j = k;
                    continue;
                }
                */
                //visited[pts.indexOf(cur_point)] = true;
                //StdOut.print(i + " " + cur_point + "=>");
                boolean found = false;
                int schIdx;
                for(schIdx = 0; schIdx < i; schIdx ++)
                    if(slopes[schIdx] == cur_slope)
                    {
                        found = true;
                        break;
                    }
                //StdOut.println("find in left array" + cur_point + " " + slopes[schIdx]);
                if(found)
                {
                    j = k;
                    continue;
                }
                StdOut.print(cur_point);
                //cur_point.draw();
                for(int l = j; l < k; l++)
                {
                    //Point tmpPoint = new_pts.get(l);
                    //visited[pts.indexOf(tmpPoint)] = true;
                    //StdOut.print( " -> " + tmpPoint);
                    StdOut.print( " -> " + new_pts[l]);
                    //tmpPoint.draw();
                }
                //cur_point.drawTo(new_pts.get(k-1));
                cur_point.drawTo(new_pts[k-1]);

                StdOut.println();
                j = k;

                /*
                for(int l = 0; l < N; l++)
                    System.out.print(visited[l] + " ");
                System.out.println();
                */
            }
        }
   }
}
