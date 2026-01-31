import java.util.*;

public class ThreeSum {

    /*
     * Brute-force Approach
     * Time Complexity: O(n^3)
     * Space Complexity: O(number of triplets) due to set
     */
    static List<List<Integer>> threeSumBrute(int n, int[] nums) {
        Set<List<Integer>> set = new HashSet<>();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    if (nums[i] + nums[j] + nums[k] == 0) {
                        List<Integer> temp = Arrays.asList(nums[i], nums[j], nums[k]);
                        Collections.sort(temp); // handle uniqueness
                        set.add(temp);
                    }
                }
            }
        }

        return new ArrayList<>(set);
    }

    /*
     * Hashing-based Approach
     * Time Complexity: O(n^2)
     * Space Complexity: O(n) + output
     */
    static List<List<Integer>> threeSumHashing(int n, int[] nums) {
        Set<List<Integer>> set = new HashSet<>();

        for (int i = 0; i < n; i++) {
            Set<Integer> hashSet = new HashSet<>();
            for (int j = i + 1; j < n; j++) {
                int third = -(nums[i] + nums[j]);
                if (hashSet.contains(third)) {
                    List<Integer> temp = Arrays.asList(nums[i], nums[j], third);
                    Collections.sort(temp);
                    set.add(temp);
                }
                hashSet.add(nums[j]);
            }
        }

        return new ArrayList<>(set);
    }

    /*
     * Optimal Approach (Two-Pointer after sorting)
     * Time Complexity: O(n^2)
     * Space Complexity: O(1) (excluding output)
     */
    static List<List<Integer>> threeSumOptimal(int n, int[] nums) {
        Arrays.sort(nums);
        List<List<Integer>> ans = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // skip duplicates

            int j = i + 1;
            int k = n - 1;

            while (j < k) {
                int sum = nums[i] + nums[j] + nums[k];
                if (sum < 0) {
                    j++;
                } else if (sum > 0) {
                    k--;
                } else {
                    ans.add(Arrays.asList(nums[i], nums[j], nums[k]));
                    j++;
                    k--;

                    while (j < k && nums[j] == nums[j - 1]) j++;
                    while (j < k && nums[k] == nums[k + 1]) k--;
                }
            }
        }
        return ans;
    }

    // ---------- Utility function ----------
    static void printResult(String label, List<List<Integer>> res) {
        System.out.println(label + ":");
        for (List<Integer> triplet : res) {
            for (int val : triplet) System.out.print(val + " ");
            System.out.println();
        }
        System.out.println("--------------------------");
    }

    // ---------- Main ----------
    public static void main(String[] args) {
        int[] nums = {-1, 0, 1, 2, -1, -4};
        int n = nums.length;

        printResult("Brute-force Result", threeSumBrute(n, nums));
        printResult("Hashing Result", threeSumHashing(n, nums));
        printResult("Optimal Two-Pointer Result", threeSumOptimal(n, nums));
    }
}
