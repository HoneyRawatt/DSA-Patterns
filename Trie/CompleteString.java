package Trie;
import java.util.*;

/*
 Intuition:
 A string is valid only if ALL its prefixes exist as complete words in the Trie.

 Example:
 "ninja" is valid if:
 "n", "ni", "nin", "ninj", "ninja" all exist.
*/

class TrieNode {
    TrieNode[] links = new TrieNode[26];
    boolean flag = false;

    boolean containsKey(char ch) {
        return links[ch - 'a'] != null;
    }

    void put(char ch, TrieNode node) {
        links[ch - 'a'] = node;
    }

    TrieNode get(char ch) {
        return links[ch - 'a'];
    }

    void setEnd() {
        flag = true;
    }

    boolean isEnd() {
        return flag;
    }
}

class Trie {
    private TrieNode root;

    Trie() {
        root = new TrieNode();
    }

    /*
     Insert word into Trie
     Time: O(L)
     Space: O(L)
    */
    void insert(String word) {
        TrieNode node = root;
        for (char ch : word.toCharArray()) {
            if (!node.containsKey(ch)) {
                node.put(ch, new TrieNode());
            }
            node = node.get(ch);
        }
        node.setEnd();
    }

    /*
     Check if all prefixes of word exist
     Time: O(L)
     Space: O(1)
    */
    boolean checkIfPrefixExists(String word) {
        TrieNode node = root;
        for (char ch : word.toCharArray()) {
            if (!node.containsKey(ch)) {
                return false;
            }
            node = node.get(ch);
            if (!node.isEnd()) {
                return false;
            }
        }
        return true;
    }
}

public class CompleteString{

    /*
     Complete String Function

     Time Complexity:
     O(N * L)

     Space Complexity:
     O(N * L)
    */
    public static String completeString(int n, String[] a) {
        Trie trie = new Trie();

        for (String word : a) {
            trie.insert(word);
        }

        String longest = "";

        for (String word : a) {
            if (trie.checkIfPrefixExists(word)) {
                if (word.length() > longest.length()) {
                    longest = word;
                } 
                else if (word.length() == longest.length()
                         && word.compareTo(longest) < 0) {
                    longest = word;
                }
            }
        }

        return longest.length() == 0 ? "None" : longest;
    }
}
