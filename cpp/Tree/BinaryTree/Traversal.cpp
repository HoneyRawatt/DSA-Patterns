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
Function: insertion()
Purpose : Builds the binary tree recursively using user input (-1 = no node)

Time Complexity:
    O(N) — Each node is created exactly once.
Space Complexity:
    O(H) — Recursive stack space (H = height of tree)
*/
TreeNode* insertion() {
    int val;
    cout << "Enter the data (-1 for no node): ";
    cin >> val;
    if (val == -1)
        return nullptr;

    TreeNode* node = new TreeNode(val);
    cout << "Enter the left child of " << val << ": ";
    node->left = insertion();

    cout << "Enter the right child of " << val << ": ";
    node->right = insertion();

    return node;
}

/*
Function: inorder()
Purpose : Recursive Inorder Traversal (Left, Root, Right)

Time Complexity: O(N)
Space Complexity: O(H)
*/
void inorder(TreeNode* root) {
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

/*
Function: preorder()
Purpose : Recursive Preorder Traversal (Root, Left, Right)

Time Complexity: O(N)
Space Complexity: O(H)
*/
void preorder(TreeNode* root) {
    if (root == nullptr)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

/*
Function: postorder()
Purpose : Recursive Postorder Traversal (Left, Right, Root)

Time Complexity: O(N)
Space Complexity: O(H)
*/
void postorder(TreeNode* root) {
    if (root == nullptr)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

/*
Function: levelorder()
Purpose : BFS traversal of all levels using a queue

Time Complexity: O(N)
Space Complexity: O(N)
*/
vector<vector<int>> levelorder(TreeNode* root) {
    vector<vector<int>> ans;
    if (root == nullptr) return ans;

    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        vector<int> level;
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
            level.push_back(node->data);
        }
        ans.push_back(level);
    }
    return ans;
}

/*
Function: preorderitr()
Purpose : Iterative Preorder Traversal using a stack

Time Complexity: O(N)
Space Complexity: O(H) — stack stores nodes (H = height of tree)
*/
vector<int> preorderitr(TreeNode* root) {
    vector<int> preorder;
    if (root == nullptr) return preorder;

    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();
        preorder.push_back(node->data);

        // Push right child first so left is processed first
        if (node->right != nullptr) st.push(node->right);
        if (node->left != nullptr) st.push(node->left);
    }
    return preorder;
}

/*
Function: inorderitr()
Purpose : Iterative Inorder Traversal using a stack

Time Complexity: O(N)
Space Complexity: O(H)
*/
vector<int> inorderitr(TreeNode* root) {
    vector<int> inorder;
    stack<TreeNode*> st;
    TreeNode* node = root;

    while (true) {
        if (node != nullptr) {
            st.push(node);
            node = node->left;
        } else {
            if (st.empty()) break;
            node = st.top();
            st.pop();
            inorder.push_back(node->data);
            node = node->right;
        }
    }
    return inorder;
}

/*
Function: postorderitr()
Purpose : Iterative Postorder Traversal using two stacks

Time Complexity: O(N)
Space Complexity: O(2H) ≈ O(H)
*/
vector<int> postorderitr(TreeNode* root) {
    vector<int> postorder;
    if (root == nullptr) return postorder;

    stack<TreeNode*> st1, st2;
    st1.push(root);

    while (!st1.empty()) {
        TreeNode* node = st1.top();
        st1.pop();
        st2.push(node);

        if (node->left) st1.push(node->left);
        if (node->right) st1.push(node->right);
    }

    while (!st2.empty()) {
        postorder.push_back(st2.top()->data);
        st2.pop();
    }
    return postorder;
}
/*
Function: postorderitr_1stack()
Purpose : Iterative Postorder Traversal using only one stack.

Logic:
- Traverse left as much as possible.
- When no left child exists:
    - Check right child of the top node.
    - If no right child → process the node (add to postorder).
    - If right child exists → move to right subtree.
- Use `temp` to track recently visited node so we don't revisit right subtrees.

Time Complexity: O(N)
Space Complexity: O(H)
*/
vector<int> postorderitr_1stack(TreeNode* root) {
    vector<int> post;
    if (root == nullptr) return post;

    stack<TreeNode*> st;
    TreeNode* curr = root;
    TreeNode* temp = nullptr;

    while (curr != nullptr || !st.empty()) {
        if (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        } else {
            temp = st.top()->right;
            if (temp == nullptr) {
                // No right child → process node
                temp = st.top();
                st.pop();
                post.push_back(temp->data);

                // Keep popping while current node is right child of top
                while (!st.empty() && temp == st.top()->right) {
                    temp = st.top();
                    st.pop();
                    post.push_back(temp->data);
                }
            } else {
                // Move to right child
                curr = temp;
            }
        }
    }
    return post;
}


int main() {
    TreeNode* root = nullptr;
    root = insertion();

    cout << "\nRecursive Traversals:" << endl;
    cout << "Inorder: ";
    inorder(root);
    cout << "\nPreorder: ";
    preorder(root);
    cout << "\nPostorder: ";
    postorder(root);

    cout << "\n\nIterative Traversals:" << endl;

    vector<int> pre = preorderitr(root);
    cout << "Preorder (Iterative): ";
    for (int val : pre) cout << val << " ";
    cout << endl;

    vector<int> ino = inorderitr(root);
    cout << "Inorder (Iterative): ";
    for (int val : ino) cout << val << " ";
    cout << endl;

    vector<int> post = postorderitr(root);
    cout << "Postorder (Iterative): ";
    for (int val : post) cout << val << " ";
    cout << endl;

    cout << "\nLevel Order Traversal:\n";
    vector<vector<int>> levels = levelorder(root);
    for (auto& level : levels) {
        for (int val : level)
            cout << val << " ";
        cout << endl;
    }

    cout << endl;
    return 0;
}
