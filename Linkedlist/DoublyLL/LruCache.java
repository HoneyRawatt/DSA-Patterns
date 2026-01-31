package Linkedlist.DoublyLL;

/**
 * ============================
 * Problem Statement:
 * ============================
 * Design a Least Recently Used (LRU) Cache that supports:
 *
 * 1. get(key): Return the value of the key if it exists, otherwise return -1.
 *    Accessing a key makes it the most recently used.
 *
 * 2. put(key, value): Insert or update the key-value pair.
 *    If the cache exceeds its capacity, evict the least recently used key.
 *
 * ============================
 * Intuition / Approach:
 * ============================
 * We need O(1) operations for both get and put.
 *
 * - HashMap provides O(1) access to nodes using keys.
 * - Doubly Linked List maintains usage order:
 *      - Most Recently Used (MRU) near the head
 *      - Least Recently Used (LRU) near the tail
 *
 * On every get/put:
 * - Move the accessed node to the front.
 * - Evict from the tail when capacity is exceeded.
 *
 * ============================
 * Time Complexity:
 * ============================
 * get() → O(1)
 * put() → O(1)
 *
 * ============================
 * Space Complexity:
 * ============================
 * O(capacity) for HashMap + Doubly Linked List
 */

import java.util.HashMap;
import java.util.Map;

class Node {
    int key;
    int val;
    Node next;
    Node prev;

    Node(int key, int val) {
        this.key = key;
        this.val = val;
    }
}

class LRUCache {

    private Map<Integer, Node> map;
    private int capacity;
    private Node head; // Dummy head
    private Node tail; // Dummy tail

    // Constructor
    public LRUCache(int capacity) {
        this.capacity = capacity;
        map = new HashMap<>();

        // Dummy nodes to avoid edge cases
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head.next = tail;
        tail.prev = head;
    }

    // Remove node from doubly linked list
    private void deleteNode(Node node) {
        Node prevNode = node.prev;
        Node nextNode = node.next;
        prevNode.next = nextNode;
        nextNode.prev = prevNode;
    }

    // Insert node right after head (MRU position)
    private void insertAtHead(Node node) {
        Node afterHead = head.next;
        head.next = node;
        node.prev = head;
        node.next = afterHead;
        afterHead.prev = node;
    }

    // Get value by key
    public int get(int key) {
        if (!map.containsKey(key))
            return -1;

        Node node = map.get(key);

        // Move accessed node to front
        deleteNode(node);
        insertAtHead(node);

        return node.val;
    }

    // Put key-value pair
    public void put(int key, int value) {

        // If key already exists → update and move to front
        if (map.containsKey(key)) {
            Node node = map.get(key);
            node.val = value;

            deleteNode(node);
            insertAtHead(node);
        } 
        // Key does not exist
        else {
            // If cache is full → remove LRU
            if (map.size() == capacity) {
                Node lru = tail.prev;
                map.remove(lru.key);
                deleteNode(lru);
            }

            // Insert new node
            Node node = new Node(key, value);
            map.put(key, node);
            insertAtHead(node);
        }
    }
}

// Driver code
public class LruCache{
    public static void main(String[] args) {

        LRUCache cache = new LRUCache(2);

        cache.put(1, 10);
        cache.put(2, 20);
        System.out.println(cache.get(1)); // 10
        cache.put(3, 30);                 // evicts key 2
        System.out.println(cache.get(2)); // -1
        cache.put(4, 40);                 // evicts key 1
        System.out.println(cache.get(1)); // -1
        System.out.println(cache.get(3)); // 30
        System.out.println(cache.get(4)); // 40
    }
}

