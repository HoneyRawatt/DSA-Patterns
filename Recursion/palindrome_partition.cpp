 #include <bits/stdc++.h>
using namespace std;

// Utility function to check if a substring is a palindrome
bool isPalindrome(string s, int start, int end) {
    while (start <= end) {
        if (s[start++] != s[end--]) return false;
    }
    return true;
}

// Recursive backtracking function to generate all palindromic partitions
void generatePartitions(int index, string s, vector<string>& path, vector<vector<string>>& result) {
    // Base case: if index reaches end of string, push current path to result
    if (index == s.size()) {
        result.push_back(path);
        return;
    }

    // Try all substrings starting from index
    for (int i = index; i < s.size(); i++) {
        // If substring s[index..i] is a palindrome, include it in path
        if (isPalindrome(s, index, i)) {
            path.push_back(s.substr(index, i - index + 1)); // Add current palindrome substring
            generatePartitions(i + 1, s, path, result);     // Recurse for remaining substring
            path.pop_back(); // Backtrack
        }
    }
}

int main() {
    string s = "aabb";

    vector<vector<string>> result;
    vector<string> path;

    generatePartitions(0, s, path, result);

    // Output all the partitions
    cout << "Palindrome Partitions of \"" << s << "\":" << endl;
    for (const auto& partition : result) {
        cout << "[ ";
        for (const string& str : partition) {
            cout << "\"" << str << "\" ";
        }
        cout << "]" << endl;
    }

    return 0;
}

/*
============================
TIME & SPACE COMPLEXITY
============================

Time Complexity:
- There are 2^(N-1) possible ways to partition a string of length N.
- For each partition, palindrome checking takes O(N).
- Overall Time Complexity: O(2^N * N)

Space Complexity:
- Recursion stack depth: O(N)
- Path list: O(N)
- Result storage: O(2^N * N)
- Overall Auxiliary Space (excluding output): O(N)
*/
 