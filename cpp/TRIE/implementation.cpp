#include<bits/stdc++.h>
using namespace std;

/*
 Node structure for Trie
 Each node stores:
 - links[26] : pointers to next characters
 - flag      : true if a word ends here
*/
struct Node {
    Node* links[26];
    bool flag = false;

    // Check if a character link exists
    bool containsKey(char ch) {
        return (links[ch - 'a'] != NULL);
    }

    // Create a link for a character
    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    // Get the next node for a character
    Node* get(char ch) {
        return links[ch - 'a'];
    }

    // Mark end of word
    void setEnd() {
        flag = true;
    }

    // Check if it is end of word
    bool isEnd() {
        return flag;
    }
};

class Trie {
private:
    Node* root;

public:
    // Constructor
    Trie() {
        root = new Node();
    }

    /*
     Insert a word into Trie

     Intuition:
     - Start from root
     - For each character, create node if it doesn't exist
     - Move forward
     - Mark the last node as end of word

     Time Complexity: O(L)
     Space Complexity: O(L) (only when new nodes are created)
     where L = length of word
    */
    void insert(string word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node());
            }
            node = node->get(word[i]);
        }
        node->setEnd();
    }

    /*
     Search for a complete word

     Intuition:
     - Traverse character by character
     - If any character is missing → false
     - At end, check end flag

     Time Complexity: O(L)
     Space Complexity: O(1)
    */
    bool search(string word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                return false;
            }
            node = node->get(word[i]);
        }
        return node->isEnd();
    }

    /*
     Check if a prefix exists

     Intuition:
     - Similar to search
     - We do NOT care about end flag
     - If traversal succeeds, prefix exists

     Time Complexity: O(L)
     Space Complexity: O(1)
    */
    bool startsWith(string prefix) {
        Node* node = root;
        for (int i = 0; i < prefix.length(); i++) {
            if (!node->containsKey(prefix[i])) {
                return false;
            }
            node = node->get(prefix[i]);
        }
        return true;
    }
};
