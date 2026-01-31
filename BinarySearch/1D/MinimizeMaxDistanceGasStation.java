package BinarySearch.1D;
/*
 * Problem: Minimize Max Distance to Gas Station
 * GFG / Binary Search on Answer
 */
public class MinimizeMaxDistanceGasStation {

    /*
     * =========================================================
     * | Method                  | Time Complexity     | Space |
     * |-------------------------|---------------------|-------|
     * | Brute Force             | O(k * n)            | O(n)  |
     * | Priority Queue (Greedy) | O(k * log n)        | O(n)  |
     * | Binary Search (Optimal) | O(n * log(range/ε)) | O(1)  |
     * =========================================================
     */

    /*
     * 🐢 BRUTE FORCE APPROACH
     * -----------------------
     * 🧠 INTUITION:
     * - We add gas stations one by one.
     * - Each time, we find the segment that currently has the
     *   maximum distance and split it.
     * - gasCount[i] tells how many extra stations are placed
     *   between stations[i] and stations[i+1].
     *
     * Time Complexity: O(k * n)
     * Space Complexity: O(n)
     */
    public static double minimizeMaxDistBrute(int[] stations, int k) {
        int n = stations.length;
        int[] gasCount = new int[n - 1];

        for (int added = 0; added < k; added++) {
            double maxSection = -1;
            int maxIndex = -1;

            for (int i = 0; i < n - 1; i++) {
                double length = stations[i + 1] - stations[i];
                double section = length / (gasCount[i] + 1);

                if (section > maxSection) {
                    maxSection = section;
                    maxIndex = i;
                }
            }
            gasCount[maxIndex]++;
        }

        double ans = 0;
        for (int i = 0; i < n - 1; i++) {
            double length = stations[i + 1] - stations[i];
            ans = Math.max(ans, length / (gasCount[i] + 1));
        }
        return ans;
    }

    /*
     * ⚡ PRIORITY QUEUE (GREEDY) APPROACH
     * -----------------------------------
     * 🧠 INTUITION:
     * - Always split the segment which currently has
     *   the maximum distance.
     * - Max heap keeps track of the largest segment.
     *
     * Time Complexity: O(k * log n)
     * Space Complexity: O(n)
     */
    public static double minimizeMaxDistBetter(int[] stations, int k) {
        int n = stations.length;
        int[] gasCount = new int[n - 1];

        PriorityQueue<double[]> pq =
                new PriorityQueue<>((a, b) -> Double.compare(b[0], a[0]));

        for (int i = 0; i < n - 1; i++) {
            pq.offer(new double[]{stations[i + 1] - stations[i], i});
        }

        for (int added = 0; added < k; added++) {
            double[] top = pq.poll();
            int idx = (int) top[1];
            gasCount[idx]++;

            double fullLength = stations[idx + 1] - stations[idx];
            double newSegment = fullLength / (gasCount[idx] + 1);
            pq.offer(new double[]{newSegment, idx});
        }

        return pq.peek()[0];
    }

    /*
     * 🧠 HELPER FUNCTION (Binary Search)
     * ----------------------------------
     * - Counts how many extra stations are required
     *   to ensure every segment length <= dist.
     *
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    public static int requiredStations(double dist, int[] stations) {
        int count = 0;
        for (int i = 1; i < stations.length; i++) {
            double segment = stations[i] - stations[i - 1];
            count += (int) Math.floor(segment / dist);
        }
        return count;
    }

    /*
     * 🚀 BINARY SEARCH (OPTIMAL APPROACH)
     * -----------------------------------
     * 🧠 INTUITION:
     * - We minimize the maximum distance.
     * - If we can achieve max distance = X with ≤ k stations,
     *   then we can also achieve it with any value > X.
     * - Hence, binary search on the answer.
     *
     * Search Space:
     * - low = 0
     * - high = max distance between adjacent stations
     *
     * Time Complexity: O(n * log(range / ε))
     * Space Complexity: O(1)
     */
    public static double minimizeMaxDistanceOptimized(int[] stations, int k) {
        int n = stations.length;
        double low = 0;
        double high = 0;

        for (int i = 0; i < n - 1; i++) {
            high = Math.max(high, stations[i + 1] - stations[i]);
        }

        double eps = 1e-6;
        while (high - low > eps) {
            double mid = (low + high) / 2.0;
            if (requiredStations(mid, stations) > k)
                low = mid;
            else
                high = mid;
        }
        return high;
    }

    /*
     * 🧪 DRIVER CODE
     */
    public static void main(String[] args) {
        int[] stations = {1, 2, 3, 4};
        int k = 3;

        System.out.printf("Brute Force Result: %.6f%n",
                minimizeMaxDistBrute(stations, k));
        System.out.printf("Priority Queue Result: %.6f%n",
                minimizeMaxDistBetter(stations, k));
        System.out.printf("Binary Search Result: %.6f%n",
                minimizeMaxDistanceOptimized(stations, k));
    }
}
