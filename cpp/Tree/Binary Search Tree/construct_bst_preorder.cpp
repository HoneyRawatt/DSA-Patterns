#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) {
        this->val = val;
        left = right = nullptr;
    }
};

// Helper to insert a node in BST
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);
    if (val < root->val)
        root->left = insertBST(root->left, val);
    else
        root->right = insertBST(root->right, val);
    return root;
}

// Brute Force: Build BST from preorder by inserting nodes one by one
TreeNode* bstFromPreorder_Brute(vector<int>& preorder) {
    TreeNode* root = nullptr;
    for (int val : preorder) {
        root = insertBST(root, val);
    }
    return root;
}

/*
Approach: 
- Take each preorder element.
- Insert it into BST at its correct position.

Time Complexity: O(N²)
Space Complexity: O(N) for recursion stack
*/

#include <unordered_map>

TreeNode* buildTree(vector<int>& preorder, int preStart, int preEnd,
                    vector<int>& inorder, int inStart, int inEnd,
                    unordered_map<int, int>& inMap) {
    if (preStart > preEnd || inStart > inEnd) return nullptr;

    TreeNode* root = new TreeNode(preorder[preStart]);
    int inRoot = inMap[root->val];
    int numsLeft = inRoot - inStart;

    root->left = buildTree(preorder, preStart + 1, preStart + numsLeft,
                           inorder, inStart, inRoot - 1, inMap);
    root->right = buildTree(preorder, preStart + numsLeft + 1, preEnd,
                            inorder, inRoot + 1, inEnd, inMap);

    return root;
}

// Better approach: Sort preorder to get inorder and build tree
TreeNode* bstFromPreorder_Better(vector<int>& preorder) {
    vector<int> inorder = preorder;
    sort(inorder.begin(), inorder.end());

    unordered_map<int, int> inMap;
    for (int i = 0; i < inorder.size(); i++)
        inMap[inorder[i]] = i;

    return buildTree(preorder, 0, preorder.size() - 1,
                     inorder, 0, inorder.size() - 1, inMap);
}

/*
Approach:
- Sort preorder → gives inorder.
- Build BST using preorder + inorder construction.
Time Complexity: O(N log N)
Space Complexity: O(N)
*/

TreeNode* buildBST(vector<int>& preorder, int& i, int bound) {
    if (i == preorder.size() || preorder[i] > bound) return nullptr;
    TreeNode* root = new TreeNode(preorder[i++]);
    root->left = buildBST(preorder, i, root->val);
    root->right = buildBST(preorder, i, bound);
    return root;
}

TreeNode* bstFromPreorder_Optimal(vector<int>& preorder) {
    int i = 0;
    return buildBST(preorder, i, INT_MAX);
}

/*
Approach:
- Use preorder sequence directly.
- Maintain upper bound for valid node values.
- Each element is processed once.

Time Complexity: O(N)
Space Complexity: O(N) (recursion)
*/


//    🧾 Summary Table
// Approach	Idea	                                   Time	         Space	    Notes
// Brute	Insert each node one by one	               O(N²)	     O(N)  	    Simple, slow
// Better	Sort preorder → use inorder + preorder	O(N log N)	     O(N)	    Uses sorting
// Optimal	Use preorder with bounds	               O(N)	         O(N)	    Most efficient



// ---------- MAIN ----------
int main() {
    vector<int> preorder = {8, 5, 1, 7, 10, 12};

    cout << "Brute Force BST Inorder: ";
    TreeNode* root1 = bstFromPreorder_Brute(preorder);
    printInorder(root1);
    cout << endl;

    cout << "Better Approach BST Inorder: ";
    TreeNode* root2 = bstFromPreorder_Better(preorder);
    printInorder(root2);
    cout << endl;

    cout << "Optimal Approach BST Inorder: ";
    TreeNode* root3 = bstFromPreorder_Optimal(preorder);
    printInorder(root3);
    cout << endl;

    return 0;
}