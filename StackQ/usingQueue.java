package StackQ;

import java.util.LinkedList;
import java.util.Queue;

class Stack {
    private Queue<Integer> q = new LinkedList<>();

    public void push(int x) {
        int s = q.size();
        q.offer(x); // add new element

        // Rotate the queue to make new element at front
        for (int i = 0; i < s; i++) {
            q.offer(q.poll());
        }
    }

    public void pop() {
        if (q.isEmpty()) {
            System.out.println("Stack Underflow!");
            return;
        }
        q.poll();
    }

    public int top() {
        if (q.isEmpty()) {
            System.out.println("Stack is Empty!");
            return -1;
        }
        return q.peek();
    }

    public boolean empty() {
        return q.isEmpty();
    }

    public int size() {
        return q.size();
    }
}

public class usingQueue{
    public static void main(String[] args) {
        Stack s = new Stack();
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
