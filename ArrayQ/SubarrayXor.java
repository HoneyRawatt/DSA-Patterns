import java.util.*;

public class SubarrayXor {

    // ---------- Optimal Approach using HashMap ----------
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    public static int subarrayXORK(int[] arr, int k) {
        int xor = 0;
        Map<Integer, Integer> map = new HashMap<>();
        int count = 0;

        map.put(0, 1); // Initialize prefix XOR 0

        for (int i = 0; i < arr.length; i++) {
            xor ^= arr[i];

            int x = xor ^ k; // Needed prefix XOR to satisfy: prefix ^ xor = k
            count += map.getOrDefault(x, 0);

            map.put(xor, map.getOrDefault(xor, 0) + 1);
        }

        return count;
    }

    // ---------- Brute-force Approach ----------
    // Time Complexity: O(n^2)
    // Space Complexity: O(1)
    public static int subarrayXORKBrute(int[] arr, int k) {
        int n = arr.length;
        int count = 0;

        for (int i = 0; i < n; i++) {
            int xor = 0;
            for (int j = i; j < n; j++) {
                xor ^= arr[j];
                if (xor == k) count++;
            }
        }

        return count;
    }

    // ---------- Main ----------
    public static void main(String[] args) {
        int[] arr = {4, 2, 2, 6, 4};
        int k = 6;

        System.out.println("Optimal count: " + subarrayXORK(arr, k));
        System.out.println("Brute-force count: " + subarrayXORKBrute(arr, k));
    }
}
