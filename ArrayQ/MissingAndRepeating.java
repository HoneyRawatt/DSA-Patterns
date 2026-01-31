import java.util.*;

public class MissingAndRepeating {

    // Time Complexity: O(n^2)
    // Space Complexity: O(1)
    static int[] find_missing_Repeating_num_brute(int[] a) {
        int n = a.length;
        int repeating = -1, missing = -1;

        for (int val = 1; val <= n; val++) {  // loop over values
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (a[j] == val) cnt++;
            }
            if (cnt == 2) repeating = val;
            else if (cnt == 0) missing = val;

            if (repeating != -1 && missing != -1) break;
        }
        return new int[]{repeating, missing};
    }

    // ✅ 1. Hashing Approach
    static int[] find_missing_Repeating_num_hashing(int[] a) {
        int n = a.length;
        int[] hasharr = new int[n + 1];

        for (int i = 0; i < n; i++) {
            hasharr[a[i]]++;
        }

        int repeating = -1, missing = -1;
        for (int i = 1; i <= n; i++) {
            if (hasharr[i] == 2) repeating = i;
            else if (hasharr[i] == 0) missing = i;
        }
        return new int[]{repeating, missing};
    }

    // ✅ 2. Math Approach
    static int[] find_missing_Repeating_num_Math(int[] a) {
        long n = a.length;

        long sn = (n * (n + 1)) / 2;
        long s2n = (n * (n + 1) * (2 * n + 1)) / 6;

        long s = 0, s2 = 0;
        for (int i = 0; i < n; i++) {
            s += a[i];
            s2 += (long) a[i] * a[i];
        }

        long val1 = s - sn;      // x - y
        long val2 = s2 - s2n;    // x^2 - y^2
        val2 = val2 / val1;      // x + y

        long x = (val1 + val2) / 2;  // repeating
        long y = x - val1;           // missing

        return new int[]{(int) x, (int) y};
    }

    // ✅ 3. XOR Approach
    static int[] find_missing_Repeating_num_xor(int[] a) {
        int n = a.length;
        int xr = 0;

        for (int i = 0; i < n; i++) {
            xr ^= a[i];
            xr ^= (i + 1);
        }

        int bitno = 0;
        while ((xr & (1 << bitno)) == 0) bitno++;

        int one = 0, zero = 0;

        for (int i = 0; i < n; i++) {
            if ((a[i] & (1 << bitno)) != 0) one ^= a[i];
            else zero ^= a[i];
        }

        for (int i = 1; i <= n; i++) {
            if ((i & (1 << bitno)) != 0) one ^= i;
            else zero ^= i;
        }

        int count = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == one) count++;
        }

        if (count == 2) return new int[]{one, zero};
        else return new int[]{zero, one};
    }

    // ✅ Utility function
    static void print_result(int[] res) {
        System.out.println("Repeating: " + res[0] + ", Missing: " + res[1]);
    }

    // ✅ Main function
    public static void main(String[] args) {
        int[] arr = {4, 3, 6, 2, 1, 1}; // 1 repeating, 5 missing

        System.out.println("Brute Force Approach:");
        print_result(find_missing_Repeating_num_brute(arr));

        System.out.println("\nHashing Approach:");
        print_result(find_missing_Repeating_num_hashing(arr));

        System.out.println("\nMath Approach:");
        print_result(find_missing_Repeating_num_Math(arr));

        System.out.println("\nXOR Approach:");
        print_result(find_missing_Repeating_num_xor(arr));
    }
}
