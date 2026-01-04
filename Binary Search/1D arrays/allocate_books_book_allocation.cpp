#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric> // For accumulate
using namespace std;

    /*
     * 🧠 INTUITION (Helper Function):
     * --------------------------------
     * Given a maximum allowed pages limit (`pages`),
     * we count how many students are required if:
     * - Each student gets contiguous books.
     * - No student gets more than `pages`.
     *
     * If pages exceed limit, assign next book to a new student.
     *
     * Time Complexity: O(N)
     * Space Complexity: O(1)
     */
int countStudent(vector<int> arr, int pages) {
    int students = 1;
    long long pagesStudent = 0;

    for (int i = 0; i < arr.size(); i++) {
        if (pagesStudent + arr[i] <= pages) {
            pagesStudent += arr[i];
        } else {
            students++;
            pagesStudent = arr[i];
        }
    }

    return students;
}


    /*
     * 🐢 BRUTE FORCE APPROACH
     * ------------------------
     * - Try every possible maximum pages value
     *   from max(book pages) to sum(book pages).
     * - For each value, check how many students are needed.
     * - First valid value is the answer.
     *
     * Time Complexity:
     *   O((sum - max) * N) → Very slow
     *
     * Space Complexity: O(1)
     */
int findPagesBrute(vector<int>& arr, int m, int n) {
    if (m > n) return -1;

    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);

    for (int pages = low; pages <= high; pages++) {
        if (countStudent(arr, pages) <= m) {
            return pages;
        }
    }

    return -1;  // Shouldn't reach here
}


    /*
     * 🚀 OPTIMIZED APPROACH (Binary Search on Answer)
     * -----------------------------------------------
     * 🧠 INTUITION:
     * - We are minimizing the maximum pages assigned to any student.
     * - If we can allocate books with max pages = X,
     *   then we can also allocate with any value > X.
     * - If we cannot allocate with X,
     *   then any value < X will also fail.
     *
     * Search Space:
     * - Minimum = max(book pages)
     * - Maximum = sum(book pages)
     *
     * Time Complexity:
     *   Sorting not required
     *   Binary Search → O(log(sum - max))
     *   Count check → O(N)
     *   Overall → O(N log(sum))
     *
     * Space Complexity: O(1)
     */
int findPages(vector<int>& arr, int m, int n) {
    if (m > n) return -1;  // Can't assign if students > books

    int low = *max_element(arr.begin(), arr.end());           // At least one book per student
    int high = accumulate(arr.begin(), arr.end(), 0);         // At most all books to one student

    while (low <= high) {
        int mid = low + ((high - low) / 2);
        int students = countStudent(arr, mid);
 
        if (students > m) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;  // Minimum number of max pages
}

int main() {
    vector<int> books = {12, 34, 67, 90};  // Pages in each book
    int students = 2;                      // Number of students
    int n = books.size();

    int result = findPages(books, students, n);
    if (result != -1)
        cout << "Minimum pages: " << result << endl;
    else
        cout << "Assignment not possible!" << endl;
    
    findPagesBrute(books, students, n);
    if (result != -1)
        cout << "Minimum pages (brute): " << result << endl;
    else
        cout << "Assignment not possible!" << endl;

    return 0;
}
