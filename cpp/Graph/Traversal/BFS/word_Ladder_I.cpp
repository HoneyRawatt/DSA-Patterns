#include <bits/stdc++.h>
using namespace std;

/*
--------------------------------------------------
Problem: Word Ladder (LeetCode 127)
Approach: BFS (Shortest Path in an Unweighted Graph)
--------------------------------------------------
Time Complexity:  O(N * M * 26)
    N = number of words in wordList
    M = length of each word
Space Complexity: O(N)
--------------------------------------------------
*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        queue<pair<string, int>> q;
        q.push({beginWord, 1});

        unordered_set<string> st(wordList.begin(), wordList.end());
        if (st.find(endWord) == st.end()) return 0; // endWord not in wordList

        st.erase(beginWord);

        while (!q.empty()) {
            string word = q.front().first;
            int steps = q.front().second;
            q.pop();

            if (word == endWord) return steps;

            for (int i = 0; i < word.size(); i++) {
                char original = word[i];
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch;
                    if (st.find(word) != st.end()) {
                        st.erase(word);
                        q.push({word, steps + 1});
                    }
                }
                word[i] = original;
            }
        }
        return 0;
    }
};

// ----------------------------
// Main Function
// ----------------------------
int main() {
    Solution sol;
    string beginWord, endWord;
    int n;

    cout << "Enter begin word: ";
    cin >> beginWord;
    cout << "Enter end word: ";
    cin >> endWord;

    cout << "Enter number of words in word list: ";
    cin >> n;

    vector<string> wordList(n);
    cout << "Enter words in word list:\n";
    for (int i = 0; i < n; i++) cin >> wordList[i];

    int result = sol.ladderLength(beginWord, endWord, wordList);

    if (result == 0)
        cout << "\nNo transformation sequence possible.\n";
    else
        cout << "\nShortest transformation sequence length: " << result << "\n";

    return 0;
}
