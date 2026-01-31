#include <iostream>
using namespace std;

/*
Function: minBitFlips
Purpose: Find the minimum number of bit flips to convert 'start' into 'goal'.
Approach: XOR + Brian Kernighan's algorithm to count set bits.
Time Complexity: O(k), where k is the number of set bits in (start ^ goal) [Worst case: O(log(max(start, goal)))]
Space Complexity: O(1), no extra space used.
*/
int minBitFlips(int start, int goal) {
    // XOR: identifies differing bits (1 means bit differs)
    int ans = start ^ goal;

    int cnt = 0;
    // Brian Kernighan’s algorithm: removes rightmost set bit in each loop
    while (ans != 0) {
        ans = ans & (ans - 1);
        cnt++;
    }
    return cnt;
}

int main() {
    int start, goal;
    cout << "Enter start number: ";
    cin >> start;
    cout << "Enter goal number: ";
    cin >> goal;

    int result = minBitFlips(start, goal);

    cout << "Minimum bit flips needed: " << result << endl;

    /*
    Time Complexity:
        - XOR takes O(1)
        - Counting set bits takes O(k), where k <= log2(max(start, goal))
        - Overall: O(log(max(start, goal))) in worst case.

    Space Complexity:
        - O(1) extra space used.
    */

    return 0;
}
