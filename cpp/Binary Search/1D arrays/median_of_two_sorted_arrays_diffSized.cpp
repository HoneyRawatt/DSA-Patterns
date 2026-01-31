#include <vector>
#include <climits>
#include <iostream>
using namespace std;

/*
    Approach 1: Brute-force
    ------------------------
    - Merge both arrays into one sorted array.
    - Return the middle element(s) as the median.
    
    Time Complexity: O(n1 + n2)
    Space Complexity: O(n1 + n2)
*/
double median_brute(vector<int>& a, vector<int>& b) {
    int n1 = a.size(), n2 = b.size();
    vector<int> c; 
    int i = 0, j = 0;

    // Merge both arrays
    while (i < n1 && j < n2) {
        if (a[i] < b[j]) c.push_back(a[i++]);
        else c.push_back(b[j++]);
    }

    // Copy remaining elements
    while (i < n1) c.push_back(a[i++]);
    while (j < n2) c.push_back(b[j++]);

    int n = n1 + n2;

    // Return median
    if (n % 2 == 1)
        return c[n / 2];
    return (double)(c[n / 2] + c[n / 2 - 1]) / 2.0; 
}


/*
    Approach 2: Better merge (No extra space)
    ------------------------------------------
    - Simulate merge until median position.
    - Keep track of the two middle values if total is even.

    Time Complexity: O(n1 + n2)
    Space Complexity: O(1)
*/
double median_better(vector<int>& a, vector<int>& b) {
    int n1 = a.size(), n2 = b.size();
    int i = 0, j = 0;
    int total = n1 + n2;
    int mid2 = total / 2;
    int mid1 = mid2 - 1;
    int count = 0;
    int val1 = -1, val2 = -1;

    // Merge up to the median indices
    while (i < n1 && j < n2) {
        int val = (a[i] < b[j]) ? a[i++] : b[j++];
        if (count == mid1) val1 = val;
        if (count == mid2) val2 = val;
        count++;
    }

    while (i < n1) {
        int val = a[i++];
        if (count == mid1) val1 = val;
        if (count == mid2) val2 = val;
        count++;
    }

    while (j < n2) {
        int val = b[j++];
        if (count == mid1) val1 = val;
        if (count == mid2) val2 = val;
        count++;
    }

    if (total % 2 == 1)
        return val2; // For odd, mid2 is the middle element
    return (double)(val1 + val2) / 2.0;
}


/*
    Approach 3: Binary Search (Optimal)
    -----------------------------------
    - Binary search on the smaller array to partition both arrays such that:
        max(left1, left2) <= min(right1, right2)
    - This gives the correct partition for median computation.

    Time Complexity: O(log(min(n1, n2)))
    Space Complexity: O(1)
*/
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int n1 = nums1.size();
    int n2 = nums2.size();

    // Ensure binary search is on the smaller array
    if (n1 > n2) return findMedianSortedArrays(nums2, nums1);

    int low = 0, high = n1;
    int total = n1 + n2;
    int leftPartitionSize = (total + 1) / 2;

    while (low <= high) {
        int cut1 = (low + high) / 2;
        int cut2 = leftPartitionSize - cut1;

        // Edge values or actual elements
        int l1 = (cut1 == 0) ? INT_MIN : nums1[cut1 - 1];
        int l2 = (cut2 == 0) ? INT_MIN : nums2[cut2 - 1];
        int r1 = (cut1 == n1) ? INT_MAX : nums1[cut1];
        int r2 = (cut2 == n2) ? INT_MAX : nums2[cut2];

        // Valid partition condition
        if (l1 <= r2 && l2 <= r1) {
            if (total % 2 == 0)
                return (max(l1, l2) + min(r1, r2)) / 2.0;
            else
                return max(l1, l2);
        }
        // Too far on right in nums1
        else if (l1 > r2) {
            high = cut1 - 1;
        }
        // Too far on left in nums1
        else {
            low = cut1 + 1;
        }
    }

    return 0.0; // Should never reach here
}


/*
    Main function to test all 3 approaches
*/
int main() {
    vector<int> nums1 = {1, 3};
    vector<int> nums2 = {2,4,7};

    cout << fixed;
    cout.precision(5);

    cout << "Brute Force Median:        " << median_brute(nums1, nums2) << endl;
    cout << "Better Merge Median:       " << median_better(nums1, nums2) << endl;
    cout << "Binary Search Median:      " << findMedianSortedArrays(nums1, nums2) << endl;

    return 0;
}
