#include <iostream>
using namespace std;

// Method 1: Left shift mask
bool check_ith_bit_set_or_not_leftShift(int n, int i) {
    return (n & (1 << i)) != 0;
}

// Method 2: Right shift and check last bit
bool check_ith_bit_set_or_not_rightShift(int n, int i) {
    return ((n >> i) & 1) == 1;
}

// Set i-th bit
void set_ith_bit(int &n, int i) {
    n = n | (1 << i);
}

// Clear i-th bit
void clear_ith_bit(int &n, int i) {
    n = n & ~(1 << i);
}

// Toggle i-th bit
void toggle_the_ith_bit(int &n, int i) {
    n = n ^ (1 << i);
}

// Remove rightmost set bit
void remove_the_last_set_bit_rightmost(int &n) {
    n = n & (n - 1);
}

// Check if number is power of 2
bool check_if_the_no_is_power_of_2(int n) {
    if (n <= 0) return false;
    return (n & (n - 1)) == 0;
}

// Count set bits (basic method)
int count_the_no_of_set_bits1(int n) {
    int cnt = 0;
    while (n > 0) {
        if ((n & 1) == 1) cnt++;
        n = n >> 1;
    }
    return cnt;
}

// Count set bits (Brian Kernighan's algorithm)
int count_the_no_of_set_bits2(int n) {
    int cnt = 0;
    while (n != 0) {
        n = n & (n - 1);
        cnt++;
    }
    return cnt;
}

int main() {
    int n = 13; // binary: 1101
    cout << "Original number: " << n << endl;

    // Check bits using left shift
    for (int i = 0; i < 4; i++) {
        cout << "Bit " << i << " (left shift check): "
             << (check_ith_bit_set_or_not_leftShift(n, i) ? "SET" : "NOT SET") << endl;
    }

    // Check bits using right shift
    for (int i = 0; i < 4; i++) {
        cout << "Bit " << i << " (right shift check): "
             << (check_ith_bit_set_or_not_rightShift(n, i) ? "SET" : "NOT SET") << endl;
    }

    // Set bit 1
    set_ith_bit(n, 1);
    cout << "After setting bit 1: " << n << endl;

    // Clear bit 2
    clear_ith_bit(n, 2);
    cout << "After clearing bit 2: " << n << endl;

    // Toggle bit 0
    toggle_the_ith_bit(n, 0);
    cout << "After toggling bit 0: " << n << endl;

    // Remove rightmost set bit
    remove_the_last_set_bit_rightmost(n);
    cout << "After removing rightmost set bit: " << n << endl;

    // Check power of 2
    cout << "Is power of 2? " << (check_if_the_no_is_power_of_2(n) ? "YES" : "NO") << endl;

    // Count set bits
    cout << "Set bits (method 1): " << count_the_no_of_set_bits1(n) << endl;
    cout << "Set bits (method 2): " << count_the_no_of_set_bits2(n) << endl;

    return 0;
}
