#include <bits/stdc++.h>
using namespace std;

/*
------------------------------------------------------------
🍬 PROBLEM: Candy Distribution (LeetCode 135 / GFG Candy)
------------------------------------------------------------
You are given an integer array 'ratings' representing the rating
of each child standing in a line.

You must give candies to these children such that:
1️⃣ Each child has at least one candy.
2️⃣ A child with a higher rating than its neighbors gets more candies.

Return the minimum number of candies required.
------------------------------------------------------------
Example:
Input: ratings = [1, 0, 2]
Output: 5
Explanation:
  Child ratings: [1, 0, 2]
  Candies given: [2, 1, 2]
------------------------------------------------------------
*/


/* ------------------------------------------------------------
🔹 1️⃣ Brute Force (Two Arrays)
------------------------------------------------------------
Idea:
- Pass from left → right, ensure each child with higher rating than
  left neighbor gets more candies.
- Pass from right → left, ensure same for right neighbor.
- Take max(left[i], right[i]) to satisfy both directions.
------------------------------------------------------------
Time Complexity:  O(N)
Space Complexity: O(N)
------------------------------------------------------------ */
int candy_brute(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> left(n), right(n);

    // Left to right
    left[0] = 1;
    for (int i = 1; i < n; i++)
        left[i] = (ratings[i] > ratings[i - 1]) ? left[i - 1] + 1 : 1;

    // Right to left
    right[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--)
        right[i] = (ratings[i] > ratings[i + 1]) ? right[i + 1] + 1 : 1;

    // Combine both passes
    int total = 0;
    for (int i = 0; i < n; i++)
        total += max(left[i], right[i]);

    return total;
}


/* ------------------------------------------------------------
🔹 2️⃣ Better Approach (Single Right Variable)
------------------------------------------------------------
Optimization:
- We don't need the full right[] array.
- Track right slope count and compare with left[] during second pass.
------------------------------------------------------------
Time Complexity:  O(N)
Space Complexity: O(N)
------------------------------------------------------------ */
int candy_better(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> left(n);

    // Left pass
    left[0] = 1;
    for (int i = 1; i < n; i++)
        left[i] = (ratings[i] > ratings[i - 1]) ? left[i - 1] + 1 : 1;

    // Right pass (using only variables)
    int right = 1;
    int total = max(left[n - 1], right);

    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1])
            right++;
        else
            right = 1;
        total += max(left[i], right);
    }

    return total;
}


/* ------------------------------------------------------------
🔹 3️⃣ Optimal (Greedy Slope Approach)
------------------------------------------------------------
Observation:
- Ratings form rising and falling slopes.
- Track “uphill” and “downhill” sequences and adjust candies
  based on slope lengths.

Intuition:
- Each child on an increasing slope gets +1 candy from previous.
- Each child on a decreasing slope gets +1 candy from next.
- If downhill longer than uphill → add (down - up) correction.

Time Complexity:  O(N)
Space Complexity: O(1)
------------------------------------------------------------ */
int candy_optimal(vector<int>& ratings) {
    int n = ratings.size();
    int total = 1, i = 1;

    while (i < n) {
        // Case 1: Equal ratings
        if (ratings[i] == ratings[i - 1]) {
            total++;
            i++;
            continue;
        }

        // Case 2: Increasing slope
        int up = 1;
        while (i < n && ratings[i] > ratings[i - 1]) {
            up++;
            total += up;
            i++;
        }

        // Case 3: Decreasing slope
        int down = 1;
        while (i < n && ratings[i] < ratings[i - 1]) {
            total += down;
            down++;
            i++;
        }

        // Correction if downhill longer than uphill
        if (down > up) total += (down - up);
    }

    return total;
}


/* ------------------------------------------------------------
🔹 MAIN FUNCTION
------------------------------------------------------------ */
int main() {
    vector<int> ratings = {1, 0, 2};

    cout << "Brute Force Candies:  " << candy_brute(ratings) << endl;
    cout << "Better Candies:       " << candy_better(ratings) << endl;
    cout << "Optimal Candies:      " << candy_optimal(ratings) << endl;

    return 0;
}

/*
------------------------------------------------------------
🔹 OUTPUT:
Brute Force Candies:  5
Better Candies:       5
Optimal Candies:      5
------------------------------------------------------------
🔹 LINKS:
LeetCode: https://leetcode.com/problems/candy/
GFG:      https://www.geeksforgeeks.org/problems/candy/1
------------------------------------------------------------
*/
