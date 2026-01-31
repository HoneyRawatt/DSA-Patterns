#include <bits/stdc++.h>
using namespace std;

/*
-------------------- BRUTE FORCE APPROACH --------------------

Intuition:
- A number n can be divided by any number from 1 to n.
- Check every number i in range [1, n].
- If i divides n (n % i == 0), then i is a divisor.

Time Complexity:
- O(n) → we check all numbers from 1 to n

Space Complexity:
- O(k) → where k is the number of divisors stored in the vector
*/
vector<int> print_divisor_ofnumber_brute(int n) {
    vector<int> ans;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0)
            ans.push_back(i);
    }
    return ans;
}

/*
-------------------- OPTIMAL APPROACH --------------------

Intuition:
- Divisors always come in pairs.
- If i divides n, then (n / i) is also a divisor.
- One of the pair will always be <= sqrt(n).
- So we only iterate from 1 to sqrt(n).
- Special case: if i == n/i, add it only once (perfect square).

Example:
n = 36
Pairs: (1,36), (2,18), (3,12), (4,9), (6,6)

Time Complexity:
- O(√n) → loop runs till sqrt(n)

Space Complexity:
- O(k) → storing k divisors
*/
vector<int> print_divisor_ofnumber_optimal(int n) {
    vector<int> ans;
    for (int i = 1; i <= sqrt(n); i++) {
        if (n % i == 0) {
            ans.push_back(i);
            if (n / i != i)
                ans.push_back(n / i);
        }
    }
    return ans;
}

int main() {
    int n;
    cout << "Enter number: ";
    cin >> n;

    cout << "\nDivisors using brute force:\n";
    vector<int> brute = print_divisor_ofnumber_brute(n);
    for (int x : brute)
        cout << x << " ";

    cout << "\n\nDivisors using optimal approach:\n";
    vector<int> optimal = print_divisor_ofnumber_optimal(n);
    for (int x : optimal)
        cout << x << " ";

    return 0;
}
