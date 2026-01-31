#include <bits/stdc++.h>
using namespace std;


// Time Complexity:
// - O(n) → checks all numbers from 1 to n

// Space Complexity:
// - O(1) → no extra space used
// */
string prime_brute(int n) {
    int cnt = 1; // 1 is always a divisor

    if (n<=1) 
        return "NOT PRIME";   // (logically incorrect, but kept as per your code)

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
- We only check till sqrt(n) because:
  If n = a * b and both a, b > sqrt(n), then a * b > n (not possible).

Optimization:
- The moment we find a divisor, we stop and return "NOT PRIME".

Time Complexity:
- O(√n)

Space Complexity:
- O(1)
*/
string isPrime(int n) {
    if (n <= 1)
        return "NOT PRIME";

    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0)
            return "NOT PRIME";
    }
    return "PRIME";
}

int main() {
    int n;
    cout << "Enter number: ";
    cin >> n;

    cout << isPrime(n);
    return 0;
}
