package QueueQ;
import java.util.Stack;

// ---------- Approach 1: Costly Push ----------
class QueueUsingStackPush {
    private Stack<Integer> s1 = new Stack<>();
    private Stack<Integer> s2 = new Stack<>();

    public void push(int x) {
        // Move everything from s1 to s2
        while (!s1.isEmpty()) {
            s2.push(s1.pop());
        }
        // Push new element into s1
        s1.push(x);
        // Move everything back to s1
        while (!s2.isEmpty()) {
            s1.push(s2.pop());
        }
    }

    public void pop() {
        if (s1.isEmpty()) {
            System.out.println("Queue is Empty");
            return;
        }
        s1.pop();
    }

    public int top() {
        if (s1.isEmpty()) {
            System.out.println("Queue is Empty");
            return -1;
        }
        return s1.peek();
    }

    public boolean empty() {
        return s1.isEmpty();
    }
}

// ---------- Approach 2: Costly Pop/Top ----------
class QueueUsingStackPop {
    private Stack<Integer> s1 = new Stack<>();
    private Stack<Integer> s2 = new Stack<>();

    public void push(int x) {
        s1.push(x);
    }

    private void transfer() {
        while (!s1.isEmpty()) {
            s2.push(s1.pop());
        }
    }

    public void pop() {
        if (s1.isEmpty() && s2.isEmpty()) {
            System.out.println("Queue is Empty");
            return;
        }
        if (s2.isEmpty()) transfer();
        s2.pop();
    }

    public int top() {
        if (s1.isEmpty() && s2.isEmpty()) {
            System.out.println("Queue is Empty");
            return -1;
        }
        if (s2.isEmpty()) transfer();
        return s2.peek();
    }

    public boolean empty() {
        return s1.isEmpty() && s2.isEmpty();
    }
}

// ---------- Demo ----------
public class usingstack{
    public static void main(String[] args) {

        System.out.println("Approach 1: Costly Push");
        QueueUsingStackPush q1 = new QueueUsingStackPush();
        q1.push(10);
        q1.push(20);
        q1.push(30);
        System.out.println(q1.top()); // 10
        q1.pop();
        System.out.println(q1.top()); // 20

        System.out.println("\nApproach 2: Costly Pop");
        QueueUsingStackPop q2 = new QueueUsingStackPop();
        q2.push(100);
        q2.push(200);
        q2.push(300);
        System.out.println(q2.top()); // 100
        q2.pop();
        System.out.println(q2.top()); // 200
    }
}
