#include<bits/stdc++.h>
using namespace std;

struct Node {
    Node* links[26] = {nullptr};

    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }
};

/*
 Count distinct substrings using Trie

 Time Complexity: O(N^2)
 Space Complexity: O(N^2)
*/
int countDistinctSubstrings(string &word) {
    Node* root = new Node();
    int cnt = 0;

    for (int i = 0; i < word.size(); i++) {
        Node* node = root;
        for (int j = i; j < word.size(); j++) {
            if (!node->containsKey(word[j])) {
                cnt++;                         // new substring found
                node->put(word[j], new Node());
            }
            node = node->get(word[j]);
        }
    }

    return cnt + 1;  // +1 for empty substring
}
