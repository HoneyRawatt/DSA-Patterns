package BitManipulation;
public class XORRange {

    /*
     XOR from 1 to n follows a repeating pattern every 4 numbers:
     n % 4 == 0 → result = n
     n % 4 == 1 → result = 1
     n % 4 == 2 → result = n + 1
     n % 4 == 3 → result = 0

     Time Complexity: O(1)
     Space Complexity: O(1)
    */
    public static int xorOfNumbers(int n) {
        if (n % 4 == 0) return n;
        if (n % 4 == 1) return 1;
        if (n % 4 == 2) return n + 1;
        return 0; // n % 4 == 3
    }

    /*
     XOR of numbers in range [l, r] = XOR(1..r) ^ XOR(1..l-1)
     Time Complexity: O(1)
     Space Complexity: O(1)
    */
    public static int xorOfRange(int l, int r) {
        return xorOfNumbers(r) ^ xorOfNumbers(l - 1);
    }

    public static void main(String[] args) {
        int l = 3, r = 9;
        System.out.println("XOR from " + l + " to " + r + " = " + xorOfRange(l, r));
    }
}
