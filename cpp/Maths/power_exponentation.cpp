#include <bits/stdc++.h>
using namespace std;

/*
-------------------- BINARY EXPONENTIATION --------------------

Intuition:
- Instead of multiplying x, n times (O(n)),
  we use the fact that:
    x^n =
      x * x^(n-1)        if n is odd
      (x^2)^(n/2)        if n is even
- This reduces the power exponentially.

Algorithm:
- If n is odd → multiply answer by x
- Square x and reduce n by half
- Repeat until n becomes 0

Time Complexity:
- O(log n)

Space Complexity:
- O(1)
*/
double power_expo(double x, int n) {
    long long m = n;   // store original n
    double ans = 1.0;

    if (m < 0)
        m = -m;

    while (m > 0) {
        if (m % 2 == 1) {
            ans *= x;
            m--;
        } else {
            x *= x;
            m /= 2;
        }
    }

    if (n < 0)
        ans = 1.0 / ans;

    return ans;
}

int main() {
    double x;
    int n;

    cout << "Enter base: ";
    cin >> x;
    cout << "Enter exponent: ";
    cin >> n;

    cout << "Result: " << power_expo(x, n);
    return 0;
}
