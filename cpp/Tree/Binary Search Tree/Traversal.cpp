#include <iostream>
using namespace std;

/*
Class: TreeNode
Purpose: Represents a node in a binary search tree (BST)
*/
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        this->val = val;
        left = nullptr;
        right = nullptr;
    }
};

/*
Function: insert
Purpose: Inserts a new value into the BST and returns the root.
*/
TreeNode* insert(TreeNode* root, int val) {
    if (root == nullptr)
        return new TreeNode(val);

    TreeNode* curr = root;
    while (true) {
        if (val > curr->val) {
            if (curr->right != nullptr)
                curr = curr->right;
            else {
                curr->right = new TreeNode(val);
                break;
            }
        } else {
            if (curr->left != nullptr)
                curr = curr->left;
            else {
                curr->left = new TreeNode(val);
                break;
            }
        }
    }
    return root;
}

/*
Helper: Finds the rightmost node in a subtree.
*/
TreeNode* findLastRight(TreeNode* root) {
    if (root->right == nullptr)
        return root;
    return findLastRight(root->right);
}

/*
Helper: Deletes a node (used in iterative version)
*/
TreeNode* helper(TreeNode* root) {
    if (root->left == nullptr)
        return root->right;
    else if (root->right == nullptr)
        return root->left;

    // Both children exist
    TreeNode* rightChild = root->right;
    TreeNode* lastRight = findLastRight(root->left);
    lastRight->right = rightChild;
    return root->left;
}

/*
Helper: Finds smallest node in a subtree (used in recursive version)
*/
TreeNode* findMin(TreeNode* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

/*
Version 1: Iterative deleteNode (O(1) extra space)
*/
TreeNode* deleteNodeIterative(TreeNode* root, int key) {
    if (root == nullptr)
        return nullptr;

    if (root->val == key)
        return helper(root);

    TreeNode* curr = root;
    while (curr != nullptr) {
        if (key < curr->val) {
            if (curr->left != nullptr && curr->left->val == key) {
                curr->left = helper(curr->left);
                break;
            } else
                curr = curr->left;
        } else {
            if (curr->right != nullptr && curr->right->val == key) {
                curr->right = helper(curr->right);
                break;
            } else
                curr = curr->right;
        }
    }
    return root;
}

/*
Version 2: Recursive deleteNode (simpler, but uses O(h) space)
*/
TreeNode* deleteNodeRecursive(TreeNode* root, int key) {
    if (root == nullptr)
        return nullptr;

    if (key < root->val)
        root->left = deleteNodeRecursive(root->left, key);
    else if (key > root->val)
        root->right = deleteNodeRecursive(root->right, key);
    else {
        // Node found
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        // Node has two children
        TreeNode* successor = findMin(root->right);
        root->val = successor->val;
        root->right = deleteNodeRecursive(root->right, successor->val);
    }

    return root;
}

/*
Helper: inorder traversal to verify BST structure
*/
void inorder(TreeNode* root) {
    if (!root)
        return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

/*
Main function for testing
*/
int main() {
    TreeNode* root = nullptr;

    // Insert nodes
    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 10);
    root = insert(root, 1);
    root = insert(root, 6);
    root = insert(root, 14);
    root = insert(root, 4);
    root = insert(root, 7);
    root = insert(root, 13);

    cout << "Inorder before deletion: ";
    inorder(root);
    cout << endl;

    int key = 6;

    // You can choose which version to test:
    // root = deleteNodeIterative(root, key);
    root = deleteNodeRecursive(root, key);

    cout << "Inorder after deleting " << key << ": ";
    inorder(root);
    cout << endl;

    return 0;
}

/*
Complexity:
Operation       Time        Space
Insert          O(h)        O(1)
Search          O(h)        O(1)
Delete          O(h)        O(h) (recursive) or O(1) (iterative)

For balanced BST: h = log n
For skewed BST:   h = n
*/
