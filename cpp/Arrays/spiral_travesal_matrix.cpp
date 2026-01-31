#include <iostream>
#include <vector>
using namespace std;

vector<int> spiral_matrix(vector<vector<int>>& mat) {
    int n = mat.size();
    int m = mat[0].size();
    int left = 0, right = m - 1;
    int top = 0, bottom = n - 1;
    vector<int> ans;

    while (top <= bottom && left <= right) {
        // Traverse top row
        for (int i = left; i <= right; i++)
            ans.push_back(mat[top][i]);
        top++;

        // Traverse right column
        for (int i = top; i <= bottom; i++)
            ans.push_back(mat[i][right]);
        right--;

        // Traverse bottom row (if still valid)
        if (top <= bottom) {
            for (int i = right; i >= left; i--)
                ans.push_back(mat[bottom][i]);
            bottom--;
        }

        // Traverse left column (if still valid)
        if (left <= right) {
            for (int i = bottom; i >= top; i--)
                ans.push_back(mat[i][left]);
            left++;
        }
    }
    return ans;
}

int main() {
    vector<vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<int> res = spiral_matrix(mat);
    for (int val : res)
        cout << val << " ";
    cout << endl;

    return 0;
}
