import java.util.*;

public class MissingElement {

    /* 
     * Approach 1: XOR Method
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int missingele_XOR(int[] a, int n) {
        int xor1 = 0, xor2 = 0;

        for (int i = 0; i < n; i++) {
            xor2 ^= a[i];       // XOR of array elements
            xor1 ^= (i + 1);    // XOR of 1..n
        }
        xor1 ^= (n + 1);        // include (n+1)

        return xor1 ^ xor2;
    }

    /* 
     * Approach 2: Sum Formula
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     * ⚠ Risk of integer overflow for very large n
     */
    static int missingele_sum(int[] a, int n) {
        int totalSum = (n + 1) * (n + 2) / 2;
        int arraySum = 0;

        for (int i = 0; i < n; i++) {
            arraySum += a[i];
        }
        return totalSum - arraySum;
    }

    /* 
     * Approach 3: Brute Force
     * Time Complexity: O(n²)
     * Space Complexity: O(1)
     * ❌ Not optimal for large n
     */
    static int missingele_brute(int[] a, int n) {
        for (int i = 1; i <= n + 1; i++) {
            boolean found = false;
            for (int j = 0; j < n; j++) {
                if (a[j] == i) {
                    found = true;
                    break;
                }
            }
            if (!found) return i;
        }
        return -1;
    }

    /* 
     * Approach 4: Hashing
     * Time Complexity: O(n)
     * Space Complexity: O(n)
     */
    static int missingele_hashing(int[] a, int n) {
        int[] hash = new int[n + 2];

        for (int i = 0; i < n; i++) {
            hash[a[i]] = 1;
        }

        for (int i = 1; i <= n + 1; i++) {
            if (hash[i] == 0) return i;
        }
        return -1;
    }

    // Driver Code
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int[] arr = new int[n];

        System.out.println("Enter the elements:");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        System.out.println("Missing Element using XOR: " + missingele_XOR(arr, n));
        System.out.println("Missing Element using SUM: " + missingele_sum(arr, n));
        System.out.println("Missing Element using BRUTE: " + missingele_brute(arr, n));
        System.out.println("Missing Element using HASHING: " + missingele_hashing(arr, n));
    }
}
