#include <iostream>
#include <vector>
using namespace std;

/*
=====================================================
BRUTE FORCE APPROACH — O(n²)
-----------------------------------------------------
Idea:
A celebrity is a person who:
1) Is known by everyone else  → knowme[i] == n-1
2) Knows no one               → iknow[i] == 0

Steps:
- Traverse the matrix
- Count:
  • how many people know i      → knowme[i]
  • how many people i knows     → iknow[i]
- Find index that satisfies celebrity conditions
=====================================================
*/
int celebrity_brute(vector<vector<int>> mat) {
    int n = mat.size();

    // knowme[i]  -> number of people who know person i
    // iknow[i]   -> number of people person i knows
    vector<int> knowme(n, 0), iknow(n, 0);

    // Fill knowme and iknow arrays
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] == 1) {
                knowme[j]++;   // person j is known by i
                iknow[i]++;    // person i knows j
            }
        }
    }

    // Check celebrity condition
    for (int i = 0; i < n; i++) {
        // Celebrity must be known by n-1 people and know nobody
        if (knowme[i] == n - 1 && iknow[i] == 0)
            return i; // celebrity found
    }

    return -1; // no celebrity
}

/*
=====================================================
OPTIMAL APPROACH — O(n)
-----------------------------------------------------
Idea:
- Use two pointers to eliminate non-celebrities
- If A knows B → A can't be celebrity
- If A doesn't know B → B can't be celebrity

Steps:
1) Find a potential celebrity
2) Verify that candidate
=====================================================
*/
int celebrity(vector<vector<int>> mat) {
    int n = mat.size();
    int top = 0, down = n - 1;

    // Step 1: Find potential celebrity
    while (top < down) {
        if (mat[top][down] == 1)
            top++;   // top knows down → top not celebrity
        else
            down--;  // top doesn't know down → down not celebrity
    }

    // Possible celebrity
    int candidate = top;

    // Step 2: Verify candidate
    for (int i = 0; i < n; i++) {
        if (i == candidate) continue;

        // Celebrity should:
        // 1) Not know anyone
        // 2) Be known by everyone
        if (mat[candidate][i] == 1 || mat[i][candidate] == 0)
            return -1;
    }

    return candidate; // confirmed celebrity
}

int main() {
    vector<vector<int>> mat = {
        {0, 1, 1},
        {0, 0, 1},
        {0, 0, 0}
    };

    cout << "Brute Force Celebrity: " << celebrity_brute(mat) << endl;
    cout << "Optimal Celebrity: " << celebrity(mat) << endl;

    return 0;
}
