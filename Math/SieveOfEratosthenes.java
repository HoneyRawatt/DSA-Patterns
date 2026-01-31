import java.util.*;

class SieveOfEratosthenes {

    /*
    -------------------- SIEVE OF ERATOSTHENES --------------------

    Intuition:
    - Assume all numbers from 2 to n are prime.
    - For every prime number i, mark all its multiples as NOT prime.
    - Start marking from i*i because smaller multiples
      would already have been marked by smaller primes.

    Time Complexity:
    - O(n log log n)

    Space Complexity:
    - O(n)
    */
    public static ArrayList<Integer> sieve(int n) {

        boolean[] prime = new boolean[n + 1];
        Arrays.fill(prime, true);

        // 0 and 1 are not prime
        if (n >= 0) prime[0] = false;
        if (n >= 1) prime[1] = false;

        for (int i = 2; i * i <= n; i++) {
            if (prime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    prime[j] = false;
                }
            }
        }

        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 2; i <= n; i++) {
            if (prime[i]) {
                ans.add(i);
            }
        }

        return ans;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter n: ");
        int n = sc.nextInt();

        ArrayList<Integer> primes = sieve(n);

        System.out.println("Prime numbers up to " + n + ":");
        for (int x : primes) {
            System.out.print(x + " ");
        }

        sc.close();
    }
}
