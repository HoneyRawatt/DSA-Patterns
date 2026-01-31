package SlidingWindow;
import java.util.*;

public class countnoofnicesubarray {
    /*
    ========================================================
    Function: numberOfSubarrays
    --------------------------------------------------------
    Counts the number of subarrays with exactly k odd numbers.
    Formula:
        exactly_k = atMost(k) - atMost(k - 1)
    --------------------------------------------------------
    Time Complexity: O(n) (calls atMost twice)
    Space Complexity: O(1)
    ========================================================
    */
    public static int numberOfSubarrays(int[] nums, int k) {
        return atMost(nums, k) - atMost(nums, k - 1);
    }

    /*
    ========================================================
    Function: atMost
    --------------------------------------------------------
    Counts the number of subarrays with at most 'goal' odd numbers
    using sliding window approach.

    Steps:
    1. Initialize window pointers l = 0, r = 0.
    2. Maintain sum = number of odd numbers in window.
    3. Expand r while sum <= goal.
    4. Shrink l if sum > goal.
    5. For each r, add (r - l + 1) to the total count.
    --------------------------------------------------------
    Time Complexity: O(n)
    Space Complexity: O(1)
    ========================================================
    */
    public static int atMost(int[] nums, int goal) {
        if (goal < 0) return 0; // no subarray possible

        int l = 0, count = 0, sum = 0;

        for (int r = 0; r < nums.length; r++) {
            sum += nums[r] % 2; // 1 if odd, 0 if even

            // Shrink window if odd count exceeds goal
            while (sum > goal) {
                sum -= nums[l] % 2;
                l++;
            }

            count += r - l + 1; // All subarrays ending at r
        }

        return count;
    }

    // ------------------- MAIN METHOD -------------------
    public static void main(String[] args) {
        int[] nums = {1, 1, 2, 1, 1};
        int k = 3;

        int result = numberOfSubarrays(nums, k);
        System.out.println("Number of subarrays with exactly " + k + " odd numbers: " + result);
    }
}
