package ArrayQ;

import java.util.*;

public class IntersectionArray {

    // Method 1: Brute force using visited array
    public static List<Integer> intersectionArray(int[] a, int[] b) {
        List<Integer> ans = new ArrayList<>();

        int n1 = a.length;
        int n2 = b.length;
        int[] vis = new int[n2]; // visited array

        for (int i = 0; i < n1; i++) {
            for (int j = 0; j < n2; j++) {

                if (a[i] == b[j] && vis[j] == 0) {
                    ans.add(b[j]);
                    vis[j] = 1;
                    break;
                }

                if (b[j] > a[i]) break; // optimization for sorted arrays
            }
        }
        return ans;
    }

    // Method 2: Optimal two-pointer approach (sorted arrays)
    public static List<Integer> intersectionArray2(int[] a, int[] b) {
        List<Integer> ans = new ArrayList<>();

        int i = 0, j = 0;
        int n1 = a.length, n2 = b.length;

        while (i < n1 && j < n2) {
            if (a[i] < b[j]) {
                i++;
            } else if (b[j] < a[i]) {
                j++;
            } else {
                ans.add(a[i]);
                i++;
                j++;
            }
        }
        return ans;
    }

    // Driver code
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the size of arr1 and arr2: ");
        int n1 = sc.nextInt();
        int n2 = sc.nextInt();

        int[] arr1 = new int[n1];
        int[] arr2 = new int[n2];

        System.out.print("Enter the elements arr1: ");
        for (int i = 0; i < n1; i++) {
            arr1[i] = sc.nextInt();
        }

        System.out.print("Enter the elements arr2: ");
        for (int i = 0; i < n2; i++) {
            arr2[i] = sc.nextInt();
        }

        List<Integer> intersection = intersectionArray(arr1, arr2);

        for (int x : intersection) {
            System.out.print(x + " ");
        }

        sc.close();
    }
}
