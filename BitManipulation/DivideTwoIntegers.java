package BitManipulation;

public class DivideTwoIntegers {

    /*
     Brute Force Division
     Repeated subtraction
     Time Complexity: O(dividend / divisor)
     Space Complexity: O(1)
    */
    public static int divideTwoIntBrute(int dividend, int divisor) {
        if (divisor == 0) return Integer.MAX_VALUE;

        int sum = 0, count = 0;
        while (sum + divisor <= dividend) {
            sum += divisor;
            count++;
        }
        return count;
    }

    /*
     Optimized Division using Bit Manipulation
     - Uses left shifts to subtract largest power-of-two multiples
     - Handles overflow and sign correctly

     Time Complexity: O(log(dividend))
     Space Complexity: O(1)
    */
    public static int divideTwoInt(int dividend, int divisor) {

        // Edge cases
        if (divisor == 0) return Integer.MAX_VALUE;
        if (dividend == divisor) return 1;
        if (dividend == Integer.MIN_VALUE && divisor == -1)
            return Integer.MAX_VALUE;

        // Determine sign
        boolean positive = (dividend >= 0) == (divisor >= 0);

        long n = Math.abs((long) dividend);
        long d = Math.abs((long) divisor);

        long ans = 0;

        while (n >= d) {
            int shift = 0;

            // Find maximum shift where (d << shift) <= n
            while (n >= (d << (shift + 1))) {
                shift++;
            }

            ans += (1L << shift);
            n -= (d << shift);
        }

        if (ans > Integer.MAX_VALUE)
            return positive ? Integer.MAX_VALUE : Integer.MIN_VALUE;

        return positive ? (int) ans : (int) -ans;
    }

    public static void main(String[] args) {
        int dividend = 43;
        int divisor = 5;

        System.out.println("Brute Result: " + divideTwoIntBrute(dividend, divisor));
        System.out.println("Optimized Result: " + divideTwoInt(dividend, divisor));
    }
}

