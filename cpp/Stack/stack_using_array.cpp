#include <iostream>
using namespace std;

class Stack {
    int arr[10];
    int topIndex;

public:
    Stack() {
        topIndex = -1;
    }

    void push(int x) {
        if (topIndex >= 9) {
            cout << "Overflow" << endl;
            return;
        }
        topIndex++;
        arr[topIndex] = x;
    }

    int top() {
        if (topIndex == -1) {
            cout << "Empty" << endl;
            return -1; // return invalid value
        }
        return arr[topIndex];
    }

    void pop() {
        if (topIndex == -1) {
            cout << "Underflow" << endl;
            return;
        }
        topIndex--;
    }

    int size() {
        return topIndex + 1;
    }

    bool empty() {
        return topIndex == -1;
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
    s.pop(); // underflow
}
