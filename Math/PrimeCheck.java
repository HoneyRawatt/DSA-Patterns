import java.util.*;

class PrimeCheck {

    /*
    -------------------- BRUTE FORCE PRIME CHECK --------------------

    Time Complexity:
    - O(n) → checks all numbers from 1 to n

    Space Complexity:
    - O(1) → no extra space used
    */
    public static String prime_brute(int n) {
        int cnt = 1; // 1 is always a divisor

        if (n <= 1)
            return "NOT PRIME";

        for (int i = 2; i <= n; i++) {
            if (n % i == 0) {
                cnt++;
            }
            if (cnt > 2)
                return "NOT PRIME";
        }
        return "PRIME";
    }

    /*
    -------------------- OPTIMAL PRIME CHECK --------------------

    Intuition:
    - A prime number has exactly two divisors: 1 and itself.
    - 0 and 1 are NOT prime.
    - If n has any divisor other than 1 and itself, it is NOT prime.
    - We only check till sqrt(n).

    Optimization:
    - Stop as soon as a divisor is found.

    Time Complexity:
    - O(√n)

    Space Complexity:
    - O(1)
    */
    public static String isPrime(int n) {
        if (n <= 1)
            return "NOT PRIME";

        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0)
                return "NOT PRIME";
        }
        return "PRIME";
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number: ");
        int n = sc.nextInt();

        System.out.println(isPrime(n));

        sc.close();
    }
}

