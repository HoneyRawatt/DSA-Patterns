#include<bits/stdc++.h>
using namespace std;

int largestRectangleArea(vector<int>& histo) {
    stack<int> st;
    int maxa = 0;
    int n = histo.size();

    for (int i = 0; i <= n; i++) {
        while (!st.empty() && (i == n || histo[st.top()] >= histo[i])) {
            int height = histo[st.top()];
            st.pop();

            int width;
            if (st.empty()) width = i;
            else width = i - st.top() - 1;

            maxa = max(maxa, height * width);
        }
        st.push(i);
    }
    return maxa;
}

int maximalAreaofSubmatrixofall(vector<vector<int>>& mat, int n, int m) {
    int maxarea = 0;
    vector<int> height(m, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (mat[i][j] == 1)
                height[j]++;
            else
                height[j] = 0;
        }

        int area = largestRectangleArea(height);
        maxarea = max(maxarea, area);
    }
    return maxarea;
}

int main() {
    vector<vector<int>> mat = {
        {1, 0, 1, 1},
        {1, 1, 1, 1},
        {1, 1, 1, 0}
    };

    int n = mat.size();
    int m = mat[0].size();

    cout << maximalAreaofSubmatrixofall(mat, n, m) << endl;
    return 0;
}
