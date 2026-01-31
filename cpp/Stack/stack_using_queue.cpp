#include <iostream>
#include <queue>
using namespace std;

class Stack {
    queue<int> q;

public:
    void push(int x) {
        int s = q.size();
        q.push(x);  // add new element

        // Rotate the queue to make new element at front
        for (int i = 0; i < s; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    void pop() {
        if (q.empty()) {
            cout << "Stack Underflow!" << endl;
            return;
        }
        q.pop();
    }

    int top() {
        if (q.empty()) {
            cout << "Stack is Empty!" << endl;
            return -1;
        }
        return q.front();
    }

    bool empty() {
        return q.empty();
    }

    int size() {
        return q.size();
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
