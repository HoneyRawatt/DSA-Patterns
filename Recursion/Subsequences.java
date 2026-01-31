package Recursion;
import java.util.ArrayList;

public class Subsequences{

    /*
    ====================================================
    INTUITION:
    ----------------------------------------------------
    - For each element, we have two choices:
        1) Pick the element
        2) Do NOT pick the element
    - We explore both choices using recursion.
    - When we reach index == n, one subsequence is formed.
    - This is a classic "Pick / Not Pick" recursion pattern.
    ====================================================
    */

    static void subseq(int ind, ArrayList<Integer> ds, int[] arr, int n) {

        // Base case: reached end of array
        if (ind == n) {
            if (ds.size() == 0) {
                System.out.print("{}");
            } else {
                for (int x : ds) {
                    System.out.print(x + " ");
                }
            }
            System.out.println();
            return;
        }

        // PICK the current element
        ds.add(arr[ind]);
        subseq(ind + 1, ds, arr, n);

        // BACKTRACK (remove last picked element)
        ds.remove(ds.size() - 1);

        // NOT PICK the current element
        subseq(ind + 1, ds, arr, n);
    }

    public static void main(String[] args) {
        int n = 4;
        int[] arr = {5, 3, 4, 1};
        ArrayList<Integer> ds = new ArrayList<>();

        subseq(0, ds, arr, n);
    }
}
