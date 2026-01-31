#include <bits/stdc++.h>
using namespace std;

// Function to return the kth permutation of numbers 1 to n
string getpermutation(int n, int k) {
    int fact = 1;
    vector<int> numbers;

    // Step 1: Build factorial (n-1)! and fill numbers from 1 to n
    for (int i = 1; i < n; i++) {
        fact *= i;
        numbers.push_back(i);  // stores: 1, 2, 3
    }
    numbers.push_back(n); // now numbers = [1, 2, 3, 4]

    string ans = "";
    k = k - 1; // Decrement k to convert it to 0-based index

    // Step 2: Build the answer string by choosing digits one by one
    while (!numbers.empty()) {
        int index = k / fact;
        ans += to_string(numbers[index]);
        numbers.erase(numbers.begin() + index);

        if (numbers.empty()) break;

        k = k % fact;
        fact = fact / numbers.size();
    }

    return ans;
}

int main() {
    int n = 4, k = 17;

    // Call the function
    string result = getpermutation(n, k);
    cout << "The " << k << "th permutation of numbers from 1 to " << n << " is: " << result << endl;

    return 0;
}

/*
============================
TIME & SPACE COMPLEXITY
============================

Time Complexity:
- We perform n iterations.
- Removing an element from ArrayList costs O(n).
- Overall Time Complexity: O(n^2)

Space Complexity:
- List to store numbers: O(n)
- StringBuilder: O(n)
- Overall Space Complexity: O(n)
*/