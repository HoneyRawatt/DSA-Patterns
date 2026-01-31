
import java.util.*;

class PrimeFactors {

    /*
    Helper function to check if a number is prime
    Time Complexity: O(√n)
    Space Complexity: O(1)
    */
    public static boolean isPrime(int n) {
        if (n <= 1)
            return false;

        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0)
                return false;
        }
        return true;
    }

    /*
    -------------------- BRUTE FORCE PRIME FACTORS --------------------

    Intuition:
    - Try every number from 2 to n
    - If i divides n and i is prime, then i is a prime factor

    Time Complexity:
    - O(n√n)

    Space Complexity:
    - O(k)
    */
    public static ArrayList<Integer> primefactors_brute(int n) {
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 2; i <= n; i++) {
            if (n % i == 0 && isPrime(i)) {
                ans.add(i);
            }
        }
        return ans;
    }

    /*
    -------------------- BETTER PRIME FACTORS --------------------

    Intuition:
    - Factors come in pairs: (i, n/i)
    - Only iterate till sqrt(n)
    - Check primality of both i and n/i

    Time Complexity:
    - O(n)

    Space Complexity:
    - O(k)
    */
    public static ArrayList<Integer> primefactors_better(int n) {
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) {
                if (isPrime(i))
                    ans.add(i);

                if (n / i != i && isPrime(n / i))
                    ans.add(n / i);
            }
        }
        return ans;
    }

    /*
    -------------------- OPTIMAL PRIME FACTORIZATION --------------------

    Intuition:
    - Divide n by its smallest prime factor
    - Remove all occurrences of that factor
    - Continue till sqrt(n)
    - If remaining n > 1, it is also a prime factor

    Example:
    n = 36 → 2, 3

    Time Complexity:
    - O(√n)

    Space Complexity:
    - O(k)
    */
    public static ArrayList<Integer> primefactors_optimal(int n) {
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) {
                ans.add(i);
                while (n % i == 0) {
                    n /= i;
                }
            }
        }
        if (n != 1)
            ans.add(n);

        return ans;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number: ");
        int n = sc.nextInt();

        System.out.println("\nPrime Factors (Brute): " + primefactors_optimal(n));
    }
}
