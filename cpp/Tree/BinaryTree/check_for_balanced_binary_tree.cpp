#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm> // for max
using namespace std;

/*
Class: TreeNode
Purpose: Node of a binary tree
*/
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
Function: insertion
Purpose: Recursively build a binary tree from user input
Input: -1 means no node
Time Complexity: O(N) - each node created once
Space Complexity: O(H) - recursion stack (H = height)
*/
TreeNode* insertion() {
    int val;
    cout << "Enter data (-1 for no node): ";
    cin >> val;
    if (val == -1) return nullptr;

    TreeNode* node = new TreeNode(val);
    cout << "Enter left child of " << val << ":\n";
    node->left = insertion();
    cout << "Enter right child of " << val << ":\n";
    node->right = insertion();
    return node;
}

/*
Recursive Traversals
Time Complexity: O(N)
Space Complexity: O(H)
*/
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

/*
Level-order Traversal using queue (BFS)
Time Complexity: O(N)
Space Complexity: O(N)
*/
vector<vector<int>> levelorder(TreeNode* root) {
    vector<vector<int>> ans;
    if (!root) return ans;

    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            level.push_back(node->data);
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        ans.push_back(level);
    }
    return ans;
}

/*
Iterative Traversals
Time Complexity: O(N)
Space Complexity: O(H)
*/
vector<int> preorderitr(TreeNode* root) {
    vector<int> pre;
    if (!root) return pre;
    stack<TreeNode*> st;
    st.push(root);

    while (!st.empty()) {
        TreeNode* node = st.top(); st.pop();
        pre.push_back(node->data);
        if (node->right) st.push(node->right);
        if (node->left) st.push(node->left);
    }
    return pre;
}

vector<int> inorderitr(TreeNode* root) {
    vector<int> ino;
    stack<TreeNode*> st;
    TreeNode* node = root;
    while (node || !st.empty()) {
        if (node) {
            st.push(node);
            node = node->left;
        } else {
            node = st.top(); st.pop();
            ino.push_back(node->data);
            node = node->right;
        }
    }
    return ino;
}

vector<int> postorderitr(TreeNode* root) {
    vector<int> post;
    if (!root) return post;

    stack<TreeNode*> st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        TreeNode* node = st1.top(); st1.pop();
        st2.push(node);
        if (node->left) st1.push(node->left);
        if (node->right) st1.push(node->right);
    }
    while (!st2.empty()) {
        post.push_back(st2.top()->data);
        st2.pop();
    }
    return post;
}

/*
Function: maxDepth
Purpose: Compute maximum depth of binary tree
Time Complexity: O(N)
Space Complexity: O(H)
*/
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

/*
Function: isBalancedBrute
Purpose: Brute-force check for balanced tree
Time Complexity: O(N^2) - calls maxDepth for each node
Space Complexity: O(H)
*/
bool isBalancedBrute(TreeNode* root) {
    if (!root) return true;
    int lh = maxDepth(root->left);
    int rh = maxDepth(root->right);
    if (abs(lh - rh) > 1) return false;
    return isBalancedBrute(root->left) && isBalancedBrute(root->right);
}

/*
Optimized O(N) check for balanced tree
Time Complexity: O(N)
Space Complexity: O(H)
Returns -1 if unbalanced, else height of subtree
*/
int checkBalanced(TreeNode* root) {
    if (!root) return 0;

    int lh = checkBalanced(root->left);
    if (lh == -1) return -1;
    int rh = checkBalanced(root->right);
    if (rh == -1) return -1;

    if (abs(lh - rh) > 1) return -1;

    return 1 + max(lh, rh);
}

bool isBalanced(TreeNode* root) {
    return checkBalanced(root) != -1;
}

/*
Main Function
*/
int main() {
    TreeNode* root = insertion();

    cout << "\nRecursive Traversals:\n";
    cout << "Inorder: "; inorder(root); cout << endl;
    cout << "Preorder: "; preorder(root); cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;

    cout << "\nIterative Traversals:\n";
    vector<int> pre = preorderitr(root);
    cout << "Preorder (iterative): "; for (int x : pre) cout << x << " "; cout << endl;

    vector<int> ino = inorderitr(root);
    cout << "Inorder (iterative): "; for (int x : ino) cout << x << " "; cout << endl;

    vector<int> post = postorderitr(root);
    cout << "Postorder (iterative): "; for (int x : post) cout << x << " "; cout << endl;

    cout << "\nLevel Order Traversal:\n";
    vector<vector<int>> levels = levelorder(root);
    for (auto &lvl : levels) {
        for (int x : lvl) cout << x << " ";
        cout << endl;
    }

    cout << "\nMaximum Depth: " << maxDepth(root) << endl;
    cout << "Balanced (Brute): " << (isBalancedBrute(root) ? "Yes" : "No") << endl;
    cout << "Balanced (Optimized): " << (isBalanced(root) ? "Yes" : "No") << endl;

    return 0;
}
