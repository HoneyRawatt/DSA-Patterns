#include <iostream>
#include <stack>
using namespace std;

// ---------- Approach 1: Costly Push ----------
class QueueUsingStackPush {
    stack<int> s1, s2;
public:
    void push(int x) {
        // Move everything from s1 to s2
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
        // Push new element into s1
        s1.push(x);
        // Move everything back to s1
        while (!s2.empty()) {
            s1.push(s2.top());
            s2.pop();
        }
    }

    void pop() {
        if (s1.empty()) {
            cout << "Queue is Empty\n";
            return;
        }
        s1.pop();
    }

    int top() {
        if (s1.empty()) {
            cout << "Queue is Empty\n";
            return -1;
        }
        return s1.top();
    }

    bool empty() {
        return s1.empty();
    }
};

// ---------- Approach 2: Costly Pop/Top ----------
class QueueUsingStackPop {
    stack<int> s1, s2;
public:
    void push(int x) {
        s1.push(x);
    }

    void transfer() {
        while (!s1.empty()) {
            s2.push(s1.top());
            s1.pop();
        }
    }

    void pop() {
        if (s1.empty() && s2.empty()) {
            cout << "Queue is Empty\n";
            return;
        }
        if (s2.empty()) transfer();
        s2.pop();
    }

    int top() {
        if (s1.empty() && s2.empty()) {
            cout << "Queue is Empty\n";
            return -1;
        }
        if (s2.empty()) transfer();
        return s2.top();
    }

    bool empty() {
        return s1.empty() && s2.empty();
    }
};

// ---------- Demo ----------
int main() {
    cout << "Approach 1: Costly Push\n";
    QueueUsingStackPush q1;
    q1.push(10);
    q1.push(20);
    q1.push(30);
    cout << q1.top() << endl; // 10
    q1.pop();
    cout << q1.top() << endl; // 20

    cout << "\nApproach 2: Costly Pop\n";
    QueueUsingStackPop q2;
    q2.push(100);
    q2.push(200);
    q2.push(300);
    cout << q2.top() << endl; // 100
    q2.pop();
    cout << q2.top() << endl; // 200
}
