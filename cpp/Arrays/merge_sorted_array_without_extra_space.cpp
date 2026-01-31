#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

/*
 * Brute-force Merge (Extra Array)
 * Time: O(n + m)
 * Space: O(n + m)
 */
void merge_brute(long long arr1[], long long arr2[], int n, int m) {
    long long arr3[n + m];
    int left = 0;
    int right = 0;
    int indx = 0;

    while (left < n && right < m) {
        if (arr1[left] < arr2[right]) {
            arr3[indx++] = arr1[left++];
        } else {
            arr3[indx++] = arr2[right++];
        }
    }
    while (left < n) arr3[indx++] = arr1[left++];
    while (right < m) arr3[indx++] = arr2[right++];

    for (int i = 0; i < n + m; i++) {
        if (i < n) arr1[i] = arr3[i];
        else arr2[i - n] = arr3[i];
    }
}

/*
 * Optimal Merge 1 (Swap end of arr1 with start of arr2 and sort both)
 * Time: O(n log n + m log m)
 * Space: O(1)
 */
void merge_optimal1(long long arr1[], long long arr2[], int n, int m) {
    int left = n - 1;
    int right = 0;
    while (left >= 0 && right < m) {
        if (arr1[left] > arr2[right]) {
            swap(arr1[left], arr2[right]);
            left--;
            right++;
        } else {
            break;
        }
    }
    sort(arr1, arr1 + n);
    sort(arr2, arr2 + m);
}

/*
 * Swap helper (Only swap if arr1[ind1] > arr2[ind2])
 */
void swapGreater(long long arr1[], long long arr2[], int ind1, int ind2) {
    if (arr1[ind1] > arr2[ind2]) {
        swap(arr1[ind1], arr2[ind2]);
    }
}

/*
 * Optimal Merge 2 (GAP Method / Shell Sort)
 * Time: O((n + m) * log(n + m))
 * Space: O(1)
 */
void merge_optimal2(long long arr1[], long long arr2[], int n, int m) {
    int len = n + m;
    int gap = ceil(len / 2.0);

    while (gap > 0) {
        int left = 0;
        int right = left + gap;

        while (right < len) {
            // Case 1: both in arr1
            if (left < n && right < n) {
                swapGreater(arr1, arr1, left, right);
            }
            // Case 2: left in arr1, right in arr2
            else if (left < n && right >= n) {
                swapGreater(arr1, arr2, left, right - n);
            }
            // Case 3: both in arr2
            else {
                swapGreater(arr2, arr2, left - n, right - n);
            }

            left++;
            right++;
        }

        if (gap == 1) break;
        gap = ceil(gap / 2.0);
    }
}


void print_array(long long arr[], int size) {
    for (int i = 0; i < size; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    long long arr1[] = {1, 4, 7, 8, 10};
    long long arr2[] = {2, 3, 9};
    int n = 5, m = 3;

    // Uncomment any one to test
    // merge_brute(arr1, arr2, n, m);
    // merge_optimal1(arr1, arr2, n, m);
    merge_optimal2(arr1, arr2, n, m);

    cout << "Merged Array 1: ";
    print_array(arr1, n);

    cout << "Merged Array 2: ";
    print_array(arr2, m);

    return 0;
}

