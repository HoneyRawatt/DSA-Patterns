package StackQ;

public class Stacka{
    private int[] arr = new int[10];
    private int topIndex;

    // Constructor
    public Stacka() {
        topIndex = -1;
    }

    // Push element onto stack
    public void push(int x) {
        if (topIndex >= 9) {
            System.out.println("Overflow");
            return;
        }
        topIndex++;
        arr[topIndex] = x;
    }

    // Return top element
    public int top() {
        if (topIndex == -1) {
            System.out.println("Empty");
            return -1; // invalid value
        }
        return arr[topIndex];
    }

    // Pop element from stack
    public void pop() {
        if (topIndex == -1) {
            System.out.println("Underflow");
            return;
        }
        topIndex--;
    }

    // Return size of stack
    public int size() {
        return topIndex + 1;
    }

    // Check if stack is empty
    public boolean empty() {
        return topIndex == -1;
    }
}

// Example usage
public class usingArr{
    public static void main(String[] args) {
        Stacka s = new Stacka();
        s.push(10);
        s.push(20);
        s.push(30);

        System.out.println("Top: " + s.top()); // 30
        s.pop();
        System.out.println("Top after pop: " + s.top()); // 20
        System.out.println("Size: " + s.size()); // 2

        s.pop();
        s.pop();
        s.pop(); // underflow
    }
}
