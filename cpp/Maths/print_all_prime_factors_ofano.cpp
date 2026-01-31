#include <bits/stdc++.h>
using namespace std;

/*
Helper function to check if a number is prime
Time: O(√n)
Space: O(1)
*/
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= sqrt(n); i++) {
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
- O(n √n) → for each i, we check primality

Space Complexity:
- O(k) → number of prime factors
*/
vector<int> primefactors_brute(int n) {
    vector<int> ans;
    for (int i = 2; i <= n; i++) {
        if (n % i == 0 && isPrime(i)) {
            ans.push_back(i);
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
- O(√n √n) ≈ O(n)

Space Complexity:
- O(k)
*/
vector<int> primefactors_better(int n) {
    vector<int> ans;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            if (isPrime(i))
                ans.push_back(i);

            if (n / i != i && isPrime(n / i))
                ans.push_back(n / i);
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
n = 36
36 → 2,2 → 3,3

Time Complexity:
- O(√n)

Space Complexity:
- O(k)
*/
vector<int> primefactors_optimal(int n) {
    vector<int> ans;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            ans.push_back(i);
            while (n % i == 0) {
                n /= i;
            }
        }
    }
    if (n != 1)
        ans.push_back(n);

    return ans;
}

int main() {
    int n;
    cout << "Enter number: ";
    cin >> n;

    cout << "\nPrime Factors (Brute): ";
    for (int x : primefactors_brute(n))
        cout << x << " ";

    cout << "\nPrime Factors (Better): ";
    for (int x : primefactors_better(n))
        cout << x << " ";

    cout << "\nPrime Factors (Optimal): ";
    for (int x : primefactors_optimal(n))
        cout << x << " ";

    return 0;
}
