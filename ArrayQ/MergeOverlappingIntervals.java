import java.util.*;

class MergeOverlappingIntervals{

    /*
     * Brute-force Approach
     * Time Complexity: O(n^2)
     * Space Complexity: O(n)
     */
    public static List<List<Integer>> mergeIntervalsBrute(int[][] arr) {
        int n = arr.length;
        Arrays.sort(arr, (a, b) -> a[0] - b[0]); // sort by start

        List<List<Integer>> ans = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            int start = arr[i][0];
            int end = arr[i][1];

            // already covered
            if (!ans.isEmpty() && end <= ans.get(ans.size() - 1).get(1))
                continue;

            for (int j = i + 1; j < n; j++) {
                if (arr[j][0] <= end) {
                    end = Math.max(end, arr[j][1]);
                } else {
                    break;
                }
            }

            ans.add(Arrays.asList(start, end));
        }

        return ans;
    }

    /*
     * Optimal Approach
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    public static List<List<Integer>> mergeIntervalsOptimal(int[][] arr) {
        int n = arr.length;
        Arrays.sort(arr, (a, b) -> a[0] - b[0]);

        List<List<Integer>> ans = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            if (ans.isEmpty() || arr[i][0] > ans.get(ans.size() - 1).get(1)) {
                ans.add(Arrays.asList(arr[i][0], arr[i][1]));
            } else {
                ans.get(ans.size() - 1).set(
                        1,
                        Math.max(ans.get(ans.size() - 1).get(1), arr[i][1])
                );
            }
        }

        return ans;
    }

    // -------- Driver Code --------
    public static void main(String[] args) {
        int[][] intervals = {
                {1, 3}, {2, 6}, {8, 10}, {15, 18}, {17, 20}
        };

        System.out.println("Brute-force:");
        System.out.println(mergeIntervalsBrute(intervals));

        System.out.println("Optimized:");
        System.out.println(mergeIntervalsOptimal(intervals));
    }
}
