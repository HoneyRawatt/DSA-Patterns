package BinarySearch.1D;

import java.util.*;

public class KokoEatingBananas {

    // Brute Force Approach
    // Time Complexity: O(maxPile * n)
    // Space Complexity: O(1)
    //
    // Intuition:
    // - Try every possible eating speed from 1 to max pile
    // - For each speed, calculate total hours required
    // - First speed that takes <= h hours is the answer
    static int minEatingSpeedBrute(int[] piles, int h) {
        int maxPile = 0;
        for (int pile : piles)
            maxPile = Math.max(maxPile, pile);

        for (int speed = 1; speed <= maxPile; speed++) {
            long hours = 0;

            for (int bananas : piles) {
                hours += (bananas + speed - 1) / speed; // ceiling division
            }

            if (hours <= h)
                return speed;
        }
        return maxPile; // fallback
    }

    // Binary Search (Optimized)
    // Time Complexity: O(n log maxPile)
    // Space Complexity: O(1)
    //
    // Intuition:
    // - Minimum speed = 1
    // - Maximum speed = max pile size
    // - If a speed works, try smaller speed
    // - If it doesn't, increase speed
    static int minEatingSpeed(int[] piles, int h) {
        int left = 1;
        int right = 0;

        for (int pile : piles)
            right = Math.max(right, pile);

        int ans = right;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            long hours = 0;

            for (int bananas : piles) {
                hours += (bananas + mid - 1) / mid; // ceiling division
            }

            if (hours <= h) {
                ans = mid;       // valid speed
                right = mid - 1; // try slower
            } else {
                left = mid + 1;  // too slow
            }
        }
        return ans;
    }

    // Driver code
    public static void main(String[] args) {
        int[] piles1 = {3, 6, 7, 11};
        int h = 8;

        System.out.println("Minimum eating speed: " +
                minEatingSpeed(piles1, h));  // Output: 4

        System.out.println("Minimum eating speed (brute): " +
                minEatingSpeedBrute(piles1, h)); // Output: 4
    }
}

