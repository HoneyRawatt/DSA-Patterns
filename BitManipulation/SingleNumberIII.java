package BitManipulation;

import java.util.*;

public class SingleNumberIII {

    /*
     Brute Force Approach:
     - Count frequency of each number using a map
     - Numbers appearing exactly once are the answer
     Time Complexity: O(n) with HashMap (or O(n log n) with TreeMap)
     Space Complexity: O(n)
    */
    public static List<Integer> singleNumberBrute(int[] nums) {
        Map<Integer, Integer> map = new HashMap<>();
        for (int num : nums) {
            map.put(num, map.getOrDefault(num, 0) + 1);
        }

        List<Integer> ans = new ArrayList<>();
        for (int key : map.keySet()) {
            if (map.get(key) == 1) ans.add(key);
        }
        return ans;
    }

    /*
     Optimized Bit Manipulation Approach:
     - XOR of all numbers gives xor_val = num1 ^ num2
     - Find rightmost set bit in xor_val (bit where num1 and num2 differ)
     - Partition numbers into two groups based on that bit
     - XOR each group to get num1 and num2
     Time Complexity: O(n)
     Space Complexity: O(1)
    */
    public static List<Integer> singleNumberOptimized(int[] nums) {
        int xorVal = 0;
        for (int num : nums) xorVal ^= num;

        // Find rightmost set bit
        int rightmost = xorVal & -xorVal;

        int num1 = 0, num2 = 0;
        for (int num : nums) {
            if ((num & rightmost) != 0) num1 ^= num; // group 1
            else num2 ^= num;                         // group 2
        }

        return Arrays.asList(num1, num2);
    }

    public static void main(String[] args) {
        int[] nums = {1, 2, 1, 3, 2, 5};

        List<Integer> bruteAns = singleNumberBrute(nums);
        System.out.println("Brute: " + bruteAns.get(0) + ", " + bruteAns.get(1));

        List<Integer> optAns = singleNumberOptimized(nums);
        System.out.println("Optimized: " + optAns.get(0) + ", " + optAns.get(1));
    }
}
