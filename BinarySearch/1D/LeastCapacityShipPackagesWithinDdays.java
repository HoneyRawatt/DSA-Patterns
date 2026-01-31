package BinarySearch.1D;
import java.util.*;
public class LeastCapacityShipPackagesWithinDdays {

    /*
     * INTUITION:
     * ------------
     * We are given weights of packages in order.
     * Each day we can ship packages in sequence, but total weight per day
     * cannot exceed the ship capacity.
     *
     * We want the MINIMUM ship capacity such that all packages
     * can be shipped within 'd' days.
     *
     * Observations:
     * - Minimum possible capacity = max weight (at least one package must fit)
     * - Maximum possible capacity = sum of all weights (ship everything in one day)
     *
     * The answer lies between [maxWeight, sumWeights]
     * and the condition "can ship within D days" is MONOTONIC.
     *
     * Hence → Binary Search on answer.
     */

    // Helper function:
    // Given a capacity, find how many days are required to ship all packages
    private static int findDays(int[] weights, int capacity) {
        int days = 1;   // Start with day 1
        int load = 0;   // Current day's load

        for (int w : weights) {
            if (load + w > capacity) {
                // Cannot add this package to current day
                days++;       // Move to next day
                load = w;     // Start new day with current package
            } else {
                load += w;    // Add to current day's load
            }
        }
        return days;
    }

    /*
     * BRUTE FORCE APPROACH
     * --------------------
     * Try every capacity from maxWeight to sumWeights
     * and return the first capacity that can ship in <= D days.
     *
     * Time Complexity: O((sum - max) * N)
     * Space Complexity: O(1)
     * (Too slow for large inputs)
     */
    public static int leastWeightCapacityBrute(int[] weights, int d) {
        int maxWeight = 0, sum = 0;
        for (int w : weights) {
            maxWeight = Math.max(maxWeight, w);
            sum += w;
        }

        for (int cap = maxWeight; cap <= sum; cap++) {
            if (findDays(weights, cap) <= d) {
                return cap;
            }
        }
        return sum;
    }

    /*
     * OPTIMAL APPROACH (Binary Search)
     * --------------------------------
     * Search space: [maxWeight, sumWeights]
     *
     * If capacity works (days <= D):
     *     try smaller capacity
     * else:
     *     increase capacity
     *
     * Time Complexity:
     * O(N * log(sumWeights - maxWeight))
     *
     * Space Complexity:
     * O(1)
     */
    public static int leastWeightCapacity(int[] weights, int d) {
        int maxWeight = 0, sum = 0;
        for (int w : weights) {
            maxWeight = Math.max(maxWeight, w);
            sum += w;
        }

        int low = maxWeight, high = sum;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            int requiredDays = findDays(weights, mid);

            if (requiredDays <= d) {
                // Capacity is sufficient → try smaller
                high = mid - 1;
            } else {
                // Capacity too small → increase
                low = mid + 1;
            }
        }
        return low;
    }

    // Driver code
    public static void main(String[] args) {
        int[] weights = {1, 2, 3, 1, 1};
        int days = 4;

        System.out.println("Least capacity (Binary Search): "
                + leastWeightCapacity(weights, days));

        System.out.println("Least capacity (Brute Force): "
                + leastWeightCapacityBrute(weights, days));
    }
}
