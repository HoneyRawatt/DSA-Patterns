package BinarySearch.1D;

import java.util.Arrays;

public class AggressiveCows{

    /*
     * 🧠 INTUITION (Helper Function):
     * --------------------------------
     * We try to place cows greedily.
     * - Place the first cow in the first stall.
     * - For every next stall, place a cow only if
     *   the distance from the last placed cow is >= dist.
     * - If we can place at least 'cows' cows, return true.
     *
     * Time Complexity: O(N)
     * Space Complexity: O(1)
     */
    public static boolean canWePlace(int[] arr, int dist, int cows) {
        int countCows = 1;      // First cow placed at first stall
        int lastPlaced = arr[0];

        for (int i = 1; i < arr.length; i++) {
            // Place cow if minimum distance condition is satisfied
            if (arr[i] - lastPlaced >= dist) {
                countCows++;
                lastPlaced = arr[i];
            }
        }
        return countCows >= cows;
    }

    /*
     * 🐢 BRUTE FORCE APPROACH
     * ------------------------
     * - Sort stall positions.
     * - Try every possible minimum distance from 1 to maxDist.
     * - For each distance, check if placement is possible.
     * - Stop when placement fails.
     *
     * Time Complexity:
     *   Sorting → O(N log N)
     *   Checking distances → O(maxDist * N)
     *   Overall → O(N log N + maxDist * N)
     *
     * Space Complexity: O(1)
     */
    public static int aggressiveCowsBrute(int[] arr, int cows) {
        Arrays.sort(arr);

        int maxDist = arr[arr.length - 1] - arr[0];
        int ans = 0;

        for (int dist = 1; dist <= maxDist; dist++) {
            if (canWePlace(arr, dist, cows)) {
                ans = dist;
            } else {
                break; // Larger distances will also fail
            }
        }
        return ans;
    }

    /*
     * 🚀 OPTIMIZED APPROACH (Binary Search on Answer)
     * -----------------------------------------------
     * 🧠 INTUITION:
     * - We are maximizing the minimum distance.
     * - If we can place cows with distance 'd',
     *   then we can also place them with any smaller distance.
     * - If we cannot place cows with distance 'd',
     *   then any larger distance will also fail.
     *
     * Search Space:
     * - Minimum distance = 1
     * - Maximum distance = last stall - first stall
     *
     * Time Complexity:
     *   Sorting → O(N log N)
     *   Binary Search → O(log(maxDist))
     *   Placement check per mid → O(N)
     *   Overall → O(N log N)
     *
     * Space Complexity: O(1)
     */
    public static int aggressiveCows(int[] arr, int cows) {
        Arrays.sort(arr); // Sorting is mandatory

        int low = 1;
        int high = arr[arr.length - 1] - arr[0];
        int ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            // Check if cows can be placed with mid distance
            if (canWePlace(arr, mid, cows)) {
                ans = mid;      // Store valid answer
                low = mid + 1;  // Try to maximize distance
            } else {
                high = mid - 1; // Reduce distance
            }
        }
        return ans;
    }

    /*
     * 🧪 DRIVER CODE
     *
     * Time Complexity: O(N log N)
     * Space Complexity: O(1)
     */
    public static void main(String[] args) {
        int[] stalls = {1, 2, 8, 4, 9};
        int cows = 3;

        System.out.println("Maximum minimum distance (Binary Search): "
                + aggressiveCows(stalls, cows));

        System.out.println("Maximum minimum distance (Brute Force): "
                + aggressiveCowsBrute(stalls, cows));
    }
}

