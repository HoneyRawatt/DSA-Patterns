package BitManipulation;

public class XorSwap {

    static void swap(int[] arr) {
        // arr[0] = a, arr[1] = b
        if (arr[0] == arr[1]) return; // optional safety check

        arr[0] = arr[0] ^ arr[1];
        arr[1] = arr[0] ^ arr[1];
        arr[0] = arr[0] ^ arr[1];
    }

    public static void main(String[] args) {
        int x = 5, y = 10;

        int[] values = {x, y};
        swap(values);

        x = values[0];
        y = values[1];

        System.out.println("x = " + x + ", y = " + y); // x=10, y=5
    }
}

