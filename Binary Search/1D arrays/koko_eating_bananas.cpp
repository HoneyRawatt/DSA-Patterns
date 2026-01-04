#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

    // Brute Force Approach
    // Time Complexity: O(maxPile * n)
    // Space Complexity: O(1)
    //
    // Intuition:
    // - Try every possible eating speed from 1 to max pile
    // - For each speed, calculate total hours required
    // - First speed that takes <= h hours is the answer
    
int minEatingSpeedBrute(vector<int>& piles, int h) {
    int maxPile = *max_element(piles.begin(), piles.end());
    
    for (int speed = 1; speed <= maxPile; speed++) {
        long long hours = 0;
        for (int bananas : piles) {
            hours += (bananas + speed - 1) / speed;  // Ceil division
        }

        if (hours <= h) {
            return speed; // First speed that works
        }
    }

    return maxPile; // Fallback, should never be needed
}
    // Binary Search (Optimized)
    // Time Complexity: O(n log maxPile)
    // Space Complexity: O(1)
    //
    // Intuition:
    // - Minimum speed = 1
    // - Maximum speed = max pile size
    // - If a speed works, try smaller speed
    // - If it doesn't, increase speed
    int minEatingSpeed(std::vector<int>& piles, int h) {
        // Minimum possible eating speed is 1
        // Maximum is the size of the largest pile
        int left = 1;
        int right = *max_element(piles.begin(), piles.end());
        int ans = right;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            // Calculate total hours needed at this speed
            long long hours = 0;
            for (int bananas : piles) {
                hours += (bananas + mid - 1) / mid;  // integer ceiling
            }

            if (hours <= h) {
                ans = mid;         // Possible answer, try slower speed
                right = mid - 1;
            } else {
                left = mid + 1;    // Too slow, try faster speed
            }
        }

        return ans; // same if we return left
    }
    
int main() {
    vector<int> piles1 = {3, 6, 7, 11};
    int h = 8;
    int result = minEatingSpeed(piles1, h);
    cout << "Minimum eating speed: " << result << endl;  // Output: 4
    vector<int> piles2 = {3, 6, 7, 11};
    result = minEatingSpeedBrute(piles2, h);
    cout << "Minimum eating speed (brute): " << result << endl; // Output: 4
    return 0;
}