#include <iostream>
#include <string>
using namespace std;

/*
PROBLEM:
--------
Implement a simplified browser history with the following operations:
1) visit(url)   → navigate to a new url from the current page
2) back(steps)  → move back by `steps` pages
3) forward(steps) → move forward by `steps` pages

Constraints:
- Visiting a new URL clears forward history
- Support efficient navigation
*/

/*
Node structure for doubly-linked list:
- data → stores URL
- next → pointer to next page in history (forward)
- back → pointer to previous page in history (backward)
*/
class Node {
public:
    string data;
    Node* next;
    Node* back;

    Node() : data(""), next(nullptr), back(nullptr) {}
    Node(string x) : data(x), next(nullptr), back(nullptr) {}
    Node(string x, Node* nextNode, Node* backNode) : data(x), next(nextNode), back(backNode) {}
};

/*
Browser class simulates browser history
*/
class Browser {
    Node* currentpage;  // pointer to current page

public:
    // Initialize with homepage
    Browser(string homepage) {
        currentpage = new Node(homepage);
    }

    /*
    visit(url):
    -----------
    - Create new node with url
    - Link current page's next to new node
    - Set new node's back pointer to current page
    - Move currentpage pointer to new node
    - Forward history is automatically cleared by overwriting currentpage->next
    */
    void visit(string url) {
        Node* newnode = new Node(url);
        currentpage->next = newnode; // remove forward history
        newnode->back = currentpage;
        currentpage = newnode;
    }

    /*
    back(steps):
    -------------
    - Move back up to `steps` nodes or until back pointer is null
    - Return current page's URL
    */
    string back(int steps) {
        while (steps && currentpage->back) {
            currentpage = currentpage->back;
            steps--;
        }
        return currentpage->data;
    }

    /*
    forward(steps):
    ----------------
    - Move forward up to `steps` nodes or until next pointer is null
    - Return current page's URL
    */
    string forward(int steps) {
        while (steps && currentpage->next) {
            currentpage = currentpage->next;
            steps--;
        }
        return currentpage->data;
    }
};

/*
Driver code to test browser history
*/
int main() {
    Browser browser("leetcode.com");

    browser.visit("google.com");
    browser.visit("facebook.com");
    browser.visit("youtube.com");

    cout << browser.back(1) << endl;     // facebook.com
    cout << browser.back(1) << endl;     // google.com
    cout << browser.forward(1) << endl;  // facebook.com

    browser.visit("linkedin.com");       // forward history cleared
    cout << browser.forward(2) << endl;  // linkedin.com
    cout << browser.back(2) << endl;     // google.com
    cout << browser.back(7) << endl;     // leetcode.com

    return 0;
}

/*
TIME COMPLEXITY:
----------------
- visit(url) → O(1)
- back(steps) → O(steps)
- forward(steps) → O(steps)

SPACE COMPLEXITY:
-----------------
- O(n) where n = total pages visited (doubly-linked list nodes)
*/
