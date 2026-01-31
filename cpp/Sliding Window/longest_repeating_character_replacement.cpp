#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;
/*
========================================================
PROBLEM STATEMENT:
--------------------------------------------------------
You are given a string `s` consisting of uppercase
English letters and an integer `k`.

You can replace at most `k` characters in the string
with any other character.

Goal:
- Find the length of the longest substring that can be
  obtained after performing at most `k` replacements
  such that all characters in the substring are the same.

--------------------------------------------------------
EXAMPLE:
Input:  s = "AABABBA", k = 1
Output: 4
Explanation:
Replace one 'B' with 'A' → "AAAA"

========================================================
*/

// --------------------------------------------
// BRUTE FORCE
// Time: O(n^2 * 26) ≈ O(n^2)
// Space: O(26) = O(1)
// Remember:
// - Try every substring starting from i
// - Maintain character frequency in hash[]
// - Stop inner loop early if more than k replacements needed
int characterReplacement_brute(string s, int k){
    int maxf = 0, maxlen = 0;
    for(int i = 0; i < s.length(); i++){
        vector<int> hash(26, 0);  // Frequency of A-Z
        maxf = 0;
        for(int j = i; j < s.length(); j++){
            hash[s[j] - 'A']++;
            maxf = max(maxf, hash[s[j] - 'A']);  

            if ((j - i + 1) - maxf <= k)
                maxlen = max(maxlen, j - i + 1);
            else
                break;
        }
    }
    return maxlen;
}

// --------------------------------------------
// BETTER (Sliding Window + Recalculate maxf when shrinking)
// Time: O(26 * n) = O(n) in practice (though nested loop when shrinking)
// Space: O(26) = O(1)
// Remember:
// - Sliding window approach
// - When shrinking the window, recompute maxf
// - This makes the logic slightly inefficient but still linear in practice
int characterReplacement_better(string s, int k) {
    int l = 0, r = 0, maxf = 0, maxlen = 0;
    vector<int> hash(26, 0);  // Frequency of A-Z

    while (r < s.length()) {
        hash[s[r] - 'A']++;
        maxf = max(maxf, hash[s[r] - 'A']);

        while ((r - l + 1) - maxf > k) {
            hash[s[l] - 'A']--;
            // Recalculate maxf (slower)
            maxf = 0;
            for(int i = 0; i < 26; i++) maxf = max(maxf, hash[i]);
            l++;
        }

        if ((r - l + 1) - maxf <= k)
            maxlen = max(maxlen, r - l + 1);
        r++;
    }

    return maxlen;
}

// --------------------------------------------
// OPTIMIZED (Sliding Window without recalculating maxf)
// Time: O(n)
// Space: O(26) = O(1)
// Remember:
// - Don't recalculate maxf when shrinking
// - Let the window shrink based on previous maxf value
// - Safe because maxf only increases or remains valid window
int characterReplacement_optimized(string s, int k) {
    int l = 0, r = 0, maxf = 0, maxlen = 0;
    vector<int> hash(26, 0);  // Frequency of A-Z

    while (r < s.length()) {
        hash[s[r] - 'A']++;
        maxf = max(maxf, hash[s[r] - 'A']);

        if ((r - l + 1) - maxf > k) {
            hash[s[l] - 'A']--;
            l++;
        }

        if ((r - l + 1) - maxf <= k)
            maxlen = max(maxlen, r - l + 1);
        r++;
    }

    return maxlen;
}

int main() {
    string s = "AABABBA";
    int k = 1;

    cout << "Brute Force Result:    " << characterReplacement_brute(s, k) << endl;
    cout << "Better Result:         " << characterReplacement_better(s, k) << endl;
    cout << "Optimized Result:      " << characterReplacement_optimized(s, k) << endl;

    return 0;
}
