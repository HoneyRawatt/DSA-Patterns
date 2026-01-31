#include <iostream> 
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

/*
===============================================================================
Problem Statement:
-------------------------------------------------------------------------------
Design a mechanism to serialize and deserialize a binary tree.

Serialization:
- Convert a binary tree into a string representation so it can be stored or
  transmitted.
- Null nodes must also be represented to preserve tree structure.

Deserialization:
- Reconstruct the original binary tree from the serialized string.

Constraints / Notes:
- Node values are integers.
- Tree structure must remain unchanged after deserialization.
- The serialized format should allow unambiguous reconstruction.

Approach Used:
- Level Order Traversal (Breadth-First Search)
- Use '#' to represent NULL nodes
===============================================================================
*/

/*
Class: TreeNode
Purpose:
- Represents a single node in a binary tree.
- Each node stores an integer value and pointers to left & right children.
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
===============================================================================
Function: serialize
-------------------------------------------------------------------------------
Purpose:
- Converts a binary tree into a string using level-order traversal (BFS).

Intuition:
- Traverse the tree level by level.
- Append node values to the string.
- Use "#" to represent NULL children.
- Commas are used as separators.

Why Level Order?
- Ensures structure (including missing children) is preserved.

Input:
- root : pointer to the root of the binary tree

Output:
- A serialized string representation of the tree
===============================================================================
*/
string serialize(TreeNode* root) {
    if (!root) return "#,";  // Empty tree case

    string s = "";
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* curr = q.front();
        q.pop();

        if (curr == nullptr) {
            s.append("#,");   // Marker for NULL node
        } else {
            s.append(to_string(curr->val) + ",");
            q.push(curr->left);
            q.push(curr->right);
        }
    }
    return s;
}

/*
===============================================================================
Function: deserialize
-------------------------------------------------------------------------------
Purpose:
- Reconstructs the binary tree from the serialized string.

Intuition:
- Read values one by one using stringstream.
- Rebuild the tree using level-order traversal.
- Use queue to assign left and right children correctly.

Input:
- data : serialized string of the tree

Output:
- Pointer to the root of the reconstructed binary tree
===============================================================================
*/
TreeNode* deserialize(string data) {
    if (data.size() == 0) return nullptr;

    stringstream s(data);
    string str;

    // Read root value
    getline(s, str, ',');
    if (str == "#") return nullptr;

    TreeNode* root = new TreeNode(stoi(str));
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        // Process left child
        if (!getline(s, str, ',')) break;
        if (str == "#") {
            node->left = nullptr;
        } else {
            TreeNode* leftNode = new TreeNode(stoi(str));
            node->left = leftNode;
            q.push(leftNode);
        }

        // Process right child
        if (!getline(s, str, ',')) break;
        if (str == "#") {
            node->right = nullptr;
        } else {
            TreeNode* rightNode = new TreeNode(stoi(str));
            node->right = rightNode;
            q.push(rightNode);
        }
    }
    return root;
}

/*
Helper Function: inorder
Purpose:
- Prints inorder traversal of the tree.
- Used to verify correctness after deserialization.
*/
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

/*
===============================================================================
Main Function:
-------------------------------------------------------------------------------
1. Creates a sample binary tree.
2. Serializes the tree.
3. Deserializes the string back into a tree.
4. Prints inorder traversal to verify correctness.
===============================================================================
*/
int main() {
    /*
              1
             / \
            2   3
               / \
              4   5
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    // Serialize the tree
    string data = serialize(root);
    cout << "Serialized Tree: " << data << endl;

    // Deserialize the tree
    TreeNode* newRoot = deserialize(data);
    cout << "Inorder of Deserialized Tree: ";
    inorder(newRoot);
    cout << endl;

    return 0;
}

/*
===============================================================================
Time & Space Complexity Analysis:
-------------------------------------------------------------------------------
Time Complexity: O(N)
- Serialization visits every node once → O(N)
- Deserialization also processes every node once → O(N)

Space Complexity: O(N)
- Queue can store up to N nodes (worst case)
- Serialized string size is proportional to N
- Overall auxiliary space is linear

Where:
- N = number of nodes in the binary tree
===============================================================================
*/
