import java.util.*;

class FastPower {

    /*
    -------------------- BINARY EXPONENTIATION --------------------

    Intuition:
    - Instead of multiplying x, n times (O(n)),
      we reduce the power using:
        x^n =
          x * x^(n-1)      if n is odd
          (x*x)^(n/2)      if n is even
    - This reduces the number of operations drastically.

    Algorithm:
    - If n is odd → multiply result by x
    - Square x and divide n by 2
    - Repeat until n becomes 0

    Time Complexity:
    - O(log n)

    Space Complexity:
    - O(1)
    */
    public static double powerExpo(double x, int n) {
        long m = n;      // store original exponent
        double ans = 1.0;

        if (m < 0)
            m = -m;

        while (m > 0) {
            if (m % 2 == 1) {
                ans *= x;
                m--;
            } else {
                x *= x;
                m /= 2;
            }
        }

        if (n < 0)
            ans = 1.0 / ans;

        return ans;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter base: ");
        double x = sc.nextDouble();

        System.out.print("Enter exponent: ");
        int n = sc.nextInt();

        System.out.println("Result: " + powerExpo(x, n));

        sc.close();
    }
}
