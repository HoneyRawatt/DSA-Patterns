package ArrayQ;

import java.util.*;

// | Method       | Time              | Space                     |
// | ------------ | ----------------- | ------------------------- |
// | Using Set    | O((n+m) log(n+m)) | O(n+m)                    |
// | Two pointers | O(n+m)            | O(1) (excluding output) ✅ |

public class UnionSortedArr {

    // Method 1: Using Set
    public static int[] unionArray1(int[] a, int[] b) {
        Set<Integer> set = new TreeSet<>();

        for (int x : a) set.add(x);
        for (int x : b) set.add(x);

        int[] unionArr = new int[set.size()];
        int i = 0;
        for (int x : set) {
            unionArr[i++] = x;
        }
        return unionArr;
    }

    // Method 2: Optimal two-pointer approach (arrays must be sorted)
    public static int[] unionArray(int[] arr1, int[] arr2) {
        ArrayList<Integer> unionArr = new ArrayList<>();

        int n1 = arr1.length, n2 = arr2.length;
        int i = 0, j = 0;

        while (i < n1 && j < n2) {
            if (arr1[i] <= arr2[j]) {
                if (unionArr.size() == 0 || unionArr.get(unionArr.size() - 1) != arr1[i]) {
                    unionArr.add(arr1[i]);
                }
                i++;
            } else {
                if (unionArr.size() == 0 || unionArr.get(unionArr.size() - 1) != arr2[j]) {
                    unionArr.add(arr2[j]);
                }
                j++;
            }
        }

        while (i < n1) {
            if (unionArr.size() == 0 || unionArr.get(unionArr.size() - 1) != arr1[i]) {
                unionArr.add(arr1[i]);
            }
            i++;
        }

        while (j < n2) {
            if (unionArr.size() == 0 || unionArr.get(unionArr.size() - 1) != arr2[j]) {
                unionArr.add(arr2[j]);
            }
            j++;
        }

        // Convert ArrayList to array
        int[] result = new int[unionArr.size()];
        for (int k = 0; k < unionArr.size(); k++) {
            result[k] = unionArr.get(k);
        }

        return result;
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

        int[] unionArr = unionArray(arr1, arr2);

        for (int x : unionArr) {
            System.out.print(x + " ");
        }

        sc.close();
    }
}
