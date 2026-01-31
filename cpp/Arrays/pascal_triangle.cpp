#include <iostream>
#include <vector>
using namespace std;

// Generate a specific row using combinations (nCr)
vector<int> generateRow(int row) {
    long long ans = 1;
    vector<int> ansrow;
    ansrow.push_back(1); // First element is always 1

    for (int col = 1; col < row; col++) {
        ans = ans * (row - col);
        ans = ans / col;
        ansrow.push_back(ans);
    }
    return ansrow;
}
// Optimized Pascal's Triangle: row indexing from 1 to n (inclusive)
vector<vector<int>> pascal_triangle_optimized(int n) {
    vector<vector<int>> ans;
    for (int i = 1; i <= n; i++) {
        ans.push_back(generateRow(i));
    }
    return ans;
}

// Find a single element at position (n, r) using nCr
long long find_element_pascal_tri(int n, int r) {
    long long res = 1;
    for (int i = 1; i <= r; i++) {
        res *= (n - i + 1);
        res /= i;
    }
    return res;
}

// Brute-force Pascal's Triangle using nCr
vector<vector<int>> pascal_triangle_brute(int n) {
    vector<vector<int>> ans;
    for (int row = 0; row < n; row++) {  
        vector<int> templist;
        for (int col = 0; col <= row; col++) {  
            templist.push_back(find_element_pascal_tri(row, col));
        }
        ans.push_back(templist);
    }
    return ans;
}

// Utility function to print the triangle
void print_triangle(const vector<vector<int>>& triangle) {
    for (auto row : triangle) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
}

// Main Function
int main() {
    int n = 5;

    cout << "Pascal Triangle (Optimized):\n";
    vector<vector<int>> opt = pascal_triangle_optimized(n);
    print_triangle(opt);

    cout << "\nPascal Triangle (Brute Force):\n";
    vector<vector<int>> brute = pascal_triangle_brute(n);
    print_triangle(brute);

    return 0;
}
