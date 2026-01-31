import java.util.*;

public class LongestConsecutiveSequence {

    // 🔴 Brute Force (O(N^2))
    static int longestConsecutiveBrute(int[] arr) {
        int n = arr.length;
        if (n == 0) return 0;

        int longest = 1;

        for (int i = 0; i < n; i++) {
            int x = arr[i];
            int cnt = 1;

            // Linear search for next consecutive number
            while (contains(arr, x + 1)) {
                x = x + 1;
                cnt++;
            }

            longest = Math.max(longest, cnt);
        }

        return longest;
    }

    // Helper function for brute force
    static boolean contains(int[] arr, int target) {
        for (int num : arr) {
            if (num == target) return true;
        }
        return false;
    }

    // 🟠 Better Approach using Sorting (O(N log N))
    static int longestConsecutiveBetter(int[] arr) {
        int n = arr.length;
        if (n == 0) return 0;

        Arrays.sort(arr);

        int lastSmall = Integer.MIN_VALUE;
        int cnt = 0;
        int longest = 1;

        for (int i = 0; i < n; i++) {
            if (arr[i] - 1 == lastSmall) {
                cnt++;
                lastSmall = arr[i];
            } else if (arr[i] != lastSmall) { // skip duplicates
                cnt = 1;
                lastSmall = arr[i];
            }
            longest = Math.max(longest, cnt);
        }

        return longest;
    }

    // 🟢 Optimal using HashSet (O(N))
    static int longestConsecutiveOptimal(int[] arr) {
        int n = arr.length;
        if (n == 0) return 0;

        HashSet<Integer> set = new HashSet<>();
        for (int num : arr) {
            set.add(num);
        }

        int longest = 1;

        for (int num : set) {
            // Check if this is the start of a sequence
            if (!set.contains(num - 1)) {
                int cnt = 1;
                int x = num;

                while (set.contains(x + 1)) {
                    x++;
                    cnt++;
                }

                longest = Math.max(longest, cnt);
            }
        }

        return longest;
    }

    public static void main(String[] args) {
        int[] arr = {100, 4, 200, 1, 3, 2};

        System.out.print("Original Array: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }

        System.out.println("\n\n🔴 Brute Force Answer: " + longestConsecutiveBrute(arr.clone()));
        System.out.println("🟠 Better (Sorted) Answer: " + longestConsecutiveBetter(arr.clone()));
        System.out.println("🟢 Optimal (Using Set) Answer: " + longestConsecutiveOptimal(arr));
    }
}
