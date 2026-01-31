#include <bits/stdc++.h>
using namespace std;

/*
Goal:
Find all shortest transformation sequences from beginWord to endWord.
Each transformation changes only one letter at a time,
and each intermediate word must exist in the given wordList.
*/

// Global variables
unordered_map<string, int> mpp;  // stores shortest distance (level) of each word from beginWord
vector<vector<string>> ans;      // stores all shortest sequences
string b;                        // global copy of beginWord for DFS backtracking

// Backtracking DFS to build all shortest sequences
void dfs(string word, vector<string>& seq, int sz) {
    if (word == b) {
        // When we reach beginWord, we found a complete valid sequence
        reverse(seq.begin(), seq.end());
        ans.push_back(seq);
        reverse(seq.begin(), seq.end());
        return;
    }

    int steps = mpp[word];
    for (int i = 0; i < sz; i++) {
        char original = word[i];
        for (char ch = 'a'; ch <= 'z'; ch++) {
            word[i] = ch;
            // If this word exists and its level is exactly one less → part of shortest path
            if (mpp.find(word) != mpp.end() && mpp[word] + 1 == steps) {
                seq.push_back(word);
                dfs(word, seq, sz);
                seq.pop_back();
            }
        }
        word[i] = original;
    }
}

// Main function
vector<vector<string>> findLadders_optimal(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> st(wordList.begin(), wordList.end());
    if (st.find(endWord) == st.end()) return {};  // endWord must exist in list

    queue<string> q;
    b = beginWord;
    q.push(beginWord);
    mpp[beginWord] = 1;
    int sz = beginWord.size();

    // BFS to find the shortest distance (level) for each reachable word
    while (!q.empty()) {
        string word = q.front();
        int steps = mpp[word];
        q.pop();
        if(word==endWord) break;
        for (int i = 0; i < sz; i++) {
            char original = word[i];
            for (char ch = 'a'; ch <= 'z'; ch++) {
                word[i] = ch;
                if (st.count(word)) {
                    q.push(word);
                    st.erase(word);
                    mpp[word] = steps + 1;
                }
            }
            word[i] = original;
        }
    }

    // If endWord was reached, start DFS backtracking from it
    if (mpp.find(endWord) != mpp.end()) {
        vector<string> seq;
        seq.push_back(endWord);
        dfs(endWord, seq, sz);
    }

    return ans;
}

// Driver code
int main() {
    string beginWord = "hit";
    string endWord = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    vector<vector<string>> res = findLadders_optimal(beginWord, endWord, wordList);

    cout << "All shortest transformation sequences:\n";
    for (auto& seq : res) {
        for (auto& word : seq)
            cout << word << " ";
        cout << endl;
    }

    return 0;
}


// ⏱️ Time Complexity

// Let:

// N = number of words in wordList

// L = length of each word

// BFS Phase:

// For each word, we try L × 26 transformations.

// Checking membership in unordered_set → O(1).

// ⇒ O(N × L × 26)

// DFS Phase:

// In worst case, can explore multiple minimal paths.

// Roughly O(N × L) in practical cases.

// ✅ Total Average Time Complexity: O(N × L × 26)
// ✅ Space Complexity: O(N × L) (for queue, map, recursion, and set)