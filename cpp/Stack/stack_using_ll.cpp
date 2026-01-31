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

class Stack {
    Node* topNode;
    int count;

public:
    Stack() {
        topNode = nullptr;
        count = 0;
    }

    void push(int x) {
        Node* temp = new Node(x);
        temp->next = topNode;
        topNode = temp;
        count++;
    }

    int top() {
        if (topNode == nullptr) {
            cout << "Stack is empty!" << endl;
            return -1;
        }
        return topNode->data;
    }

    void pop() {
        if (topNode == nullptr) {
            cout << "Stack Underflow!" << endl;
            return;
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        count--;
    }

    int size() {
        return count;
    }

    bool empty() {
        return topNode == nullptr;
    }
};

// Example usage
int main() {
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << "Top: " << s.top() << endl;   // 30
    s.pop();
    cout << "Top after pop: " << s.top() << endl; // 20
    cout << "Size: " << s.size() << endl; // 2

    s.pop();
    s.pop();
    s.pop(); // Underflow

    return 0;
}
