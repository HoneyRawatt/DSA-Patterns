package Linkedlist;

/*
PROBLEM:
--------
Implement a simplified browser history:
1) visit(url) → navigate to a new url from the current page
2) back(steps) → move back by `steps` pages
3) forward(steps) → move forward by `steps` pages

Constraints:
- Visiting a new URL clears forward history
- Efficient navigation
*/

class Node {
    String data;  // stores URL
    Node next;    // points to next page (forward)
    Node back;    // points to previous page (backward)

    Node(String data) {
        this.data = data;
        this.next = null;
        this.back = null;
    }

    Node(String data, Node next, Node back) {
        this.data = data;
        this.next = next;
        this.back = back;
    }
}

class Browser {
    private Node currentPage;  // pointer to current page

    // Initialize browser with homepage
    public Browser(String homepage) {
        currentPage = new Node(homepage);
    }

    /*
    visit(url):
    -----------
    - Create new node with url
    - Link current page's next to new node
    - Set new node's back pointer to current page
    - Move currentPage pointer to new node
    - Forward history is automatically cleared by overwriting currentPage.next
    */
    public void visit(String url) {
        Node newNode = new Node(url);
        currentPage.next = newNode;  // forward history cleared
        newNode.back = currentPage;
        currentPage = newNode;
    }

    /*
    back(steps):
    -------------
    - Move back up to `steps` nodes or until back pointer is null
    - Return current page's URL
    */
    public String back(int steps) {
        while (steps > 0 && currentPage.back != null) {
            currentPage = currentPage.back;
            steps--;
        }
        return currentPage.data;
    }

    /*
    forward(steps):
    ----------------
    - Move forward up to `steps` nodes or until next pointer is null
    - Return current page's URL
    */
    public String forward(int steps) {
        while (steps > 0 && currentPage.next != null) {
            currentPage = currentPage.next;
            steps--;
        }
        return currentPage.data;
    }
}

public class BrowserHistoryDemo {
    public static void main(String[] args) {
        Browser browser = new Browser("leetcode.com");

        browser.visit("google.com");
        browser.visit("facebook.com");
        browser.visit("youtube.com");

        System.out.println(browser.back(1));     // facebook.com
        System.out.println(browser.back(1));     // google.com
        System.out.println(browser.forward(1));  // facebook.com

        browser.visit("linkedin.com");           // forward history cleared
        System.out.println(browser.forward(2));  // linkedin.com
        System.out.println(browser.back(2));     // google.com
        System.out.println(browser.back(7));     // leetcode.com
    }
}

/*
TIME COMPLEXITY:
----------------
- visit(url) → O(1)
- back(steps) → O(steps)
- forward(steps) → O(steps)

SPACE COMPLEXITY:
-----------------
- O(n), where n = total pages visited (doubly-linked list nodes)
*/

