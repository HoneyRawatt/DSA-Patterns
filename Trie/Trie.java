package Trie;
/*
 Intuition:
 A Trie (Prefix Tree) efficiently stores strings character by character.
 Each node represents one character and maintains:
 - links[26] for lowercase English letters
 - flag to mark the end of a complete word

 This allows fast insertion, word search, and prefix search.
*/

class Trie {

    /*
     Node structure
    */
    private static class Node {
        Node[] links = new Node[26];
        boolean flag = false;

        // Check if character exists
        boolean containsKey(char ch) {
            return links[ch - 'a'] != null;
        }

        // Put new node for character
        void put(char ch, Node node) {
            links[ch - 'a'] = node;
        }

        // Get node for character
        Node get(char ch) {
            return links[ch - 'a'];
        }

        // Mark end of word
        void setEnd() {
            flag = true;
        }

        // Check end of word
        boolean isEnd() {
            return flag;
        }
    }

    private Node root;

    // Constructor
    public Trie() {
        root = new Node();
    }

    /*
     Insert a word into Trie

     Intuition:
     - Start from root
     - For each character:
         • create node if missing
         • move to next node
     - Mark last node as end of word

     Time Complexity: O(L)
     Space Complexity: O(L) (only when new nodes are created)
     where L = length of word
    */
    public void insert(String word) {
        Node node = root;
        for (int i = 0; i < word.length(); i++) {
            char ch = word.charAt(i);
            if (!node.containsKey(ch)) {
                node.put(ch, new Node());
            }
            node = node.get(ch);
        }
        node.setEnd();
    }

    /*
     Search for a complete word

     Intuition:
     - Traverse Trie using characters
     - If any character is missing → false
     - At the end, check end flag

     Time Complexity: O(L)
     Space Complexity: O(1)
    */
    public boolean search(String word) {
        Node node = root;
        for (int i = 0; i < word.length(); i++) {
            char ch = word.charAt(i);
            if (!node.containsKey(ch)) {
                return false;
            }
            node = node.get(ch);
        }
        return node.isEnd();
    }

    /*
     Check if prefix exists

     Intuition:
     - Same traversal as search
     - No need to check end flag

     Time Complexity: O(L)
     Space Complexity: O(1)
    */
    public boolean startsWith(String prefix) {
        Node node = root;
        for (int i = 0; i < prefix.length(); i++) {
            char ch = prefix.charAt(i);
            if (!node.containsKey(ch)) {
                return false;
            }
            node = node.get(ch);
        }
        return true;
    }
}
