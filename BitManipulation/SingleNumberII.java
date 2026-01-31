package BitManipulation;

import java.util.*;

public class SingleNumberII {

    /*
     Brute Force Approach:
     - Count occurrences of each element using a map
     - Return the element whose count is 1
     Time Complexity: O(n log n)  (TreeMap) or O(n) with HashMap
     Space Complexity: O(n)
    */
    public static int singleNumberBrute(int[] nums) {
        Map<Integer, Integer> map = new HashMap<>();
        for (int num : nums) {
            map.put(num, map.getOrDefault(num, 0) + 1);
        }
        for (int key : map.keySet()) {
            if (map.get(key) == 1) return key;
        }
        return -1; // not found
    }

    /*
     Better Approach (Bitwise counting):
     - For each bit position 0..30, count how many numbers have that bit set
     - If count % 3 == 1, that bit belongs to the unique number
     Time Complexity: O(31 * n) -> O(n)
     Space Complexity: O(1)
    */
    public static int singleNumberBitCount(int[] nums) {
        int ans = 0;
        for (int bit = 0; bit < 31; bit++) {
            int count = 0;
            for (int num : nums) {
                if ((num & (1 << bit)) != 0) count++;
            }
            if (count % 3 == 1) {
                ans |= (1 << bit);
            }
        }
        return ans;
    }

    /*
     Sorting Approach:
     - Sort the array
     - Unique number will not follow the "appear 3 times" pattern
     Time Complexity: O(n log n)
     Space Complexity: O(1) or O(n) depending on sort implementation
    */
    public static int singleNumberSort(int[] nums) {
        Arrays.sort(nums);
        int n = nums.length;
        for (int i = 0; i < n - 1; i += 3) {
            if (i + 1 >= n || nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }
        return nums[n - 1];
    }

    /*
     Bit Manipulation (Most Optimized):
     - Maintain two variables (ones and twos)
     - ones -> bits appeared once
     - twos -> bits appeared twice
     - On the third occurrence, bit is removed from both
     Time Complexity: O(n)
     Space Complexity: O(1)
    */
    public static int singleNumberOptimized(int[] nums) {
        int ones = 0, twos = 0;
        for (int num : nums) {
            ones = (ones ^ num) & ~twos;
            twos = (twos ^ num) & ~ones;
        }
        return ones;
    }

    public static void main(String[] args) {
        int[] nums = {2, 2, 3, 2};

        System.out.println("Brute Force: " + singleNumberBrute(nums));
        System.out.println("Bit Count: " + singleNumberBitCount(nums));
        System.out.println("Sorting: " + singleNumberSort(nums));
        System.out.println("Optimized Bit Manipulation: " + singleNumberOptimized(nums));
    }
}

