#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int data) {
        this->data = data;
        left = nullptr;
        right = nullptr;
    }
};

/*
Function: Pre_In_Post()
Purpose : Generate Preorder, Inorder, and Postorder traversals in a single pass.

Logic:
- Use a stack of pairs (node, state)
  where state = 1 → Preorder,
        state = 2 → Inorder,
        state = 3 → Postorder.
- For each node:
    - When first encountered (state 1): add to Preorder, push back with state=2, then push its left.
    - When encountered second time (state 2): add to Inorder, push back with state=3, then push its right.
    - When encountered third time (state 3): add to Postorder.

Time Complexity: O(N) — Each node is processed exactly 3 times.
Space Complexity: O(H) — Stack stores up to height of tree nodes.
*/
void Pre_In_Post(TreeNode* root) {
    if (root == nullptr) return;

    stack<pair<TreeNode*, int>> st;
    st.push({root, 1});
    vector<int> pre, in, post;

    while (!st.empty()) {
        auto it = st.top();
        st.pop();

        // state 1 -> preorder
        if (it.second == 1) {
            pre.push_back(it.first->data);
            it.second++;
            st.push(it);
            if (it.first->left)
                st.push({it.first->left, 1});
        }
        // state 2 -> inorder
        else if (it.second == 2) {
            in.push_back(it.first->data);
            it.second++;
            st.push(it);
            if (it.first->right)
                st.push({it.first->right, 1});
        }
        // state 3 -> postorder
        else {
            post.push_back(it.first->data);
        }
    }

    // Print all traversals
    cout << "\nPreorder: ";
    for (int x : pre) cout << x << " ";

    cout << "\nInorder: ";
    for (int x : in) cout << x << " ";

    cout << "\nPostorder: ";
    for (int x : post) cout << x << " ";
    cout << endl;
}

int main() {
    // Simple example tree:
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Pre_In_Post(root);

    return 0;
}
