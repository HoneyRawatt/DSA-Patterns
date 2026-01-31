package Trie;

class Node {
    Node[] links = new Node[26];

    boolean containsKey(char ch) {
        return links[ch - 'a'] != null;
    }

    void put(char ch, Node node) {
        links[ch - 'a'] = node;
    }

    Node get(char ch) {
        return links[ch - 'a'];
    }
}

public class DistinctSubstring {

    /*
     Count distinct substrings using Trie

     Time Complexity: O(N^2)
     Space Complexity: O(N^2)
    */
    public static int countSubs(String word) {
        Node root = new Node();
        int cnt = 0;   

        for (int i = 0; i < word.length(); i++) {
            Node node = root;
            for (int j = i; j < word.length(); j++) {

                char ch = word.charAt(j);   

                if (!node.containsKey(ch)) {
                    node.put(ch, new Node());
                    cnt++;                 // new substring found
                }
                node = node.get(ch);
            }
        }

        return cnt + 1;   // +1 for empty substring
    }
}
