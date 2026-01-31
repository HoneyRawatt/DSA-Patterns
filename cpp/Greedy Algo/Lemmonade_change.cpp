#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
💰 PROBLEM: Lemonade Change (LeetCode 860)
-----------------------------------------------------
You are selling lemonade at $5 per cup.
Customers pay with either $5, $10, or $20 bills.
You must provide correct change to each customer in order.

Return true if you can give change to all customers; otherwise false.
-----------------------------------------------------
*/

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;  // we don't need to track $20 bills
        
        for (int i = 0; i < bills.size(); i++) {
            if (bills[i] == 5) {
                // Customer pays with $5 — no change needed
                five++;
            } 
            else if (bills[i] == 10) {
                // Customer pays with $10 — need to give one $5 as change
                if (five > 0) {
                    five--;
                    ten++;
                } else {
                    return false;  // not enough $5 to give change
                }
            } 
            else {  // bills[i] == 20
                // Prefer to give one $10 and one $5 as change if possible
                if (ten > 0 && five > 0) {
                    ten--;
                    five--;
                } 
                else if (five >= 3) {
                    // Otherwise, give three $5 bills
                    five -= 3;
                } 
                else {
                    return false;  // cannot give proper change
                }
            }
        }
        return true;  // all customers received correct change
    }
};

int main() {
    Solution sol;

    // Example 1
    vector<int> bills1 = {5, 5, 5, 10, 20};
    cout << "Can give change (example 1): " 
         << (sol.lemonadeChange(bills1) ? "true" : "false") << endl;

    // Example 2
    vector<int> bills2 = {5, 5, 10, 10, 20};
    cout << "Can give change (example 2): " 
         << (sol.lemonadeChange(bills2) ? "true" : "false") << endl;

    return 0;
}


// ⏱️ Time Complexity

// We process each customer exactly once → O(n)
// (where n = number of customers)

// 💾 Space Complexity

// We use only a few integer counters → O(1)