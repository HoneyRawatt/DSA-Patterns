#include <iostream>
#include <climits>
using namespace std;

/*
 Brute Force Division
 Time Complexity: O(dividend/divisor)
 Space Complexity: O(1)
*/
int dividetwoint_brute(int dividend, int divisor) {
    if (divisor == 0) return INT_MAX;

    int sum = 0, cnt = 0;
    while (sum + divisor <= dividend) {
        sum += divisor;
        cnt++;
    }
    return cnt;
}

/*
 Optimized Division using Bit Manipulation
 Time Complexity: O(log(dividend))
 Space Complexity: O(1)
*/
int dividetwoint(int dividend, int divisor) {
    if (divisor == 0) return INT_MAX;
    if (dividend == divisor) return 1;
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;

    // Determine sign
    bool positive = (dividend >= 0) == (divisor >= 0);

    long long n = llabs((long long) dividend);
    long long d = llabs((long long) divisor);

    long long ans = 0;

    while (n >= d) {
        int shift = 0;

        // Find highest power of 2 such that (d << shift) <= n
        while (n >= (d << (shift + 1))) {
            shift++;
        }

        ans += (1LL << shift);
        n -= (d << shift);
    }

    if (ans > INT_MAX)
        return positive ? INT_MAX : INT_MIN;

    return positive ? (int)ans : -(int)ans;
}
