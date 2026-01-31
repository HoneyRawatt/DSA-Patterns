#include<bits/stdc++.h>
using namespace std;

/*
 Node structure for Trie with counters
*/
struct Node {
    Node* links[26];
    int cntEndWith = 0;   // number of words ending here
    int cntPrefix = 0;   // number of words passing through

    bool containsKey(char ch) {
        return (links[ch - 'a'] != nullptr);
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    void increaseEnd() {
        cntEndWith++;
    }

    void increasePrefix() {
        cntPrefix++;
    }

    void deleteEnd() {
        cntEndWith--;
    }

    void reducePrefix() {
        cntPrefix--;
    }

    int getEnd() {
        return cntEndWith;
    }

    int getPrefix() {
        return cntPrefix;
    }
};

class Trie {
private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }

    /*
     Insert a word

     Intuition:
     - Traverse character by character
     - Create node if missing
     - Increase prefix count for each node
     - Increase end count at last node

     Time Complexity: O(L)
     Space Complexity: O(L)
    */
    void insert(string &word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                node->put(word[i], new Node());   
            }
            node = node->get(word[i]);         
            node->increasePrefix();
        }
        node->increaseEnd();
    }

    /*
     Count words equal to given word

     Intuition:
     - Traverse the word
     - If path breaks → 0
     - Return cntEndWith of last node

     Time Complexity: O(L)
     Space Complexity: O(1)
    */
    int countWordsEqualTo(string &word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                return 0;
            }
            node = node->get(word[i]);
        }
        return node->getEnd();   
    }

    /*
     Count words starting with given prefix

     Intuition:
     - Traverse prefix
     - If path exists, return cntPrefix of last node

     Time Complexity: O(L)
     Space Complexity: O(1)
    */
    int countWordsStartingWith(string &word) {
        Node* node = root;
        for (int i = 0; i < word.length(); i++) {
            if (!node->containsKey(word[i])) {
                return 0;
            }
            node = node->get(word[i]);   
        }
        return node->getPrefix();
    }

    /*
     Erase a word

     Intuition:
     - Traverse word
     - Reduce prefix count at each node
     - Reduce end count at last node

     Time Complexity: O(L)
     Space Complexity: O(1)
    */
    void erase(string &word) {
        Node* node = root;
        for (int i = 0; i < word.size(); i++) {
            if (!node->containsKey(word[i])) {
                return;
            }
            node = node->get(word[i]);
            node->reducePrefix();
        }
        node->deleteEnd();
    }
};
