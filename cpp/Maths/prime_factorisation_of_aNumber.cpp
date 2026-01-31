#include <bits/stdc++.h>
using namespace std;

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
vector<int> getPrimeFactorsBrute(int n) {
    vector<int> factors;
    for (int i = 2; i <= n; i++) {
        while (n % i == 0) {
            factors.push_back(i);
            n /= i;
        }
    }
    return factors;
}

vector<vector<int>> Prime_factorisation_brute(vector<int>& queries) {
    int q = queries.size();
    vector<vector<int>> factors(q);

    for (int i = 0; i < q; i++) {
        factors[i] = getPrimeFactorsBrute(queries[i]);
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
vector<vector<int>> Prime_factorisation_optimal(vector<int>& queries) {

    int q = queries.size();
    int maxn = 100000;

    // Step 1: Build SPF array
    vector<int> spf(maxn + 1);
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

    // Step 2: Factorize queries
    vector<vector<int>> factors(q);
    for (int i = 0; i < q; i++) {
        int n = queries[i];
        while (n != 1) {
            factors[i].push_back(spf[n]);
            n /= spf[n];
        }
    }
    return factors;
}

int main() {
    vector<int> queries = {36, 60, 97};

    auto brute = Prime_factorisation_brute(queries);
    auto optimal = Prime_factorisation_optimal(queries);

    cout << "Brute Force:\n";
    for (auto &v : brute) {
        for (int x : v) cout << x << " ";
        cout << "\n";
    }

    cout << "\nOptimal (SPF):\n";
    for (auto &v : optimal) {
        for (int x : v) cout << x << " ";
        cout << "\n";
    }

    return 0;
}
