/**
 * ============================
 * Problem Statement:
 * ============================
 * Design a Least Recently Used (LRU) Cache that supports the following operations
 * in O(1) average time complexity:
 *
 * 1. get(key): Return the value of the key if it exists in the cache,
 *    otherwise return -1. Accessing a key makes it the most recently used.
 *
 * 2. put(key, value): Insert or update the value of the key.
 *    If the cache reaches its capacity, evict the least recently used key.
 *
 * ============================
 * Intuition / Approach:
 * ============================
 * We need:
 *  - Fast lookup by key  → Hash map
 *  - Fast update of usage order → Doubly linked list
 *
 * Doubly Linked List:
 *  - Most recently used node is placed near the head
 *  - Least recently used node is near the tail
 *
 * Hash Map:
 *  - Maps key → corresponding node in the linked list
 *
 * This combination allows:
 *  - O(1) access (map)
 *  - O(1) deletion and insertion (DLL)
 *
 * ============================
 * Time Complexity:
 * ============================
 * get()  → O(1)
 * put()  → O(1)
 *
 * ============================
 * Space Complexity:
 * ============================
 * O(capacity) for hashmap + linked list
 */

#include <iostream>
#include <map>
using namespace std;

// Doubly Linked List Node
class Node {
public:
    int key, val;
    Node* next;
    Node* prev;

    Node(int key, int val) {
        this->key = key;
        this->val = val;
        next = nullptr;
        prev = nullptr;
    }
};

class LRUCache {
public:
    map<int, Node*> mpp;  // key → node
    int capacity;
    Node* head;           // Dummy head
    Node* tail;           // Dummy tail

    // Constructor: Initialize cache with given capacity
    LRUCache(int capacity) {
        this->capacity = capacity;
        mpp.clear();

        // Dummy nodes to avoid edge cases
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;
    }

    // Remove a node from the doubly linked list
    void DeleteNode(Node* node) {
        Node* prevnode = node->prev;
        Node* afternode = node->next;
        prevnode->next = afternode;
        afternode->prev = prevnode;
    }

    // Insert a node right after the head (most recently used)
    void InsertHead(Node* node) {
        Node* currafterhead = head->next;
        head->next = node;
        node->next = currafterhead;
        currafterhead->prev = node;
        node->prev = head;
    }

    // Get value for a key
    int get(int key) {
        // Key not present
        if (mpp.find(key) == mpp.end())
            return -1;

        // Move accessed node to front (MRU)
        Node* node = mpp[key];
        int value = node->val;
        DeleteNode(node);
        InsertHead(node);
        return value;
    }

    // Insert or update key-value
    void put(int key, int value) {
        // If key already exists
        if (mpp.find(key) != mpp.end()) {
            Node* node = mpp[key];
            node->val = value;

            // Move to front
            DeleteNode(node);
            InsertHead(node);
        } else {
            // Cache full → remove least recently used node
            if (mpp.size() == capacity) {
                Node* last = tail->prev;  // LRU node
                mpp.erase(last->key);
                DeleteNode(last);
            }

            // Insert new node
            Node* node = new Node(key, value);
            mpp[key] = node;
            InsertHead(node);
        }
    }
};

int main() {
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cout << cache.get(1) << endl; // 10
    cache.put(3, 30);             // evicts key 2
    cout << cache.get(2) << endl; // -1
    cache.put(4, 40);             // evicts key 1
    cout << cache.get(1) << endl; // -1
    cout << cache.get(3) << endl; // 30
    cout << cache.get(4) << endl; // 40

    return 0;
}
