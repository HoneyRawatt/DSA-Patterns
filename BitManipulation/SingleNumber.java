package BitManipulation;

import java.util.Scanner;

public class SingleNumber {

    /*
     Function: singleNumber
     Purpose: Find the element that appears only once where all others appear twice.
     Approach: XOR property (a ^ a = 0, a ^ 0 = a).
     Time Complexity: O(n)  where n = size of array
     Space Complexity: O(1)  no extra space used
    */
    public static int singleNumber(int[] arr) {
        int result = 0; // XOR accumulator

        for (int i = 0; i < arr.length; i++) {
            result ^= arr[i]; // Cancel out pairs, leave the single number
        }
        return result;
    }

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();

        int[] arr = new int[n];
        System.out.print("Enter " + n + " numbers: ");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        System.out.println("Single number is: " + singleNumber(arr));

        /*
         Time Complexity:
             - O(n): single pass through array
         Space Complexity:
             - O(1): constant extra space
        */

        sc.close();
    }
}

