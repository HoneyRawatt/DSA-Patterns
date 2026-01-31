#include <bits/stdc++.h>
using namespace std;

/*
--------------------------------------------------------
Problem: Word Ladder II (All Shortest Transformation Sequences)
--------------------------------------------------------
Goal:
Given two words (beginWord and endWord) and a dictionary,
find all the shortest transformation sequences from beginWord
to endWord such that:
  1. Only one letter can be changed at a time.
  2. Each transformed word must exist in the wordList.

--------------------------------------------------------
Approach:
We use BFS to find the shortest transformation path length
and simultaneously track all possible transformation sequences
of that minimum length.

Why BFS?
- Because it explores all words at a given transformation level
  before moving deeper — ensuring shortest paths first.

Key Idea:
- Each queue element stores the *entire path* (vector<string>)
  from beginWord to the current word.
- When we move to a new level, we remove words used in that level
  from the dictionary (`unordered_set`) to avoid revisiting.

--------------------------------------------------------
Time Complexity: O(N * M * 26)
    N = number of words in wordList
    M = length of each word
    (for each word, we try changing each character to 26 letters)
Space Complexity: O(N * M)
    For storing paths and visited words
--------------------------------------------------------
*/

vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
    vector<vector<string>> ans;
    unordered_set<string> st(wordList.begin(), wordList.end());

    if (st.find(endWord) == st.end())
        return ans; // no valid transformation if endWord not in dictionary

    queue<vector<string>> q;
    q.push({beginWord}); // start BFS with the begin word

    vector<string> usedOnLevel; // track words used in current BFS level
    int level = 1; // current BFS depth
    int shortestPathLength = INT_MAX;

    while (!q.empty()) {
        vector<string> path = q.front();
        q.pop();

        // if we move to a deeper level
        if (path.size() > level) {
            level++;
            // remove all words used on the previous level from the dictionary
            for (auto &w : usedOnLevel)
                st.erase(w);
            usedOnLevel.clear();
        }

        string word = path.back();

        // if we reach the endWord
        if (word == endWord) {
            if (path.size() <= shortestPathLength) {
                shortestPathLength = path.size();
                ans.push_back(path);
            }
            continue;
        }

        // Try changing each character in the word
        for (int i = 0; i < word.size(); i++) {
            char original = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                word[i] = c;

                // if the transformed word exists in dictionary
                if (st.find(word) != st.end()) {
                    path.push_back(word);      // add to path
                    q.push(path);              // push new path into queue
                    usedOnLevel.push_back(word); // mark as used in this level
                    path.pop_back();           // backtrack for next transformation
                }
            }
            word[i] = original; // restore original letter
        }
    }

    return ans;
}

// --------------------------------------------------------
// Main function to test
// --------------------------------------------------------
int main() {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    vector<vector<string>> result = findLadders(beginWord, endWord, wordList);

    if (result.empty()) {
        cout << "No transformation sequence possible.\n";
    } else {
        cout << "All shortest transformation sequences:\n";
        for (auto &path : result) {
            for (int i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i != path.size() - 1) cout << " -> ";
            }
            cout << "\n";
        }
    }

    return 0;
}
