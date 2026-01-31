import java.util.*;

class PrintDivisor_number {

    /*
    -------------------- BRUTE FORCE APPROACH --------------------

    Intuition:
    - Every divisor of n lies between 1 and n.
    - Check each number from 1 to n.
    - If i divides n, then i is a divisor.

    Time Complexity:
    - O(n) → checking all numbers from 1 to n

    Space Complexity:
    - O(k) → k is the number of divisors stored
    */
    public static ArrayList<Integer> brute(int n) {
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            if (n % i == 0) {
                ans.add(i);
            }
        }
        return ans;
    }

    /*
    -------------------- OPTIMAL APPROACH --------------------

    Intuition:
    - Divisors come in pairs: (i, n/i)
    - One of them will always be ≤ sqrt(n)
    - So we only iterate till sqrt(n)
    - If i == n/i (perfect square), add only once

    Example:
    n = 36 → (1,36), (2,18), (3,12), (4,9), (6,6)

    Time Complexity:
    - O(√n)

    Space Complexity:
    - O(k)
    */
    public static ArrayList<Integer> optimal(int n) {
        ArrayList<Integer> ans = new ArrayList<>();
        for (int i = 1; i <= Math.sqrt(n); i++) {
            if (n % i == 0) {
                ans.add(i);
                if (n / i != i)
                    ans.add(n / i);
            }
        }
        return ans;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number: ");
        int n = sc.nextInt();

        System.out.println("\nDivisors using brute force:");
        ArrayList<Integer> bruteAns = brute(n);
        for (int x : bruteAns)
            System.out.print(x + " ");

        System.out.println("\n\nDivisors using optimal approach:");
        ArrayList<Integer> optimalAns = optimal(n);
        for (int x : optimalAns)
            System.out.print(x + " ");

        sc.close();
    }
}
