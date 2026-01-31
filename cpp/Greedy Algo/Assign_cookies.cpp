#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------------------
🧩 PROBLEM: Assign Cookies
-----------------------------------------------------
Each child i has a greed factor g[i].
Each cookie j has a size s[j].
A child will be content if given a cookie with size >= greed factor.
Goal: Maximize number of content children.
-----------------------------------------------------
*/

class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        // Sort both greed and cookie arrays
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        
        int i = 0, j = 0; // i -> child, j -> cookie
        int n = g.size(), m = s.size();

        // Greedily try to assign smallest possible cookie to each child
        while (i < n && j < m) {
            if (g[i] <= s[j]) {
                // Cookie satisfies this child's greed
                i++;
            }
            // Move to next cookie (whether assigned or not)
            j++;
        }
        return i; // Number of satisfied children
    }
};

int main() {
    Solution sol;

    // Example input
    vector<int> g = {1, 2, 3};  // children's greed
    vector<int> s = {1, 1};     // cookie sizes

    int result = sol.findContentChildren(g, s);
    cout << "Maximum number of content children: " << result << endl;

    return 0;
}

// | Step             | Purpose                     | Complexity                                    |
// | ---------------- | --------------------------- | --------------------------------------------- |
// | Sort both arrays | Prepare for greedy matching | O(n log n + m log m)                          |
// | Two-pointer scan | Match cookies to children   | O(n + m)                                      |
// | **Total**        |                             | **O(n log n + m log m)** time, **O(1)** space |
