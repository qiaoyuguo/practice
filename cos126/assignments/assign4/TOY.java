/*************************************************************************
 *  Compilation:  javac TOY.java
 *  Execution:    java TOY file.toy 
 *  Dependencies: StdIn.java In.java
 *
 *  We use variables of type int to store the TOY registers, main
 *  memory, and program counter even though in TOY these quantities
 *  are 16 and 8 bit integers. Java does not have an 8-bit unsigned
 *  type. The type short in Java does represent 16-bit 2's complement
 *  integers, but using it requires alot of casting. Instead, we are
 *  careful to treat all of the variable as if they were the appropriate
 *  type so that the behavior truly models the TOY machine.
 *
 *************************************************************************/

import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class TOY { 

    // return a 4-digit hex string corresponding to 16-bit integer n
    public static String toHex(int n) {
        return String.format("%04X", n & 0xFFFF);
    }

    // return a 16-bit integer corresponding to the 4-digit hex string s
    public static int fromHex(String s) {
        return Integer.parseInt(s, 16)  & 0xFFFF;
    }

    // write to an array of hex integers, 8 per line to standard output
    public static void show(int[] a) {
        for (int i = 0; i < a.length; i++) {
            System.out.print(toHex(a[i]) + " ");
            if (i % 8 == 7) System.out.println();
        }
    }

    // write core dump of TOY to standard output
    public static void dump(int pc, int[] R, int[] mem) {

        System.out.println("PC:");
        System.out.printf("%02X\n", pc);
        System.out.println();
        System.out.println("Registers:");
        show(R);
        System.out.println();
        System.out.println("Main memory:");
        show(mem);
        System.out.println();
    }


    // the TOY simulator
    public static void main(String[] args) { 

        int pc    = 0x10;             // program counter
        int[] R   = new int[16];      // 16 registers
        int[] mem = new int[256];     // 256 main memory locations


       /****************************************************************
        *  Read in memory location and instruction.         
        *  A valid input line consists of 2 hex digits followed by a 
        *  colon, followed by any number of spaces, followed by 4
        *  hex digits. The rest of the line is ignored.
        ****************************************************************/
        // read the TOY program directly from the file
        String filename = args[0];
        In in = new In(filename);

        String regexp = "([0-9A-Fa-f]{2}):[ \t]*([0-9A-Fa-f]{4}).*";
        Pattern pattern = Pattern.compile(regexp);
        while (!in.isEmpty()) {
            String line = in.readLine();
            Matcher matcher = pattern.matcher(line);
            if (matcher.find()) {
                int addr = fromHex(matcher.group(1));
                int inst = fromHex(matcher.group(2));
                mem[addr] = inst;
            }
        }
        System.out.println("Core Dump of TOY Before Executing");
        System.out.println("---------------------------------------");
        dump(pc, R, mem);

        System.out.println("Terminal");
        System.out.println("---------------------------------------");

        while (true) {
            // Fetch and parse
            int inst = mem[pc++];           // fetch next instruction
            int op   = (inst >> 12) &  15;    // get opcode (bits 12-15)
            int d    = (inst >>  8) &  15;    // get dest   (bits  8-11)
            int s    = (inst >>  4) &  15;    // get s      (bits  4- 7)
            int t    = (inst >>  0) &  15;    // get t      (bits  0- 3)
            int addr = (inst >>  0) & 255;    // get addr   (bits  0- 7)

            // halt
            if (op == 0) break;

            // stdin 
            if ((addr == 255 && op == 8) || (R[t] == 255 && op == 10))
                mem[255] = fromHex(StdIn.readString());

            // Execute
            switch (op) {
                case  1: R[d] = R[s] +  R[t];               break;    // add
                case  2: R[d] = R[s] -  R[t];               break;    // subtract
                case  3: R[d] = R[s] &  R[t];               break;    // bitwise and
                case  4: R[d] = R[s] ^  R[t];               break;    // bitwise xor
                case  5: R[d] = R[s] << R[t];               break;    // shift left
                case  6: R[d] = (short) R[s] >> R[t];       break;    // shift right
                case  7: R[d] = addr;                       break;    // load address
                case  8: R[d] = mem[addr];                  break;    // load
                case  9: mem[addr] = R[d];                  break;    // store
                case 10: R[d] = mem[R[t] & 255];            break;    // load indirect
                case 11: mem[R[t] & 255] = R[d];            break;    // store indirect
                case 12: if ((short) R[d] == 0) pc = addr;  break;    // branch if zero
                case 13: if ((short) R[d] >  0) pc = addr;  break;    // branch if positive
                case 14: pc = R[d];                         break;    // jump indirect
                case 15: R[d] = pc; pc = addr;              break;    // jump and link
            }

            // stdout
            if ((addr == 255 && op == 9) || (R[t] == 255 && op == 11))
                System.out.println(toHex(mem[255]));

            R[0] = 0;                // ensure R0 is always 0
            R[d] = R[d] & 0xFFFF;    // don't let R[d] overflow a 16-bit integer
            pc = pc & 0xFF;          // don't let pc overflow an 8-bit integer

        }


       /*****************************************************
        *  Print out final contents of TOY.
        *****************************************************/
        System.out.println();
        System.out.println("Core Dump of TOY After Executing");
        System.out.println("---------------------------------------");
        dump(pc, R, mem);
    }
}
