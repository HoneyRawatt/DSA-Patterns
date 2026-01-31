import java.util.*;

public class LongestSubarraySumK {

    // Brute Force Approach
    // Time Complexity: O(n^2)
    // Space Complexity: O(1)
    static int longestSubarrayWithSumKBrute(int[] a, long k) {
        int n = a.length, maxLen = 0;
        for (int i = 0; i < n; i++) {
            long sum = 0;
            for (int j = i; j < n; j++) {
                sum += a[j];
                if (sum == k) {
                    maxLen = Math.max(maxLen, j - i + 1);
                }
            }
        }
        return maxLen;
    }

    // Hashing (Prefix Sum) Approach
    // Works with negative numbers as well
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    static int longestSubarrayWithSumKHashing(int[] a, long k) {
        Map<Long, Integer> preSumMap = new HashMap<>();
        long sum = 0;
        int maxLen = 0;

        for (int i = 0; i < a.length; i++) {
            sum += a[i];

            if (sum == k) {
                maxLen = Math.max(maxLen, i + 1);
            }

            long rem = sum - k;
            if (preSumMap.containsKey(rem)) {
                int len = i - preSumMap.get(rem);
                maxLen = Math.max(maxLen, len);
            }

            preSumMap.putIfAbsent(sum, i);
        }

        return maxLen;
    }

    // Two-Pointer Approach (Only works for non-negative numbers)
    // Time Complexity: O(n)
    // Space Complexity: O(1)
    static int longestSubarrayWithSumKTwoPointer(int[] a, long k) {
        int left = 0, right = 0, maxLen = 0;
        long sum = 0;

        while (right < a.length) {
            sum += a[right];

            while (left <= right && sum > k) {
                sum -= a[left];
                left++;
            }

            if (sum == k) {
                maxLen = Math.max(maxLen, right - left + 1);
            }

            right++;
        }

        return maxLen;
    }

    // Driver Code
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter array size: ");
        int n = sc.nextInt();
        int[] arr = new int[n];

        System.out.println("Enter the elements: ");
        for (int i = 0; i < n; i++) arr[i] = sc.nextInt();

        System.out.print("Enter target sum k: ");
        long k = sc.nextLong();

        System.out.println("Longest subarray with sum " + k + ":");
        System.out.println("Brute Force: " + longestSubarrayWithSumKBrute(arr, k));
        System.out.println("Hashing: " + longestSubarrayWithSumKHashing(arr, k));
        System.out.println("Two-pointer: " + longestSubarrayWithSumKTwoPointer(arr, k) + " (Only for non-negative numbers)");

        sc.close();
    }
}
