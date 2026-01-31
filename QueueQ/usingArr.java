package QueueQ;

class Q {
    private int currSize;
    private int[] arr = new int[10];
    private int start, end;

    // Constructor
    public Q() {
        currSize = 0;
        start = -1;
        end = -1;
    }

    // Push element into queue
    public void push(int x) {
        if (currSize == 10) {
            System.out.println("Overflow");
            return;
        }
        if (start == -1) start = 0; // first element
        end = (end + 1) % 10;
        arr[end] = x;
        currSize++;
    }

    // Pop element from queue
    public void pop() {
        if (currSize == 0) {
            System.out.println("Empty");
            return;
        }
        start = (start + 1) % 10;
        currSize--;

        // Reset when queue becomes empty
        if (currSize == 0) {
            start = -1;
            end = -1;
        }
    }

    // Get front element
    public int top() {
        if (currSize == 0) {
            System.out.println("Empty");
            return -1;
        }
        return arr[start];
    }

    // Current size
    public int size() {
        return currSize;
    }

    // Check if empty
    public boolean empty() {
        return currSize == 0;
    }
}

// Example usage
public class usingArr{
    public static void main(String[] args) {
        Q q = new Q();
        q.push(10);
        q.push(20);
        q.push(30);

        System.out.println("Front: " + q.top()); // 10
        q.pop();
        System.out.println("Front after pop: " + q.top()); // 20
        System.out.println("Size: " + q.size()); // 2

        q.pop();
        q.pop();
        q.pop(); // Empty
    }
}
