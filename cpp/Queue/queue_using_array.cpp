#include <iostream>
using namespace std;

class Q {
    int currsize;
    int arr[10];
    int start, end;

public:
    Q() {
        currsize = 0;
        start = -1;
        end = -1;
    }

    void push(int x) {
        if (currsize == 10) {
            cout << "Overflow" << endl;
            return;
        }
        if (start == -1) start = 0; // first element
        end = (end + 1) % 10;
        arr[end] = x;
        currsize++;
    }

    void pop() {
        if (currsize == 0) {
            cout << "Empty" << endl;
            return;
        }
        start = (start + 1) % 10;
        currsize--;
        if (currsize == 0) { // reset to initial state
            start = -1;
            end = -1;
        }
    }

    int top() {
        if (currsize == 0) {
            cout << "Empty" << endl;
            return -1;
        }
        return arr[start];
    }

    int size() {
        return currsize;
    }

    bool empty() {
        return currsize == 0;
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

    q.pop();
    q.pop();
    q.pop(); // Empty
}
