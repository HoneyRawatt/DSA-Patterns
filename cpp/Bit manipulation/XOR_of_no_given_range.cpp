#include <iostream>
using namespace std;

/*
 XOR from 1 to n follows a repeating pattern every 4 numbers:
 n % 4 == 0 → result = n
 n % 4 == 1 → result = 1
 n % 4 == 2 → result = n + 1
 n % 4 == 3 → result = 0

 Time Complexity: O(1)
 Space Complexity: O(1)
*/
int xor_of_no(int n) {
    if (n % 4 == 0) return n;
    if (n % 4 == 1) return 1;
    if (n % 4 == 2) return n + 1;
    return 0; // n % 4 == 3
}

/*
 XOR of numbers in range [l, r] = XOR(1..r) ^ XOR(1..l-1)

 Time Complexity: O(1)
 Space Complexity: O(1)
*/
int xor_of_range(int l, int r) {
    return xor_of_no(r) ^ xor_of_no(l - 1);
}

int main() {
    int l = 3, r = 9;
    cout << "XOR from " << l << " to " << r << " = " << xor_of_range(l, r) << endl;
}
