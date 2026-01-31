package BitManipulation;

public class BitManibasic {

    // Method 1: Left shift mask
    static boolean checkIthBitLeftShift(int n, int i) {
        return (n & (1 << i)) != 0;
    }

    // Method 2: Right shift and check last bit
    static boolean checkIthBitRightShift(int n, int i) {
        return ((n >> i) & 1) == 1;
    }

    // Set i-th bit
    static int setIthBit(int n, int i) {
        return n | (1 << i);
    }

    // Clear i-th bit
    static int clearIthBit(int n, int i) {
        return n & ~(1 << i);
    }

    // Toggle i-th bit
    static int toggleIthBit(int n, int i) {
        return n ^ (1 << i);
    }

    // Remove rightmost set bit
    static int removeRightmostSetBit(int n) {
        return n & (n - 1);
    }

    // Check if number is power of 2
    static boolean isPowerOfTwo(int n) {
        if (n <= 0) return false;
        return (n & (n - 1)) == 0;
    }

    // Count set bits (basic method)
    static int countSetBits1(int n) {
        int cnt = 0;
        while (n > 0) {
            if ((n & 1) == 1) cnt++;
            n >>= 1;
        }
        return cnt;
    }

    // Count set bits (Brian Kernighan's algorithm)
    static int countSetBits2(int n) {
        int cnt = 0;
        while (n != 0) {
            n &= (n - 1);
            cnt++;
        }
        return cnt;
    }

    public static void main(String[] args) {

        int n = 13; // binary: 1101
        System.out.println("Original number: " + n);

        // Check bits using left shift
        for (int i = 0; i < 4; i++) {
            System.out.println(
                "Bit " + i + " (left shift check): " +
                (checkIthBitLeftShift(n, i) ? "SET" : "NOT SET")
            );
        }

        // Check bits using right shift
        for (int i = 0; i < 4; i++) {
            System.out.println(
                "Bit " + i + " (right shift check): " +
                (checkIthBitRightShift(n, i) ? "SET" : "NOT SET")
            );
        }

        // Set bit 1
        n = setIthBit(n, 1);
        System.out.println("After setting bit 1: " + n);

        // Clear bit 2
        n = clearIthBit(n, 2);
        System.out.println("After clearing bit 2: " + n);

        // Toggle bit 0
        n = toggleIthBit(n, 0);
        System.out.println("After toggling bit 0: " + n);

        // Remove rightmost set bit
        n = removeRightmostSetBit(n);
        System.out.println("After removing rightmost set bit: " + n);

        // Check power of 2
        System.out.println("Is power of 2? " + (isPowerOfTwo(n) ? "YES" : "NO"));

        // Count set bits
        System.out.println("Set bits (method 1): " + countSetBits1(n));
        System.out.println("Set bits (method 2): " + countSetBits2(n));
    }
}
