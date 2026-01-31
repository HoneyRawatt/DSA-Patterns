#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int val) {
        data = val;
        next = nullptr;
    }

    Node(int val, Node* nextNode) {
        data = val;
        next = nextNode;
    }
};

class Q {
    Node* start;
    Node* end;
    int currSize;

public:
    Q() {
        start = nullptr;
        end = nullptr;
        currSize = 0;
    }

    void push(int x) {
        Node* temp = new Node(x);
        if (start == nullptr) {
            start = end = temp;
        } else {
            end->next = temp;
            end = temp;
        }
        currSize++;
    }

    void pop() {
        if (start == nullptr) {
            cout << "Empty" << endl;
            return;
        }
        Node* temp = start;
        start = start->next;
        delete temp;
        currSize--;
        if (start == nullptr) { // reset if queue becomes empty
            end = nullptr;
        }
    }

    int top() {
        if (start == nullptr) {
            cout << "Empty" << endl;
            return -1;
        }
        return start->data;
    }

    int size() {
        return currSize;
    }

    bool empty() {
        return currSize == 0;
    }
};

// Example usage
int main() {
    Q q;
    q.push(10);
    q.push(20);
    q.push(30);

    cout << "Front: " << q.top() << endl; // 10
    q.pop();
    cout << "Front after pop: " << q.top() << endl; // 20
    cout << "Size: " << q.size() << endl; // 2
}
