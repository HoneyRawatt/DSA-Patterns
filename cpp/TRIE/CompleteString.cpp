#include<bits/stdc++.h>
using namespace std;

struct Node {
    Node* links[26] = {nullptr};
    bool flag = false;

    bool containsKey(char ch) {
        return links[ch - 'a'] != nullptr;
    }

    void put(char ch, Node* node) {
        links[ch - 'a'] = node;
    }

    Node* get(char ch) {
        return links[ch - 'a'];
    }

    void setEnd() {
        flag = true;
    }

    bool isEnd() {
        return flag;
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
     Insert word into Trie
     Time: O(L)
     Space: O(L)
    */
    void insert(string &word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) {
                node->put(ch, new Node());
            }
            node = node->get(ch);
        }
        node->setEnd();
    }

    /*
     Check if ALL prefixes of word exist
     Time: O(L)
     Space: O(1)
    */
    bool checkIfPrefixExists(string &word) {
        Node* node = root;
        for (char ch : word) {
            if (!node->containsKey(ch)) {
                return false;
            }
            node = node->get(ch);
            if (!node->isEnd()) {
                return false;
            }
        }
        return true;
    }
};

/*
 Complete String Function

 Time Complexity:
 - Insert all words: O(N * L)
 - Check all words: O(N * L)

 Total: O(N * L)

 Space Complexity:
 - Trie nodes: O(N * L)
*/
string completeString(int n, vector<string> &a) {
    Trie trie;

    for (auto &it : a) {
        trie.insert(it);
    }

    string longest = "";

    for (auto &it : a) {
        if (trie.checkIfPrefixExists(it)) {
            if (it.length() > longest.length()) {
                longest = it;
            } 
            else if (it.length() == longest.length() && it < longest) {
                longest = it;
            }
        }
    }

    if (longest == "") return "None";
    return longest;
}
