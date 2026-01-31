package Trie;
import java.util.*;

class Node {
    Node[] links;

    // Constructor
    Node() {
        links = new Node[2];
    }

    boolean containsKey(int bit) {
        return links[bit] != null;
    }

    Node get(int bit) {
        return links[bit];
    }

    void put(int bit, Node node) {
        links[bit] = node;
    }
}

class Trie {
    private Node root;

    Trie() {
        root = new Node();
    }

    // Insert number into trie
    void insert(int num) {
        Node node = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (!node.containsKey(bit)) {
                node.put(bit, new Node());
            }
            node = node.get(bit);
        }
    }

    // Get maximum XOR for a number
    int getMax(int num) {
        Node node = root;
        int maxNum = 0;

        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;

            // Prefer opposite bit
            if (node.containsKey(1 - bit)) {
                maxNum |= (1 << i);
                node = node.get(1 - bit);
            } else {
                node = node.get(bit);
            }
        }
        return maxNum;
    }
}

public class MaxXor {

    // Function to calculate max XOR between two arrays
    static int maxXor(int n, int m, int[] arr1, int[] arr2) {
        Trie trie = new Trie();

        // Insert elements of arr1
        for (int x : arr1) {
            trie.insert(x);
        }

        int maxi = 0;

        // Query for each element of arr2
        for (int x : arr2) {
            maxi = Math.max(maxi, trie.getMax(x));
        }

        return maxi;
    }

    // ---------------- DRIVER CODE ----------------
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int n = sc.nextInt();
        int m = sc.nextInt();

        int[] arr1 = new int[n];
        int[] arr2 = new int[m];

        for (int i = 0; i < n; i++) arr1[i] = sc.nextInt();
        for (int i = 0; i < m; i++) arr2[i] = sc.nextInt();

        System.out.println(maxXor(n, m, arr1, arr2));
        sc.close();
    }
}
