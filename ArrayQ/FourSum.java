import java.util.*;

public class FourSum {

    // ---------- Brute-force Approach ----------
    public static List<List<Integer>> fourSumBrute(int[] nums, int target) {
        int n = nums.length;
        Set<List<Integer>> set = new HashSet<>();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                for (int k = j + 1; k < n; k++) {
                    for (int l = k + 1; l < n; l++) {
                        long sum = 1L * nums[i] + nums[j] + nums[k] + nums[l];
                        if (sum == target) {
                            List<Integer> quad = Arrays.asList(nums[i], nums[j], nums[k], nums[l]);
                            Collections.sort(quad);
                            set.add(quad);
                        }
                    }
                }
            }
        }

        return new ArrayList<>(set);
    }

    // ---------- Hashing-based Approach ----------
    public static List<List<Integer>> fourSumHashing(int[] nums, int target) {
        int n = nums.length;
        Set<List<Integer>> set = new HashSet<>();

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                Set<Long> hashSet = new HashSet<>();
                for (int k = j + 1; k < n; k++) {
                    long sum = 1L * nums[i] + nums[j] + nums[k];
                    long fourth = target - sum;

                    if (hashSet.contains(fourth)) {
                        List<Integer> quad = Arrays.asList(nums[i], nums[j], nums[k], (int) fourth);
                        Collections.sort(quad);
                        set.add(quad);
                    }

                    hashSet.add((long) nums[k]);
                }
            }
        }

        return new ArrayList<>(set);
    }

    // ---------- Optimal Two-Pointer Approach ----------
    public static List<List<Integer>> fourSumOptimal(int[] nums, int target) {
        int n = nums.length;
        List<List<Integer>> ans = new ArrayList<>();
        Arrays.sort(nums);

        for (int i = 0; i < n; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            for (int j = i + 1; j < n; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) continue;

                int k = j + 1;
                int l = n - 1;

                while (k < l) {
                    long sum = 1L * nums[i] + nums[j] + nums[k] + nums[l];

                    if (sum == target) {
                        ans.add(Arrays.asList(nums[i], nums[j], nums[k], nums[l]));
                        k++;
                        l--;

                        while (k < l && nums[k] == nums[k - 1]) k++;
                        while (k < l && nums[l] == nums[l + 1]) l--;
                    } else if (sum < target) {
                        k++;
                    } else {
                        l--;
                    }
                }
            }
        }

        return ans;
    }

    // ---------- Utility to print results ----------
    public static void printResult(String label, List<List<Integer>> res) {
        System.out.println(label + ":");
        for (List<Integer> quad : res) {
            for (int val : quad) System.out.print(val + " ");
            System.out.println();
        }
        System.out.println("------");
    }

    // ---------- Main ----------
    public static void main(String[] args) {
        int[] nums = {1, 0, -1, 0, -2, 2};
        int target = 0;

        List<List<Integer>> resBrute = fourSumBrute(nums, target);
        List<List<Integer>> resHash = fourSumHashing(nums, target);
        List<List<Integer>> resOpt = fourSumOptimal(nums, target);

        printResult("Brute-force", resBrute);
        printResult("Hashing", resHash);
        printResult("Optimal", resOpt);
    }
}
