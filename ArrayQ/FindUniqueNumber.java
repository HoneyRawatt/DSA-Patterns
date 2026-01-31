import java.util.*;

public class FindUniqueNumber {

    /*
     * Approach 1: Brute Force
     * Time Complexity: O(n^2)
     * Space Complexity: O(1)
     */
    static int findOnceBrute(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n; i++) {
            int cnt = 0;
            int num = arr[i];
            for (int j = 0; j < n; j++) {
                if (arr[j] == num) cnt++;
            }
            if (cnt == 1) return num;
        }
        return -1;
    }

    /*
     * Approach 2: Hashing (using array)
     * Works only if elements are non-negative
     * Time Complexity: O(n + maxValue)
     * Space Complexity: O(maxValue)
     */
    static int findOnceHashing(int[] arr) {
        int n = arr.length;
        int max = Arrays.stream(arr).max().getAsInt();
        int[] hash = new int[max + 1];

        for (int num : arr) hash[num]++;
        for (int num : arr) {
            if (hash[num] == 1) return num;
        }
        return -1;
    }

    /*
     * Approach 3: Using Map
     * Time Complexity: O(n log n)
     * Space Complexity: O(n)
     */
    static int findOnceMap(int[] arr) {
        HashMap<Integer,Integer>map=new HashMap<>();
        for(int i=0;i<arr.length;i++) map.put(arr[i],map.getOrDefault(arr[i],0)+1);
        
        for (var entry : map.entrySet()) {
            if (entry.getValue() == 1) return entry.getKey();
        }
        return -1;
    }

    /*
     * Approach 4: XOR (works if all elements appear twice except one)
     * Time Complexity: O(n)
     * Space Complexity: O(1)
     */
    static int findOnceXOR(int[] arr) {
        int xor = 0;
        for (int num : arr) xor ^= num;
        return xor;
    }

    // Driver Code
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        int[] arr = new int[n];
        System.out.println("Enter the elements: ");
        for (int i = 0; i < n; i++) arr[i] = sc.nextInt();

        System.out.println("Appears once (Brute): " + findOnceBrute(arr));
        System.out.println("Appears once (Hashing): " + findOnceHashing(arr));
        System.out.println("Appears once (Map): " + findOnceMap(arr));
        System.out.println("Appears once (XOR): " + findOnceXOR(arr));

        sc.close();
    }
}


