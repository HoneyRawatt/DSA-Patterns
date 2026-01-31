package BitManipulation;
import java.util.Scanner;

public class MinBitFlips {

    /*
     Function: minBitFlips
     Purpose: Find the minimum number of bit flips to convert 'start' into 'goal'.
     Approach: XOR + Brian Kernighan's algorithm to count set bits.
     Time Complexity: O(k), where k is the number of set bits in (start ^ goal)
                      Worst case: O(log(max(start, goal)))
     Space Complexity: O(1)
    */
    static int minBitFlips(int start, int goal) {

        // XOR identifies differing bits
        int ans = start ^ goal;

        int cnt = 0;
        // Brian Kernighan’s algorithm
        while (ans != 0) {
            ans = ans & (ans - 1);
            cnt++;
        }
        return cnt;
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter start number: ");
        int start = sc.nextInt();

        System.out.print("Enter goal number: ");
        int goal = sc.nextInt();

        int result = minBitFlips(start, goal);

        System.out.println("Minimum bit flips needed: " + result);

        sc.close();
    }
}
