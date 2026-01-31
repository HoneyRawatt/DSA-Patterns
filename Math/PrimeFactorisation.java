import java.util.*;

class PrimeFactorisation {

    /*
    -------------------- BRUTE FORCE PRIME FACTORIZATION --------------------

    Intuition:
    - For a number n, try dividing by every number from 2 to n
    - If it divides, keep dividing until it no longer does

    Time Complexity (per number):
    - O(n)

    Space Complexity:
    - O(k) → number of prime factors
    */
    public static ArrayList<Integer> getPrimeFactorsBrute(int n) {
        ArrayList<Integer> factors = new ArrayList<>();

        for (int i = 2; i <= n; i++) {
            while (n % i == 0) {
                factors.add(i);
                n /= i;
            }
        }
        return factors;
    }

    public static ArrayList<ArrayList<Integer>> primeFactorisationBrute(
            ArrayList<Integer> queries) {

        ArrayList<ArrayList<Integer>> factors = new ArrayList<>();

        for (int n : queries) {
            factors.add(getPrimeFactorsBrute(n));
        }
        return factors;
    }

    /*
    -------------------- OPTIMAL PRIME FACTORIZATION (SPF) --------------------

    Intuition:
    - Precompute Smallest Prime Factor (SPF) for every number
    - To factorize n:
      repeatedly divide by spf[n]

    Preprocessing Time:
    - O(n log log n)

    Factorization Time (per query):
    - O(log n)

    Space Complexity:
    - O(n + total factors)
    */
    public static ArrayList<ArrayList<Integer>> primeFactorisationOptimal(
            ArrayList<Integer> queries) {

        int maxn = 100_000;

        // Step 1: Build SPF array
        int[] spf = new int[maxn + 1];
        for (int i = 1; i <= maxn; i++)
            spf[i] = i;

        for (int i = 2; i * i <= maxn; i++) {
            if (spf[i] == i) { // i is prime
                for (int j = i * i; j <= maxn; j += i) {
                    if (spf[j] == j)
                        spf[j] = i;
                }
            }
        }

        // Step 2: Factorize each query
        ArrayList<ArrayList<Integer>> factors = new ArrayList<>();

        for (int n : queries) {
            ArrayList<Integer> curr = new ArrayList<>();
            while (n != 1) {
                curr.add(spf[n]);
                n /= spf[n];
            }
            factors.add(curr);
        }
        return factors;
    }

    public static void main(String[] args) {

        ArrayList<Integer> queries = new ArrayList<>();
        queries.add(36);
        queries.add(60);
        queries.add(97);

        System.out.println("Brute Force Prime Factors:");
        System.out.println(primeFactorisationBrute(queries));

        System.out.println("\nOptimal Prime Factors (SPF):");
        System.out.println(primeFactorisationOptimal(queries));
    }
}
