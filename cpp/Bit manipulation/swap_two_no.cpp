#include <iostream>
using namespace std;

void swap(int &a, int &b) {
    if (&a == &b) return; // Prevent self-swap bug
    a = a ^ b;
    b = a ^ b;
    a = a ^ b;
}

int main() {
    int x = 5, y = 10;
    swap(x, y);
    cout << "x = " << x << ", y = " << y << endl; // x=10, y=5
}
