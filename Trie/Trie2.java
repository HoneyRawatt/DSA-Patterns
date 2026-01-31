package Trie;

public /*
 Intuition:
 This Trie stores counters instead of just a boolean.
 Each node maintains:
 - cntPrefix : number of words passing through this node
 - cntEndWith: number of words ending at this node

 This allows:
 - Counting exact words
 - Counting words starting with a prefix
 - Safe deletion (erase)
*/

class Trie2 {

    /*
     Node structure
    */
    private static class Node {
        Node[] links = new Node[26];
        int cntEndWith = 0;
        int cntPrefix = 0;

        boolean containsKey(char ch) {
            return links[ch - 'a'] != null;
        }

        Node get(char ch) {
            return links[ch - 'a'];
        }

        void put(char ch, Node node) {
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
    }

    private Node root;

    // Constructor
    public Trie2() {
        root = new Node();
    }

    /*
     Insert a word

     Time Complexity: O(L)
     Space Complexity: O(L)
    */
    public void insert(String word) {
        Node node = root;
        for (int i = 0; i < word.length(); i++) {
            char ch = word.charAt(i);
            if (!node.containsKey(ch)) {
                node.put(ch, new Node());
            }
            node = node.get(ch);
            node.increasePrefix();
        }
        node.increaseEnd();
    }

    /*
     Count words exactly equal to given word

     Time Complexity: O(L)
     Space Complexity: O(1)
    */
    public int countWordsEqualTo(String word) {
        Node node = root;
        for (int i = 0; i < word.length(); i++) {
            char ch = word.charAt(i);
            if (!node.containsKey(ch)) {
                return 0;
            }
            node = node.get(ch);
        }
        return node.getEnd();
    }

    /*
     Count words starting with given prefix

     Time Complexity: O(L)
     Space Complexity: O(1)
    */
    public int countWordsStartingWith(String prefix) {
        Node node = root;
        for (int i = 0; i < prefix.length(); i++) {
            char ch = prefix.charAt(i);
            if (!node.containsKey(ch)) {
                return 0;
            }
            node = node.get(ch);
        }
        return node.getPrefix();
    }

    /*
     Erase a word

     Time Complexity: O(L)
     Space Complexity: O(1)
    */
    public void erase(String word) {
        Node node = root;
        for (int i = 0; i < word.length(); i++) {
            char ch = word.charAt(i);
            if (!node.containsKey(ch)) {
                return;
            }
            node = node.get(ch);
            node.reducePrefix();
        }
        node.deleteEnd();
    }
}

