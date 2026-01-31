package BinarySearch.1D;

public class Sqrt{
    // Function to find floor value of square root of n
    // Time Complexity: O(log n)
    // Space Complexity: O(1)
    //
    // Intuition:
    // - Square root lies between 1 and n
    // - Use binary search to avoid overflow
    // - If mid*mid <= n, mid can be an answer
    // - Store it and try to find a bigger valid value
    static int sqrt(int n) {
        if (n == 0 || n == 1) return n;

        int low = 1, high = n;
        int ans = 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            long square = (long) mid * mid; // prevent overflow

            if (square == n)
                return mid;
            else if (square < n) {
                ans = mid;       // possible floor value
                low = mid + 1;   // try to find a larger one
            } else {
                high = mid - 1;  // square too large
            }
        }
        return ans;
    }

    // Driver code
    public static void main(String[] args) {
        int n = 25;
        System.out.println("Floor of square root of " + n + " is " + sqrt(n));
    }
}

