import java.util.*;

public class SubarraySumK {

    /*
     * Optimal Approach using Hash Map
     * Time Complexity: O(n)
     * Space Complexity: O(n) for map
     */
    public static int subarrayWithSumK(int[] a, int k) {
        int sum = 0;
        Map<Integer, Integer> mp = new HashMap<>();
        int n = a.length;
        int cnt = 0;

        mp.put(sum, 1); // Initialize with prefix sum 0

        for (int i = 0; i < n; i++) {
            sum += a[i];

            int x = sum - k;   // IMPORTANT: sum - k
            cnt += mp.getOrDefault(x, 0);

            mp.put(sum, mp.getOrDefault(sum, 0) + 1);
        }

        return cnt;
    }

    /*
     * Brute-force Approach
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     */
    public static int subarrayWithSumKBrute(int[] a, int k) {
        int n = a.length;
        int cnt = 0;

        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = i; j < n; j++) {
                sum += a[j];
                if (sum == k) cnt++;
            }
        }

        return cnt;
    }

    // Test
    public static void main(String[] args) {
        int[] arr = {1, 2, 3, -3, 1, 1, 1};
        int k = 3;

        System.out.println(subarrayWithSumK(arr, k));
        System.out.println(subarrayWithSumKBrute(arr, k));
    }
}
