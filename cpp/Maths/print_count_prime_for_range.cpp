#include <bits/stdc++.h>
using namespace std;

/*
-------------------- PRIME CHECK --------------------

Time Complexity: O(√n)
Space Complexity: O(1)
*/
bool isPrime(int n) {
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
- O(Q * (R-L+1) * √n)

Space Complexity:
- O(Q)
*/
vector<int> count_prime_for_range_brute(vector<pair<int,int>> &queries) {
    int q = queries.size();
    vector<int> primecnt;

    for (int i = 0; i < q; i++) {
        int l = queries[i].first;
        int r = queries[i].second;
        int cnt = 0;

        for (int j = l; j <= r; j++) {
            if (isPrime(j))
                cnt++;
        }
        primecnt.push_back(cnt);
    }
    return primecnt;
}

/*
-------------------- SIEVE FUNCTION --------------------

Returns array where:
prime[i] = 1 if i is prime, else 0

Time Complexity: O(n log log n)
Space Complexity: O(n)
*/
vector<int> getSieve(int n) {
    vector<int> prime(n + 1, 1);
    prime[0] = prime[1] = 0;

    for (int i = 2; i * i <= n; i++) {
        if (prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                prime[j] = 0;
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
- For each query:
  answer = prefix[r] - prefix[l-1]

Time Complexity:
- Preprocessing: O(n log log n)
- Each Query: O(1)

Space Complexity:
- O(n + Q)
*/
vector<int> count_prime_for_range_optimal(vector<pair<int,int>> &queries) {

    int MAXN = 1e6;
    vector<int> prime = getSieve(MAXN);

    // Build prefix sum
    for (int i = 1; i <= MAXN; i++) {
        prime[i] += prime[i - 1];
    }

    vector<int> primecnt;
    for (int i = 0; i < queries.size(); i++) {
        int l = queries[i].first;
        int r = queries[i].second;

        if (l == 0)
            primecnt.push_back(prime[r]);
        else
            primecnt.push_back(prime[r] - prime[l - 1]);
    }

    return primecnt;
}

int main() {
    vector<pair<int,int>> queries = {
        {1, 10},
        {10, 20},
        {1, 100}
    };

    cout << "Brute Force Results:\n";
    vector<int> brute = count_prime_for_range_brute(queries);
    for (int x : brute)
        cout << x << " ";

    cout << "\n\nOptimal Results:\n";
    vector<int> optimal = count_prime_for_range_optimal(queries);
    for (int x : optimal)
        cout << x << " ";

    return 0;
}
