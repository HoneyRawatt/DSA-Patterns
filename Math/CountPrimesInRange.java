import java.util.*;

class CountPrimesInRange {

    /*
    -------------------- PRIME CHECK --------------------

    Time Complexity: O(√n)
    Space Complexity: O(1)
    */
    public static boolean isPrime(int n) {
        if (n <= 1)
            return false;

        for (int i = 2; i * i <= n; i++) {
            if (n % i == 0)
                return false;
        }
        return true;
    }

    /*
    -------------------- BRUTE FORCE RANGE PRIME COUNT --------------------

    Intuition:
    - For each query [l, r]
    - Check every number in range
    - Count how many are prime

    Time Complexity:
    - O(Q * (R - L + 1) * √n)

    Space Complexity:
    - O(Q)
    */
    public static ArrayList<Integer> countPrimeRangeBrute(ArrayList<int[]> queries) {
        ArrayList<Integer> primeCnt = new ArrayList<>();

        for (int[] q : queries) {
            int l = q[0];
            int r = q[1];
            int cnt = 0;

            for (int i = l; i <= r; i++) {
                if (isPrime(i))
                    cnt++;
            }
            primeCnt.add(cnt);
        }
        return primeCnt;
    }

    /*
    -------------------- SIEVE OF ERATOSTHENES --------------------

    Returns:
    prime[i] = true if i is prime

    Time Complexity: O(n log log n)
    Space Complexity: O(n)
    */
    public static boolean[] getSieve(int n) {
        boolean[] prime = new boolean[n + 1];
        Arrays.fill(prime, true);

        if (n >= 0) prime[0] = false;
        if (n >= 1) prime[1] = false;

        for (int i = 2; i * i <= n; i++) {
            if (prime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    prime[j] = false;
                }
            }
        }
        return prime;
    }

    /*
    -------------------- OPTIMAL RANGE PRIME COUNT --------------------

    Intuition:
    - Precompute primes using Sieve
    - Build prefix sum array:
      prefix[i] = number of primes ≤ i
    - Answer each query in O(1)

    Time Complexity:
    - Preprocessing: O(n log log n)
    - Each Query: O(1)

    Space Complexity:
    - O(n + Q)
    */
    public static ArrayList<Integer> countPrimeRangeOptimal(ArrayList<int[]> queries) {

        int MAXN = 1_000_000;

        boolean[] isPrime = getSieve(MAXN);

        int[] prefix = new int[MAXN + 1];
        for (int i = 1; i <= MAXN; i++) {
            prefix[i] = prefix[i - 1] + (isPrime[i] ? 1 : 0);
        }

        ArrayList<Integer> primeCnt = new ArrayList<>();
        for (int[] q : queries) {
            int l = q[0];
            int r = q[1];

            if (l == 0)
                primeCnt.add(prefix[r]);
            else
                primeCnt.add(prefix[r] - prefix[l - 1]);
        }
        return primeCnt;
    }

    public static void main(String[] args) {

        ArrayList<int[]> queries = new ArrayList<>();
        queries.add(new int[]{1, 10});
        queries.add(new int[]{10, 20});
        queries.add(new int[]{1, 100});

        System.out.println("Brute Force Results:");
        System.out.println(countPrimeRangeBrute(queries));

        System.out.println("\nOptimal Results:");
        System.out.println(countPrimeRangeOptimal(queries));
    }
}
