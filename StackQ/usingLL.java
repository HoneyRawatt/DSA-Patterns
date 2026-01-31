package StackQ;

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

class Stackl {
    private Node topNode;
    private int count;

    public Stackl() {
        topNode = null;
        count = 0;
    }

    public void push(int x) {
        Node temp = new Node(x);
        temp.next = topNode;
        topNode = temp;
        count++;
    }

    public int top() {
        if (topNode == null) {
            System.out.println("Stack is empty!");
            return -1;
        }
        return topNode.data;
    }

    public void pop() {
        if (topNode == null) {
            System.out.println("Stack Underflow!");
            return;
        }
        topNode = topNode.next;
        count--;
    }

    public int size() {
        return count;
    }

    public boolean empty() {
        return topNode == null;
    }
}

public class usingLL{
    public static void main(String[] args) {
        Stackl s = new Stackl();
        s.push(10);
        s.push(20);
        s.push(30);

        System.out.println("Top: " + s.top()); // 30
        s.pop();
        System.out.println("Top after pop: " + s.top()); // 20
        System.out.println("Size: " + s.size()); // 2

        s.pop();
        s.pop();
        s.pop(); // Underflow
    }
}

