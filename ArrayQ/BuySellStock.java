import java.util.*;
public class BuySellStock {

    /*
     * Optimal One-Pass Approach
     *
     * Time Complexity: O(N)
     * Space Complexity: O(1)
     */
    static int buySellStock(int[] arr, int n) {
        int minPrice = arr[0];
        int maxProfit = 0;

        for (int i = 1; i < n; i++) {
            int cost = arr[i] - minPrice;
            maxProfit = Math.max(maxProfit, cost);
            minPrice = Math.min(minPrice, arr[i]);
        }

        return maxProfit;
    }

    public static void main(String[] args) {
        int[] prices = {7, 1, 5, 3, 6, 4};

        int profit = buySellStock(prices, prices.length);
        System.out.println("Max Profit = " + profit);
    }
}
