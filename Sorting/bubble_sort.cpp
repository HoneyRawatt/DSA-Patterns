#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

    /*
     * Worst Case Time Complexity: O(n^2)
     * ---------------------------------
     * Occurs when the array is in reverse order.
     * For each pass, we compare adjacent elements across the array.
     *
     * Best Case Time Complexity: O(n)
     * -------------------------------
     * Occurs when the array is already sorted.
     * Due to the didSwap flag, the algorithm stops after the first pass.
     *
     * Average Case Time Complexity: O(n^2)
     *
     * Space Complexity: O(1)
     * ----------------------
     * In-place sorting.
     * Only a few variables are used (i, j, didSwap).
     */

void bubble_sort(vector<int>&arr){
    for(int i=arr.size()-1;i>=0;i--){
        int didswap=0;
        for(int j=0;j<=i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                didswap=1;
            } 
        }
        if(didswap==0) break;
    }
}

int main() {
    vector<int> arr = {64, 25, 12, 22, 11};
    bubble_sort(arr);
    cout << "Sorted array: ";
    for(int num : arr) {
        cout << num << " ";
    }

    return 0;
}
