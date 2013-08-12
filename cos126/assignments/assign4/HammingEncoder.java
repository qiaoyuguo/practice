/*************************************************************************
 *  Compilation:  javac HammingEncoder.java
 *  Execution:    java HammingEncoder < encode12.txt
 *  Dependencies: StdIn.java StdOut.java
 *  
 *  Read in sequences of 4 bits at a time from standard input,
 *  compute 3 parity bits for the Hamming code, and print the
 *  resulting 7 bits to standard output.
 *
 *  % more encode3.txt 
 *  0001 0001 0000 0001
 *  0001 0001 0001 0000
 *  0001 0001 0001 0001
 *  FFFF     
 *
 *  % java HammingEncoder < encode3.txt 
 *  0001
 *  0001
 *  0000
 *  0001
 *  0001
 *  0000
 *  0000
 *  0001
 *  0001
 *  0001
 *  0000
 *  0000
 *  0000
 *  0000
 *  0001
 *  0001
 *  0001
 *  0001
 *  0001
 *  0001
 *  0001
 *
 *************************************************************************/

public class HammingEncoder {

    // return an integer corresponding to the 4-digit hex string
    public static int fromHex(String s) {
        return Integer.parseInt(s, 16)  & 0xFFFF;
    }

    public static void main(String[] args) {
        while(!StdIn.isEmpty()) {
            int m1 = fromHex(StdIn.readString());
            if (m1 == 0xFFFF) break;
            int m2 = fromHex(StdIn.readString());
            int m3 = fromHex(StdIn.readString());
            int m4 = fromHex(StdIn.readString());

            // compute parity bits
            int p1 = m1 ^ m2 ^ m4;
            int p2 = m1 ^ m3 ^ m4;
            int p3 = m2 ^ m3 ^ m4;

            // print results to standard output
            // the %04d prints the integer with leading 0s
            StdOut.printf("%04d\n%04d\n%04d\n%04d\n", m1, m2, m3, m4);
            StdOut.printf("%04d\n%04d\n%04d\n", p1, p2, p3);
        }
    }
}
