package QueueQ;

class Node {
    int data;
    Node next;

    Node(int val) {
        data = val;
        next = null;
    }

    Node(int val, Node nextNode) {
        data = val;
        next = nextNode;
    }
}

class Q {
    private Node start;
    private Node end;
    private int currSize;

    public Q() {
        start = null;
        end = null;
        currSize = 0;
    }

    public void push(int x) {
        Node temp = new Node(x);
        if (start == null) {
            start = end = temp;
        } else {
            end.next = temp;
            end = temp;
        }
        currSize++;
    }

    public void pop() {
        if (start == null) {
            System.out.println("Empty");
            return;
        }
        start = start.next;
        currSize--;
        if (start == null) { // reset if queue becomes empty
            end = null;
        }
    }

    public int top() {
        if (start == null) {
            System.out.println("Empty");
            return -1;
        }
        return start.data;
    }

    public int size() {
        return currSize;
    }

    public boolean empty() {
        return currSize == 0;
    }
}

public class usingLL{
    public static void main(String[] args) {
        Q q = new Q();
        q.push(10);
        q.push(20);
        q.push(30);

        System.out.println("Front: " + q.top()); // 10
        q.pop();
        System.out.println("Front after pop: " + q.top()); // 20
        System.out.println("Size: " + q.size()); // 2
    }
}

