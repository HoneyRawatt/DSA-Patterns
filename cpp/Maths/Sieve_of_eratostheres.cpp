#include <bits/stdc++.h>
using namespace std;

/*
-------------------- SIEVE OF ERATOSTHENES --------------------

Intuition:
- Assume all numbers from 2 to n are prime.
- For every prime number i, mark all its multiples as NOT prime.
- Start marking from i*i because smaller multiples
  would already have been marked by smaller primes.

Steps:
1. Create a boolean/array to mark prime numbers
2. Mark multiples of each prime as non-prime
3. Collect all remaining prime numbers

Time Complexity:
- O(n log log n)

Space Complexity:
- O(n)
*/
vector<int> SieveofEratosthenes(int n) {
    vector<int> prime(n + 1, 1); // 1 means prime
    prime[0] = prime[1] = 0;

    for (int i = 2; i * i <= n; i++) {
        if (prime[i] == 1) {
            for (int j = i * i; j <= n; j += i) {
                prime[j] = 0;
            }
        }
    }

    vector<int> ans;
    for (int i = 2; i <= n; i++) {
        if (prime[i] == 1)
            ans.push_back(i);
    }

    return ans;
}

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    vector<int> primes = SieveofEratosthenes(n);

    cout << "Prime numbers up to " << n << ":\n";
    for (int x : primes)
        cout << x << " ";

    return 0;
}
